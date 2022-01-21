cmake_minimum_required(VERSION 3.0)
project(ChatServerTest)
add_definitions(-DUSE_STANDALONE_ASIO)
add_definitions(-DASIO_STANDALONE)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
include_directories(../../include/thirdparty/)
include_directories(../../include/thirdparty/SQLiteCpp/include/)
include_directories(../../include/thirdparty/SQLiteCpp/sqlite3/)
include_directories(../../include/msgstruct/)
include_directories(../ChatServer/)

if(APPLE)
    include_directories(${PROJECT_SOURCE_DIR} "/usr/local/include" "/usr/local/ssl/include")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
    link_directories(/usr/local/lib)
elseif(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 ")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /WX")
else()
    include_directories(${PROJECT_SOURCE_DIR} "/usr/local/include")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -static-libgcc -static-libstdc++")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wno-unused-local-typedefs")
endif()

link_directories(/usr/local/lib64)
if(WIN32)
else()
link_libraries(pthread dl)
endif()	
set(SERVER_FILES main.cpp
    ../ChatServer/CDataBaseSqlite.cpp 
    ../ChatServer/CDataBaseInterface.cpp
    ../../../include/thirdparty/SQLiteCpp/src/Backup.cpp
    ../../../include/thirdparty/SQLiteCpp/src/Column.cpp
    ../../../include/thirdparty/SQLiteCpp/src/Database.cpp
    ../../../include/thirdparty/SQLiteCpp/src/Exception.cpp
    ../../../include/thirdparty/SQLiteCpp/src/Statement.cpp
    ../../../include/thirdparty/SQLiteCpp/src/Transaction.cpp
    ../../../include/thirdparty/SQLiteCpp/sqlite3/sqlite3.c
    )
add_executable(ChatServerTest ${SERVER_FILES})
#add_executable(FmtLearn ${LEARN_SERVER_FILES})
set(EXECUTABLE_OUTPUT_PATH ${BUILD_BIN_DIR})