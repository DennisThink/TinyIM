#include "CClientSessManager.h"
#include "CClientSess.h"
#include <algorithm>
namespace ChatServer
{
std::shared_ptr<spdlog::logger> CClientSessManager::ms_loger;



/**
 * @brief 将从远端服务器发送来的消息，发送到Server，
 * 
 * @param 接收到的消息
 */
void CClientSessManager::send_back(const TransBaseMsg_t* msg)
{
	if(msg)
	{
		LOG_INFO(ms_loger,"Good Mesg  [{} {}]",__FILENAME__, __LINE__);
	}
	if(m_server)
	{
		m_server->SendBack(msg);
	}
}


/**
 * @brief 启动Manager
 * 
 * @param pServer 服务的总控类
 * @param ioService asio::io_service
 * @param ec 发生的异常
 */
void CClientSessManager::Start(CChatServer* pServer,asio::io_service& ioService, std::error_code& ec)
{
	m_server=pServer;
	auto pSess = std::make_shared<CClientSess>(ioService,m_config.m_strServerIp,m_config.m_nPort,this);
	m_SessMap.insert(std::pair<int,std::shared_ptr<CClientSess>>(1,pSess));
	pSess->StartConnect();
	ec.clear();
}

/**
 * @brief 发送消息到远端的服务器
 * 
 * @param msg 待发送的消息
 */
void CClientSessManager::SendTo(const TransBaseMsg_t* msg)
{
	if(nullptr != msg)
	{
		return ;
	}
}

/**
 * @brief 响应定时器，需要定时处理的任务，可以写成一个函数，在此处调用
 * 
 */
void CClientSessManager::OnTimer()
{
	CheckSessConn();
}

/**
 * @brief 检查当前的所有连接
 * 
 */
void CClientSessManager::CheckSessConn()
{
	for(auto sessItem:m_SessMap)
	{
		if(sessItem.second->IsConnect())
		{
			LOG_WARN(ms_loger,"{} Connected [{} {}]",sessItem.second->GetConnectInfo(), __FILENAME__, __LINE__);
			sessItem.second->SendKeepAlive();
		}
		else
		{
			LOG_WARN(ms_loger,"{} Not Connected [{} {}]",sessItem.second->GetConnectInfo(), __FILENAME__, __LINE__);
			sessItem.second->StartConnect();
		}
	}
}


}