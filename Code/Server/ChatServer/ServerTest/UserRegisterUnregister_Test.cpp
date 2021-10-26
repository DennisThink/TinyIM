#ifndef _IMAP_163_TEST_CPP_
#define _IMAP_163_TEST_CPP_
#include "ServerTest.h"
#include "CommonMsg.h"

#if 0
//��??��
TEST_CASE("RegisterUser") {
    int sockFd = Open("127.0.0.1",9000);
	CHECK(sockFd > 0);
	std::string userName = "test1@test1.com";
	std::string password = "test1@test1.com";
	{
		UserRegisterReqMsg reqMsg;
		reqMsg.m_strUserName = userName;
		reqMsg.m_strPassword = password;
		reqMsg.m_strNickName = "test1";
		TransBaseMsg_t trans(reqMsg.GetMsgType(), reqMsg.ToString());

		CHECK(Send(sockFd,trans.GetData(),static_cast<int>(trans.GetSize())));
	}
    
	{
		std::string strMsg;
		CHECK(Recv(sockFd, strMsg));
		if (strMsg.length() > sizeof(Header))
		{
			TransBaseMsg_t trans(strMsg.c_str());
			CHECK_EQ(trans.GetType(), MessageType::UserRegisterRsp_Type);
			UserRegisterRspMsg rspMsg;
			rspMsg.FromString(trans.to_string());
			CHECK_EQ(rspMsg.m_strUserName, userName);
			CHECK_EQ(rspMsg.m_eErrCode, ERROR_CODE_TYPE::E_CODE_SUCCEED);
		}
		else
		{
			CHECK(false);
		}
	}
	
	{
		UserUnRegisterReqMsg reqMsg;
		reqMsg.m_strUserName = userName;
		reqMsg.m_strPassword = password;
		TransBaseMsg_t trans(reqMsg.GetMsgType(), reqMsg.ToString());

		CHECK(Send(sockFd, trans.GetData(), static_cast<int>(trans.GetSize())));
	}
    
	{
		std::string strMsg;
		CHECK(Recv(sockFd, strMsg));
		if (strMsg.length() > sizeof(Header))
		{
			TransBaseMsg_t trans(strMsg.c_str());
			CHECK_EQ(trans.GetType(), MessageType::UserUnRegisterRsp_Type);
			UserUnRegisterRspMsg rspMsg;
			rspMsg.FromString(trans.to_string());
			CHECK_EQ(rspMsg.m_strUserName, userName);
			CHECK_EQ(rspMsg.m_eErrCode, ERROR_CODE_TYPE::E_CODE_SUCCEED);
		}
		else
		{
			CHECK(false);
		}
	}
 
	CHECK(Close(sockFd));
}


//??��
TEST_CASE("Register Twice") {
	int sockFd = Open("127.0.0.1", 9000);
	CHECK(sockFd > 0);
	std::string userName = "test1@test1.com";
	std::string password = "test1@test1.com";
	//??��
	{
		UserRegisterReqMsg reqMsg;
		reqMsg.m_strUserName = userName;
		reqMsg.m_strPassword = password;
		reqMsg.m_strNickName = "test1";
		TransBaseMsg_t trans(reqMsg.GetMsgType(), reqMsg.ToString());

		CHECK(Send(sockFd, trans.GetData(), static_cast<int>(trans.GetSize())));
	}

	{
		std::string strMsg;
		CHECK(Recv(sockFd, strMsg));
		if (strMsg.length() > sizeof(Header))
		{
			TransBaseMsg_t trans(strMsg.c_str());
			CHECK_EQ(trans.GetType(), MessageType::UserRegisterRsp_Type);
			UserRegisterRspMsg rspMsg;
			rspMsg.FromString(trans.to_string());
			CHECK_EQ(rspMsg.m_strUserName, userName);
			CHECK_EQ(rspMsg.m_eErrCode, ERROR_CODE_TYPE::E_CODE_SUCCEED);
		}
		else
		{
			CHECK(false);
		}
	}

	//?��?��
	{
		UserRegisterReqMsg reqMsg;
		reqMsg.m_strUserName = userName;
		reqMsg.m_strPassword = password;
		reqMsg.m_strNickName = "test1";
		TransBaseMsg_t trans(reqMsg.GetMsgType(), reqMsg.ToString());

		CHECK(Send(sockFd, trans.GetData(), static_cast<int>(trans.GetSize())));
	}

	{
		std::string strMsg;
		CHECK(Recv(sockFd, strMsg));
		if (strMsg.length() > sizeof(Header))
		{
			TransBaseMsg_t trans(strMsg.c_str());
			CHECK_EQ(trans.GetType(), MessageType::UserRegisterRsp_Type);
			UserRegisterRspMsg rspMsg;
			rspMsg.FromString(trans.to_string());
			CHECK_EQ(rspMsg.m_strUserName, userName);
			CHECK_EQ(rspMsg.m_eErrCode, ERROR_CODE_TYPE::E_CODE_USER_HAS_EXIST);
		}
		else
		{
			CHECK(false);
		}
	}

	{
		UserUnRegisterReqMsg reqMsg;
		reqMsg.m_strUserName = userName;
		reqMsg.m_strPassword = password;
		TransBaseMsg_t trans(reqMsg.GetMsgType(), reqMsg.ToString());

		CHECK(Send(sockFd, trans.GetData(), static_cast<int>(trans.GetSize())));
	}

	{
		std::string strMsg;
		CHECK(Recv(sockFd, strMsg));
		if (strMsg.length() > sizeof(Header))
		{
		TransBaseMsg_t trans(strMsg.c_str());
		CHECK_EQ(trans.GetType(), MessageType::UserUnRegisterRsp_Type);
		UserUnRegisterRspMsg rspMsg;
		rspMsg.FromString(trans.to_string());
		CHECK_EQ(rspMsg.m_strUserName, userName);
		CHECK_EQ(rspMsg.m_eErrCode, ERROR_CODE_TYPE::E_CODE_SUCCEED);
		}
		else
		{
			CHECK(false);
		}
	}

	CHECK(Close(sockFd));

}

TEST_CASE("UserLogin") {
	int sockFd = Open("127.0.0.1", 9000);
	CHECK(sockFd > 0);
	std::string userName = "test1@test1.com";
	std::string password = "test1@test1.com";
	{
		UserRegisterReqMsg reqMsg;
		reqMsg.m_strUserName = userName;
		reqMsg.m_strPassword = password;
		reqMsg.m_strNickName = "test1";
		TransBaseMsg_t trans(reqMsg.GetMsgType(), reqMsg.ToString());

		CHECK(Send(sockFd, trans.GetData(), static_cast<int>(trans.GetSize())));
	}

	{
		std::string strMsg;
		CHECK(Recv(sockFd, strMsg));
		if (strMsg.length() > sizeof(Header))
		{
			TransBaseMsg_t trans(strMsg.c_str());
			CHECK_EQ(trans.GetType(), MessageType::UserRegisterRsp_Type);
			UserRegisterRspMsg rspMsg;
			rspMsg.FromString(trans.to_string());
			CHECK_EQ(rspMsg.m_strUserName, userName);
			CHECK_EQ(rspMsg.m_eErrCode, ERROR_CODE_TYPE::E_CODE_SUCCEED);
		}
		else
		{
			CHECK(false);
		}
	}

	//Login
	{
		{
			UserLoginReqMsg reqMsg;
			reqMsg.m_strUserName = userName;
			reqMsg.m_strPassword = password;
			TransBaseMsg_t trans(reqMsg.GetMsgType(), reqMsg.ToString());

			CHECK(Send(sockFd, trans.GetData(), static_cast<int>(trans.GetSize())));
		}

		{
			std::string strMsg;
			CHECK(Recv(sockFd, strMsg));
			if (strMsg.length() > sizeof(Header))
			{
				TransBaseMsg_t trans(strMsg.c_str());
				CHECK_EQ(trans.GetType(), MessageType::UserLoginRsp_Type);
				UserLoginRspMsg rspMsg;
				rspMsg.FromString(trans.to_string());
				CHECK_EQ(rspMsg.m_strUserName, userName);
				CHECK_EQ(rspMsg.m_eErrCode, ERROR_CODE_TYPE::E_CODE_SUCCEED);
			}
			else
			{
				CHECK(false);
			}
		}

	}
	{
		UserUnRegisterReqMsg reqMsg;
		reqMsg.m_strUserName = userName;
		reqMsg.m_strPassword = password;
		TransBaseMsg_t trans(reqMsg.GetMsgType(), reqMsg.ToString());

		CHECK(Send(sockFd, trans.GetData(), static_cast<int>(trans.GetSize())));
	}

	{
		std::string strMsg;
		CHECK(Recv(sockFd, strMsg));
		if (strMsg.length() > sizeof(Header))
		{
			TransBaseMsg_t trans(strMsg.c_str());
			CHECK_EQ(trans.GetType(), MessageType::UserUnRegisterRsp_Type);
			UserUnRegisterRspMsg rspMsg;
			rspMsg.FromString(trans.to_string());
			CHECK_EQ(rspMsg.m_strUserName, userName);
			CHECK_EQ(rspMsg.m_eErrCode, ERROR_CODE_TYPE::E_CODE_SUCCEED);
		}
		else
		{
			CHECK(false);
		}
	}

	CHECK(Close(sockFd));
}


TEST_CASE("SendMessage") {

	int sockFd = Open("127.0.0.1", 9000);
	CHECK(sockFd > 0);
	std::string userName1 = "test1@test1.com";
	std::string password1 = "test1@test1.com";
	{
		UserRegisterReqMsg reqMsg;
		reqMsg.m_strUserName = userName1;
		reqMsg.m_strPassword = password1;
		reqMsg.m_strNickName = "test1";
		TransBaseMsg_t trans(reqMsg.GetMsgType(), reqMsg.ToString());

		CHECK(Send(sockFd, trans.GetData(), static_cast<int>(trans.GetSize())));
	}

	{
		std::string strMsg;
		CHECK(Recv(sockFd, strMsg));
		if (strMsg.length() > sizeof(Header))
		{
			TransBaseMsg_t trans(strMsg.c_str());
			CHECK_EQ(trans.GetType(), MessageType::UserRegisterRsp_Type);
			UserRegisterRspMsg rspMsg;
			rspMsg.FromString(trans.to_string());
			CHECK_EQ(rspMsg.m_strUserName, userName1);
			CHECK_EQ(rspMsg.m_eErrCode, ERROR_CODE_TYPE::E_CODE_SUCCEED);
		}
		else
		{
			CHECK(false);
		}
	}

	//Login
	{
		{
			UserLoginReqMsg reqMsg;
			reqMsg.m_strUserName = userName1;
			reqMsg.m_strPassword = password1;
			TransBaseMsg_t trans(reqMsg.GetMsgType(), reqMsg.ToString());

			CHECK(Send(sockFd, trans.GetData(), static_cast<int>(trans.GetSize())));
		}

		{
			std::string strMsg;
			CHECK(Recv(sockFd, strMsg));
			if (strMsg.length() > sizeof(Header))
			{
				TransBaseMsg_t trans(strMsg.c_str());
				CHECK_EQ(trans.GetType(), MessageType::UserLoginRsp_Type);
				UserLoginRspMsg rspMsg;
				rspMsg.FromString(trans.to_string());
				CHECK_EQ(rspMsg.m_strUserName, userName1);
				CHECK_EQ(rspMsg.m_eErrCode, ERROR_CODE_TYPE::E_CODE_SUCCEED);
			}
			else
			{
				CHECK(false);
			}
		}
	}




	int sockFd2 = Open("127.0.0.1", 9000);
	CHECK(sockFd2 > 0);
	std::string userName2 = "test2@test2.com";
	std::string password2 = "test2@test2.com";
	{
		UserRegisterReqMsg reqMsg;
		reqMsg.m_strUserName = userName2;
		reqMsg.m_strPassword = password2;
		reqMsg.m_strNickName = "test2";
		TransBaseMsg_t trans(reqMsg.GetMsgType(), reqMsg.ToString());

		CHECK(Send(sockFd2, trans.GetData(), static_cast<int>(trans.GetSize())));
	}

	{
		std::string strMsg;
		CHECK(Recv(sockFd2, strMsg));
		if (strMsg.length() > sizeof(Header))
		{
			TransBaseMsg_t trans(strMsg.c_str());
			CHECK_EQ(trans.GetType(), MessageType::UserRegisterRsp_Type);
			UserRegisterRspMsg rspMsg;
			rspMsg.FromString(trans.to_string());
			CHECK_EQ(rspMsg.m_strUserName, userName2);
			CHECK_EQ(rspMsg.m_eErrCode, ERROR_CODE_TYPE::E_CODE_SUCCEED);
		}
		else
		{
			CHECK(false);
		}
	}



	//Send  Msg
	{
		{
			FriendChatSendTxtReqMsg txtChatMsg;
			txtChatMsg.m_strSenderId = userName1;
			txtChatMsg.m_strReceiverId = userName2;
			txtChatMsg.m_strContext = "https://www.dennisthink.com/";

			TransBaseMsg_t trans(txtChatMsg.GetMsgType(), txtChatMsg.ToString());

			CHECK(Send(sockFd, trans.GetData(), static_cast<int>(trans.GetSize())));
		}
		{
			std::string strMsg;
			CHECK(Recv(sockFd, strMsg));
			if (strMsg.length() > sizeof(Header))
			{
				TransBaseMsg_t trans(strMsg.c_str());
				CHECK_EQ(trans.GetType(), MessageType::FriendChatSendTxtMsgRsp_Type);
			    FriendChatSendTxtRspMsg rspMsg;
				rspMsg.FromString(trans.to_string());
				//CHECK_EQ(rspMsg.m_strSender, userName1);
				//CHECK_EQ(rspMsg.m_strReceiver, userName2);
				CHECK_EQ(rspMsg.m_eErrCode, ERROR_CODE_TYPE::E_CODE_SUCCEED);
			}
			else
			{
				CHECK(false);
			}
		}
	}




	//UnRegister User1
	{
		UserUnRegisterReqMsg reqMsg;
		reqMsg.m_strUserName = userName1;
		reqMsg.m_strPassword = password1;
		TransBaseMsg_t trans(reqMsg.GetMsgType(), reqMsg.ToString());

		CHECK(Send(sockFd, trans.GetData(), static_cast<int>(trans.GetSize())));
	}

	{
		std::string strMsg;
		CHECK(Recv(sockFd, strMsg));
		if (strMsg.length() > sizeof(Header))
		{
			TransBaseMsg_t trans(strMsg.c_str());
			CHECK_EQ(trans.GetType(), MessageType::UserUnRegisterRsp_Type);
			UserUnRegisterRspMsg rspMsg;
			rspMsg.FromString(trans.to_string());
			CHECK_EQ(rspMsg.m_strUserName, userName1);
			CHECK_EQ(rspMsg.m_eErrCode, ERROR_CODE_TYPE::E_CODE_SUCCEED);
		}
		else
		{
			CHECK(false);
		}
	}

	CHECK(Close(sockFd));



	//UnRegister User2
	{
		UserUnRegisterReqMsg reqMsg;
		reqMsg.m_strUserName = userName2;
		reqMsg.m_strPassword = password2;
		TransBaseMsg_t trans(reqMsg.GetMsgType(), reqMsg.ToString());

		CHECK(Send(sockFd2, trans.GetData(), static_cast<int>(trans.GetSize())));
	}

	{
		std::string strMsg;
		CHECK(Recv(sockFd2, strMsg));
		if (strMsg.length() > sizeof(Header))
		{
			TransBaseMsg_t trans(strMsg.c_str());
			CHECK_EQ(trans.GetType(), MessageType::UserUnRegisterRsp_Type);
			UserUnRegisterRspMsg rspMsg;
			rspMsg.FromString(trans.to_string());
			CHECK_EQ(rspMsg.m_strUserName, userName2);
			CHECK_EQ(rspMsg.m_eErrCode, ERROR_CODE_TYPE::E_CODE_SUCCEED);
		}
		else
		{
			CHECK(false);
		}
	}

	CHECK(Close(sockFd2));
}


TEST_CASE("RecvMessage") {
	int sockFd2 = Open("127.0.0.1", 9000);
	CHECK(sockFd2 > 0);
	std::string userName2 = "test2@test2.com";
	std::string password2 = "test2@test2.com";
	{
		UserRegisterReqMsg reqMsg;
		reqMsg.m_strUserName = userName2;
		reqMsg.m_strPassword = password2;
		reqMsg.m_strNickName = "test2";
		TransBaseMsg_t trans(reqMsg.GetMsgType(), reqMsg.ToString());

		CHECK(Send(sockFd2, trans.GetData(), static_cast<int>(trans.GetSize())));
	}

	{
		std::string strMsg;
		CHECK(Recv(sockFd2, strMsg));
		if (strMsg.length() > sizeof(Header))
		{
			TransBaseMsg_t trans(strMsg.c_str());
			CHECK_EQ(trans.GetType(), MessageType::UserRegisterRsp_Type);
			UserRegisterRspMsg rspMsg;
			rspMsg.FromString(trans.to_string());
			CHECK_EQ(rspMsg.m_strUserName, userName2);
			//CHECK_EQ(rspMsg.m_eErrCode, ERROR_CODE_TYPE::E_CODE_SUCCEED);
		}
		else
		{
			CHECK(false);
		}
	}

	//Login
	{
		{
			UserLoginReqMsg reqMsg;
			reqMsg.m_strUserName = userName2;
			reqMsg.m_strPassword = password2;
			TransBaseMsg_t trans(reqMsg.GetMsgType(), reqMsg.ToString());

			CHECK(Send(sockFd2, trans.GetData(), static_cast<int>(trans.GetSize())));
		}

		{
			std::string strMsg;
			CHECK(Recv(sockFd2, strMsg));
			if (strMsg.length() > sizeof(Header))
			{
				TransBaseMsg_t trans(strMsg.c_str());
				CHECK_EQ(trans.GetType(), MessageType::UserLoginRsp_Type);
				UserLoginRspMsg rspMsg;
				rspMsg.FromString(trans.to_string());
				CHECK_EQ(rspMsg.m_strUserName, userName2);
				CHECK_EQ(rspMsg.m_eErrCode, ERROR_CODE_TYPE::E_CODE_SUCCEED);
			}
			else
			{
				CHECK(false);
			}
		}
	}

	

	//RecvMessage
	bool bRece = true;
	if (sockFd2 > 0)
	{
		bRece = false;
		FriendChatRecvTxtReqMsg rspMsg;
		{
			std::string strMsg;
			CHECK(Recv(sockFd2, strMsg));
			if (strMsg.length() > sizeof(Header))
			{
				TransBaseMsg_t trans(strMsg.c_str());
				CHECK_EQ(trans.GetType(), MessageType::FriendChatReceiveTxtMsgReq_Type);

				rspMsg.FromString(trans.to_string());
				CHECK_EQ(rspMsg.m_strToId, userName2);
				bRece = true;
			}
			else
			{
				CHECK(false);
			}
		}

		{
			FriendChatRecvTxtRspMsg txtChatMsg;
			txtChatMsg.m_strMsgId = rspMsg.m_strMsgId;

			TransBaseMsg_t trans(txtChatMsg.GetMsgType(), txtChatMsg.ToString());

			CHECK(Send(sockFd2, trans.GetData(), static_cast<int>(trans.GetSize())));
		}
		//Sleep(2000);
	}
	else
	{
		CHECK(false);
	}




	//UnRegister User2
	{
		UserUnRegisterReqMsg reqMsg;
		reqMsg.m_strUserName = userName2;
		reqMsg.m_strPassword = password2;
		TransBaseMsg_t trans(reqMsg.GetMsgType(), reqMsg.ToString());

		CHECK(Send(sockFd2, trans.GetData(), static_cast<int>(trans.GetSize())));
	}

	{
		std::string strMsg;
		CHECK(Recv(sockFd2, strMsg));
		if (strMsg.length() > sizeof(Header))
		{
			TransBaseMsg_t trans(strMsg.c_str());
			CHECK_EQ(trans.GetType(), MessageType::UserUnRegisterRsp_Type);
			UserUnRegisterRspMsg rspMsg;
			rspMsg.FromString(trans.to_string());
			CHECK_EQ(rspMsg.m_strUserName, userName2);
			CHECK_EQ(rspMsg.m_eErrCode, ERROR_CODE_TYPE::E_CODE_SUCCEED);
		}
		else
		{
			CHECK(false);
		}
	}

	CHECK(Close(sockFd2));



}

TEST_CASE("AddFriend") {

	int sockFd = Open("127.0.0.1", 9000);
	CHECK(sockFd > 0);
	std::string userName1 = "test1@test1.com";
	std::string password1 = "test1@test1.com";
	{
		UserRegisterReqMsg reqMsg;
		reqMsg.m_strUserName = userName1;
		reqMsg.m_strPassword = password1;
		reqMsg.m_strNickName = "test1";
		TransBaseMsg_t trans(reqMsg.GetMsgType(), reqMsg.ToString());

		CHECK(Send(sockFd, trans.GetData(), static_cast<int>(trans.GetSize())));
	}

	{
		std::string strMsg;
		CHECK(Recv(sockFd, strMsg));
		if (strMsg.length() > sizeof(Header))
		{
			TransBaseMsg_t trans(strMsg.c_str());
			CHECK_EQ(trans.GetType(), MessageType::UserRegisterRsp_Type);
			UserRegisterRspMsg rspMsg;
			rspMsg.FromString(trans.to_string());
			CHECK_EQ(rspMsg.m_strUserName, userName1);
			CHECK_EQ(rspMsg.m_eErrCode, ERROR_CODE_TYPE::E_CODE_SUCCEED);
		}
		else
		{
			CHECK(false);
		}
	}

	//Login
	{
		{
			UserLoginReqMsg reqMsg;
			reqMsg.m_strUserName = userName1;
			reqMsg.m_strPassword = password1;
			TransBaseMsg_t trans(reqMsg.GetMsgType(), reqMsg.ToString());

			CHECK(Send(sockFd, trans.GetData(), static_cast<int>(trans.GetSize())));
		}

		{
			std::string strMsg;
			CHECK(Recv(sockFd, strMsg));
			if (strMsg.length() > sizeof(Header))
			{
				TransBaseMsg_t trans(strMsg.c_str());
				CHECK_EQ(trans.GetType(), MessageType::UserLoginRsp_Type);
				UserLoginRspMsg rspMsg;
				rspMsg.FromString(trans.to_string());
				CHECK_EQ(rspMsg.m_strUserName, userName1);
				CHECK_EQ(rspMsg.m_eErrCode, ERROR_CODE_TYPE::E_CODE_SUCCEED);
			}
			else
			{
				CHECK(false);
			}
		}
	}




	int sockFd2 = Open("127.0.0.1", 9000);
	CHECK(sockFd2 > 0);
	std::string userName2 = "test2@test2.com";
	std::string password2 = "test2@test2.com";
	{
		UserRegisterReqMsg reqMsg;
		reqMsg.m_strUserName = userName2;
		reqMsg.m_strPassword = password2;
		reqMsg.m_strNickName = "test2";
		TransBaseMsg_t trans(reqMsg.GetMsgType(), reqMsg.ToString());

		CHECK(Send(sockFd2, trans.GetData(), static_cast<int>(trans.GetSize())));
	}

	{
		std::string strMsg;
		CHECK(Recv(sockFd2, strMsg));
		if (strMsg.length() > sizeof(Header))
		{
			TransBaseMsg_t trans(strMsg.c_str());
			CHECK_EQ(trans.GetType(), MessageType::UserRegisterRsp_Type);
			UserRegisterRspMsg rspMsg;
			rspMsg.FromString(trans.to_string());
			CHECK_EQ(rspMsg.m_strUserName, userName2);
			CHECK_EQ(rspMsg.m_eErrCode, ERROR_CODE_TYPE::E_CODE_SUCCEED);
		}
		else
		{
			CHECK(false);
		}
	}



	//Add Friend  Msg
	{
		{
			AddFriendSendReqMsg addFriendReq;
			//addFriendReq.m_strUserName = userName1;
			//addFriendReq.m_strFriendName = userName2;

			TransBaseMsg_t trans(addFriendReq.GetMsgType(), addFriendReq.ToString());

			CHECK(Send(sockFd, trans.GetData(), static_cast<int>(trans.GetSize())));
		}
		{
			std::string strMsg;
			CHECK(Recv(sockFd, strMsg));
			if (strMsg.length() > sizeof(Header))
			{
				TransBaseMsg_t trans(strMsg.c_str());
				CHECK_EQ(trans.GetType(), MessageType::AddFriendSendRsp_Type);
				AddFriendSendRspMsg rspMsg;
				rspMsg.FromString(trans.to_string());
				CHECK_EQ(rspMsg.m_strUserName, userName1);
				//CHECK_EQ(rspMsg.m_strFriendName, userName2);
				CHECK_EQ(rspMsg.m_eErrCode, ERROR_CODE_TYPE::E_CODE_SUCCEED);
			}
			else
			{
				CHECK(false);
			}
		}
	}

	//Add Friend Recv
	if(0)
	{
		AddFriendRecvReqMsg rspMsg;
		{
			std::string strMsg;
			CHECK(Recv(sockFd2, strMsg));
			if (strMsg.length() > sizeof(Header))
			{
				TransBaseMsg_t trans(strMsg.c_str());
				CHECK_EQ(trans.GetType(), MessageType::AddFriendRecvReq_Type);
				
				rspMsg.FromString(trans.to_string());
				//CHECK_EQ(rspMsg.m_strUserName, userName1);
				//CHECK_EQ(rspMsg.m_strFriendName, userName2);
			}
			else
			{
				CHECK(false);
			}
		}

		{
			AddFriendRecvRspMsg addFriendReq;
			addFriendReq.m_strUserName = userName1;
			addFriendReq.m_strFriendName = userName2;
			addFriendReq.m_option = E_FRIEND_OPTION::E_AGREE_ADD;
			TransBaseMsg_t trans(addFriendReq.GetMsgType(), addFriendReq.ToString());

			CHECK(Send(sockFd2, trans.GetData(), static_cast<int>(trans.GetSize())));
		}
		
	}

	//Notify Add Friend
	if(0)
	{
		AddFriendNotifyReqMsg rspMsg;
		{
			std::string strMsg;
			CHECK(Recv(sockFd, strMsg));
			if (strMsg.length() > sizeof(Header))
			{
				TransBaseMsg_t trans(strMsg.c_str());
				CHECK_EQ(trans.GetType(), MessageType::AddFriendNotifyReq_Type);
				AddFriendNotifyReqMsg rspMsg;
				rspMsg.FromString(trans.to_string());
				CHECK_EQ(rspMsg.m_strUserName, userName1);
				CHECK_EQ(rspMsg.m_strFriendName, userName2);
			}
			else
			{
				CHECK(false);
			}
		}


		{
			AddFriendNotifyRspMsg addFriendReq;
			addFriendReq.m_strMsgId = rspMsg.m_strMsgId;

			TransBaseMsg_t trans(addFriendReq.GetMsgType(), addFriendReq.ToString());

			CHECK(Send(sockFd, trans.GetData(), static_cast<int>(trans.GetSize())));
		}
		
	}



	//UnRegister User1
	{
		UserUnRegisterReqMsg reqMsg;
		reqMsg.m_strUserName = userName1;
		reqMsg.m_strPassword = password1;
		TransBaseMsg_t trans(reqMsg.GetMsgType(), reqMsg.ToString());

		CHECK(Send(sockFd, trans.GetData(), static_cast<int>(trans.GetSize())));
	}

	{
		std::string strMsg;
		CHECK(Recv(sockFd, strMsg));
		if (strMsg.length() > sizeof(Header))
		{
			TransBaseMsg_t trans(strMsg.c_str());
			CHECK_EQ(trans.GetType(), MessageType::UserUnRegisterRsp_Type);
			UserUnRegisterRspMsg rspMsg;
			rspMsg.FromString(trans.to_string());
			CHECK_EQ(rspMsg.m_strUserName, userName1);
			CHECK_EQ(rspMsg.m_eErrCode, ERROR_CODE_TYPE::E_CODE_SUCCEED);
		}
		else
		{
			CHECK(false);
		}
	}

	CHECK(Close(sockFd));



	//UnRegister User2
	{
		UserUnRegisterReqMsg reqMsg;
		reqMsg.m_strUserName = userName2;
		reqMsg.m_strPassword = password2;
		TransBaseMsg_t trans(reqMsg.GetMsgType(), reqMsg.ToString());

		CHECK(Send(sockFd2, trans.GetData(), static_cast<int>(trans.GetSize())));
	}

	{
		std::string strMsg;
		CHECK(Recv(sockFd2, strMsg));
		if (strMsg.length() > sizeof(Header))
		{
			TransBaseMsg_t trans(strMsg.c_str());
			CHECK_EQ(trans.GetType(), MessageType::UserUnRegisterRsp_Type);
			UserUnRegisterRspMsg rspMsg;
			rspMsg.FromString(trans.to_string());
			CHECK_EQ(rspMsg.m_strUserName, userName2);
			CHECK_EQ(rspMsg.m_eErrCode, ERROR_CODE_TYPE::E_CODE_SUCCEED);
		}
		else
		{
			CHECK(false);
		}
	}

	CHECK(Close(sockFd2));
}



TEST_CASE("AddFriend_AGREE")
{

	int sockFd = Open("127.0.0.1", 9000);
	CHECK(sockFd > 0);
	std::string userName1 = "AddFriend_AGREE@test1.com";
	std::string password1 = "AddFriend_AGREE@test1.com";
	{
		UserRegisterReqMsg reqMsg;
		reqMsg.m_strUserName = userName1;
		reqMsg.m_strPassword = password1;
		reqMsg.m_strNickName = "test1";
		TransBaseMsg_t trans(reqMsg.GetMsgType(), reqMsg.ToString());

		CHECK(Send(sockFd, trans.GetData(), static_cast<int>(trans.GetSize())));
	}

	{
		std::string strMsg;
		CHECK(Recv(sockFd, strMsg));
		if (strMsg.length() > sizeof(Header))
		{
			TransBaseMsg_t trans(strMsg.c_str());
			CHECK_EQ(trans.GetType(), MessageType::UserRegisterRsp_Type);
			UserRegisterRspMsg rspMsg;
			rspMsg.FromString(trans.to_string());
			CHECK_EQ(rspMsg.m_strUserName, userName1);
			CHECK_EQ(rspMsg.m_eErrCode, ERROR_CODE_TYPE::E_CODE_SUCCEED);
		}
		else
		{
			CHECK(false);
		}
	}

	//Login
	{
		{
			UserLoginReqMsg reqMsg;
			reqMsg.m_strUserName = userName1;
			reqMsg.m_strPassword = password1;
			TransBaseMsg_t trans(reqMsg.GetMsgType(), reqMsg.ToString());

			CHECK(Send(sockFd, trans.GetData(), static_cast<int>(trans.GetSize())));
		}

		{
			std::string strMsg;
			CHECK(Recv(sockFd, strMsg));
			if (strMsg.length() > sizeof(Header))
			{
				TransBaseMsg_t trans(strMsg.c_str());
				CHECK_EQ(trans.GetType(), MessageType::UserLoginRsp_Type);
				UserLoginRspMsg rspMsg;
				rspMsg.FromString(trans.to_string());
				CHECK_EQ(rspMsg.m_strUserName, userName1);
				CHECK_EQ(rspMsg.m_eErrCode, ERROR_CODE_TYPE::E_CODE_SUCCEED);
			}
			else
			{
				CHECK(false);
			}
		}
	}




	int sockFd2 = Open("127.0.0.1", 9000);
	CHECK(sockFd2 > 0);
	std::string userName2 = "AddFriend_AGREE2@test2.com";
	std::string password2 = "AddFriend_AGREE2@test2.com";
	{
		UserRegisterReqMsg reqMsg;
		reqMsg.m_strUserName = userName2;
		reqMsg.m_strPassword = password2;
		reqMsg.m_strNickName = "test2";
		TransBaseMsg_t trans(reqMsg.GetMsgType(), reqMsg.ToString());

		CHECK(Send(sockFd2, trans.GetData(), static_cast<int>(trans.GetSize())));
	}

	{
		std::string strMsg;
		CHECK(Recv(sockFd2, strMsg));
		if (strMsg.length() > sizeof(Header))
		{
			TransBaseMsg_t trans(strMsg.c_str());
			CHECK_EQ(trans.GetType(), MessageType::UserRegisterRsp_Type);
			UserRegisterRspMsg rspMsg;
			rspMsg.FromString(trans.to_string());
			CHECK_EQ(rspMsg.m_strUserName, userName2);
			CHECK_EQ(rspMsg.m_eErrCode, ERROR_CODE_TYPE::E_CODE_SUCCEED);
		}
		else
		{
			CHECK(false);
		}
	}

	{
		{
			UserLoginReqMsg reqMsg;
			reqMsg.m_strUserName = userName2;
			reqMsg.m_strPassword = password2;
			TransBaseMsg_t trans(reqMsg.GetMsgType(), reqMsg.ToString());

			CHECK(Send(sockFd2, trans.GetData(), static_cast<int>(trans.GetSize())));
		}

		{
			std::string strMsg;
			CHECK(Recv(sockFd2, strMsg));
			if (strMsg.length() > sizeof(Header))
			{
				TransBaseMsg_t trans(strMsg.c_str());
				CHECK_EQ(trans.GetType(), MessageType::UserLoginRsp_Type);
				UserLoginRspMsg rspMsg;
				rspMsg.FromString(trans.to_string());
				CHECK_EQ(rspMsg.m_strUserName, userName2);
				CHECK_EQ(rspMsg.m_eErrCode, ERROR_CODE_TYPE::E_CODE_SUCCEED);
			}
			else
			{
				CHECK(false);
			}
		}
	}


	//Add Friend  Msg
	{
		{
			AddFriendSendReqMsg addFriendReq;
			//addFriendReq.m_strUserName = userName1;
			//addFriendReq.m_strFriendName = userName2;

			TransBaseMsg_t trans(addFriendReq.GetMsgType(), addFriendReq.ToString());

			CHECK(Send(sockFd, trans.GetData(), static_cast<int>(trans.GetSize())));
		}
		{
			std::string strMsg;
			CHECK(Recv(sockFd, strMsg));
			if (strMsg.length() > sizeof(Header))
			{
				TransBaseMsg_t trans(strMsg.c_str());
				CHECK_EQ(trans.GetType(), MessageType::AddFriendSendRsp_Type);
				AddFriendSendRspMsg rspMsg;
				rspMsg.FromString(trans.to_string());
				//CHECK_EQ(rspMsg.m_strUserName, userName1);
				//CHECK_EQ(rspMsg.m_strFriendName, userName2);
				CHECK_EQ(rspMsg.m_eErrCode, ERROR_CODE_TYPE::E_CODE_SUCCEED);
			}
			else
			{
				CHECK(false);
			}
		}
	}

	//Add Friend Recv
	{
		AddFriendRecvReqMsg rspMsg;
		{
			std::string strMsg;
			CHECK(Recv(sockFd2, strMsg));
			if (strMsg.length() > sizeof(Header))
			{
				TransBaseMsg_t trans(strMsg.c_str());
				CHECK_EQ(trans.GetType(), MessageType::AddFriendRecvReq_Type);

				rspMsg.FromString(trans.to_string());
				CHECK_EQ(rspMsg.m_strUserName, userName2);
				CHECK_EQ(rspMsg.m_strFriendName, userName1);
			}
			else
			{
				CHECK(false);
			}
		}

		{
			AddFriendRecvRspMsg addFriendReq;
			addFriendReq.m_strMsgId = rspMsg.m_strMsgId;
			addFriendReq.m_strUserName = userName2;
			addFriendReq.m_strFriendName = userName1;
			addFriendReq.m_option = E_FRIEND_OPTION::E_AGREE_ADD;
			TransBaseMsg_t trans(addFriendReq.GetMsgType(), addFriendReq.ToString());

			CHECK(Send(sockFd2, trans.GetData(), static_cast<int>(trans.GetSize())));
		}

	}

	//Notify Add Friend
	{
		AddFriendNotifyReqMsg rspMsg;
		{
			std::string strMsg;
			CHECK(Recv(sockFd, strMsg));
			if (strMsg.length() > sizeof(Header))
			{
				TransBaseMsg_t trans(strMsg.c_str());
				CHECK_EQ(trans.GetType(), MessageType::AddFriendNotifyReq_Type);
				CHECK(rspMsg.FromString(trans.to_string()));
				CHECK_EQ(rspMsg.m_strUserName, userName1);
				CHECK_EQ(rspMsg.m_strFriendName, userName2);
			}
			else
			{
				CHECK(false);
			}
		}


		{
			AddFriendNotifyRspMsg addFriendReq;
			addFriendReq.m_strMsgId = rspMsg.m_strMsgId;

			TransBaseMsg_t trans(addFriendReq.GetMsgType(), addFriendReq.ToString());

			CHECK(Send(sockFd, trans.GetData(), static_cast<int>(trans.GetSize())));
		}

	}



	//UnRegister User1
	{
		UserUnRegisterReqMsg reqMsg;
		reqMsg.m_strUserName = userName1;
		reqMsg.m_strPassword = password1;
		TransBaseMsg_t trans(reqMsg.GetMsgType(), reqMsg.ToString());

		CHECK(Send(sockFd, trans.GetData(), static_cast<int>(trans.GetSize())));
	}

	{
		std::string strMsg;
		CHECK(Recv(sockFd, strMsg));
		if (strMsg.length() > sizeof(Header))
		{
			TransBaseMsg_t trans(strMsg.c_str());
			CHECK_EQ(trans.GetType(), MessageType::UserUnRegisterRsp_Type);
			UserUnRegisterRspMsg rspMsg;
			rspMsg.FromString(trans.to_string());
			CHECK_EQ(rspMsg.m_strUserName, userName1);
			CHECK_EQ(rspMsg.m_eErrCode, ERROR_CODE_TYPE::E_CODE_SUCCEED);
		}
		else
		{
			CHECK(false);
		}
	}

	CHECK(Close(sockFd));



	//UnRegister User2
	{
		UserUnRegisterReqMsg reqMsg;
		reqMsg.m_strUserName = userName2;
		reqMsg.m_strPassword = password2;
		TransBaseMsg_t trans(reqMsg.GetMsgType(), reqMsg.ToString());

		CHECK(Send(sockFd2, trans.GetData(), static_cast<int>(trans.GetSize())));
	}

	{
		std::string strMsg;
		CHECK(Recv(sockFd2, strMsg));
		if (strMsg.length() > sizeof(Header))
		{
			TransBaseMsg_t trans(strMsg.c_str());
			CHECK_EQ(trans.GetType(), MessageType::UserUnRegisterRsp_Type);
			UserUnRegisterRspMsg rspMsg;
			rspMsg.FromString(trans.to_string());
			CHECK_EQ(rspMsg.m_strUserName, userName2);
			CHECK_EQ(rspMsg.m_eErrCode, ERROR_CODE_TYPE::E_CODE_SUCCEED);
		}
		else
		{
			CHECK(false);
		}
	}

	CHECK(Close(sockFd2));
}


TEST_CASE("RemoveFriend")
{

	int sockFd = Open("127.0.0.1", 9000);
	CHECK(sockFd > 0);
	std::string userName1 = "AddFriend_AGREE@test1.com";
	std::string password1 = "AddFriend_AGREE@test1.com";
	{
		UserRegisterReqMsg reqMsg;
		reqMsg.m_strUserName = userName1;
		reqMsg.m_strPassword = password1;
		reqMsg.m_strNickName = "test1";
		TransBaseMsg_t trans(reqMsg.GetMsgType(), reqMsg.ToString());

		CHECK(Send(sockFd, trans.GetData(), static_cast<int>(trans.GetSize())));
	}

	{
		std::string strMsg;
		CHECK(Recv(sockFd, strMsg));
		if (strMsg.length() > sizeof(Header))
		{
			TransBaseMsg_t trans(strMsg.c_str());
			CHECK_EQ(trans.GetType(), MessageType::UserRegisterRsp_Type);
			UserRegisterRspMsg rspMsg;
			rspMsg.FromString(trans.to_string());
			CHECK_EQ(rspMsg.m_strUserName, userName1);
			CHECK_EQ(rspMsg.m_eErrCode, ERROR_CODE_TYPE::E_CODE_SUCCEED);
		}
		else
		{
			CHECK(false);
		}
	}

	//Login
	{
		{
			UserLoginReqMsg reqMsg;
			reqMsg.m_strUserName = userName1;
			reqMsg.m_strPassword = password1;
			TransBaseMsg_t trans(reqMsg.GetMsgType(), reqMsg.ToString());

			CHECK(Send(sockFd, trans.GetData(), static_cast<int>(trans.GetSize())));
		}

		{
			std::string strMsg;
			CHECK(Recv(sockFd, strMsg));
			if (strMsg.length() > sizeof(Header))
			{
				TransBaseMsg_t trans(strMsg.c_str());
				CHECK_EQ(trans.GetType(), MessageType::UserLoginRsp_Type);
				UserLoginRspMsg rspMsg;
				rspMsg.FromString(trans.to_string());
				CHECK_EQ(rspMsg.m_strUserName, userName1);
				CHECK_EQ(rspMsg.m_eErrCode, ERROR_CODE_TYPE::E_CODE_SUCCEED);
			}
			else
			{
				CHECK(false);
			}
		}
	}




	int sockFd2 = Open("127.0.0.1", 9000);
	CHECK(sockFd2 > 0);
	std::string userName2 = "AddFriend_AGREE2@test2.com";
	std::string password2 = "AddFriend_AGREE2@test2.com";
	{
		UserRegisterReqMsg reqMsg;
		reqMsg.m_strUserName = userName2;
		reqMsg.m_strPassword = password2;
		reqMsg.m_strNickName = "test2";
		TransBaseMsg_t trans(reqMsg.GetMsgType(), reqMsg.ToString());

		CHECK(Send(sockFd2, trans.GetData(), static_cast<int>(trans.GetSize())));
	}

	{
		std::string strMsg;
		CHECK(Recv(sockFd2, strMsg));
		if (strMsg.length() > sizeof(Header))
		{
			TransBaseMsg_t trans(strMsg.c_str());
			CHECK_EQ(trans.GetType(), MessageType::UserRegisterRsp_Type);
			UserRegisterRspMsg rspMsg;
			rspMsg.FromString(trans.to_string());
			CHECK_EQ(rspMsg.m_strUserName, userName2);
			CHECK_EQ(rspMsg.m_eErrCode, ERROR_CODE_TYPE::E_CODE_SUCCEED);
		}
		else
		{
			CHECK(false);
		}
	}

	{
		{
			UserLoginReqMsg reqMsg;
			reqMsg.m_strUserName = userName2;
			reqMsg.m_strPassword = password2;
			TransBaseMsg_t trans(reqMsg.GetMsgType(), reqMsg.ToString());

			CHECK(Send(sockFd2, trans.GetData(), static_cast<int>(trans.GetSize())));
		}

		{
			std::string strMsg;
			CHECK(Recv(sockFd2, strMsg));
			if (strMsg.length() > sizeof(Header))
			{
				TransBaseMsg_t trans(strMsg.c_str());
				CHECK_EQ(trans.GetType(), MessageType::UserLoginRsp_Type);
				UserLoginRspMsg rspMsg;
				rspMsg.FromString(trans.to_string());
				CHECK_EQ(rspMsg.m_strUserName, userName2);
				CHECK_EQ(rspMsg.m_eErrCode, ERROR_CODE_TYPE::E_CODE_SUCCEED);
			}
			else
			{
				CHECK(false);
			}
		}
	}


	//Add Friend  Msg
	{
		{
			AddFriendSendReqMsg addFriendReq;
			addFriendReq.m_strUserName = userName1;
			addFriendReq.m_strFriendName = userName2;

			TransBaseMsg_t trans(addFriendReq.GetMsgType(), addFriendReq.ToString());

			CHECK(Send(sockFd, trans.GetData(), static_cast<int>(trans.GetSize())));
		}
		{
			std::string strMsg;
			CHECK(Recv(sockFd, strMsg));
			if (strMsg.length() > sizeof(Header))
			{
				TransBaseMsg_t trans(strMsg.c_str());
				CHECK_EQ(trans.GetType(), MessageType::AddFriendSendRsp_Type);
				AddFriendSendRspMsg rspMsg;
				rspMsg.FromString(trans.to_string());
				CHECK_EQ(rspMsg.m_strUserName, userName1);
				CHECK_EQ(rspMsg.m_strFriendName, userName2);
				CHECK_EQ(rspMsg.m_eErrCode, ERROR_CODE_TYPE::E_CODE_SUCCEED);
			}
			else
			{
				CHECK(false);
			}
		}
	}

	//Add Friend Recv
	{
		AddFriendRecvReqMsg rspMsg;
		{
			std::string strMsg;
			CHECK(Recv(sockFd2, strMsg));
			if (strMsg.length() > sizeof(Header))
			{
				TransBaseMsg_t trans(strMsg.c_str());
				CHECK_EQ(trans.GetType(), MessageType::AddFriendRecvReq_Type);

				rspMsg.FromString(trans.to_string());
				CHECK_EQ(rspMsg.m_strUserName, userName2);
				CHECK_EQ(rspMsg.m_strFriendName, userName1);
			}
			else
			{
				CHECK(false);
			}
		}

		{
			AddFriendRecvRspMsg addFriendReq;
			addFriendReq.m_strMsgId = rspMsg.m_strMsgId;
			addFriendReq.m_strUserName = userName2;
			addFriendReq.m_strFriendName = userName1;
			addFriendReq.m_option = E_FRIEND_OPTION::E_AGREE_ADD;
			TransBaseMsg_t trans(addFriendReq.GetMsgType(), addFriendReq.ToString());

			CHECK(Send(sockFd2, trans.GetData(), static_cast<int>(trans.GetSize())));
		}

	}

	//Notify Add Friend
	{
		AddFriendNotifyReqMsg rspMsg;
		{
			std::string strMsg;
			CHECK(Recv(sockFd, strMsg));
			if (strMsg.length() > sizeof(Header))
			{
				TransBaseMsg_t trans(strMsg.c_str());
				CHECK_EQ(trans.GetType(), MessageType::AddFriendNotifyReq_Type);
				CHECK(rspMsg.FromString(trans.to_string()));
				CHECK_EQ(rspMsg.m_strUserName, userName1);
				CHECK_EQ(rspMsg.m_strFriendName, userName2);
			}
			else
			{
				CHECK(false);
			}
		}

		{
			AddFriendNotifyRspMsg addFriendReq;
			addFriendReq.m_strMsgId = rspMsg.m_strMsgId;

			TransBaseMsg_t trans(addFriendReq.GetMsgType(), addFriendReq.ToString());

			CHECK(Send(sockFd, trans.GetData(), static_cast<int>(trans.GetSize())));
		}
	}


	//RemoveFriend
	{
		{
			RemoveFriendReqMsg reqMsg;
			reqMsg.m_strUserId = userName2;
			reqMsg.m_strFriendId = userName1;
			TransBaseMsg_t trans(reqMsg.GetMsgType(), reqMsg.ToString());

			CHECK(Send(sockFd2, trans.GetData(), static_cast<int>(trans.GetSize())));
		}

		
		{
			std::string strMsg;
			CHECK(Recv(sockFd2, strMsg));
			if (strMsg.length() > sizeof(Header))
			{
				TransBaseMsg_t trans(strMsg.c_str());
				CHECK_EQ(trans.GetType(), MessageType::RemoveFriendRsp_Type);
				RemoveFriendRspMsg rspMsg;
				rspMsg.FromString(trans.to_string());
				CHECK_EQ(rspMsg.m_strUserId, userName2);
				CHECK_EQ(rspMsg.m_strFriendId, userName1);
			}
			else
			{
				CHECK(false);
			}
		}
	}


	//UnRegister User1
	{
		UserUnRegisterReqMsg reqMsg;
		reqMsg.m_strUserName = userName1;
		reqMsg.m_strPassword = password1;
		TransBaseMsg_t trans(reqMsg.GetMsgType(), reqMsg.ToString());

		CHECK(Send(sockFd, trans.GetData(), static_cast<int>(trans.GetSize())));
	}

	{
		std::string strMsg;
		CHECK(Recv(sockFd, strMsg));
		if (strMsg.length() > sizeof(Header))
		{
			TransBaseMsg_t trans(strMsg.c_str());
			CHECK_EQ(trans.GetType(), MessageType::UserUnRegisterRsp_Type);
			UserUnRegisterRspMsg rspMsg;
			rspMsg.FromString(trans.to_string());
			CHECK_EQ(rspMsg.m_strUserName, userName1);
			CHECK_EQ(rspMsg.m_eErrCode, ERROR_CODE_TYPE::E_CODE_SUCCEED);
		}
		else
		{
			CHECK(false);
		}
	}

	CHECK(Close(sockFd));



	//UnRegister User2
	{
		UserUnRegisterReqMsg reqMsg;
		reqMsg.m_strUserName = userName2;
		reqMsg.m_strPassword = password2;
		TransBaseMsg_t trans(reqMsg.GetMsgType(), reqMsg.ToString());

		CHECK(Send(sockFd2, trans.GetData(), static_cast<int>(trans.GetSize())));
	}

	{
		std::string strMsg;
		CHECK(Recv(sockFd2, strMsg));
		if (strMsg.length() > sizeof(Header))
		{
			TransBaseMsg_t trans(strMsg.c_str());
			CHECK_EQ(trans.GetType(), MessageType::UserUnRegisterRsp_Type);
			UserUnRegisterRspMsg rspMsg;
			rspMsg.FromString(trans.to_string());
			CHECK_EQ(rspMsg.m_strUserName, userName2);
			CHECK_EQ(rspMsg.m_eErrCode, ERROR_CODE_TYPE::E_CODE_SUCCEED);
		}
		else
		{
			CHECK(false);
		}
	}

	CHECK(Close(sockFd2));
}
#endif

#endif