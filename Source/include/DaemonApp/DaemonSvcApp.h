//
// Created by 王耀华 on 16/9/23.
//

#ifndef DEV_CHK_CDAEMONAPP_H
#define DEV_CHK_CDAEMONAPP_H
#ifdef WIN32
#else
#include <functional>
#include <string>
#include <memory>
#include <iostream>
#ifdef WIN32

#else
#include <dirent.h>
#include <sys/wait.h>
#endif

#include "json11.hpp"
#include "Log.h"
#include "asio_common.h"
//TODO: 支持远程管理代理：
//      工作子进程管理：重启子进程，更新配置，重新加载配置，读取日志，重定位日志
//      如果管理进程被杀，则子进程也终止
class DaemonSvcApp
{
protected:
    std::function<void(int)> m_onworker_exit=[](int status){
        std::cout<<"Statu"<<status<<std::endl;
    };
    std::function<void(int level)> m_on_fork_error=[](int level){
        std::cout<<"Level "<<level<<std::endl;
        sleep(10);
    };
    bool m_bStopMon=false;
    const char* m_tag;
    const char* m_errmsg;
    int m_errno;
    int set_error(int err, const char* msg){m_errno=err;m_errmsg=msg;return err;}

    int parse_proc_cmdline(pid_t pid, const std::function<void(const char*, int no)>& fn);
    int enum_instance_by_tag(const char *tag, const std::function<void(int pid, const std::string& cmdline)> &callback);
public:
    asio::io_service m_ioService;
    std::shared_ptr<spdlog::logger> m_loger;
	std::shared_ptr<spdlog::sinks::daily_file_sink_st> m_DebugSink;
	json11::Json m_configJson;
public:
    DaemonSvcApp(){}

	
    void set_tag(const char* tag){m_tag=tag;}
    void list(const std::function<void(pid_t,const std::string&)>& proc);
    DaemonSvcApp& on_fork_error(const std::function<void(int level)> &fn){m_on_fork_error=fn; return *this; }
    DaemonSvcApp& on_worker_exit(const std::function<void(int)>& fn){m_onworker_exit=fn; return *this; }
    int daemon(const std::function<int()> &workproc);
};

extern DaemonSvcApp theApp;
#endif
#endif //DEV_CHK_CDAEMONAPP_H
