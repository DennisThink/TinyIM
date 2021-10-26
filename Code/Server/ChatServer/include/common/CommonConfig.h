#ifndef _COMMON_CONFIG_H_
#define _COMMON_CONFIG_H_
#include <string>

#ifdef WIN32
static std::string g_SERVER_VERSION = "v0.0.1 " + std::string(__DATE__) + " " + std::string(__TIME__) + " " + std::to_string(_MSC_VER);
#else
static std::string g_SERVER_VERSION = "v0.0.1 "+ std::string(__DATE__)+" "+std::string(__TIME__)+" "+std::string(__VERSION__);
#endif

#define DEBUG 0
#endif
