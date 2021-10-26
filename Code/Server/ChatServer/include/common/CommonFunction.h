#ifndef _COMMON_FUNCTION_H_
#define _COMMON_FUNCTION_H_

#ifdef WIN32
#else
#include <dirent.h>
#include <unistd.h>
#endif

#include <functional>
#include <string>
#include <memory>
#include <fstream>
#include <iostream>


#include <string.h>

#include "CommonConfig.h"
#include "Log.h"
#include "json11.hpp"

#ifdef  WIN32
#include <windows.h>
std::string unified_path(const char* path)
{
	char chpath[MAX_PATH];
	GetModuleFileName(NULL, (LPSTR)chpath, sizeof(chpath));
	std::string strPath = std::string(chpath);
	strPath = strPath.substr(0,strPath.rfind("\\")+1);
	return strPath + std::string(path);
}

#else
std::string my_fullpath(){
    //-1表示出错
    char buf[0x400];
    auto len=readlink ("/proc/self/exe", buf, sizeof(buf));
    return {buf,size_t(len<0 ? 0 : len)};
}
std::string unified_path(const char* path)
{
	char buf[0x400] = { 0 };
	realpath(path, buf);
	return buf;
}

#endif



int load_txtfile(const char *file, std::string &content)
{
    std::ifstream is(file, std::ifstream::in);
    if (is) {
        is.seekg (0, is.end);
        std::size_t length = static_cast<std::size_t>(is.tellg());
        is.seekg (0, is.beg);
		std::cout<<length<<std::endl;
		char * pChar = new char[length];
		memset(pChar, 0, length);
        is.read (pChar,length);
		std::cout << pChar << std::endl;
		content = std::string(pChar);
		delete[] pChar;

        if (is)
            return 0;
    }
	else
	{
		std::cout << "fileError" << std::endl;
	}
    return errno;
}

int write_txtfile(const char *file, std::string &content)
{
    std::ofstream os(file, std::ofstream::out);
    if (os) {
        os.write(content.c_str(),content.length());
        os.close();
    }
    return errno;
}


//打印参数选项
void PrintParamOption()
{
    std::cout<<"Too less arg ,You might Use the following argument "<<std::endl;
    std::cout<<"To Start,Stop Program User the CMD "<<std::endl;
    std::cout<<"--------------------"<<std::endl;
    std::cout<<"(ProgramName) -cfg (ConfigFileName) -tag=(TAG) [-start|-stop]"<<std::endl;
    std::cout<<"--------------------"<<std::endl;
	//std::cout<<"-restart : to Restart the Server "<<std::endl;
    std::cout<<"-tag=(TAG)       : Use tag to inditify different program "<<std::endl;
	std::cout<<"-stop            : to Stop the Server "<<std::endl;
	std::cout<<"-start           : to Start the Server "<<std::endl;
	std::cout<<"-cfg (cfgFile)   : to Use the specific Config File"<<std::endl;
    std::cout<<"-genCfg (cfgFile): To Generate the specific Config File"<<std::endl;
	std::cout<<"-v               : to Show the Server Version"<<std::endl;
	std::cout << "                                              " << std::endl;
	std::cout <<" If you have any question about this problem,please connect "<<std::endl; 
	std::cout<<"  Email:  dennismi1024@gmail.com" << std::endl;
	std::cout<<"  blog :  https://www.dennisthink.com/" << std::endl;
}

enum class ServerCmd
{
    CMD_STOP,
    CMD_START,
    CMD_RESTART,
    CMD_INFO,
};
struct ParseParamResult
{
    std::string m_strTag;
    ServerCmd m_cmd;
    std::string m_cfgFile;
    bool m_bReturn;
};

void GenerateCfgFileType(std::string fileName);

using GenerateCfgFileFunc = decltype(GenerateCfgFileType);

ParseParamResult ParseParam(int argc,char * argv[],GenerateCfgFileFunc func)
{
    ParseParamResult result;
    result.m_bReturn = false;
    for(int i=1; i<argc; i++){
        if(!strcmp(argv[i],"-restart"))
        {
            result.m_cmd=ServerCmd::CMD_RESTART;
        }
        else if(!strcmp(argv[i],"-stop"))
        {
            result.m_cmd=ServerCmd::CMD_STOP;
        }
        else if(!strncmp(argv[i],"-tag=",5)){
            result.m_strTag = argv[i];
        }else if(!strcmp(argv[i],"-cfg")) {
            if(i < (argc - 1))
            {
                result.m_cfgFile = unified_path(argv[++i]);
            }   
        }else if(!strcmp(argv[i],"-genCfg")) {
            std::cout<<"Run Here"<<std::endl;
            if (i <= (argc - 1))
            {    
                std::cout<<"Run Here"<<argv[i]<<argv[i+1]<<std::endl;
                func(argv[++i]);
                result.m_bReturn = true;
            }
        } else if(!strcmp(argv[i],"-info")){
            result.m_cmd=ServerCmd::CMD_INFO;
        } else if(!strcmp(argv[i],"-v")){
            std::cout<<g_SERVER_VERSION<<std::endl;
	        std::cout<<"Debug: "<<DEBUG<<std::endl;
            result.m_bReturn = true;	
		} else if(!strcmp(argv[i],"-start"))
		{
			result.m_cmd = ServerCmd::CMD_START;
		}
		else
		{
			std::cout<<"unknown command"<<std::endl;
			result.m_bReturn = true;
		}
    }
    return result;
}

std::shared_ptr<spdlog::logger> CreateLogger(json11::Json& cfg)
{
    std::vector<spdlog::sink_ptr> sinks;
	auto logDir=cfg["LogDir"].string_value();

	if(std::string(logDir).length() <= 0)
	{
		printf("Please Config your [LogDir] in Config File \n");
		return nullptr;
	}
	else
	{
		printf("LogDir %s \n",logDir.c_str());
	}
    int debugOn = cfg["debugon"].int_value();


    //调试日志
	std::string strDebug=logDir+"Debug";
	std::string strBusin=logDir+"Busin";
    auto debugFile =std::make_shared<spdlog::sinks::daily_file_sink_st>(strDebug+"txt",00,00,true);

    debugFile->set_level(spdlog::level::trace);
    //业务日志
    auto businFile =std::make_shared<spdlog::sinks::daily_file_sink_st>(strBusin+"txt",00,00,true);
    if(1 == debugOn)
    {
        businFile->set_level(spdlog::level::debug);
    }
    else
    {
        businFile->set_level(spdlog::level::info);
    }
    


    sinks.push_back(debugFile);
    sinks.push_back(businFile);

	auto combined_logger = std::make_shared<spdlog::logger>("T",begin(sinks),end(sinks));
	//spdlog::register_logger(combined_logger);
    return combined_logger;
}
#endif