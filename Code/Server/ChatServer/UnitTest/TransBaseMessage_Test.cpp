
#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>
#include "CommonMsg.h"
#include "../../MediumServer/EncodingUtil.h"


TEST_CASE("KeepAliveReqBase") {
    KeepAliveReqMsg reqMsg("UnitTest");
    KeepAliveReqMsg parseMsg;
    CHECK_EQ(true,parseMsg.FromString(reqMsg.ToString()));
    CHECK_EQ(reqMsg.ToString(),parseMsg.ToString());
    
}

TEST_CASE("KeepAliveReqBase") {
    KeepAliveReqMsg reqMsg("UnitTest");
    std::shared_ptr<TransBaseMsg_t> pMsg = std::make_shared<TransBaseMsg_t>(reqMsg.GetMsgType(),reqMsg.ToString());
    CHECK_EQ(reqMsg.GetMsgType(),pMsg->GetType());
    CHECK_EQ(reqMsg.ToString().length()+8,pMsg->GetSize());
    KeepAliveReqMsg parseMsg;

    CHECK_EQ(reqMsg.ToString(),pMsg->to_string());
    CHECK_EQ(true,parseMsg.FromString(pMsg->to_string()));
    CHECK_EQ(reqMsg.ToString(),parseMsg.ToString());
    
}

TEST_CASE("GetFriendListRsp") {
	GetFriendListRspMsg rspMsg;
	
	std::shared_ptr<TransBaseMsg_t> pMsg = std::make_shared<TransBaseMsg_t>(rspMsg.GetMsgType(), rspMsg.ToString());
	CHECK_EQ(rspMsg.GetMsgType(), pMsg->GetType());
	CHECK_EQ(rspMsg.ToString().length() + 8, pMsg->GetSize());
	GetFriendListRspMsg newRsp;
	CHECK(newRsp.FromString(pMsg->to_string()));
}

TEST_CASE("NetFailedReportMsg") {
	NetFailedReportMsg reqMsg("UnitTest");
	NetFailedReportMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
}

TEST_CASE("NetRecoverReportMsg") {
	NetRecoverReportMsg reqMsg("UnitTest");
	NetRecoverReportMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
}

TEST_CASE("UserLoginReqMsg") {
	UserLoginReqMsg reqMsg;
	reqMsg.m_strUserName = "UserLoginReqMsg";
	reqMsg.m_strPassword = "UserLoginReqMsg";
	reqMsg.m_strMsgId = "1234567890";
	UserLoginReqMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
	CHECK(parseMsg.Valid());
}


TEST_CASE("UserLoginRspMsg") {
	UserLoginRspMsg reqMsg;
	UserLoginRspMsg parseMsg;

	reqMsg.m_strUserName = "UserLoginRspMsg";
	reqMsg.m_strUserId = "12345678";
	reqMsg.m_strMsgId = "1234567890";
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
	CHECK(parseMsg.Valid());
}

TEST_CASE("UserLogoutReqMsg") {
	UserLogoutReqMsg reqMsg;
	reqMsg.m_strUserName = "UserLogoutReqMsg";
	reqMsg.m_strPassword = "UserLogoutReqMsg";
	reqMsg.m_strMsgId = "1234567890";
	UserLogoutReqMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
	CHECK(parseMsg.Valid());
}


TEST_CASE("UserLogoutRspMsg") {
	UserLogoutRspMsg reqMsg;
	reqMsg.m_strMsgId = "1234567890";
	reqMsg.m_strUserName = "UserLogoutRspMsg";
	UserLogoutRspMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
	CHECK(parseMsg.Valid());
}

TEST_CASE("UserRegisterReqMsg") {
	UserRegisterReqMsg reqMsg;
	
	reqMsg.m_strUserName = "UserRegisterReqMsg";
	reqMsg.m_strPassword = "UserRegisterReqMsg";
	reqMsg.m_strNickName = "UserRegisterReqMsg";
	reqMsg.m_strMsgId = "1234567890";
	UserRegisterReqMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
	CHECK(parseMsg.Valid());
}

TEST_CASE("UserRegisterRspMsg") {
	UserRegisterRspMsg reqMsg;

	reqMsg.m_strUserName = "UserRegisterRspMsg";
	reqMsg.m_strMsgId = "1234567890";

	UserRegisterRspMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
	CHECK(parseMsg.Valid());
}

TEST_CASE("UserUnRegisterReqMsg") {
	UserUnRegisterReqMsg reqMsg;
	
	reqMsg.m_strMsgId = "01234567890";
	reqMsg.m_strUserName = "UserUnRegisterReqMsg";
	reqMsg.m_strPassword = "UserUnRegisterReqMsg";
	reqMsg.m_strVerifyCode = "UserUnRegisterReqMsg";
	UserUnRegisterReqMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
	CHECK(parseMsg.Valid());
}

TEST_CASE("UserUnRegisterRspMsg") {
	UserUnRegisterRspMsg reqMsg;

	reqMsg.m_strMsgId = "1234567890";
	reqMsg.m_strUserName = "UserUnRegisterRspMsg";
	UserUnRegisterRspMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
	CHECK(reqMsg.Valid());
}

TEST_CASE("FriendChatSendTxtReqMsg") {
	FriendChatSendTxtReqMsg reqMsg;

	reqMsg.m_strMsgId = "1234567890";
	reqMsg.m_strSenderId = "FriendChatSendTxtReqMsg";
	reqMsg.m_strReceiverId = "FriendChatSendTxtReqMsg";
	reqMsg.m_strContext = "FriendChatSendTxtReqMsg";

	FriendChatSendTxtReqMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
	CHECK(parseMsg.Valid());
}

TEST_CASE("FriendChatSendTxtRspMsg") {
	FriendChatSendTxtRspMsg reqMsg;

	reqMsg.m_strMsgId = "1234567890";
	reqMsg.m_strSenderId = "654321";
	reqMsg.m_strReceiverId = "123456";

	FriendChatSendTxtRspMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
	CHECK(parseMsg.Valid());
}

TEST_CASE("FriendChatRecvTxtReqMsg") {
	FriendChatRecvTxtReqMsg reqMsg;

	reqMsg.m_strMsgId = "1234567890";
	reqMsg.m_strFromId = "FriendChatRecvTxtReqMsg";
	reqMsg.m_strToId = "FriendChatRecvTxtReqMsg";
	reqMsg.m_strContext = "FriendChatRecvTxtReqMsg";
	FriendChatRecvTxtReqMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
	CHECK(parseMsg.Valid());
}

TEST_CASE("FriendChatRecvTxtRspMsg") {
	FriendChatRecvTxtRspMsg reqMsg;

	reqMsg.m_strMsgId = "1234567890";
	reqMsg.m_strFromId = "12345678";
	reqMsg.m_strToId = "12345678";

	FriendChatRecvTxtRspMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
	CHECK(parseMsg.Valid());
}

TEST_CASE("GetFriendListReqMsg") {
	GetFriendListReqMsg reqMsg;

	reqMsg.m_strMsgId = "1234567890";
	reqMsg.m_strUserId = "12345678";

	GetFriendListReqMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
	CHECK(parseMsg.Valid());
}

TEST_CASE("GetFriendListRspMsg") {
	GetFriendListRspMsg reqMsg;
	GetFriendListRspMsg parseMsg;

	reqMsg.m_strUserId = "12345678";
	reqMsg.m_strMsgId = "11111111";
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
	CHECK(parseMsg.Valid());
}

TEST_CASE("FriendChatRecvTxtReqMsg") {
	FriendChatRecvTxtReqMsg reqMsg;

	reqMsg.m_strMsgId = "1234567890";
	reqMsg.m_strFromId = "12322222";
	reqMsg.m_strToId = "33333333";
	reqMsg.m_strContext = "FriendChatRecvTxtReqMsg";

	FriendChatRecvTxtReqMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
	CHECK(parseMsg.Valid());
}

TEST_CASE("AddFriendSendReqMsg") {
	AddFriendSendReqMsg reqMsg;

	reqMsg.m_strMsgId = "12345678";
	reqMsg.m_strUserId = "12345678";
	reqMsg.m_strFriendId = "22222222";
	AddFriendSendReqMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
	CHECK(parseMsg.Valid());
}

TEST_CASE("AddFriendSendRspMsg") {
	AddFriendSendRspMsg reqMsg;

	reqMsg.m_strMsgId = "12345678";
	reqMsg.m_strUserId = "234234234";
	reqMsg.m_strFriendId = "222333344";

	AddFriendSendRspMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());

	CHECK(parseMsg.Valid());
}

TEST_CASE("AddFriendRecvReqMsg") {
	AddFriendRecvReqMsg reqMsg;

	reqMsg.m_strMsgId = "1234234234";
	reqMsg.m_strUserId = "2342342342";
	reqMsg.m_strFriendId = "223423423423";

	AddFriendRecvReqMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
	CHECK(parseMsg.Valid());
}

TEST_CASE("FriendChatRecvTxtReqMsg") {
	AddFriendRecvRspMsg reqMsg;
	
	reqMsg.m_strMsgId = "12345678";
	reqMsg.m_strUserId = "12345";
	reqMsg.m_strFriendId = "2342342";
	
	AddFriendRecvRspMsg parseMsg;



	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
	CHECK(parseMsg.Valid());
}

TEST_CASE("FriendChatRecvTxtReqMsg") {
	AddFriendRecvRspMsg reqMsg;

	reqMsg.m_strMsgId = "12345678";
	reqMsg.m_strUserId = "12345678";
	reqMsg.m_strFriendId = "FriendId";

	AddFriendRecvRspMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
	CHECK(parseMsg.Valid());
}

TEST_CASE("FriendChatRecvTxtReqMsg") {
	AddFriendRecvRspMsg reqMsg;
	AddFriendRecvRspMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
}

TEST_CASE("FriendChatRecvTxtReqMsg") {
	AddFriendRecvRspMsg reqMsg;
	AddFriendRecvRspMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
}

TEST_CASE("AddFriendNotifyReqMsg") {
	AddFriendNotifyReqMsg reqMsg;

	reqMsg.m_strMsgId = "1234234";
	reqMsg.m_strUserId = "22222222";
	reqMsg.m_strFriendId = "3333333";
	AddFriendNotifyReqMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
	CHECK(parseMsg.Valid());
}

TEST_CASE("AddFriendNotifyRspMsg") {
	AddFriendNotifyRspMsg reqMsg;

	reqMsg.m_strMsgId = "12345342";
	AddFriendNotifyRspMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
	CHECK(parseMsg.Valid());
}

TEST_CASE("RemoveFriendReqMsg") {
	RemoveFriendReqMsg reqMsg;

	reqMsg.m_strMsgId = "12345678";
	reqMsg.m_strUserId = "22222222";
	reqMsg.m_strFriendId = "33333333";

	RemoveFriendReqMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
	CHECK(parseMsg.Valid());
}

TEST_CASE("RemoveFriendRspMsg") {
	
	RemoveFriendRspMsg reqMsg;

	reqMsg.m_strMsgId = "12345678";
	reqMsg.m_strUserId = "22222222";
	reqMsg.m_strFriendId = "33333333";

	RemoveFriendRspMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());

	CHECK(parseMsg.Valid());
}

TEST_CASE("FindFriendReqMsg") {
	FindFriendReqMsg reqMsg;

	reqMsg.m_strMsgId = "12345678";
	reqMsg.m_strUserId = "22222222";
	reqMsg.m_strWantedName = "Wanted3333";

	FindFriendReqMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());

	CHECK(parseMsg.Valid());
}

TEST_CASE("FindFriendRspMsg") {
	FindFriendRspMsg reqMsg;
	UserBaseInfo baseInfo;
	reqMsg.m_friendInfoVec.push_back(baseInfo);
	reqMsg.m_friendInfoVec.push_back(baseInfo);
	FindFriendRspMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
}

TEST_CASE("AddTeamReqMsg") {
	AddTeamReqMsg reqMsg;
	AddTeamReqMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
}

TEST_CASE("AddTeamRspMsg") {
	AddTeamRspMsg reqMsg;
	AddTeamRspMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
}

TEST_CASE("RemoveTeamReqMsg") {
	RemoveTeamReqMsg reqMsg;
	RemoveTeamReqMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
}

TEST_CASE("RemoveTeamRspMsg") {
	RemoveTeamRspMsg reqMsg;
	RemoveTeamRspMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
}

TEST_CASE("MoveFriendToTeamReqMsg") {
	MoveFriendToTeamReqMsg reqMsg;
	MoveFriendToTeamReqMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
}

TEST_CASE("MoveFriendToTeamRspMsg") {
	MoveFriendToTeamRspMsg reqMsg;
	MoveFriendToTeamRspMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
}

TEST_CASE("CreateGroupReqMsg") {
	CreateGroupReqMsg reqMsg;
	reqMsg.m_strMsgId = "1234567890";
	reqMsg.m_strGroupName = "CreateGroup";
	reqMsg.m_strUserId = "12345678";
	CreateGroupReqMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
	CHECK(parseMsg.Valid());
}

TEST_CASE("CreateGroupRspMsg") {
	CreateGroupRspMsg reqMsg;
	reqMsg.m_strMsgId = "1234567890";

	reqMsg.m_strGroupId = "GroupId";
	reqMsg.m_strUserId = "UserName";
	reqMsg.m_strGroupName = "GroupName";

	CreateGroupRspMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
	CHECK(parseMsg.Valid());
}

TEST_CASE("DestroyGroupReqMsg") {
	DestroyGroupReqMsg reqMsg;

	reqMsg.m_strGroupId = "12345678";
	reqMsg.m_strMsgId = "1234567890124";
	reqMsg.m_strGroupName = "HelloWorld";
	reqMsg.m_strUserId = "Hello";

	DestroyGroupReqMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
	CHECK(parseMsg.Valid());
}

TEST_CASE("DestroyGroupRspMsg") {
	
	DestroyGroupRspMsg reqMsg;

	reqMsg.m_strMsgId = "1234567890";
	reqMsg.m_strGroupName = "HelloWorld";
	reqMsg.m_strGroupId = "1234234";
	reqMsg.m_strUserId = "234234";

	DestroyGroupRspMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
	CHECK(parseMsg.Valid());
}

TEST_CASE("RemoveTeamReqMsg") {
	FindGroupReqMsg reqMsg;

	reqMsg.m_strMsgId = "12345678";
	reqMsg.m_strGroupName = "nihao";
	reqMsg.m_strUserId = "word";

	FindGroupReqMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
	CHECK(parseMsg.Valid());
}

TEST_CASE("FindGroupRspMsg") {
	
	FindGroupRspMsg reqMsg;
	
	reqMsg.m_strMsgId = "1234234234";
	reqMsg.m_strGroupId = "1234234";
	reqMsg.m_strGroupName = "nihao";
	reqMsg.m_strGroupOwner = "nihao2";
	reqMsg.m_strUserId = "woshi";

	FindGroupRspMsg parseMsg;

	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
	CHECK(parseMsg.Valid());
}

TEST_CASE("AddToGroupReqMsg") {
	AddToGroupReqMsg reqMsg;

	reqMsg.m_strGroupId = "22222222";
	reqMsg.m_strMsgId = "2234234234";
	reqMsg.m_strUserId = "nihao";
	AddToGroupReqMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
	CHECK(parseMsg.Valid());
}

TEST_CASE("AddToGroupRspMsg") {
	AddToGroupRspMsg reqMsg;

	reqMsg.m_strMsgId = "123456789";
	reqMsg.m_strGroupId = "22222222";
	reqMsg.m_strUserId = "UserName";
	AddToGroupRspMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
	CHECK(parseMsg.Valid());
}


TEST_CASE("AddToGroupRecvReqMsg") {
	AddToGroupRecvReqMsg reqMsg;

	reqMsg.m_strAdminId = "Admin";
	reqMsg.m_strMsgId = "12345678";
	reqMsg.m_strGroupId = "GroupId";
	reqMsg.m_strUserId = "UserName";
	AddToGroupRecvReqMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());

	CHECK(parseMsg.Valid());
}


TEST_CASE("AddToGroupRecvRspMsg") {
	AddToGroupRecvRspMsg reqMsg;

	reqMsg.m_strGroupId = "12345678";
	reqMsg.m_strAdminId = "Admin";
	reqMsg.m_strUserId = "UserName";
	AddToGroupRecvRspMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
	CHECK(parseMsg.Valid());
}


TEST_CASE("AddToGroupNotifyReqMsg") {
	AddToGroupNotifyReqMsg reqMsg;

	reqMsg.m_strMsgId = "12345678";
	reqMsg.m_strGroupId = "GroupId";
	reqMsg.m_strUserId = "UserName";
	AddToGroupNotifyReqMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());

	CHECK(parseMsg.Valid());
}

TEST_CASE("AddToGroupNotifyRspMsg") {
	AddToGroupNotifyRspMsg reqMsg;

	reqMsg.m_strMsgId = "123456767";
	reqMsg.m_strAdminId = "Admin";
	reqMsg.m_strGroupId = "GroupId";
	reqMsg.m_strUserId = "UserName";
	AddToGroupNotifyRspMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
	CHECK(parseMsg.Valid());
}

TEST_CASE("InviteFriendToGroupReqMsg") {
	InviteFriendToGroupReqMsg reqMsg;
	InviteFriendToGroupReqMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
}

TEST_CASE("InviteFriendToGroupRspMsg") {
	InviteFriendToGroupRspMsg reqMsg;
	InviteFriendToGroupRspMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
}

TEST_CASE("InviteFriendToGroupRecvRspMsg") {
	InviteFriendToGroupRecvRspMsg reqMsg;
	InviteFriendToGroupRecvRspMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
}


TEST_CASE("InviteFriendToGroupNotifyReqMsg") {
	InviteFriendToGroupNotifyReqMsg reqMsg;
	InviteFriendToGroupNotifyReqMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
}

TEST_CASE("InviteFriendToGroupNotifyRspMsg") {
	InviteFriendToGroupNotifyRspMsg reqMsg;
	InviteFriendToGroupNotifyRspMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
}

TEST_CASE("SendGroupTextMsgReqMsg") {
	SendGroupTextMsgReqMsg reqMsg;
	SendGroupTextMsgReqMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
}

TEST_CASE("SendGroupTextMsgRspMsg") {
	SendGroupTextMsgRspMsg reqMsg;
	SendGroupTextMsgRspMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
}

TEST_CASE("RecvGroupTextMsgReqMsg") {
	RecvGroupTextMsgReqMsg reqMsg;
	RecvGroupTextMsgReqMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
}

TEST_CASE("RecvGroupTextMsgRspMsg") {
	RecvGroupTextMsgRspMsg reqMsg;
	RecvGroupTextMsgRspMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
}

TEST_CASE("GetGroupListReqMsg") {
	GetGroupListReqMsg reqMsg;
	GetGroupListReqMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
}


TEST_CASE("GetGroupListRspMsg") {
	GetGroupListRspMsg reqMsg;
	GetGroupListRspMsg parseMsg;
	CHECK_EQ(true, parseMsg.FromString(reqMsg.ToString()));
	CHECK_EQ(reqMsg.ToString(), parseMsg.ToString());
}

