/**
 * @file CClientSess.h
 * @author DennisMi (https://www.dennisthink.com/)
 * @brief 
 * @version 0.1
 * @date 2019-07-20
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _CLIENT_CORE_C_CLIENT_SESS_H_
#define _CLIENT_CORE_C_CLIENT_SESS_H_
#include "asio_common.h"
#include "Log.h"
#include "CMediumServer.h"
#include "CommonMsg.h"
namespace ClientCore
{
using asio::ip::tcp;
class CClientSessManager;
/**
 * @brief 用于连接到远端服务器的Sess
 * 
 */
class CClientSess : public std::enable_shared_from_this<CClientSess>  {
protected:
	enum STATE
	{
		ST_CONN_FINISHED=0,
		ST_CONNING,
		ST_NOT_CONNECT
	};
    asio::io_service& m_ioService;

	std::string m_serverIp;
	int 		m_serverPort;

	//持有此连接的消息队列
    CClientSessManager* m_queue;
	//tcp连接的socket
	asio::ip::tcp::socket   m_socket;

	//连接信息,需要多次获取,因此保存到变量中
	std::string m_connectInfo;

	//Sess的连接状态
	int m_bConnect=ST_NOT_CONNECT;
	
	enum { max_length = 16384, msg_max_len=8192 };
	
	//接收buf
	char m_recvbuf[max_length];
	
	//接收位置
    uint32_t m_recvpos=0;
public:
	static	std::shared_ptr<spdlog::logger> ms_loger;
public:
	//检查是否为同一个连接
	bool is_same_connect(const std::string& strIp,const int nport)
	{
		return (( m_serverIp.compare(strIp)==0) && 
			(nport == m_serverPort ));
	}
	//获取连接的ip地址和端口号,格式为 xx.xx.xx.xx:port
	std::string GetConnectInfo(){return m_connectInfo;}

	bool SendKeepAlive();
	
	

    //CClientSess(asio::io_service& ioService,std::string& strIp,int port,CClientSessManager* queue);
    CClientSess(asio::io_service& ioService,std::string& strIp,int port);
    int StartConnect();
    int StopConnect();
	bool IsConnect(){return m_bConnect == ST_CONN_FINISHED;}
	bool SendMessage(std::shared_ptr<TransBaseMsg_t> pMsg);
private:
	int do_read();
	void handle_message(const TransBaseMsg_t* msg);

	
	void handleKeepAliveReq(const KeepAliveReqMsg& reqMsg);
	
	void handleKeepAliveRsp(const KeepAliveRspMsg& rspMsg);
};
}

#endif //CAPNSSESS
