cmake_minimum_required(VERSION 3.0)
project(UnitTest)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
include_directories(../include/thirdparty/doctest/)
include_directories(../common/)
include_directories(../common/util/)
include_directories(../../../msgStruct/)
include_directories(../../../msgStruct/json11/)
include_directories(../include/thirdparty/mysql/include/)
include_directories(../include/mysql/)
include_directories(../include/common/)
include_directories(../include/thirdparty/)
include_directories(../include/thirdparty/SnowFlake/)
link_directories(../include/thirdparty/mysql/lib/)
link_directories(../include/thirdparty/mysql/lib/)
link_libraries(libmysql.lib)
link_libraries(mysqlclient.lib)
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
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wno-unused-local-typedefs")
endif()

link_directories(/usr/local/lib64)

if(WIN32)
else()
link_libraries(pthread dl)
endif()	
set(SERVER_FILES main.cpp

    ../../../msgStruct/json11/json11.cpp

    ../MediumServer/CMySqlConnect.cpp
../MediumServer/EncodingUtil.cpp 
../../../msgStruct/CommonDef.cpp
../../../msgStruct/CommonMsg.cpp
)
#set(LEARN_SERVER_FILES fmtLearn.cpp
#  ../include/thirdparty/fmt/src/format.cc
#  ../include/thirdparty/fmt/src/posix.cc
#  ../include/thirdparty/json11/json11.cpp)
add_executable(UnitTest ${SERVER_FILES} )
#add_executable(FmtLearn ${LEARN_SERVER_FILES})
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin) 