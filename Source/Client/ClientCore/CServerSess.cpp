#include "CClientSess.h"
#include "CMediumServer.h"
namespace ClientCore
{
std::shared_ptr<spdlog::logger> CServerSess::ms_loger;

/**
 * @brief 从socket的读取数据的函数
 * 
 */
void CServerSess::do_read()
{
	auto self = shared_from_this();
	m_socket.async_read_some(
		asio::buffer(m_recvbuf + m_recvpos, max_length - m_recvpos),
		[this, self](std::error_code ec, std::size_t length) {
			TransBaseMsg_t msg(m_recvbuf);
			auto curlen = m_recvpos + length;
			LOG_DBG(ms_loger, "Server async_read_some:size:{:#x}  ec:{} [{} {}]", length,
				 ec.message(), __FILENAME__, __LINE__);
			while (curlen >= sizeof(Header) && curlen >= msg.GetSize())
			{
				handle_message(&msg);
				curlen -= msg.GetSize();
				memmove(m_recvbuf, m_recvbuf + msg.GetSize(), curlen);
			}
			m_recvpos = (uint32_t)curlen;
			if (m_recvpos < max_length && !ec)
			{
				do_read();
			}
			else
			{
				CloseSocket();
			}
		});
}

/**
 * @brief 当do_read函数接收到一个完整消息的时候，调用此函数，在此函数中完成消息类型的判断和消息分发
 * 
 * @param hdr 需要被处理的消息
 */
void CServerSess::handle_message(const TransBaseMsg_t *hdr)
{
	LOG_INFO(ms_loger, "[ {} ]  Recv: [ {} {} ]  {}    [ {} {} ]", UserId(), MsgType(hdr->GetType()), hdr->GetSize(), hdr->to_string(), __FILENAME__, __LINE__);
	switch (hdr->GetType())
	{
	case MessageType::KeepAliveReq_Type:
	{
		KeepAliveReqMsg msg;
		if (msg.FromString(hdr->to_string()))
		{
			handleKeepAliveReq(msg);
		}
		else
		{
			LOG_ERR(ms_loger, "Bad KeepAlivReqMsg {}  [ {} {} ] ", hdr->to_string(), __FILENAME__, __LINE__);
		}
		return;
	}
	break;
	case MessageType::KeepAliveRsp_Type:
	{
		KeepAliveRspMsg msg;
		if (msg.FromString(hdr->to_string()))
		{
			handleKeepAliveRsp(msg);
		}
		else
		{
			LOG_ERR(ms_loger, "Bad KeepAlivRspMsg {} [ {} {} ] ", hdr->to_string(),__FILENAME__, __LINE__);
		}
		return;
	}
	break;
	case MessageType::UserLoginReq_Type:
	{
		UserLoginReqMsg msg;
		if (msg.FromString(hdr->to_string())) {
			//m_server->HandleUserLoginReq(shared_from_this(),msg);
		}
		else {

		}
	}break;
	case MessageType::UserLogoutReq_Type: {
		UserLogoutReqMsg msg;
		if (msg.FromString(hdr->to_string())) {
			//m_server->HandleUserLogoutReq(shared_from_this(), msg);
		}
	}break;
	case MessageType::UserRegisterReq_Type:
	{
		UserRegisterReqMsg msg;
		if (msg.FromString(hdr->to_string())) {
			//m_server->HandleUserRegisterReq(shared_from_this(),msg);
		}
	}break;
	case MessageType::UserUnRegisterReq_Type:
	{
		UserUnRegisterReqMsg msg;
		if (msg.FromString(hdr->to_string())) {
			//m_server->HandleUserUnRegisterReq(shared_from_this(), msg);
		}
	}break;
	case MessageType::FriendChatSendTxtMsgReq_Type:
	{
		FriendChatSendTxtReqMsg msg;
		if (msg.FromString(hdr->to_string())) {
			//m_server->HandleFrientChatSendTxtReq(shared_from_this(), msg);
		}
	}break;

	case MessageType::FriendChatReceiveTxtMsgRsp_Type:
	{
		FriendChatRecvTxtRspMsg msg;
		if (msg.FromString(hdr->to_string())) {
			//m_server->HandleFriendChatRecvMsgRsp(shared_from_this(), msg);
		}
	}break;
	case MessageType::GetFriendListReq_Type:
	{
		GetFriendListReqMsg msg;
		if (msg.FromString(hdr->to_string())) {
			//m_server->HandleGetFriendListReq(shared_from_this(),msg);
		}
	}break;
	case MessageType::FindFriendReq_Type:
	{
		FindFriendReqMsg msg;
		if (msg.FromString(hdr->to_string())) {
			//m_server->HandleFindFriendReq(shared_from_this(), msg);
		}
	}break;
	case MessageType::AddFriendSendReq_Type:
	{
		AddFriendSendReqMsg msg;
		if (msg.FromString(hdr->to_string())) {
			//m_server->HandleAddFriendReq(shared_from_this(),msg);
		}
	}break;
	case MessageType::AddFriendRecvRsp_Type:
	{
		AddFriendRecvRspMsg msg;
		if (msg.FromString(hdr->to_string())) {
			//m_server->HandleAddFriendRecvRsp(shared_from_this(), msg);
		}
	}break;
	case MessageType::AddFriendNotifyRsp_Type:
	{
		AddFriendNotifyRspMsg msg;
		if (msg.FromString(hdr->to_string())) {
			//m_server->HandleAddFriendNotifyRsp(shared_from_this(), msg);
		}
	}break;
	case MessageType::RemoveFriendReq_Type:
	{
		RemoveFriendReqMsg msg;
		if (msg.FromString(hdr->to_string())) {
			//m_server->HandleRemoveFriendReq(shared_from_this(), msg);
		}
	}break;
	case MessageType::AddTeamReq_Type:
	{
		AddTeamReqMsg msg;
		if (msg.FromString(hdr->to_string())) {
			//m_server->HandleAddTeamReq(shared_from_this(), msg);
		}
	}break;
	case MessageType::RemoveTeamReq_Type:
	{
		RemoveTeamReqMsg msg;
		if (msg.FromString(hdr->to_string())) {
			//m_server->HandleRemoveTeamReq(shared_from_this(), msg);
		}
	}break;
	case MessageType::MoveFriendToTeamReq_Type: {
		MoveFriendToTeamReqMsg msg;
		if (msg.FromString(hdr->to_string())) {
			//m_server->HandleMoveFriendToTeamReq(shared_from_this(), msg);
		}
	}break;
	case MessageType::CreateGroupReq_Type:
	{
		CreateGroupReqMsg msg;
		if (msg.FromString(hdr->to_string())) {
			//m_server->HandleCreateGroupReq(shared_from_this(),msg);
		}
	}break;
	case MessageType::DestroyGroupReq_Type:
	{
		DestroyGroupReqMsg msg;
		if (msg.FromString(hdr->to_string())) {
			//m_server->HandleDestroyGroupReq(shared_from_this(), msg);
		}
	}break;
	case MessageType::FindGroupReq_Type:
	{
		FindGroupReqMsg msg;
		if (msg.FromString(hdr->to_string())) {
			//m_server->HandleFindGroupReq(shared_from_this(), msg);
		}
	}break;
	case MessageType::GetGroupListReq_Type:
	{
		GetGroupListReqMsg msg;
		if (msg.FromString(hdr->to_string())) {
			//m_server->HandleGetGroupListReq(shared_from_this(),msg);
		}
	}break;
	case MessageType::SendGroupTextMsgReq_Type:
	{
		SendGroupTextMsgReqMsg msg;
		if (msg.FromString(hdr->to_string())) {
			//m_server->HandleSendGroupTextReq(shared_from_this(), msg);
		}
	}break;
	case MessageType::AddToGroupReq_Type: {
		AddToGroupReqMsg msg;
		if (msg.FromString(hdr->to_string())) {
			//m_server->HandleAddToGroupReq(shared_from_this(), msg);
		}
	}break;
	case MessageType::RecvGroupTextMsgRsp_Type:
	{
		RecvGroupTextMsgRspMsg msg;
		if (msg.FromString(hdr->to_string())) {
			m_server->HandleRecvGroupTextMsgRspMsg(shared_from_this(), msg);
		}
	}break;
	case MessageType::FriendSendFileMsgReq_Type:
	{
		FriendSendFileMsgReqMsg reqMsg;
		if (reqMsg.FromString(hdr->to_string())) {
			m_server->HandleFriendSendFileReq(shared_from_this(), reqMsg);
		}
	}break;
	case MessageType::FriendRecvFileMsgRsp_Type:
	{
		FriendRecvFileMsgRspMsg reqMsg;
		if (reqMsg.FromString(hdr->to_string())) {
			m_server->HandleFriendRecvFileRsp(shared_from_this(), reqMsg);
		}
	}break;
	case MessageType::FriendNotifyFileMsgRsp_Type:
	{
		FriendNotifyFileMsgRspMsg rspMsg;
		if (rspMsg.FromString(hdr->to_string())) {
			m_server->HandleFriendNotifyFileRsp(shared_from_this(), rspMsg);
		}
	}break;
	case MessageType::FileSendDataReq_Type:
	{
		FileDataSendReqMsg reqMsg;
		if (reqMsg.FromString(hdr->to_string())) {
			m_server->HandleFileDataSendReqMsg(shared_from_this(), reqMsg);
		}
	}break;
	case MessageType::FileRecvDataRsp_Type:
	{
		FileDataRecvRspMsg rspMsg;
		if (rspMsg.FromString(hdr->to_string())) {
			m_server->HandleFileDataRecvRspMsg(shared_from_this(),rspMsg);
		}
	}break;
	case MessageType::FileVerifyReq_Type:
	{
		FileVerifyReqMsg reqMsg;
		if (reqMsg.FromString(hdr->to_string())) {
			m_server->HandleFileVerifyReq(shared_from_this(), reqMsg);
		}
	}break;
	case MessageType::FileVerifyRsp_Type:
	{
		FileVerifyRspMsg rspMsg;
		if (rspMsg.FromString(hdr->to_string())) {
			m_server->HandleFileVerifyRsp(shared_from_this(), rspMsg);
		}
	}break;
	case MessageType::UserKickOffRsp_Type:
	{
		UserKickOffRspMsg rspMsg;
		if (rspMsg.FromString(hdr->to_string())) {
			m_server->HandleUserKickOffRsp(shared_from_this(), rspMsg);
		}
	}break;
	case MessageType::FriendUnReadMsgNotifyRsp_Type:
	{
		FriendUnReadNotifyRspMsg rspMsg;
		if (rspMsg.FromString(hdr->to_string())) {
			m_server->HandleFriendUnReadNotifyRspMsg(shared_from_this(), rspMsg);
		}
	}break;
	default:
	{
		LOG_ERR(ms_loger, "User:{} Unhandle MsgType:{} [ {} {} ]", UserId(), MsgType(hdr->GetType()), __FILENAME__, __LINE__);
	}break;
	}
}

/**
 * @brief 处理心跳请求消息
 * 
 * @param reqMsg 心跳请求消息
 */
void CServerSess::handleKeepAliveReq(const KeepAliveReqMsg &reqMsg)
{
	LOG_INFO(ms_loger, "KeepAliveReq:{} [ {} {} ] ", reqMsg.ToString(), __FILENAME__, __LINE__);
	KeepAliveRspMsg rspMsg("MediumServer");
	auto pMsg =
		std::make_shared<TransBaseMsg_t>(rspMsg.GetMsgType(), rspMsg.ToString());
	SendMsg(pMsg);
	if (m_server)
	{
		m_server->HandleUserKeepAliveReq(shared_from_this());
	}
}

/**
 * @brief 处理心跳回复消息
 * 
 * @param rspMsg 心跳回复消息
 */
void CServerSess::handleKeepAliveRsp(const KeepAliveRspMsg &rspMsg)
{
	LOG_INFO(ms_loger, "KeepAliveRsp:{} [ {} {} ] ", rspMsg.ToString(), __FILENAME__, __LINE__);
}



/**
 * @brief 关闭socket
 * 
 */
void CServerSess::CloseSocket() {
	m_socket.close();
	m_bConnect = false;
	LOG_INFO(ms_loger, "{} Leave Server [ {} {}]", UserId(), __FILENAME__, __LINE__);
	if (m_server) {
		m_server->OnSessClose(shared_from_this());
	}
}

} // namespace MediumServer