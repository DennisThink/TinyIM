cmake_minimum_required(VERSION 3.0)
project(MediumServer)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
include_directories(../../../msgStruct/)
include_directories(../../../msgStruct/json11/)
include_directories(../../../include/thirdparty/mysql/include/)
include_directories(../../../include/thirdparty/SnowFlake/)

include_directories(../include/common/)
include_directories(../include/DaemonApp/)
include_directories(../../include/thirdparty/mysql/include/)
include_directories(../include/mysql/)


link_directories(../include/thirdparty/mysql/lib/)
if(APPLE)
    include_directories(${PROJECT_SOURCE_DIR} "/usr/local/include" "/usr/local/ssl/include")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
    link_directories(/usr/local/lib)
elseif(WIN32)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 ")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /WX")
else()
    include_directories(${PROJECT_SOURCE_DIR} "/usr/local/include")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -static-libgcc -static-libstdc++")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
endif()
link_directories(/usr/local/lib/)
link_libraries(mysqlclient)
if(WIN32)
else()
link_libraries(pthread)
endif()
set(SERVER_FILES 
		MediumServer.cpp
		CServerSess.h CServerSess.cpp
		CClientSessManager.h CClientSessManager.cpp
        CMediumServer.h CMediumServer.cpp 
        ../../../msgStruct/json11/json11.cpp
        CClientSess.h CClientSess.cpp 
        ../include/DaemonApp/DaemonSvcApp.h 
        ../include/DaemonApp/DaemonSvcApp.cpp
		../../../msgStruct/CommonDef.cpp
		../../../msgStruct/CommonMsg.cpp
		CTimeUtil.h 
		CTimeUtil.cpp
        CMySqlConnect.cpp
		EncodingUtil.cpp
        #../include/thirdparty/fmt/src/format.cc
        #../include/thirdparty/fmt/src/posix.cc
        )
add_executable(ChatServer ${SERVER_FILES})
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin)  