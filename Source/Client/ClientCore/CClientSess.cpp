/**
 * @file CClientSess.cpp
 * @author DennisMi (https://www.dennisthink.com/)
 * @brief 连接到远程服务器所使用的Sess，暂时没有用到
 * @version 0.1
 * @date 2019-07-19
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "CClientSess.h"
#include "CMediumServer.h"
#include "asio.hpp"
#include "json11.hpp"
#include <iostream>
namespace ClientCore
{
std::shared_ptr<spdlog::logger> CClientSess::ms_loger;

/*CClientSess::CClientSess(asio::io_service &ioService, std::string &strIp,
						 int port, CClientSessManager *queue)
	: m_ioService(ioService), m_serverIp(strIp), m_serverPort(port),
	  m_queue(queue), m_socket(ioService), m_bConnect(ST_NOT_CONNECT)
{
	m_connectInfo = m_serverIp + ":" + std::to_string(m_serverPort);
	StartConnect();
}*/

CClientSess::CClientSess(asio::io_service &ioService, std::string &strIp,
						 int port)
	: m_ioService(ioService), m_serverIp(strIp), m_serverPort(port), m_socket(ioService), m_bConnect(ST_NOT_CONNECT)
{
	m_connectInfo = m_serverIp + ":" + std::to_string(m_serverPort);
	StartConnect();
}
/**
 * @brief 连接socket
 *
 * @return int 返回0
 */
int CClientSess::StartConnect()
{
	LOG_INFO(ms_loger, "Try To Connected To :{} [{} {}]", GetConnectInfo(),__FILENAME__, __LINE__);
	if (ST_NOT_CONNECT == m_bConnect)
	{
		m_bConnect = ST_CONNING;
		LOG_WARN(ms_loger, "Start Connect To  IP:{} Port:{} [{} {}]", m_serverIp, m_serverPort,__FILENAME__,__LINE__);
		tcp::resolver reso(m_ioService);
		std::string strPort = std::to_string(m_serverPort);
		auto endpoint_iterator = reso.resolve({m_serverIp, strPort});
		asio::async_connect(
			m_socket, endpoint_iterator,
			[this](std::error_code ec, asio::ip::tcp::endpoint endPt) {
				if (!ec)
				{
					m_bConnect = ST_CONN_FINISHED;
					do_read();
					LOG_WARN(ms_loger, "Connect Success IP:{} Port:{} [{} {}]",
						 endPt.address().to_string(), endPt.port(),__FILENAME__, __LINE__);
				}
				else
				{
					m_bConnect = ST_NOT_CONNECT;
					LOG_WARN(ms_loger, "Connect Failed To {} Code:{} Msg:{}  [{} {}]",
						 this->GetConnectInfo(), ec.value(), ec.message(), __FILENAME__, __LINE__);
				}
			});
	}
	return 0;
}

/**
 * @brief 关闭socket
 *
 * @return int 返回0
 */
int CClientSess::StopConnect()
{
	LOG_INFO(ms_loger, "Connect Closed IP:{},port:{} [{} {}]", m_serverIp, m_serverPort, __FILENAME__, __LINE__);
	m_bConnect = ST_NOT_CONNECT;
	m_socket.close();
	return 0;
}

/**
 * @brief
 * 处理消息的总入口，在此处根据消息类型，完成消息的分发,需要增加新消息的，在此处增加分发代码
 *
 * @param hdr TransBaseMsg_t消息体指针
 */
void CClientSess::handle_message(const TransBaseMsg_t *hdr)
{

	LOG_INFO(ms_loger, "handle_message MsgId {}  [{} {}]",1,__FILENAME__, __LINE__);
	if (nullptr != hdr)
	{
		switch (hdr->GetType())
		{
		case MessageType::KeepAliveReq_Type:
		{
			KeepAliveReqMsg reqMsg;
			if (reqMsg.FromString(hdr->to_string()))
			{
				handleKeepAliveReq(reqMsg);
			}
		}
		break;
		case MessageType::KeepAliveRsp_Type:
		{
			KeepAliveRspMsg rspMsg;
			if (rspMsg.FromString(hdr->to_string()))
			{
				handleKeepAliveRsp(rspMsg);
			}
		}
		break;
		
		default:
		{
		}
		break;
		}
	}
}

/**
 * @brief 从socket读取数据
 *
 * @return int 返回0
 */
int CClientSess::do_read()
{
	if (IsConnect())
	{
		LOG_INFO(ms_loger, "Client  read data ");
		auto self = shared_from_this();
		m_socket.async_read_some(
			asio::buffer(m_recvbuf + m_recvpos, max_length - m_recvpos),
			[this, self](std::error_code ec, std::size_t length) {
				if (ec)
				{
					m_socket.close();
					m_bConnect = ST_NOT_CONNECT;
					return;
				}
				else
				{
					TransBaseMsg_t msg(m_recvbuf);
					auto curlen = m_recvpos + length;
					LOG_INFO(ms_loger, "Client async_read_some:size:{:#x}  ec:{}", length,
						 ec.message());
					while (curlen >= sizeof(Header) && curlen >= msg.GetSize())
					{
						LOG_INFO(ms_loger, " read data {} ", curlen);
						handle_message(&msg);
						curlen -= msg.GetSize();
						memmove(m_recvbuf, m_recvbuf + msg.GetSize(), curlen);
					}
					m_recvpos = (uint32_t)curlen;
					if (m_recvpos < max_length && !ec)
					{
						do_read();
					}
				}
			});
	}
	return 0;
}

/**
 * @brief 发送消息到对端
 *
 * @param pMsg 待发送的消息
 * @return true 发送成功
 * @return false 发送失败
 */
bool CClientSess::SendMessage(std::shared_ptr<TransBaseMsg_t> pMsg)
{
	if (IsConnect())
	{
		auto self = shared_from_this();
		asio::async_write(
			m_socket, asio::buffer(pMsg->GetData(), pMsg->GetSize()),
			[this, self, pMsg](std::error_code ec, std::size_t length) mutable {
				if (ec)
				{
					LOG_WARN(ms_loger, " {} Send KeepAlive Failed [{} {}]", GetConnectInfo(), __FILENAME__, __LINE__);
					StopConnect();
				}
				else
				{
					LOG_WARN(ms_loger, " {} Send KeepAlive Succeed {} {} [{} {}]", GetConnectInfo(),
						 MsgType(pMsg->GetType()),length, __FILENAME__, __LINE__);
				}
			});
	}
	else
	{
		LOG_WARN(ms_loger, "{} Not Connect  [{} {}]", GetConnectInfo(), __FILENAME__, __LINE__);
		StartConnect();
	}
	return true;
}


/**
 * @brief 发送心跳请求消息
 * 
 * @return true 发送成功
 * @return false 发送失败
 */
bool CClientSess::SendKeepAlive()
{
	KeepAliveReqMsg reqMsg("MediumServer");
	auto pMsg =
		std::make_shared<TransBaseMsg_t>(reqMsg.GetMsgType(), reqMsg.ToString());
	SendMessage(pMsg);
	return true;
}

/**
 * @brief 处理心跳请求消息
 * 
 * @param reqMsg 心跳请求消息
 */
void CClientSess::handleKeepAliveReq(const KeepAliveReqMsg &reqMsg)
{
	LOG_INFO(ms_loger, "KeepAliveReq: {} [{} {}]", reqMsg.ToPrintString(), __FILENAME__, __LINE__);
	KeepAliveRspMsg rspMsg("MediumMessage");
	auto pMsg =
		std::make_shared<TransBaseMsg_t>(rspMsg.GetMsgType(), rspMsg.ToString());
	SendMessage(pMsg);
}

/**
 * @brief 处理心跳回复消息
 * 
 * @param rspMsg 心跳回复消息
 */
void CClientSess::handleKeepAliveRsp(const KeepAliveRspMsg &rspMsg)
{
	LOG_INFO(ms_loger, "KeepAliveRsp:{} [{} {}]", rspMsg.ToPrintString(), __FILENAME__, __LINE__);
}

} // namespace MediumServer