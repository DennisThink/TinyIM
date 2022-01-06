#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>
#include "CommonMsg.h"
#include "../../../include/thirdparty/httpServer/client_http.hpp"

using HttpClient = SimpleWeb::Client<SimpleWeb::HTTP>;

std::string g_strUserOne = "TestUser1";
std::string g_strUserTwo = "TestUser2";
std::string g_strGroupOne = "TestGroup1";

UserRegisterRspMsg Do_RegisterUser(HttpClient& client, std::string strUser) {
	UserRegisterRspMsg rspMsg;
	try {
		UserRegisterReqMsg reqMsg;
		reqMsg.m_strMsgId = "3333";
		reqMsg.m_strUserName = strUser;
		reqMsg.m_strPassword = strUser;
		reqMsg.m_strNickName = strUser;
		auto rsp = client.request("POST", "/register_user", reqMsg.ToString());
		std::string strRsp = rsp->content.string();
		std::cout << strRsp << std::endl;
		CHECK(rspMsg.FromString(strRsp));

	}
	catch (const SimpleWeb::system_error& e) {
		std::cerr << "Client Req Error " << e.what() << std::endl;
	}

	return rspMsg;
}
void RegisterUser(HttpClient& client,std::string strUser) {
	UserRegisterRspMsg rspMsg = Do_RegisterUser(client, strUser);
	CHECK_EQ(ERROR_CODE_TYPE::E_CODE_SUCCEED, rspMsg.m_eErrCode);
}

UserUnRegisterRspMsg Do_UnRegisterUser(HttpClient& client, std::string strUser) {
	UserUnRegisterRspMsg rspMsg;
	try {
		UserUnRegisterReqMsg reqMsg;
		reqMsg.m_strMsgId = "3333";
		reqMsg.m_strUserName = strUser;
		reqMsg.m_strPassword = strUser;
		auto rsp = client.request("POST", "/un_register_user", reqMsg.ToString());
		std::string strRsp = rsp->content.string();
		std::cout << strRsp << std::endl;

		
		CHECK(rspMsg.FromString(strRsp));
	

	}
	catch (const SimpleWeb::system_error& e) {
		std::cerr << "Client Req Error " << e.what() << std::endl;
	}

	return rspMsg;
}


void UnRegisterUser(HttpClient& client, std::string strUser) {
	//UnRegister Twice
	UserUnRegisterRspMsg rspMsg = Do_UnRegisterUser(client, strUser);
	CHECK_EQ(ERROR_CODE_TYPE::E_CODE_SUCCEED, rspMsg.m_eErrCode);
}

UserLoginRspMsg Do_UserLogin(HttpClient& client, std::string strUser) {
	UserLoginRspMsg rspMsg;
	try {
		UserLoginReqMsg reqMsg;
		reqMsg.m_strMsgId = "3333";
		reqMsg.m_strUserName = strUser;
		reqMsg.m_strPassword = strUser;
		reqMsg.m_eNetType = CLIENT_NET_TYPE::C_NET_TYPE_WIFI;
		reqMsg.m_eOnlineType = CLIENT_ONLINE_TYPE::C_ONLINE_TYPE_ONLINE;
		reqMsg.m_eOsType = CLIENT_OS_TYPE::OS_TYPE_WINDOWS;


		auto rsp = client.request("POST", "/user_login", reqMsg.ToString());
		std::string strRsp = rsp->content.string();
		std::cout << strRsp << std::endl;
		CHECK(rspMsg.FromString(strRsp));
	}
	catch (const SimpleWeb::system_error& e) {
		std::cerr << "Client Req Error " << e.what() << std::endl;
	}

	return rspMsg;
}


void UserLogin(HttpClient& client, std::string strUser) {
	UserLoginRspMsg rspMsg = Do_UserLogin(client, strUser);
	CHECK_EQ(ERROR_CODE_TYPE::E_CODE_SUCCEED, rspMsg.m_eErrCode);
}

UserLogoutRspMsg Do_UserLogout(HttpClient& client, std::string strUser) {
	UserLogoutRspMsg rspMsg;
	try {
		UserLogoutReqMsg reqMsg;
		reqMsg.m_strMsgId = "3333";
		reqMsg.m_strUserName = strUser;
		reqMsg.m_strPassword = strUser;
		reqMsg.m_eOsType = CLIENT_OS_TYPE::OS_TYPE_WINDOWS;


		auto rsp = client.request("POST", "/user_logout", reqMsg.ToString());
		std::string strRsp = rsp->content.string();
		std::cout << strRsp << std::endl;

		
		CHECK(rspMsg.FromString(strRsp));
	}
	catch (const SimpleWeb::system_error& e) {
		std::cerr << "Client Req Error " << e.what() << std::endl;
	}

	return rspMsg;
}

void UserLogout(HttpClient& client, std::string strUser) {
	UserLogoutRspMsg rspMsg=Do_UserLogout(client,strUser);
	CHECK_EQ(ERROR_CODE_TYPE::E_CODE_SUCCEED, rspMsg.m_eErrCode);
}

FindFriendRspMsg Do_FindFriendReq(HttpClient& client, std::string strUser, std::string strFriend) {
	
	FindFriendRspMsg rspMsg;
	try {
		FindFriendReqMsg reqMsg;
		reqMsg.m_strMsgId = "33333333";
		reqMsg.m_strUserId = strUser;
		reqMsg.m_strWantedName = strFriend;


		auto rsp = client.request("POST", "/find_friend", reqMsg.ToString());
		std::string strRsp = rsp->content.string();
		std::cout << strRsp << std::endl;

		
		CHECK(rspMsg.FromString(strRsp));
		CHECK_EQ(ERROR_CODE_TYPE::E_CODE_SUCCEED, rspMsg.m_eErrCode);

	}
	catch (const SimpleWeb::system_error& e) {
		std::cerr << "Client Req Error " << e.what() << std::endl;
	}
	return rspMsg;
}

void FindFriendReq(HttpClient& client, std::string strUser,std::string strFriend) {

	FindFriendRspMsg rspMsg = Do_FindFriendReq(client,strUser,strFriend);

	CHECK_EQ(ERROR_CODE_TYPE::E_CODE_SUCCEED, rspMsg.m_eErrCode);
}

FindGroupRspMsg Do_FindGroupReq(HttpClient& client, std::string strUser, std::string strGroupName) {
	FindGroupRspMsg rspMsg;

	try {
		FindGroupReqMsg reqMsg;
		reqMsg.m_strMsgId = "33333333";
		reqMsg.m_strUserId = strUser;
		reqMsg.m_strGroupName = strGroupName;


		auto rsp = client.request("POST", "/find_group", reqMsg.ToString());
		std::string strRsp = rsp->content.string();
		std::cout << strRsp << std::endl;

		CHECK(rspMsg.FromString(strRsp));

	}
	catch (const SimpleWeb::system_error& e) {
		std::cerr << "Client Req Error " << e.what() << std::endl;
	}

	return rspMsg;
}

void FindGroupReq(HttpClient& client, std::string strUser, std::string strGroupName) {

	FindGroupRspMsg rspMsg = Do_FindGroupReq(client, strUser, strGroupName);
	
	CHECK_EQ(ERROR_CODE_TYPE::E_CODE_SUCCEED, rspMsg.m_eErrCode);

}
AddFriendSendRspMsg Do_SendAddFriendReq(HttpClient& client, std::string strUserId, std::string strFriendId) {
	AddFriendSendRspMsg rspMsg;

	try {
		AddFriendSendReqMsg reqMsg;
		reqMsg.m_strMsgId = "33333333";
		reqMsg.m_strFriendId = strFriendId;
		reqMsg.m_strUserId = strUserId;


		auto rsp = client.request("POST", "/add_friend_req", reqMsg.ToString());
		std::string strRsp = rsp->content.string();
		std::cout << strRsp << std::endl;

		CHECK(rspMsg.FromString(strRsp));

	}
	catch (const SimpleWeb::system_error& e) {
		std::cerr << "Client Req Error " << e.what() << std::endl;
	}

	return rspMsg;
}

void SendAddFriendReq(HttpClient& client, std::string strUserId, std::string strFriendId) {
	AddFriendSendRspMsg rspMsg = Do_SendAddFriendReq(client, strUserId, strFriendId);
}

AddFriendRecvReqMsg Do_GetAddFriendRequire(HttpClient& client, std::string strUserId) {
	AddFriendRecvReqMsg reqMsg;
	auto rsp = client.request("GET", "/get_add_friend_require", reqMsg.ToString());
	std::string strRsp = rsp->content.string();
	std::cout << strRsp << std::endl;
	if (reqMsg.FromString(strRsp))
	{

	}
	return reqMsg;
}
void GetAddFriendRequire(HttpClient& client, std::string strUserId) {
	AddFriendRecvReqMsg reqMsg= Do_GetAddFriendRequire(client,strUserId);
	AddFriendRecvRspMsg rspMsg;
	rspMsg.m_strMsgId = reqMsg.m_strMsgId;
	rspMsg.m_strFriendId = reqMsg.m_strFriendId;
	rspMsg.m_strUserId = reqMsg.m_strUserId;
	rspMsg.m_option = E_FRIEND_OPTION::E_AGREE_ADD;
	auto rsp = client.request("POST", "/on_add_friend_require", rspMsg.ToString());
	std::string strRsp = rsp->content.string();
}

void GetAddFriendNotify(HttpClient& client, std::string strUserId) {
	auto rsp = client.request("GET", "/get_add_friend_notify","");
	std::string strRsp = rsp->content.string();
	AddFriendNotifyReqMsg reqMsg;
	CHECK(reqMsg.FromString(strRsp));
}

RemoveFriendRspMsg Do_RemoveFriend(HttpClient& client, std::string strUserId, std::string strFriendId) {
	RemoveFriendRspMsg rspMsg;
	
	try {
		RemoveFriendReqMsg reqMsg;
		reqMsg.m_strMsgId = "33333333";
		reqMsg.m_strUserId = strUserId;
		reqMsg.m_strFriendId = strFriendId;


		auto rsp = client.request("POST", "/remove_friend", reqMsg.ToString());
		std::string strRsp = rsp->content.string();
		std::cout << strRsp << std::endl;

		CHECK(rspMsg.FromString(strRsp));

	}
	catch (const SimpleWeb::system_error& e) {
		std::cerr << "Client Req Error " << e.what() << std::endl;
	}

	return rspMsg;
}

void RemoveFriend(HttpClient& client, std::string strUserId, std::string strFriendId) {
	RemoveFriendRspMsg rspMsg = Do_RemoveFriend(client,strUserId,strFriendId);
	CHECK_EQ(rspMsg.m_eErrCode, ERROR_CODE_TYPE::E_CODE_SUCCEED);
}

CreateGroupRspMsg Do_CreateGroupReq(HttpClient& client, std::string strUserId, std::string strGroupName) {
	
	CreateGroupRspMsg rspMsg;

	try {
		CreateGroupReqMsg reqMsg;
		reqMsg.m_strMsgId = "33333333";
		reqMsg.m_strUserId = strUserId;
		reqMsg.m_strGroupName = strGroupName;

		auto rsp = client.request("POST", "/create_group", reqMsg.ToString());
		std::string strRsp = rsp->content.string();
		std::cout << strRsp << std::endl;

		CHECK(rspMsg.FromString(strRsp));
	
	}
	catch (const SimpleWeb::system_error& e) {
		std::cerr << "Client Req Error " << e.what() << std::endl;
	}

	return rspMsg;
}


void CreateGroupReq(HttpClient& client, std::string strUser,std::string strGroupName) {
	//UnRegister Twice
	
	CreateGroupRspMsg rspMsg = Do_CreateGroupReq(client, strUser, strGroupName);
	
	CHECK_EQ(rspMsg.m_eErrCode, ERROR_CODE_TYPE::E_CODE_SUCCEED);

}

DestroyGroupRspMsg Do_DestroyGroupReq(HttpClient& client, std::string strUser, std::string strGroupName,std::string strGroupId) {
	DestroyGroupRspMsg rspMsg;
	try {
		DestroyGroupReqMsg reqMsg;
		reqMsg.m_strMsgId = "33333333";
		reqMsg.m_strUserId = strUser;
		reqMsg.m_strGroupId = strGroupId;
		reqMsg.m_strGroupName = strGroupName;


		auto rsp = client.request("POST", "/destroy_group", reqMsg.ToString());
		std::string strRsp = rsp->content.string();
		std::cout << strRsp << std::endl;

		
		CHECK(rspMsg.FromString(strRsp));
		//CHECK_EQ(ERROR_CODE_TYPE::E_CODE_SUCCEED, rspMsg.m_eErrCode);

	}
	catch (const SimpleWeb::system_error& e) {
		std::cerr << "Client Req Error " << e.what() << std::endl;
	}

	return rspMsg;
}

void DestroyGroupReq(HttpClient& client, std::string strUser,std::string strGroupName,std::string strGroupId) {
	Do_DestroyGroupReq(client, strUser, strGroupName,strGroupId);
}

AddToGroupRspMsg Do_AddUserToGroupReq(HttpClient& client, std::string strUser, std::string strGroupName, std::string strGroupId) {
	AddToGroupRspMsg rspMsg;
	try {
		AddToGroupReqMsg reqMsg;
		reqMsg.m_strMsgId = "33333333";
		reqMsg.m_strUserId = strUser;
		reqMsg.m_strGroupId = strGroupId;


		auto rsp = client.request("POST", "/add_to_group", reqMsg.ToString());
		std::string strRsp = rsp->content.string();
		std::cout << strRsp << std::endl;


		CHECK(rspMsg.FromString(strRsp));
		//CHECK_EQ(ERROR_CODE_TYPE::E_CODE_SUCCEED, rspMsg.m_eErrCode);

	}
	catch (const SimpleWeb::system_error& e) {
		std::cerr << "Client Req Error " << e.what() << std::endl;
	}

	return rspMsg;
}
void AddUserToGroupReq(HttpClient& client, std::string strUser, std::string strGroupName, std::string strGroupId) {
	Do_AddUserToGroupReq(client, strUser, strGroupName, strGroupId);
}

SendGroupTextMsgRspMsg Do_SendGroupTextMsgReq(HttpClient& client, std::string strUserId, std::string strGroupId, std::string strChatContext) {
	SendGroupTextMsgRspMsg rspMsg;
	try {
		SendGroupTextMsgReqMsg reqMsg;
		reqMsg.m_strMsgId = "33333333";
		reqMsg.m_strSenderId = strUserId;
		reqMsg.m_strGroupId = strGroupId;
		reqMsg.m_strContext = strChatContext;


		auto rsp = client.request("POST", "/send_group_text_msg", reqMsg.ToString());
		std::string strRsp = rsp->content.string();
		std::cout << strRsp << std::endl;


		CHECK(rspMsg.FromString(strRsp));
		//CHECK_EQ(ERROR_CODE_TYPE::E_CODE_SUCCEED, rspMsg.m_eErrCode);

	}
	catch (const SimpleWeb::system_error& e) {
		std::cerr << "Client Req Error " << e.what() << std::endl;
	}

	return rspMsg;
}


void SendGroupTextMsgReq(HttpClient& client, std::string strUser, std::string strGroupId, std::string strChatContext) {
	Do_SendGroupTextMsgReq(client, strUser, strGroupId, strChatContext);
}

FriendChatSendTxtRspMsg Do_SendFriendChatTextMsg(HttpClient& client, std::string strUser, std::string strFriendId, std::string strChatContext) {
	FriendChatSendTxtRspMsg rspMsg;
	try {
		FriendChatSendTxtReqMsg reqMsg;
		reqMsg.m_strMsgId = "33333333";
		reqMsg.m_strSenderId = strUser;
		reqMsg.m_strReceiverId = strFriendId;
		reqMsg.m_strContext = strChatContext;


		auto rsp = client.request("POST", "/send_friend_chat_text_msg", reqMsg.ToString());
		std::string strRsp = rsp->content.string();
		std::cout << strRsp << std::endl;


		CHECK(rspMsg.FromString(strRsp));
		//CHECK_EQ(ERROR_CODE_TYPE::E_CODE_SUCCEED, rspMsg.m_eErrCode);

	}
	catch (const SimpleWeb::system_error& e) {
		std::cerr << "Client Req Error " << e.what() << std::endl;
	}

	return rspMsg;
}
void SendFriendChatTextMsg(HttpClient& client, std::string strUser, std::string strFriendId, std::string strChatContext) {
	Do_SendFriendChatTextMsg(client, strUser, strFriendId, strChatContext);
}

void Do_SendFriendSendFileReqMsg(HttpClient& client, std::string strUserId, std::string strFriendId, std::string strFileName) {
	try {
		FriendSendFileMsgReqMsg reqMsg;
		reqMsg.m_strMsgId = "33333333";
		reqMsg.m_strFileName = "TestFile.cpp";
		reqMsg.m_strFromId = strUserId;
		reqMsg.m_strToId = strFriendId;
		reqMsg.m_eOnlineType = CLIENT_ONLINE_TYPE::C_ONLINE_TYPE_ONLINE;


		auto rsp = client.request("POST", "/send_file_online_to_friend_req", reqMsg.ToString());
		std::string strRsp = rsp->content.string();
		std::cout << strRsp << std::endl;
	}
	catch (const SimpleWeb::system_error& e) {
		std::cerr << "Client Req Error " << e.what() << std::endl;
	}
}

void SendFriendSendFileReqMsg(HttpClient& client, std::string strUserId, std::string strFriendId, std::string strFileName) {
	Do_SendFriendSendFileReqMsg(client, strUserId, strFriendId, strFileName);
}

FriendSendFileMsgRspMsg Do_GetFriendSendFileRsp(HttpClient& client, std::string strUserId, std::string strFriendId, std::string strFileName) {
	FriendSendFileMsgRspMsg rspMsg;
	try {
		auto rsp = client.request("GET", "/on_send_file_online_to_friend_rsp","");
		std::string strRsp = rsp->content.string();
		std::cout << strRsp << std::endl;
		CHECK(rspMsg.FromString(strRsp));
	}
	catch (const SimpleWeb::system_error& e) {
		std::cerr << "Client Req Error " << e.what() << std::endl;
	}

	return rspMsg;
}

void GetFriendSendFileRsp(HttpClient& client, std::string strUserId, std::string strFriendId, std::string strFileName) {
	Do_GetFriendSendFileRsp(client, strUserId, strFriendId, strFileName);
}

FriendRecvFileMsgReqMsg Do_GetFriendChatRecvFileMsg(HttpClient& client, std::string strUser, std::string strFriendId, std::string strChatContext) {
	FriendRecvFileMsgReqMsg rspMsg;
	try {
		auto rsp = client.request("GET", "/recv_file_online_from_friend_req", "");
		std::string strRsp = rsp->content.string();
		std::cout << strRsp << std::endl;

		CHECK(rspMsg.FromString(strRsp));
		//CHECK_EQ(ERROR_CODE_TYPE::E_CODE_SUCCEED, rspMsg.m_eErrCode);

	}
	catch (const SimpleWeb::system_error& e) {
		std::cerr << "Client Req Error " << e.what() << std::endl;
	}

	return rspMsg;
}


void Do_PostFriendChatRecvFileMsg(HttpClient& client, FriendRecvFileMsgReqMsg reqMsg)
{
	FriendRecvFileMsgRspMsg rspMsg;
	try {
		rspMsg.m_strMsgId = reqMsg.m_strMsgId;
		rspMsg.m_strFromId = reqMsg.m_strFromId;
		rspMsg.m_strToId = reqMsg.m_strToId;
		rspMsg.m_eOnlineType = CLIENT_ONLINE_TYPE::C_ONLINE_TYPE_ONLINE;
		rspMsg.m_eOption = E_FRIEND_OPTION::E_AGREE_ADD;
		rspMsg.m_strFileName = reqMsg.m_strFileName;
		auto rsp = client.request("POST", "/on_recv_file_online_from_friend_rsp", rspMsg.ToString());
		std::string strRsp = rsp->content.string();
		std::cout << strRsp << std::endl;
		//CHECK_EQ(ERROR_CODE_TYPE::E_CODE_SUCCEED, rspMsg.m_eErrCode);

	}
	catch (const SimpleWeb::system_error& e) {
		std::cerr << "Client Req Error " << e.what() << std::endl;
	}
}

void GetFriendChatRecvFileMsg(HttpClient& client, std::string strUser, std::string strFriendId, std::string strChatContext) {
	FriendRecvFileMsgReqMsg reqMsg = Do_GetFriendChatRecvFileMsg(client, strUser, strFriendId, strChatContext);
	Do_PostFriendChatRecvFileMsg(client, reqMsg);
}


FriendChatRecvTxtReqMsg Do_GetFriendChatRecvTextMsg(HttpClient& client, std::string strUser, std::string strFriendId, std::string strChatContext) {
	FriendChatRecvTxtReqMsg rspMsg;
	try {
		auto rsp = client.request("GET", "/get_friend_chat_recv_text_msg", "");
		std::string strRsp = rsp->content.string();
		std::cout << strRsp << std::endl;

		CHECK(rspMsg.FromString(strRsp));
		//CHECK_EQ(ERROR_CODE_TYPE::E_CODE_SUCCEED, rspMsg.m_eErrCode);

	}
	catch (const SimpleWeb::system_error& e) {
		std::cerr << "Client Req Error " << e.what() << std::endl;
	}

	return rspMsg;
}


void Do_PostFriendChatRecvTextMsg(HttpClient& client,FriendChatRecvTxtReqMsg reqMsg)
{
	FriendChatRecvTxtRspMsg rspMsg;
	try {
		rspMsg.m_strMsgId = reqMsg.m_strMsgId;
		rspMsg.m_strFromId = reqMsg.m_strFromId;
		rspMsg.m_strToId = reqMsg.m_strToId;
		auto rsp = client.request("POST", "/on_friend_chat_recv_text_msg", rspMsg.ToString());
		std::string strRsp = rsp->content.string();
		std::cout << strRsp << std::endl;
		//CHECK_EQ(ERROR_CODE_TYPE::E_CODE_SUCCEED, rspMsg.m_eErrCode);

	}
	catch (const SimpleWeb::system_error& e) {
		std::cerr << "Client Req Error " << e.what() << std::endl;
	}
}

void GetFriendChatRecvTextMsg(HttpClient& client, std::string strUser, std::string strFriendId, std::string strChatContext) {
	FriendChatRecvTxtReqMsg reqMsg = Do_GetFriendChatRecvTextMsg(client, strUser, strFriendId, strChatContext);
	Do_PostFriendChatRecvTextMsg(client, reqMsg);
}

TEST_CASE("HTTP_UserRegisterReqPro") {
	HttpClient client("127.0.0.1:8000");
	//Register
	RegisterUser(client, g_strUserOne);

	//Register Twice
	{
		try {
			UserRegisterReqMsg reqMsg;
			reqMsg.m_strMsgId = "3333";
			reqMsg.m_strUserName = g_strUserOne;
			reqMsg.m_strPassword = g_strUserOne;
			reqMsg.m_strNickName = g_strUserOne;
			auto rsp = client.request("POST", "/register_user", reqMsg.ToString());
			std::string strRsp = rsp->content.string();
			std::cout << strRsp << std::endl;

			UserRegisterRspMsg rspMsg;
			CHECK(rspMsg.FromString(strRsp));
			CHECK_NE(ERROR_CODE_TYPE::E_CODE_SUCCEED, rspMsg.m_eErrCode);
			//CHECK_EQ(ERROR_CODE_TYPE::E_CODE_USER_HAS_EXIST, rspMsg.m_eErrCode);

		}
		catch (const SimpleWeb::system_error& e) {
			std::cerr << "Client Req Error " << e.what() << std::endl;
		}
	}


	//UnRegister
	UnRegisterUser(client, g_strUserOne);
}

TEST_CASE("HTTP_UserLoginReq") {
	HttpClient client("127.0.0.1:8000");
	//Register
	RegisterUser(client, g_strUserOne);
	UserLogin(client, g_strUserOne);
	UnRegisterUser(client, g_strUserOne);
}

TEST_CASE("HTTP_UserLogout") {
	HttpClient client("127.0.0.1:8000");
	//Register
	RegisterUser(client, g_strUserOne);
	UserLogin(client, g_strUserOne);
	UserLogout(client, g_strUserOne);
	UnRegisterUser(client, g_strUserOne);
}

TEST_CASE("HTTP_FindFriendReq") {
	HttpClient client("127.0.0.1:8000");
	//Register
	RegisterUser(client, g_strUserOne);
	RegisterUser(client, g_strUserTwo);
	UserLogin(client, g_strUserOne);
	FindFriendReq(client, g_strUserOne, g_strUserTwo);
	UserLogout(client, g_strUserOne);
	UnRegisterUser(client, g_strUserOne);
	UnRegisterUser(client, g_strUserTwo);
}


TEST_CASE("HTTP_AddFriend") {
	HttpClient client("127.0.0.1:8000");
	//Register
	RegisterUser(client, g_strUserOne);
	RegisterUser(client, g_strUserTwo);
	UserLoginRspMsg oneLoginRsp =  Do_UserLogin(client, g_strUserOne);
	UserLoginRspMsg twoLoginRsp = Do_UserLogin(client, g_strUserTwo);
	FindFriendRspMsg findFriendRsp = Do_FindFriendReq(client, g_strUserOne, g_strUserTwo);
	SendAddFriendReq(client, oneLoginRsp.m_strUserId, findFriendRsp.m_friendInfoVec[0].m_strUserId);
	std::this_thread::sleep_for(std::chrono::seconds(2));
	GetAddFriendRequire(client, findFriendRsp.m_friendInfoVec[0].m_strUserId);
	std::this_thread::sleep_for(std::chrono::seconds(2));
	GetAddFriendNotify(client, oneLoginRsp.m_strUserId);
	RemoveFriend(client, oneLoginRsp.m_strUserId, twoLoginRsp.m_strUserId);
	UnRegisterUser(client, g_strUserOne);
	UnRegisterUser(client, g_strUserTwo);
}

TEST_CASE("HTTP_SendFriendTxt") {
	HttpClient client("127.0.0.1:8000");
	//Register
	RegisterUser(client, g_strUserOne);
	RegisterUser(client, g_strUserTwo);
	UserLoginRspMsg oneLoginRsp = Do_UserLogin(client, g_strUserOne);
	UserLoginRspMsg twoLoginRsp = Do_UserLogin(client, g_strUserTwo);
	FindFriendRspMsg findFriendRsp = Do_FindFriendReq(client, g_strUserOne, g_strUserTwo);
	SendAddFriendReq(client, oneLoginRsp.m_strUserId, findFriendRsp.m_friendInfoVec[0].m_strUserId);
	std::this_thread::sleep_for(std::chrono::seconds(2));
	GetAddFriendRequire(client, findFriendRsp.m_friendInfoVec[0].m_strUserId);
	std::this_thread::sleep_for(std::chrono::seconds(2));
	GetAddFriendNotify(client, oneLoginRsp.m_strUserId);
	SendFriendChatTextMsg(client, oneLoginRsp.m_strUserId, twoLoginRsp.m_strUserId,"Friend Chat");
	std::this_thread::sleep_for(std::chrono::seconds(2));
	GetFriendChatRecvTextMsg(client, oneLoginRsp.m_strUserId, twoLoginRsp.m_strUserId, "Friend Chat");
	RemoveFriend(client, oneLoginRsp.m_strUserId, twoLoginRsp.m_strUserId);
	UnRegisterUser(client, g_strUserOne);
	UnRegisterUser(client, g_strUserTwo);
}

TEST_CASE("HTTP_SendFriendFile") {
	HttpClient client("127.0.0.1:8000");
	//Register
	RegisterUser(client, g_strUserOne);
	RegisterUser(client, g_strUserTwo);
	UserLoginRspMsg oneLoginRsp = Do_UserLogin(client, g_strUserOne);
	UserLoginRspMsg twoLoginRsp = Do_UserLogin(client, g_strUserTwo);
	FindFriendRspMsg findFriendRsp = Do_FindFriendReq(client, g_strUserOne, g_strUserTwo);
	SendAddFriendReq(client, oneLoginRsp.m_strUserId, findFriendRsp.m_friendInfoVec[0].m_strUserId);
	std::this_thread::sleep_for(std::chrono::seconds(2));
	GetAddFriendRequire(client, findFriendRsp.m_friendInfoVec[0].m_strUserId);
	std::this_thread::sleep_for(std::chrono::seconds(2));
	GetAddFriendNotify(client, oneLoginRsp.m_strUserId);
	SendFriendSendFileReqMsg(client, oneLoginRsp.m_strUserId, twoLoginRsp.m_strUserId, "Friend Chat");
	std::this_thread::sleep_for(std::chrono::seconds(2));
	GetFriendChatRecvFileMsg(client, oneLoginRsp.m_strUserId, twoLoginRsp.m_strUserId, "Friend Chat");
	std::this_thread::sleep_for(std::chrono::seconds(30));
	RemoveFriend(client, oneLoginRsp.m_strUserId, twoLoginRsp.m_strUserId);
	UnRegisterUser(client, g_strUserOne);
	UnRegisterUser(client, g_strUserTwo);
}
TEST_CASE("HTTP_CreateDestroyGroup") {
	HttpClient client("127.0.0.1:8000");
	//Register
	RegisterUser(client, g_strUserOne);
	UserLoginRspMsg oneLoginRsp  = Do_UserLogin(client, g_strUserOne);
	CreateGroupReq(client, oneLoginRsp.m_strUserId, g_strGroupOne);
	FindGroupReq(client, oneLoginRsp.m_strUserId, g_strGroupOne);

	FindGroupRspMsg rspMsg = Do_FindGroupReq(client, oneLoginRsp.m_strUserId, g_strGroupOne);
	DestroyGroupReq(client, oneLoginRsp.m_strUserId, g_strGroupOne,rspMsg.m_strGroupId);
	UserLogout(client, g_strUserOne);
	UnRegisterUser(client, g_strUserOne);
}


TEST_CASE("HTTP_AddToGroup") {
	HttpClient client("127.0.0.1:8000");
	//Register
	RegisterUser(client, g_strUserOne);
	RegisterUser(client, g_strUserTwo);
	UserLogin(client, g_strUserOne);
	UserLoginRspMsg loginRsp = Do_UserLogin(client, g_strUserOne);
	CreateGroupReq(client, loginRsp.m_strUserId, g_strGroupOne);
	FindGroupRspMsg rspMsg = Do_FindGroupReq(client, g_strUserOne, g_strGroupOne);
	AddUserToGroupReq(client, loginRsp.m_strUserId, rspMsg.m_strGroupName, rspMsg.m_strGroupId);
	DestroyGroupReq(client, g_strUserOne, g_strGroupOne, rspMsg.m_strGroupId);
	UserLogout(client, g_strUserOne);

	UnRegisterUser(client, g_strUserOne);
	UnRegisterUser(client, g_strUserTwo);
}


TEST_CASE("HTTP_SendGroupMsg") {
	HttpClient client("127.0.0.1:8000");
	//Register
	RegisterUser(client, g_strUserOne);
	RegisterUser(client, g_strUserTwo);
	UserLoginRspMsg userOneLoginRsp = Do_UserLogin(client, g_strUserOne);
	UserLoginRspMsg userTwoLoginRsp = Do_UserLogin(client,g_strUserTwo);
	
	CreateGroupReq(client, userOneLoginRsp.m_strUserId, g_strGroupOne);
	FindGroupRspMsg rspMsg = Do_FindGroupReq(client, g_strUserOne, g_strGroupOne);
	AddUserToGroupReq(client, userTwoLoginRsp.m_strUserId, rspMsg.m_strGroupName, rspMsg.m_strGroupId);
	SendGroupTextMsgReq(client, userOneLoginRsp.m_strUserId, rspMsg.m_strGroupId, "HTTP_SendGroupMsg");
	DestroyGroupReq(client, g_strUserOne, g_strGroupOne, rspMsg.m_strGroupId);
	UserLogout(client, g_strUserOne);

	UnRegisterUser(client, g_strUserOne);
	UnRegisterUser(client, g_strUserTwo);
}