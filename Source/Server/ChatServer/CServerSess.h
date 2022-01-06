/**
 * @file CServerSess.h
 * @author DennisMi (https://www.dennisthink.com/)
 * @brief 从ClientCore连接上来的Sess,主要处理客户端socket的网络通信
 * @version 0.1
 * @date 2019-07-19
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _MEDIUM_SERVER_C_SERVER_SESS_H_
#define _MEDIUM_SERVER_C_SERVER_SESS_H_
#include "json11.hpp"
#include "CommonMsg.h"
#include "asio_common.h"
#include "Log.h"
#include <atomic>
static std::string StringToHex(const char * data,const std::size_t length)
{
	const std::string hex = "0123456789ABCDEF";
	std::stringstream ss;

	for (std::string::size_type i = 0; i < length; ++i)
		ss << hex[(unsigned char)data[i] >> 4] << hex[(unsigned char)data[i] & 0xf];
	return ss.str();
}

using tcp=asio::ip::tcp;
namespace ChatServer
{
class CChatServer;
/**
 * @brief 用于接收客户端连接的Sess
 * 
 */
class CServerSess : public std::enable_shared_from_this<CServerSess>
{
public:
	static std::shared_ptr<spdlog::logger> ms_loger;
private:
    //套接字
    tcp::socket m_socket;
    
    //需要告知
    CChatServer* m_server;

    //是否已连接
	bool m_bConnect = false;


    enum { max_length = 16384, msg_max_len=8192 };

    //接收消息的buf    
    char m_recvbuf[max_length];
    
    //已经接收的消息的长度
    uint32_t m_recvpos=0;

	char m_sendbuf[max_length];
public:
    /**
     * @brief 发送消息函数，所有的消息需要转为TransBaseMsg_t的类型来进行发送。
     * 
     * @param msg 待发送的消息
     */
    void SendMsg(std::shared_ptr<TransBaseMsg_t> msg){
		if (m_bSend) {
			m_msgQueue.push(msg);
		}
		else
		{
			m_msgQueue.push(msg);
			m_bSend.store(true);
			DoSendMsg();
		}
    }

    CServerSess(tcp::socket socket, CChatServer* server) : m_socket(std::move(socket)),m_server(server),m_bConnect(true) { }
    
    virtual ~CServerSess(){
    }
    
	//TODO 
	std::string GetRemoteIp() const {
		return "127.0.0.1";
	}
    /**
     * @brief 启动服务
     * 
     */
    void Start() {
		LOG_INFO(ms_loger,"Start Receive Socket [{} {}]", __FILENAME__, __LINE__);
        m_recvpos=0;
        do_read();
    }
	

    /**
     * @brief 返回连接是否断开
     * 
     * @return true 连接正常
     * @return false 连接已断开
     */
	bool IsConnected()
	{
		return m_bConnect;
	}

 

    /**
     * @brief 获取连接的用户名
     * 
     * @return std::string 连接的用户名
     */
	std::string UserId() const {
		return m_strUserId;
	}


	/**
	 * @brief 设置用户名，用于标识该连接属于哪个用户
	 *
	 * @param UserName 连接所对应的用户名
	 */
	void SetUserId(const std::string userId) {
		m_strUserId = userId;
	}


	/**
	 * @brief 关闭连接对应的socket
	 *
	 */
	void CloseSocket();
private:
	std::atomic_bool m_bSend{ false };
	//连接对应的唯一用户标识
	std::string m_strUserId;
    
    /**
     * @brief 接收数据，在Start中被调用，通过asio的回调函数，实现连续接收
     *        非阻塞，不需要修改
     * 
     */
	void do_read();


    /**
     * @brief 处理消息的函数，由do_read在判断消息完整以后调用，在此函数中完成消息的分发处理，
     *        代码的示例中给出了KeepAliveReqMsg和KeepAliveRspMsg的处理示例
     * 
     * @param msg 接收到的一条消息
     */
    void handle_message(const TransBaseMsg_t* msg);


    /**
     * @brief 处理KeepAliveRsp消息，由handle_message 调用
     * 
     * @param rspMsg KeepAliveRsp消息
     */
    void handleKeepAliveRsp(const KeepAliveRspMsg& rspMsg);
    
    /**
     * @brief 处理KeepAliveReq消息
     * 
     * @param rspMsg KeepAliveReq消息
     */
    void handleKeepAliveReq(const KeepAliveReqMsg& reqMsg);


	void DoSendMsg() {
		if(!m_msgQueue.empty()) {
			auto msg = m_msgQueue.front();
			m_msgQueue.pop();
			if (IsConnected())
			{
				auto self = shared_from_this();
				std::size_t msgSize = msg->GetSize();
				memcpy(m_sendbuf, msg->GetData(), msgSize);
				LOG_DBG(ms_loger, "Write: {}  {}", StringToHex(m_sendbuf,msgSize), msgSize);
				asio::async_write(m_socket, asio::buffer(m_sendbuf, msg->GetSize()), [this, self, msg](std::error_code ec, std::size_t /*length*/) {
					if (!ec)
					{
						LOG_INFO(ms_loger, "[ {} ] SendMsg Succeed:{} {} {} [{} {}]", UserId(), MsgType(msg->GetType()), msg->GetSize(), msg->to_string(), __FILENAME__, __LINE__);
						DoSendMsg();
					}
					else
					{
						LOG_WARN(ms_loger, "[ {} ] SendMsg Failed:{} {} [{} {}]", UserId(), MsgType(msg->GetType()), msg->to_string(), __FILENAME__, __LINE__);
						CloseSocket();
					}
				});
			}
			else
			{
				CloseSocket();
			}
		}
		else
		{
			m_bSend.store(false);
		}
	}
	std::queue<std::shared_ptr<TransBaseMsg_t>> m_msgQueue;
};
}
#endif
