//
// Created by 王耀华 on 16/9/23.
//

#ifdef WIN32
#else
#include "DaemonSvcApp.h"
#include <fstream>
#include "json11.hpp"
DaemonSvcApp theApp;

int DaemonSvcApp::parse_proc_cmdline(pid_t pid, const std::function<void(const char *, int no)> &fn) {
    char buff[0x1000]={0};
    sprintf(buff, "/proc/%d/cmdline", pid);
    FILE *file = fopen(buff, "rb");
    int num = 0;
    set_error(0, nullptr);
    if (file) {
        auto len = fread(buff, 1, sizeof(buff) - 2, file);
        fclose(file);
        if (len > 0) {
            buff[len] = 0;
            buff[len + 1] = 0;
            char *p = buff;
            while (*p) {
                fn(p, num);
                num++;
                p += strlen(p) + 1;
            }
            return 0;
        }
    }
    return set_error(1, "Fail to read cmdline");
}

int DaemonSvcApp::enum_instance_by_tag(const char *tag,
                                     const std::function<void(int pid, const std::string &cmdline)> &callback) {
    set_error(0, nullptr);
    char exepath[0x200]={0};
    if(readlink("/proc/self/exe",exepath,sizeof(exepath)-8)< 0)
        return set_error(1, "Fail, may be unsupported platform.");
    std::string exe=exepath,delexe=exepath;
    delexe +=" (deleted)";

    auto my_pid = getpid();

    struct CloseDir {
        void operator()(DIR *dir) { closedir(dir); }
    };
    auto dir = std::unique_ptr<DIR, CloseDir>(opendir("/proc"));
    if (!dir)
        return set_error(2, "Fail to open /proc");
    char buff[128];
    struct dirent *next;
    while ((next = readdir(dir.get())) != NULL) {
        pid_t dstpid = atoi(next->d_name);
        if (!dstpid || dstpid == my_pid)
            continue;

        sprintf(buff, "/proc/%d/exe", dstpid);
        memset(exepath,0,sizeof(exepath));
        if(readlink(buff, exepath, sizeof(exepath)-8)< 0)
            continue;
        std::string theexe=exepath;
        if(exe!=theexe && delexe!=theexe)
                continue;

        std::string strcmdline;
        bool bMatch = (!tag || !*tag);
        parse_proc_cmdline(dstpid, [tag, &bMatch, &strcmdline](const char *arg, int no) {
            if (no)
                strcmdline += " ";
            strcmdline += arg;
            if (!bMatch)
                bMatch = !strcasecmp(arg, tag);
        });
        if (bMatch)
            callback(dstpid, strcmdline);
    }
    return m_errno;
}

void DaemonSvcApp::list(const std::function<void(pid_t, const std::string&)>& proc) {
    enum_instance_by_tag(m_tag, proc);
}

int DaemonSvcApp::daemon(const std::function<int()> &workproc) {
    //准备环境
    m_ioService.notify_fork(asio::io_service::fork_prepare);
    auto pid = fork();
    if (pid < 0) {  //on fork error
        printf("Fork error, abort!\n");
        exit(0);
    }
    if (pid > 0) {  //fathr
        m_ioService.notify_fork(asio::io_service::fork_parent);
        printf("Switch to backgound...\n");
        exit(0);
    }
    m_ioService.notify_fork(asio::io_service::fork_child);
    umask(0);
    auto sid = setsid();
    if (sid < 0)
        exit(EXIT_FAILURE);
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    auto fd = open("/dev/null", O_RDWR, 0);

    if (fd != -1) {
        dup2(fd, STDIN_FILENO);
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);
        close(fd);
    }

    while (!m_bStopMon) {
        m_ioService.notify_fork(asio::io_service::fork_prepare);
        pid = fork();
        if(!pid){
            m_ioService.notify_fork(asio::io_service::fork_child);
            return workproc();
        }
        if(pid<0){
            m_on_fork_error(1);
        }else{
            m_ioService.notify_fork(asio::io_service::fork_parent);
            int status = 0;
            pid_t child;
            do { child = wait(&status); }while(child<0 || !(WIFEXITED(status) || WIFSIGNALED(status)));
            m_onworker_exit(status);
        }
    }
    return 0;
}
#endif