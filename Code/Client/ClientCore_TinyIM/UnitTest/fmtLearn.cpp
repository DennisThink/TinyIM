#include <iostream>
#define FMT_STRING_ALIAS 1
#include <fmt/format.h>
#include "Log.h"
#include "CommonFunction.h"
namespace MySpace
{
    void Format()
    {
         std::string s = format(fmt("{}"), 42);
         std::cout<<s<<std::endl;
         auto func = [](void)->void{
            std::string s = format(fmt("{}"), 42);
            std::cout<<s<<std::endl;
                     std::string strCfg = R"({"LogDir":"/home/dennis/Log"})";
         std::string strErr;
         auto json = json11::Json::parse(strCfg,strErr);
         auto logger = CreateLogger(json);
         logger->info(format(fmt("{}"),2));
         };
         func();
         std::string strCfg = R"({"LogDir":"/home/dennis/Log"})";
         std::string strErr;
         auto json = json11::Json::parse(strCfg,strErr);
         auto logger = CreateLogger(json);
         logger->info(format(fmt("{}"),2));
         INFO(logger,format(fmt("{}"),2));
    }
}
int main(int argc,char * argv[])
{
    std::string s = format(fmt("{}"), 42);
    MySpace::Format();
    std::cout<<s<<std::endl;
    std::cout<<argc<<argv[0]<<std::endl;
    return 0;
}
