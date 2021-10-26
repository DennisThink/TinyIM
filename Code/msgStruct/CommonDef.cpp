#include "CommonDef.h"
std::string FriendOption(const E_FRIEND_OPTION& option) 
{
	switch (option)
	{
	case E_FRIEND_OPTION::E_UN_KNOWN:
	{
		return "UN_KNOWN";
	}break;
	case E_FRIEND_OPTION::E_AGREE_ADD:
	{
		return "AGREE_ADD";
	}break;
	case E_FRIEND_OPTION::E_REFUSE_ADD:
	{
		return "REFUSE_ADD";
	}break;
	default:
	{
		return "UN_KNOWN";
	}break;
	}
}

E_FRIEND_OPTION FriendOption(const std::string strOption)
{
	if ("UN_KNOWN" == strOption)
	{
		return E_FRIEND_OPTION::E_UN_KNOWN;
	}

	if ("REFUSE_ADD" == strOption)
	{
		return E_FRIEND_OPTION::E_REFUSE_ADD;
	}

	if ("AGREE_ADD" == strOption)
	{
		return E_FRIEND_OPTION::E_AGREE_ADD;
	}

	return E_FRIEND_OPTION::E_UN_KNOWN;
}


std::string FriendStatus(const E_ADD_FRIEND_STATUS relation)
{
	switch (relation)
	{
	case E_ADD_FRIEND_STATUS::E_UN_KNOWN:
	{
		return "UN_KNOWN";
	}break;
	case E_ADD_FRIEND_STATUS::E_UN_READ:
	{
		return "UN_READ";
	}break;
	case E_ADD_FRIEND_STATUS::E_READ_UN_NOTIFY:
	{
		return "READ_UN_NOTIFY";
	}break;
	case E_ADD_FRIEND_STATUS::E_NOTIFY:
	{
		return "NOTIFY";
	}break;
	default:
	{
		return "UN_KNOWN";
	}break;
	}
}

E_ADD_FRIEND_STATUS FriendStatus(const std::string strStatus)
{

	if ("UN_KNOWN" == strStatus)
	{
		return E_ADD_FRIEND_STATUS::E_UN_KNOWN;
	}
	
	if ("UN_READ" == strStatus)
	{
		return E_ADD_FRIEND_STATUS::E_UN_READ;
	}

	if ("READ_UN_NOTIFY" == strStatus)
	{
		return E_ADD_FRIEND_STATUS::E_READ_UN_NOTIFY;
	}

	if ("NOTIFY" == strStatus)
	{
		return E_ADD_FRIEND_STATUS::E_NOTIFY;
	}

	return E_ADD_FRIEND_STATUS::E_UN_KNOWN;
}


E_GROUP_MEMBER_ROLE MemberRole(const std::string strRole)
{
	if ("CREATER" == strRole)
	{
		return E_GROUP_MEMBER_ROLE::E_ROLE_CREATER;
	}

	if ("MANAGER" == strRole)
	{
		return E_GROUP_MEMBER_ROLE::E_ROLE_MANAGER;
	}

	if ("MEMBER" == strRole)
	{
		return E_GROUP_MEMBER_ROLE::E_ROLE_MEMBER;
	}

	return E_GROUP_MEMBER_ROLE::E_ROLE_UNKNOWN;

}
std::string MemberRole(const E_GROUP_MEMBER_ROLE role)
{
	switch (role)
	{
	case E_GROUP_MEMBER_ROLE::E_ROLE_CREATER:
	{
		return "CREATER";
	}break;
	case E_GROUP_MEMBER_ROLE::E_ROLE_MANAGER:
	{
		return "MANAGER";
	}break;
	case E_GROUP_MEMBER_ROLE::E_ROLE_MEMBER:
	{
		return "MEMBER";
	}
	default:
	{
		return "UNKNOWN";
	}break;
	}
}

#define ENUM_TO_STRING(ENUM_TYPE) case ENUM_TYPE:{return #ENUM_TYPE ;}break;

std::string MsgType(const MessageType& msgType)
{
	switch (msgType)
	{
		ENUM_TO_STRING(MessageType::Base_Type)
		ENUM_TO_STRING(MessageType::KeepAliveReq_Type)
		ENUM_TO_STRING(MessageType::KeepAliveRsp_Type)
		ENUM_TO_STRING(MessageType::UserLoginReq_Type)
		ENUM_TO_STRING(MessageType::UserLoginRsp_Type)
		ENUM_TO_STRING(MessageType::UserLogoutReq_Type)
		ENUM_TO_STRING(MessageType::UserLogoutRsp_Type)
		ENUM_TO_STRING(MessageType::UserRegisterReq_Type)
		ENUM_TO_STRING(MessageType::UserRegisterRsp_Type)
		ENUM_TO_STRING(MessageType::UserUnRegisterReq_Type)
		ENUM_TO_STRING(MessageType::UserUnRegisterRsp_Type)
		ENUM_TO_STRING(MessageType::FriendChatReceiveTxtMsgReq_Type)
		ENUM_TO_STRING(MessageType::FriendChatReceiveTxtMsgRsp_Type)
		ENUM_TO_STRING(MessageType::FriendChatSendTxtMsgReq_Type)
		ENUM_TO_STRING(MessageType::FriendChatSendTxtMsgRsp_Type)
		ENUM_TO_STRING(MessageType::FriendChatSendEmojiMsgReq_Type)
		ENUM_TO_STRING(MessageType::FriendChatSendEmojiMsgRsp_Type)
		ENUM_TO_STRING(MessageType::FriendChatSendImageMsgReq_Type)

		ENUM_TO_STRING(MessageType::FriendChatSendImageMsgRsp_Type)
		ENUM_TO_STRING(MessageType::FriendSendFileMsgReq_Type)
		ENUM_TO_STRING(MessageType::FriendSendFileMsgRsp_Type)
		ENUM_TO_STRING(MessageType::FriendRecvFileMsgReq_Type)
		ENUM_TO_STRING(MessageType::FriendRecvFileMsgRsp_Type)
		ENUM_TO_STRING(MessageType::FriendNotifyFileMsgReq_Type)
		ENUM_TO_STRING(MessageType::FriendNotifyFileMsgRsp_Type)

		ENUM_TO_STRING(MessageType::FileSendDataReq_Type)
		ENUM_TO_STRING(MessageType::FileSendDataRsp_Type)
		ENUM_TO_STRING(MessageType::FileRecvDataReq_Type)
		ENUM_TO_STRING(MessageType::FileRecvDataRsp_Type)

		ENUM_TO_STRING(MessageType::FriendChatSendFileDataOnLineRsp_Type)
		ENUM_TO_STRING(MessageType::FriendChatSendFileDataOffLineReq_Type)
		ENUM_TO_STRING(MessageType::FriendChatSendFileDataOffLineRsp_Type)
		ENUM_TO_STRING(MessageType::FindFriendReq_Type)
		ENUM_TO_STRING(MessageType::FindFriendRsp_Type)
		ENUM_TO_STRING(MessageType::AddFriendSendReq_Type)
		ENUM_TO_STRING(MessageType::AddFriendSendRsp_Type)
		ENUM_TO_STRING(MessageType::AddFriendRecvReq_Type)
		ENUM_TO_STRING(MessageType::AddFriendRecvRsp_Type)
		ENUM_TO_STRING(MessageType::AddFriendNotifyReq_Type)
		ENUM_TO_STRING(MessageType::AddFriendNotifyRsp_Type)
		ENUM_TO_STRING(MessageType::RemoveFriendReq_Type)
		ENUM_TO_STRING(MessageType::RemoveFriendRsp_Type)
		ENUM_TO_STRING(MessageType::GetFriendListReq_Type)
		ENUM_TO_STRING(MessageType::GetFriendListRsp_Type)
		ENUM_TO_STRING(MessageType::GetGroupListReq_Type)
		ENUM_TO_STRING(MessageType::GetGroupListRsp_Type)
		ENUM_TO_STRING(MessageType::NetFailedReport_Type)
		ENUM_TO_STRING(MessageType::NetRecoverReport_Type)
		ENUM_TO_STRING(MessageType::AddTeamReq_Type)
		ENUM_TO_STRING(MessageType::AddTeamRsp_Type)
		ENUM_TO_STRING(MessageType::RemoveTeamReq_Type)
		ENUM_TO_STRING(MessageType::RemoveTeamRsp_Type)
		ENUM_TO_STRING(MessageType::AddFriendToTeamReq_Type)
		ENUM_TO_STRING(MessageType::AddFriendToTeamRsp_Type)
		ENUM_TO_STRING(MessageType::MoveFriendToTeamReq_Type)
		ENUM_TO_STRING(MessageType::MoveFriendToTeamRsp_Type)
		ENUM_TO_STRING(MessageType::ModifyTeamNameReq_Type)
		ENUM_TO_STRING(MessageType::ModifyTeamNameRsp_Type)
		ENUM_TO_STRING(MessageType::CreateGroupReq_Type)
		ENUM_TO_STRING(MessageType::CreateGroupRsp_Type)
		ENUM_TO_STRING(MessageType::DestroyGroupReq_Type)
		ENUM_TO_STRING(MessageType::DestroyGroupRsp_Type)
		ENUM_TO_STRING(MessageType::FindGroupReq_Type)
		ENUM_TO_STRING(MessageType::FindGroupRsp_Type)
		ENUM_TO_STRING(MessageType::AddToGroupReq_Type)
		ENUM_TO_STRING(MessageType::AddToGroupRsp_Type)
		ENUM_TO_STRING(MessageType::AddToGroupRecvReq_Type)
		ENUM_TO_STRING(MessageType::AddToGroupRecvRsp_Type)
		ENUM_TO_STRING(MessageType::AddToGroupNotifyReq_Type)
		ENUM_TO_STRING(MessageType::AddToGroupNotifyRsp_Type)
		ENUM_TO_STRING(MessageType::InviteFriendToGroupReq_Type)
		ENUM_TO_STRING(MessageType::InviteFriendToGroupRsp_Type)
		ENUM_TO_STRING(MessageType::InviteToGroupRecvReq_Type)
		ENUM_TO_STRING(MessageType::InviteToGroupRecvRsp_Type)
		ENUM_TO_STRING(MessageType::InviteResultNotifyReq_Type)
		ENUM_TO_STRING(MessageType::InviteResultNotifyRsp_Type)
		ENUM_TO_STRING(MessageType::SendGroupTextMsgReq_Type)
		ENUM_TO_STRING(MessageType::SendGroupTextMsgRsp_Type)
		ENUM_TO_STRING(MessageType::RecvGroupTextMsgReq_Type)
		ENUM_TO_STRING(MessageType::RecvGroupTextMsgRsp_Type)
		ENUM_TO_STRING(MessageType::QuitGroupReq_Type)
		ENUM_TO_STRING(MessageType::QuitGroupRsp_Type)
	default:
		{
			return "UNKNOWN";
		}break;
	}
}


std::string ErrMsg(const ERROR_CODE_TYPE& errCode) {
	switch (errCode)
	{
		ENUM_TO_STRING(ERROR_CODE_TYPE::E_CODE_SUCCEED)

		//ͨ�ô���
		ENUM_TO_STRING(ERROR_CODE_TYPE::E_CODE_CONNECT_FAILED)

		//�û�ע�������
		ENUM_TO_STRING(ERROR_CODE_TYPE::E_CODE_USER_HAS_EXIST)
		//
		ENUM_TO_STRING(ERROR_CODE_TYPE::E_CODE_LOGIN_FAILED)
		ENUM_TO_STRING(ERROR_CODE_TYPE::E_CODE_NO_SUCH_USER)
		ENUM_TO_STRING(ERROR_CODE_TYPE::E_CODE_USER_NAME_PASS_WORD_NOT_MATCH)
		ENUM_TO_STRING(ERROR_CODE_TYPE::E_CODE_VERIFY_CODE_NOT_MATCH)
		default:
		{
			return "UNKNOWN_ERROR";
		}break;
	}
}
std::string   ChatType(const CHAT_MSG_TYPE& chatType)
{
	switch (chatType)
	{
	case CHAT_MSG_TYPE::E_CHAT_TEXT_TYPE:
	{
		return "E_CHAT_TEXT_TYPE";
	}break;
	case CHAT_MSG_TYPE::E_CHAT_EMOJI_TYPE:
	{
		return "E_CHAT_EMOJI_TYPE";
	}break;
	case CHAT_MSG_TYPE::E_CHAT_IMAGE_TYPE:
	{
		return "E_CHAT_IMAGE_TYPE";
	}break;
	case CHAT_MSG_TYPE::E_CHAT_FILE_TYPE:
	{
		return "E_CHAT_FILE_TYPE";
	}break;
	default:
	{
		return "E_CHAT_UNKNOWN_TYPE";
	}break;

	}
}
CHAT_MSG_TYPE ChatType(const std::string strType)
{
	if ("E_CHAT_TEXT_TYPE" == strType)
	{
		return CHAT_MSG_TYPE::E_CHAT_TEXT_TYPE;
	}
	else if ("E_CHAT_IMAGE_TYPE" == strType) {
		return CHAT_MSG_TYPE::E_CHAT_IMAGE_TYPE;
	}
	else if ("E_CHAT_EMOJI_TYPE" == strType) {
		return CHAT_MSG_TYPE::E_CHAT_EMOJI_TYPE;
	}
	else if ("E_CHAT_FILE_TYPE" == strType) {
		return CHAT_MSG_TYPE::E_CHAT_FILE_TYPE;
	}
	else {
		return CHAT_MSG_TYPE::E_CHAT_UNKNOWN_TYPE;
	}
}


std::string StringToHex(const std::string& input)
{
	static const char* const lut = "0123456789ABCDEF";
	size_t len = input.length();

	std::string output;
	output.reserve(2 * len);
	for (size_t i = 0; i < len; ++i)
	{
		const unsigned char c = input[i];
		output.push_back(lut[c >> 4]);
		output.push_back(lut[c & 15]);
	}
	return output;
}

#include <algorithm>
#include <stdexcept>

std::string HexToString(const std::string& input)
{
	static const char* const lut = "0123456789ABCDEF";
	size_t len = input.length();
	if (len & 1) throw std::invalid_argument("odd length");

	std::string output;
	output.reserve(len / 2);
	for (size_t i = 0; i < len; i += 2)
	{
		char a = input[i];
		const char* p = std::lower_bound(lut, lut + 16, a);
		if (*p != a) throw std::invalid_argument("not a hex digit");

		char b = input[i + 1];
		const char* q = std::lower_bound(lut, lut + 16, b);
		if (*q != b) throw std::invalid_argument("not a hex digit");

		output.push_back(static_cast<char>(((p - lut) << 4) | (q - lut)));
	}
	return output;
}


CLIENT_ONLINE_TYPE OnLineType(const std::string strType)
{
	if (strType == "ON_LINE")
	{
		return CLIENT_ONLINE_TYPE::C_ONLINE_TYPE_ONLINE;
	}
	else
	{
		return CLIENT_ONLINE_TYPE::C_ONLINE_TYPE_OFFLINE;
	}
}

std::string OnLineType(const CLIENT_ONLINE_TYPE onLineType)
{
	switch (onLineType)
	{
	case CLIENT_ONLINE_TYPE::C_ONLINE_TYPE_ONLINE:
	{
		return "ON_LINE";
	}break;
	default:
	{
		return "OFF_LINE";
	}break;
	}
}