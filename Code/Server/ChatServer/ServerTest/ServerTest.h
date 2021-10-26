#ifndef _SERVER_TEST_H_
#define _SERVER_TEST_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#ifdef WIN32
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#pragma comment(lib,"Ws2_32.lib ")
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <unistd.h>
#include <fcntl.h>
#endif
#include <regex>
#define MAXLINE 4096
#include <string>
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
int Open(std::string strIp,int port)
{
#ifdef WIN32
WSADATA wsaData;
int iRet = 0;
iRet = WSAStartup(MAKEWORD(2, 2), &wsaData);
if (iRet != 0)
{
	return -1;
}
if (2 != LOBYTE(wsaData.wVersion) || 2 != HIBYTE(wsaData.wVersion))
{
	WSACleanup();
	return -1;
}
#endif

    int sockfd;
    struct sockaddr_in servaddr;
    if ((sockfd = static_cast<int>(socket(AF_INET, SOCK_STREAM, 0))) < 0)
    {
        return -1;
    }
   
#ifdef _WIN32
	unsigned long ul = 1;
	//int ret = ioctlsocket(sockfd, FIONBIO, (unsigned long *)&ul);
#endif
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);

#ifdef WIN32
	servaddr.sin_addr.S_un.S_addr = inet_addr(strIp.c_str());
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
#else

	if (inet_pton(AF_INET, strIp.c_str(), &servaddr.sin_addr) <= 0)
	{
		return -1;
	}
#endif

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        return -1;
    }
    return sockfd;
}

bool Close(int socketFd)
{
#ifdef WIN32
	closesocket(socketFd);
#else
    close(socketFd);
#endif
	return true;
}

bool Send(int sockFd,std::string strMsg)
{
	//std::cout << sockFd << "  Send: " << strMsg << std::endl;
#ifdef WIN32
	std::size_t sendLen = send(sockFd, strMsg.data(), static_cast<int>(strMsg.length()), 0);
#else
    std::size_t sendLen = send(sockFd, strMsg.data(), strMsg.length(), 0);
#endif
	if(sendLen != strMsg.length())
    {
        return false;
    }
    return true;
}

bool Recv(int sockFd,std::string& strMsg)
{
    const int BUF_LEN = 128;
    char buf[BUF_LEN] = {0};
    std::size_t nRecvLen = 0;
    do{
        memset(buf,0,BUF_LEN);
        nRecvLen =  recv(sockFd,buf,BUF_LEN,0);
        strMsg = strMsg+std::string(buf,nRecvLen);
        if(nRecvLen < BUF_LEN-1)
        {
            break;
        }
		//std::cout << "READ: " << strMsg << std::endl;
    }while(nRecvLen>0);
	//std::cout << sockFd << "  READ: " << strMsg <<__LINE__ <<std::endl;
    return true;
}

bool Send(int sockFd, const char * pData,const int length)
{
	//std::cout << sockFd << "  Send: " << pData << std::endl;
	std::string strMsg(pData,length);
#ifdef WIN32
	std::size_t sendLen = send(sockFd, pData, length, 0);
#else
	std::size_t sendLen = send(sockFd, strMsg.data(), strMsg.length(), 0);
#endif
	if (sendLen != length)
	{
		return false;
	}
	return true;
}

/*
bool Recv(int sockFd, char * pData,int * pLength)
{
	const int BUF_LEN = 512;
	char buf[BUF_LEN] = { 0 };
	std::size_t nRecvLen = 0;
	do {
		memset(buf, 0, BUF_LEN);
		nRecvLen = recv(sockFd, buf, BUF_LEN, 0);
		strMsg = strMsg + std::string(buf, nRecvLen);
		if (nRecvLen < BUF_LEN - 1)
		{
			break;
		}
	} while (nRecvLen > 0);

	return true;
}*/
#endif