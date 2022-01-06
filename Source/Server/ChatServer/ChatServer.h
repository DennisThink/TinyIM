/**
 * @file CMediumServer.h
 * @author DennisMi (https://www.dennisthink.com/)
 * @brief ChatServer的核心处理逻辑
 * @version 0.1
 * @date 2019-07-19
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _MEDIUM_SERVER_C_MEDIUM_SERVER_H_
#define _MEDIUM_SERVER_C_MEDIUM_SERVER_H_

#include <functional>

#include <map>

#include "CommonMsg.h"
#include "Log.h"
#include "asio_common.h"
#include "json11.hpp"

#include "CClientSess.h"
#include "CClientSessManager.h"
#include "CServerSess.h"
#include "planform.h"
#include "CMySqlConnect.h"
#include "SnowFlake.h"
namespace TinyIMServer
{
using tcp = asio::ip::tcp;

class CChatServer : public std::enable_shared_from_this<CChatServer>
{
public:
	void HandleUserKeepAliveReq(const std::shared_ptr<CServerSess> pSess);
	void HandleUserLoginReq(const std::shared_ptr<CServerSess>& pSess, const UserLoginReqMsg& reqMsg);

	void HandleUserKickOffRsp(const std::shared_ptr<CServerSess>& pSess, const UserKickOffRspMsg& reqMsg);
	
	void HandleUserLogoutReq(const std::shared_ptr<CServerSess>& pSess, const UserLogoutReqMsg& reqMsg);
	
	void HandleUserRegisterReq(const std::shared_ptr<CServerSess>& pSess, const UserRegisterReqMsg& reqMsg);
	void HandleUserUnRegisterReq(const std::shared_ptr<CServerSess>& pSess, const UserUnRegisterReqMsg& reqMsg);

	void HandleFrientChatSendTxtReq(const std::shared_ptr<CServerSess>& pSess, const FriendChatSendTxtReqMsg& reqMsg);
	void HandleFriendChatRecvMsgReq(const std::shared_ptr<CServerSess>& pSess, const FriendChatRecvTxtReqMsg& regMsg);
	void HandleFriendChatRecvMsgRsp(const std::shared_ptr<CServerSess>& pSess, const FriendChatRecvTxtRspMsg& regMsg);

	void HandleAddFriendReq(const std::shared_ptr<CServerSess>& pSess, const AddFriendSendReqMsg& regMsg);
	void HandleAddFriendRecvRsp(const std::shared_ptr<CServerSess>& pSess, const AddFriendRecvRspMsg& rspMsg);
	void HandleAddFriendNotifyRsp(const std::shared_ptr<CServerSess>& pSess, const AddFriendNotifyRspMsg& rspMsg);
	void HandleRemoveFriendReq(const std::shared_ptr<CServerSess>& pSess, const RemoveFriendReqMsg& rspMsg);

	void HandleFindFriendReq(const std::shared_ptr<CServerSess>& pSess, const FindFriendReqMsg& reqMsg);
	void HandleGetFriendListReq(const std::shared_ptr<CServerSess>& pSess, const GetFriendListReqMsg& reqMsg);

	void HandleAddTeamReq(const std::shared_ptr<CServerSess>& pSess, const AddTeamReqMsg& reqMsg);
	void HandleRemoveTeamReq(const std::shared_ptr<CServerSess>& pSess, const RemoveTeamReqMsg& reqMsg);
	void HandleMoveFriendToTeamReq(const std::shared_ptr<CServerSess>& pSess, const MoveFriendToTeamReqMsg& reqMsg);
	

	void HandleFriendSendFileReq(const std::shared_ptr<CServerSess>& pSess, const FriendSendFileMsgReqMsg& reqMsg);
	void HandleFriendRecvFileRsp(const std::shared_ptr<CServerSess>& pSess, const FriendRecvFileMsgRspMsg& reqMsg);
	void HandleFriendNotifyFileRsp(const std::shared_ptr<CServerSess>& pSess, const FriendNotifyFileMsgRspMsg& req);

	void HandleFileVerifyReq(const std::shared_ptr<CServerSess>& pSess, const FileVerifyReqMsg& req);
	void HandleFileVerifyRsp(const std::shared_ptr<CServerSess>& pSess, const FileVerifyRspMsg& req);
	//Group
	void HandleCreateGroupReq(const std::shared_ptr<CServerSess>& pSess, const CreateGroupReqMsg& reqMsg);

	void HandleDestroyGroupReq(const std::shared_ptr<CServerSess>& pSess, const DestroyGroupReqMsg& reqMsg);

	void HandleGetGroupListReq(const std::shared_ptr<CServerSess>& pSess, const GetGroupListReqMsg& reqMsg);

	void HandleAddToGroupReq(const std::shared_ptr<CServerSess>& pSess, const AddToGroupReqMsg& reqMsg);

	void HandleFindGroupReq(const std::shared_ptr<CServerSess>& pSess, const FindGroupReqMsg& reqMsg);

	void HandleSendGroupTextReq(const std::shared_ptr<CServerSess>& pSess, const SendGroupTextMsgReqMsg& reqMsg);

	void HandleRecvGroupTextMsgRspMsg(const std::shared_ptr<CServerSess>& pSess, const RecvGroupTextMsgRspMsg& reqMsg);

	void HandleFileDataSendReqMsg(const std::shared_ptr<CServerSess>& pSess, const FileDataSendReqMsg& reqMsg);

	void HandleFileDataRecvRspMsg(const std::shared_ptr<CServerSess>& pSess, const FileDataRecvRspMsg& reqMsg);

	void HandleFriendUnReadNotifyRspMsg(const std::shared_ptr<CServerSess>& pSess, const FriendUnReadNotifyRspMsg& rspMsg);

	void OnSessClose(const std::shared_ptr<CServerSess>& pSess) {
		
		auto item = m_UserSessVec.find(pSess->UserId());
		if (item != m_UserSessVec.end() &&
			item->second == pSess)
		{
			LOG_INFO(ms_loger, "User:{} is Closed [{} {} ]", pSess->UserId(), __FILENAME__, __LINE__);
			m_UserSessVec.erase(pSess->UserId());
		}
		m_clientStateMap.erase(pSess->UserId());
		m_util.UpdateUserOnlineState(pSess->UserId(), CLIENT_ONLINE_TYPE::C_ONLINE_TYPE_OFFLINE);
	}
	
    //void HandleUserUnRegisterReq(const std::shared_ptr<CServerSess>& pSess, const  & reqMsg);
	//void HandleUserLoginReq(const std::shared_ptr<CServerSess>& pSess, const UserLoginReqMsg& reqMsg);
	//void HandleUserLoginReq(const std::shared_ptr<CServerSess>& pSess, const UserLoginReqMsg& reqMsg);
	//void HandleUserLoginReq(const std::shared_ptr<CServerSess>& pSess, const UserLoginReqMsg& reqMsg);
	
    UserLoginRspMsg DoUserLoginReq(const UserLoginReqMsg& reqMsg);
	UserLogoutRspMsg DoUserLogoutReq(const UserLogoutReqMsg& reqMsg);
	UserRegisterRspMsg DoUserRegisterReq(const UserRegisterReqMsg& reqMsg);
	UserUnRegisterRspMsg DoUserUnRegisterReq(const UserUnRegisterReqMsg& reqMsg);
	FriendChatSendTxtRspMsg DoFriendChatSendTxtReq(const FriendChatSendTxtReqMsg& reqMsg);
	AddFriendSendRspMsg DoAddFriendReq(const AddFriendSendReqMsg& reqMsg);

	GetFriendListRspMsg DoGetFriendReq(const GetFriendListReqMsg & reqMsg);

	RemoveFriendRspMsg DoRemoveFriendReq(const RemoveFriendReqMsg& reqMsg);
	FindFriendRspMsg   DoFindFriendReq(const FindFriendReqMsg& reqMsg);
	AddTeamRspMsg DoAddTeamReq(const AddTeamReqMsg& reqMsg);
	RemoveTeamRspMsg DoRemoveTeamReq(const RemoveTeamReqMsg& reqMsg);
	MoveFriendToTeamRspMsg DoMoveFriendToTeamReq(const MoveFriendToTeamReqMsg& reqMsg);

	CreateGroupRspMsg DoCreateGroupReq(const CreateGroupReqMsg& reqMsg);

	DestroyGroupRspMsg DoDestroyGroupReq(const DestroyGroupReqMsg& reqMsg);

	GetGroupListRspMsg DoGetGroupListReq(const GetGroupListReqMsg& reqMsg);

	FindGroupRspMsg DoFindGroupReq(const FindGroupReqMsg& reqMsg);

	SendGroupTextMsgRspMsg DoSendGroupTextMsgReqMsg(const SendGroupTextMsgReqMsg& reqMsg);

	AddToGroupRspMsg DoAddToGroupReqMsg(const AddToGroupReqMsg& reqMsg);
	//
  protected:
    //asio的主循环类
    asio::io_service &m_ioService;

    //用于接收连接的socket
    tcp::socket m_socket;

    //用于监听的socket
    tcp::acceptor m_acceptor;

    //服务器的IP端口设置
    IpPortCfg m_serverCfg;
    
    //数据库操作类
    CMySqlConnect m_util;
    
    //所有的客户端的连接客户端的IP端口设置
    std::vector<IpPortCfg> m_clientCfgVec;

    std::vector<std::shared_ptr<CServerSess>> m_listenList; //监听的套接字的列表

    //定时器
    std::shared_ptr<asio::high_resolution_timer> m_timer = nullptr;
    
    void SetTimer(int nSeconds);
    
    void OnTimer();

    std::vector<std::shared_ptr<CClientSessManager>> m_queueVec;
    
    std::error_code m_ec;

    void do_accept();

	bool OnUserReceiveMsg(const std::string strUser);

	bool OnAddFriendRecvReqMsg(const std::string strUser);

	bool OnAddFriendNotifyReqMsg(const std::string strUser);

	bool OnUserRecvGroupMsg(const std::string strUser);

	bool OnUserRecvGroupMsg(const std::string strUser,const std::string strMsgId, const std::string strGroupId, const std::string strSender, const std::string strMsg);
	bool OnUserRecvGroupMsg(const std::string strUser,const T_GROUP_CHAT_MSG& msg);
	void OnDispatchGroupMsg(const std::string strGroupId);

	void OnUserStateCheck(const std::string strUserId);
private:
	
   
    SnowFlake m_MsgID_Util; //消息的唯一生成器
	
  
    std::map<std::string, std::shared_ptr<CServerSess>> m_UserSessVec;  //保存UserId和Sess的对应关系
	std::map<std::string, CLIENT_SESS_STATE> m_clientStateMap;          //保存客户端的状态

	std::map<std::string, std::shared_ptr<CServerSess>> m_KickOffSessMap;  //保存UserId和Sess的对应关系

	std::string GenerateUserId();

	void HandleReLogin(std::string strUserId, std::shared_ptr<CServerSess> pSess);
 public:

    static std::shared_ptr<spdlog::logger> ms_loger; //日志指针
    inline IpPortCfg &config() { return m_serverCfg; }

    void SendBack(const TransBaseMsg_t *msg);
    void CheckAllConnect();
    CChatServer(asio::io_service &io_service)
        : m_ioService(io_service), m_socket(io_service), m_acceptor(io_service),m_MsgID_Util(1,3)
    {
        if (!m_timer)
        {
            m_timer = std::make_shared<asio::high_resolution_timer>(m_ioService);
        }
        
        m_util.ConnectToServer("admin","admin","imdev","127.0.0.1");
    }

    void start(const std::function<void(const std::error_code &)> &callback)
    {
        if (!m_serverCfg.Valid())
        {
            LOG_ERR(ms_loger, "ServerConfig Is Error {} [{} {}]", m_serverCfg.to_string(), __FILENAME__, __LINE__);
            return;
        }
        LOG_INFO(ms_loger, "Server Start Service [{} {}]", __FILENAME__, __LINE__);
        std::error_code ec;
        asio::ip::tcp::endpoint endpoint;
        if (m_serverCfg.m_strServerIp.length() > 0)
        {
            endpoint = asio::ip::tcp::endpoint(
                asio::ip::address::from_string(m_serverCfg.m_strServerIp),
                m_serverCfg.m_nPort);
        }
        else
        {
            endpoint =
                asio::ip::tcp::endpoint(asio::ip::tcp::v4(), m_serverCfg.m_nPort);
        }
        //LOG_WARN(ms_loger, "Before Open");
        m_acceptor.open(endpoint.protocol());
        //LOG_WARN(ms_loger, "Before Set Option");
        m_acceptor.set_option(asio::socket_base::reuse_address(true));
        //LOG_WARN(ms_loger, "Before Bind");
        m_acceptor.bind(endpoint, ec);
        //LOG_WARN(ms_loger, "Before Listen");
        if (!ec)
        {
            LOG_INFO(ms_loger, "Bind To {} Succeed [{} {}]", m_serverCfg.to_string(), __FILENAME__, __LINE__);
            m_acceptor.listen(asio::socket_base::max_connections, ec);
            if (!ec)
            {
                LOG_INFO(ms_loger, "Listen To {} Succeed [{} {}]", m_serverCfg.to_string(), __FILENAME__, __LINE__);
            }
            else
            {
                LOG_WARN(ms_loger, "Listen To {} Failed, Reason:{} {} [{} {}]",
                     m_serverCfg.to_string(), ec.value(), ec.message(),__FILENAME__, __LINE__);
            }
            SetTimer(30);
            do_accept();
            if(0)
			{
                for (auto item : m_clientCfgVec)
                {
                    if (item.Valid())
                    {
                        auto pQueue = std::make_shared<CClientSessManager>(item);
                        m_queueVec.push_back(pQueue);
                        std::error_code ec;
                        pQueue->Start(this, m_ioService, ec);
                        LOG_INFO(ms_loger, "ConnectTo: {} [{} {}]", item.to_string(),__FILENAME__, __LINE__);
                    }
                }
            }
        }
        else
        {
            LOG_ERR(ms_loger, "Bind To {} Failed [{} {}]", m_serverCfg.to_string(), __FILENAME__, __LINE__);
            callback(ec);
#ifndef WIN32
            exit(BIND_FAILED_EXIT);
#endif
        }
    }
	
    void loadConfig(const json11::Json &cfg, std::error_code &ec);
    //获取server的ip和端口,
    std::string getServerIpPort();
};
} // namespace MediumServer

#endif // HTTP2T1_CAGENTSERVER_H
