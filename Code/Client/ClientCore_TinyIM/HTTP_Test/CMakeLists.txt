cmake_minimum_required(VERSION 3.0)
project(HttpTest)
add_definitions(-DUSE_STANDALONE_ASIO)
add_definitions(-DASIO_STANDALONE)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
include_directories(../../../msgStruct/)
include_directories(../../../msgStruct/json11)
include_directories(../include/thirdparty/)
include_directories(../include/thirdparty/asio/)
include_directories(../include/thirdparty/spdlog/)
include_directories(../include/thirdparty/fmt/include/)
include_directories(../include/thirdparty/httpServer/)
include_directories(../include/common/)
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
	../../../msgStruct/CommonMsg.cpp
	../../../msgStruct/CommonDef.cpp

)
#set(LEARN_SERVER_FILES fmtLearn.cpp
#  ../include/thirdparty/fmt/src/format.cc
#  ../include/thirdparty/fmt/src/posix.cc
#  ../include/thirdparty/json11/json11.cpp)
add_executable(HttpTest ${SERVER_FILES})
#add_executable(FmtLearn ${LEARN_SERVER_FILES})
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin) 