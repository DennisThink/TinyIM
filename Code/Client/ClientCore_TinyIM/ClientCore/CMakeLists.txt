cmake_minimum_required(VERSION 3.0)
project(MediumServer)
add_definitions(-DUSE_STANDALONE_ASIO)
add_definitions(-DASIO_STANDALONE)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
include_directories(../../../msgStruct/)
include_directories(../../../msgStruct/json11/)
include_directories(../include/thirdparty/)
include_directories(../include/thirdparty/asio/)
include_directories(../include/thirdparty/spdlog/)
include_directories(../include/thirdparty/fmt/include/)
include_directories(../include/thirdparty/httpServer/)
include_directories(../include/thirdparty/SnowFlake/)
include_directories(../include/thirdparty/SQLiteCpp/include/)
include_directories(../include/thirdparty/SQLiteCpp/sqlite3/)
include_directories(../include/common/)
include_directories(../include/DaemonApp/)
link_libraries(zlib)
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

if(WIN32)
else()
link_libraries(pthread)
endif()
set(SERVER_FILES 
		MediumServer.cpp
		CServerSess.h CServerSess.cpp
        CMediumServer.h CMediumServer.cpp 
        ../../../msgStruct/json11/json11.cpp
        CClientSess.h CClientSess.cpp
		../include/common/IUProtocolData.cpp
        ../include/DaemonApp/DaemonSvcApp.h 
        ../include/DaemonApp/DaemonSvcApp.cpp
		./CHttpServer.h ./CHttpServer.cpp
		#CMsgPersistentUtil.h CMsgPersistentUtil.cpp
		#CFileUtil.h  CFileUtil.cpp
		../../../msgStruct/CommonDef.cpp
		../../../msgStruct/CommonMsg.cpp
        )

SET(SQLITE_CPP_SOURCE ../include/thirdparty/SQLiteCpp/sqlite3/sqlite3.c
../include/thirdparty/SQLiteCpp/src/Backup.cpp
../include/thirdparty/SQLiteCpp/src/Column.cpp
../include/thirdparty/SQLiteCpp/src/Database.cpp
../include/thirdparty/SQLiteCpp/src/Exception.cpp
../include/thirdparty/SQLiteCpp/src/Statement.cpp
../include/thirdparty/SQLiteCpp/src/Transaction.cpp)

add_executable(ClientCore ${SERVER_FILES}  ${SQLITE_CPP_SOURCE})
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin)  