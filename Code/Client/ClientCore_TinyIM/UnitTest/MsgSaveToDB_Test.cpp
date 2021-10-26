#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>
#include "CommonMsg.h"
#include "CMsgPersistentUtil.h"

static CMsgPersistentUtil util;
TEST_CASE("FriendChatRecvTextMsgInsert") {
	util.InitDataBase();
	FriendChatRecvTxtReqMsg reqMsg;
	reqMsg.m_strMsgId = "123456768";
	reqMsg.m_strFromId = "11111111";
	reqMsg.m_strToId = "22222222";
	reqMsg.m_strContext = "TEXT";
	util.Save_FriendChatRecvTxtReqMsg(reqMsg);
	FriendChatRecvTxtReqMsg recvMsg;
	util.Get_FriendChatRecvTxtReqMsg(recvMsg);
	std::cout << recvMsg.ToString() << std::endl;
	util.Update_FriendChatRecvTxtReqMsg(recvMsg);
}

TEST_CASE("GroupChatRecvTextMsgInsert") {
	util.InitDataBase();
	RecvGroupTextMsgReqMsg reqMsg;
	reqMsg.m_strMsgId = "123456768";
	reqMsg.m_strGroupId = "11111111";
	reqMsg.m_strSenderId = "22222222";
	reqMsg.m_strContext = "TEXT";
	CHECK(util.Save_RecvGroupTextMsgReqMsg(reqMsg));
	RecvGroupTextMsgReqMsg recvMsg;
	CHECK(util.Get_RecvGroupTextMsgReqMsg(recvMsg));
	std::cout << recvMsg.ToString() << std::endl;
	CHECK(util.Update_RecvGroupTextMsgReqMsg(recvMsg));
    
}