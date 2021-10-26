#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>
#include "CMySqlConnect.h"
#include "CommonMsg.h"
#include "SnowFlake/SnowFlake.h"
#include "../../MediumServer/EncodingUtil.h"
static SnowFlake g_flake(4,4);

std::string UserID() {
	return std::to_string(g_flake.nextId() % 100000000);
}

std::string MsgId() {
	return std::to_string(g_flake.nextId());
}
TEST_CASE("DataBaseConnect") {
	CMySqlConnect sqlUtil;
	CHECK(sqlUtil.ConnectToServer("admin", "admin", "imdev", "127.0.0.1"));
}

TEST_CASE("T_USER") {
	CMySqlConnect sqlUtil;
	CHECK(sqlUtil.ConnectToServer("admin", "admin", "imdev", "127.0.0.1"));
	{
		T_USER_BEAN bean;
		bean.m_strF_USER_ID = UserID();
		//�ڲ������ݿ�֮ǰ��û�д��û�
		CHECK_FALSE(sqlUtil.IsUserExist(bean.m_strF_USER_ID));
		
		bean.m_strF_USER_NAME = UserID();

		T_USER_BEAN oldBean;
		CHECK_FALSE(sqlUtil.SelectUserByName(bean.m_strF_USER_NAME, oldBean));
		bean.m_strF_PASS_WORD = bean.m_strF_USER_ID;
		bean.m_strF_NICK_NAME = bean.m_strF_USER_ID;

		CHECK(sqlUtil.InsertUser(bean));

		//�������ݿ��Ժ󣬴��û�����
		CHECK(sqlUtil.IsUserExist(bean.m_strF_USER_ID));
		//���û�����ѯ�����û�������
		CHECK_FALSE(sqlUtil.IsUserExist(bean.m_strF_USER_NAME));

		CHECK(sqlUtil.DeleteUser(bean.m_strF_USER_ID));
		//TODO: Mysql ���û������ڵ�����£�ִ��Delete��Ȼ����True����Ҫ�ٿ���Mysql���ĵ�
		//CHECK_FALSE(sqlUtil.DeleteUser(bean.m_strF_USER_ID));
		CHECK_FALSE(sqlUtil.IsUserExist(bean.m_strF_USER_ID));
	}
}


TEST_CASE("T_FRIEND_CHAT_MSG") {
	CMySqlConnect sqlUtil;
	sqlUtil.ConnectToServer("admin", "admin", "imdev", "127.0.0.1");
	
	SUBCASE("DataBaseInsertChatMsgEnglishOrg") {
		T_USER_CHAT_MSG msgBean;
		msgBean.m_strF_MSG_ID = std::to_string(g_flake.nextId());
		msgBean.m_strF_FROM_ID = UserID();
		msgBean.m_strF_TO_ID = UserID();
		msgBean.m_eChatMsgType = CHAT_MSG_TYPE::E_CHAT_TEXT_TYPE;
		msgBean.m_strF_READ_FLAG = "UNREAD";
		//msgBean.m_strF_MSG_CONTEXT = EncodeUtil::AnsiToUtf8("Good");
		CHECK(sqlUtil.InsertFriendChatMsg(msgBean));
	}

	SUBCASE("DataBaseInsertChatMsgChineseOrg"){
		T_USER_CHAT_MSG msgBean;
		msgBean.m_strF_MSG_ID = std::to_string(g_flake.nextId());
		msgBean.m_strF_FROM_ID = UserID();
		msgBean.m_strF_TO_ID = UserID();
		msgBean.m_eChatMsgType = CHAT_MSG_TYPE::E_CHAT_TEXT_TYPE;
		msgBean.m_strF_READ_FLAG = "UNREAD";
		//msgBean.m_strF_MSG_CONTEXT = EncodeUtil::AnsiToUtf8("�й�����");
		CHECK(sqlUtil.InsertFriendChatMsg(msgBean));
	}

	SUBCASE("DataBaseInsertChatMsgChinese") {
		T_USER_CHAT_MSG msgBean;
		msgBean.m_strF_MSG_ID = std::to_string(g_flake.nextId());
		msgBean.m_strF_FROM_ID = UserID();
		msgBean.m_strF_TO_ID = UserID();
		msgBean.m_eChatMsgType = CHAT_MSG_TYPE::E_CHAT_TEXT_TYPE;
		msgBean.m_strF_READ_FLAG = "UNREAD";
		msgBean.m_strF_MSG_CONTEXT = u8"�й�����";
		CHECK(sqlUtil.InsertFriendChatMsg(msgBean));
	}

	SUBCASE("DataBaseInsertChatMsgEnglish") {
		T_USER_CHAT_MSG msgBean;
		msgBean.m_strF_MSG_ID = std::to_string(g_flake.nextId());
		msgBean.m_strF_FROM_ID = UserID();
		msgBean.m_strF_TO_ID = UserID();
		msgBean.m_eChatMsgType = CHAT_MSG_TYPE::E_CHAT_TEXT_TYPE;
		msgBean.m_strF_READ_FLAG = "UNREAD";
		msgBean.m_strF_MSG_CONTEXT = "Good";
		CHECK(sqlUtil.InsertFriendChatMsg(msgBean));
	}
}

TEST_CASE("T_FRIEND_CHAT_MSG_CHAT") {
	CMySqlConnect sqlUtil;
	sqlUtil.ConnectToServer("admin", "admin", "imdev", "127.0.0.1");
	std::string strUserId = UserID();
	std::string strFriendId = UserID();
}

TEST_CASE("T_ADD_FRIEND_MSG") {
	CMySqlConnect sqlUtil;
	sqlUtil.ConnectToServer("admin", "admin", "imdev", "127.0.0.1");

	std::string strUserId = UserID();
	std::string strFriendId = UserID();
	std::string strMsgId = MsgId();
	{
		T_ADD_FRIEND_MSG_BEAN msgBean;
		msgBean.m_eF_ADD_FRIEND_STATUS = E_ADD_FRIEND_STATUS::E_UN_READ;
		msgBean.m_strF_USER_ID = strUserId;
		msgBean.m_strF_FRIEND_ID = strFriendId;
		msgBean.m_strF_MSG_ID = strMsgId;
		CHECK(sqlUtil.InsertAddFriendMsg(msgBean));
	}
	
	{
		T_ADD_FRIEND_MSG_BEAN msgBean;
		CHECK(sqlUtil.SelectUnReadAddFriendMsg(strFriendId, msgBean));
		CHECK_EQ(msgBean.m_strF_MSG_ID, strMsgId);
		//CHECK_EQ(msgBean.m_strF_USER_ID, strUserId);
	}

	{
		CHECK(sqlUtil.UpdateToReadUnNotifyAddFriendMsg(strMsgId, E_FRIEND_OPTION::E_REFUSE_ADD));
	}

	{
		CHECK(sqlUtil.UpdateToNotifyAddFriendMsg(strMsgId));
	}
}


TEST_CASE("T_FRIEND_RELATION") {
	CMySqlConnect sqlUtil;
	sqlUtil.ConnectToServer("admin", "admin", "imdev", "127.0.0.1");

	std::string strUserId = UserID();
	std::string strFriendId = UserID();
	
	//IsFriend
	{
		CHECK_FALSE(sqlUtil.IsFriend(strUserId, strFriendId));
	}

	//Add Friend
	{
		CHECK(sqlUtil.InsertFriendRelation(strUserId, strFriendId, E_FRIEND_RELATION::E_FRIEND_TYPE));
		CHECK(sqlUtil.InsertFriendRelation(strFriendId, strUserId, E_FRIEND_RELATION::E_FRIEND_TYPE));
	}

	//IsFriend
	{
		CHECK(sqlUtil.IsFriend(strUserId, strFriendId));
	}
}


TEST_CASE("T_GROUP_CHAT_TXT_MSG") {
	CMySqlConnect sqlUtil;
	sqlUtil.ConnectToServer("admin", "admin", "imdev", "127.0.0.1");

	std::string strUserId = UserID();
	std::string strGroupId = UserID();
	std::string strMsgId = MsgId();
	std::string strNewMsgId = MsgId();
	{
		T_GROUP_CHAT_MSG msgBean;
		msgBean.m_strF_MSG_ID = strNewMsgId;
		msgBean.m_strF_SENDER_ID = strUserId;
		msgBean.m_strF_GROUP_ID = strGroupId;
		msgBean.m_strF_MSG_CONTEXT = "GROUP_CHAT";
		msgBean.m_strF_OTHER_INFO = "OTHER_INFO";
		msgBean.m_eChatMsgType = CHAT_MSG_TYPE::E_CHAT_TEXT_TYPE;
		CHECK(sqlUtil.InsertGroupChatText(msgBean));
		//CHECK(sqlUtil.InsertGroupChatMsg(msgBean));
	}

	{
		T_GROUP_CHAT_MSG msgBean;
		msgBean.m_strF_MSG_ID = strMsgId;
		msgBean.m_strF_GROUP_ID = strGroupId;
		CHECK(sqlUtil.SelectGroupChatText(msgBean));
		CHECK_EQ(msgBean.m_strF_MSG_ID, strNewMsgId);
		//CHECK_EQ(msgBean.m_strF_USER_ID, strUserId);
	}
}



