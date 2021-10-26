/**
 * @file CMySqlConnect.cpp
 * @author DennisMi (https://www.dennisthink.com/)
 * @brief 处理数据库操作的相关代码
 * @version 0.1
 * @date 2019-07-20
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "CMySqlConnect.h"
#include "fmt/format.h"
#include <iostream>
std::shared_ptr<spdlog::logger> CMySqlConnect::m_loger=nullptr;

/**
 * @brief 构造函数
 * 
 */
CMySqlConnect::CMySqlConnect()
{
		if (NULL != mysql_init(&m_mysql)) {
			LOG_INFO(m_loger, "mysql_init()succeed [ {}  {}]", __FILENAME__, __LINE__);
		}
		else {
			LOG_INFO(m_loger,"mysql_init()failed  [{} {}]", __FILENAME__, __LINE__);
		}

		if (0 == mysql_library_init(0, NULL, NULL)) {
			LOG_INFO(m_loger,"mysql_library_init()succeed  [{} {}]", __FILENAME__, __LINE__);
		}
		else {
			LOG_INFO(m_loger, "mysql_library_init()failed [{} {}]", __FILENAME__, __LINE__);
		}
}

/**
 * @brief 析构函数
 * 
 */
CMySqlConnect::~CMySqlConnect()
{
    mysql_close(&m_mysql);
}

/**
 * @brief 连接到Mysql服务器
 * 
 * @param userName 数据库用户名
 * @param passwd 数据库密码
 * @param database 数据库名称
 * @param strHost 数据库服务器IP
 * @param port 数据库服务器断开
 * @return true 连接成功
 * @return false 连接失败
 */
bool CMySqlConnect::ConnectToServer(const std::string userName,
                                    const std::string passwd,
                                    const std::string database,
                                    const std::string strHost,const int port)
{
		if (NULL != mysql_real_connect(&m_mysql, strHost.c_str(),userName.c_str(),passwd.c_str(), database.c_str(), port, NULL, 0))
		{
			LOG_INFO(m_loger, "mysql_real_connect() succeed [{} {}]", __FILENAME__, __LINE__);
			int nResult = mysql_set_character_set(&m_mysql, "UTF8");
			LOG_INFO(m_loger, "{}  succeed [{} {}]", nResult, __FILENAME__, __LINE__);
            return true;
		}
		else
		{
			LOG_INFO(m_loger, "mysql_real_connect()failed[{} {}]", __FILENAME__, __LINE__);
            return false;
		}
}

/**
 * @brief 根据用户名获取用户的密码
 * 
 * @param userName 用户名
 * @param bean 用户名和密码的结构体
 * @return true 获取成功
 * @return false 获取失败
 */
bool CMySqlConnect::SelectUserByName(const std::string userName, T_USER_BEAN& bean)
{
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	int res = 0;
	bool bResult = false;
	std::string strTemplate2 = "SELECT F_USER_ID,F_USER_NAME,F_PASS_WORD FROM T_USER WHERE F_USER_NAME='{0}';";
	std::string strSql = fmt::format(strTemplate2, userName);
	LOG_INFO(m_loger, "SQL:{} [{}  {} ]", strSql, __FILENAME__, __LINE__);
	res = mysql_query(&m_mysql, strSql.c_str());
	if (!res)
	{
		result = mysql_store_result(&m_mysql);
		if (result)
		{
			while (sql_row = mysql_fetch_row(result),sql_row != nullptr)
			{
				bean.m_strF_USER_ID = sql_row[0];
				bean.m_strF_USER_NAME = sql_row[1];
				bean.m_strF_PASS_WORD = sql_row[2];
				bResult = true;
				break;
			}
		}
	}
	else
	{
		return false;
	}
	if (result != NULL)
	{
		mysql_free_result(result);
	}
    return bResult;
}


/**
 * @brief 判断用户是否存在
 * 
 * @param userName 用户名
 * @return true 存在
 * @return false 不存在
 */
bool CMySqlConnect::IsUserExist(const std::string strUserId)
{
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	int res = 0;
	std::string strTemplate2 = "SELECT F_USER_ID FROM T_USER WHERE F_USER_ID='{0}';";
	std::string strSql = fmt::format(strTemplate2, strUserId);
	LOG_INFO(m_loger, "SQL:{} [{}  {} ]", strSql  ,__FILENAME__, __LINE__);
	res = mysql_query(&m_mysql, strSql.c_str());
	bool bExist = false;
	if (!res)
	{
		result = mysql_store_result(&m_mysql);
		if (result)
		{
			while (sql_row = mysql_fetch_row(result),sql_row != nullptr)
			{
				bExist = true;
				break;
			}
		}
	}
	else
	{
		return bExist;
	}
	if (result != NULL)
	{
		mysql_free_result(result);
	}
	return bExist;
}


/**
 * @brief 判断userName 和friendName是不是好友
 * 
 * @param userName 用户名
 * @param friendName 好友用户名
 * @return true friendName是userName的好友
 * @return false 不是好友
 */
bool CMySqlConnect::IsFriend(const std::string userId,const std::string friendId)
{
	MYSQL_RES *result=nullptr;
	MYSQL_ROW sql_row;
	int res = 0;
	std::string strTemplate2 = "SELECT F_STATUS FROM T_FRIEND_RELATION WHERE F_USER_ID='{0}' AND F_FRIEND_ID='{1}';";
	std::string strSql = fmt::format(strTemplate2, userId, friendId);
	LOG_INFO(m_loger, "SQL:{} [{}  {} ]", strSql, __FILENAME__, __LINE__);
	res = mysql_query(&m_mysql, strSql.c_str());
	bool bExist = false;
	if (!res)
	{
		result = mysql_store_result(&m_mysql);
		if (result)
		{
			while (sql_row = mysql_fetch_row(result),sql_row != nullptr)
			{
				bExist = true;
				break;
			}
		}
	}
	else
	{
		return bExist;
	}
	if (result != NULL)
	{
		mysql_free_result(result);
	}
	return bExist;
}

/**
 * @brief 更新用户的密码
 * 
 * @param bean 用户名和密码的结构体
 * @return true 更新成功
 * @return false 更新失败
 */
bool CMySqlConnect::UpdateUser(const T_USER_BEAN& bean)
{
	int res = 0;
	std::string strTemplate2 = "UPDATE T_USER SET F_PASS_WORD='{0}' WHERE F_USER_NAME='{1}';";
	std::string strSql = fmt::format(strTemplate2, bean.m_strF_PASS_WORD, bean.m_strF_USER_NAME);
	LOG_INFO(m_loger, "SQL:{} [{}  {} ]", strSql, __FILENAME__, __LINE__);
	res = mysql_query(&m_mysql, strSql.c_str());//查询
	if (!res)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CMySqlConnect::UpdateUserOnlineState(const std::string strUserId, const CLIENT_ONLINE_TYPE type)
{
	int res = 0;
	std::string strTemplate2 = "UPDATE T_USER SET F_ON_LINE_STATE='{0}' WHERE F_USER_ID='{1}';";
	std::string strSql = fmt::format(strTemplate2, OnLineType(type), strUserId);
	LOG_INFO(m_loger, "SQL:{} [{}  {} ]", strSql, __FILENAME__, __LINE__);
	res = mysql_query(&m_mysql, strSql.c_str());//查询
	if (!res)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * @brief 删除某个用户
 * 
 * @param userName 待删除的用户名
 * @return true 删除成功
 * @return false 删除失败
 */
bool CMySqlConnect::DeleteUser(const std::string strUserId)
{
	int res = 0;
	std::string strTemplate2 = "DELETE FROM T_USER WHERE F_USER_ID='{0}';";
	std::string strSql = fmt::format(strTemplate2, strUserId);
	LOG_INFO(m_loger, "SQL:{} [{}  {} ]", strSql, __FILENAME__, __LINE__);
	res = mysql_query(&m_mysql, strSql.c_str());//查询
	if (!res)
	{
		return true;
	}
	else
	{
		return false;
	}
	return true;
}


/**
 * @brief 插入用户信息到数据库
 * 
 * @param bean 用户名和密码的结构体
 * @return true 成功
 * @return false 失败
 */
bool CMySqlConnect::InsertUser(const T_USER_BEAN& bean)
{
	if (bean.IsValid())
	{
		int res = 0;
		std::string strTemplate2 = "INSERT INTO T_USER(F_USER_ID,F_USER_NAME,F_PASS_WORD,F_NICK_NAME) VALUES('{0}','{1}','{2}','{3}');";
		std::string strSql = fmt::format(strTemplate2, bean.m_strF_USER_ID, bean.m_strF_USER_NAME, bean.m_strF_PASS_WORD, bean.m_strF_NICK_NAME);

		LOG_INFO(m_loger, "SQL:{} [{}  {} ]", strSql, __FILENAME__, __LINE__);
		res = mysql_query(&m_mysql, strSql.c_str());//查询
		if (!res)
		{

		}
		else
		{
			return false;
		}
		return true;
	}
	else
	{
		return false;
	}
	
}

/**
 * @brief 根据用户名查找用户的其他信息
 * 
 * @param userName 用户名
 * @param bean 用户的其他信息
 * @return true 成功
 * @return false 失败
 */
bool CMySqlConnect::SelectUserInfoByName(const std::string userId, T_USER_INFO_BEAN& bean)
{
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	int res = 0;
	std::string strTemplate2 = "SELECT F_USER_ID,\
F_USER_NAME,\
F_ADDRESS,\
F_BIRTH_DATE,\
F_EMAIL_ADDR,\
F_NICK_NAME,\
F_SIGNATURE,\
F_FACE_ID,\
F_ON_LINE_STATE \
FROM T_USER WHERE F_USER_ID='{0}' OR F_USER_NAME='{0}';";
	
	std::string strSql = fmt::format(strTemplate2, userId);
	LOG_INFO(m_loger, "SQL:{} [{}  {} ]", strSql, __FILENAME__, __LINE__);
	res = mysql_query(&m_mysql, strSql.c_str());
	if (!res)
	{
		result = mysql_store_result(&m_mysql);
		if (result)
		{
			while (sql_row = mysql_fetch_row(result),sql_row != nullptr)
			{
				bean.m_strF_USER_ID = sql_row[0];
				bean.m_strF_USER_NAME = sql_row[1];
				bean.m_strF_ADDRESS = sql_row[2];
				bean.m_strF_BIRTH_DATE = sql_row[3];
				bean.m_strF_EMAIL_ADDR = sql_row[4];
				bean.m_strF_NICK_NAME = sql_row[5];
				bean.m_strF_SIGNATURE = sql_row[6];
				bean.m_strF_FACE_ID = sql_row[7];
				bean.m_eOnlineState = OnLineType(sql_row[8]);
				break;
			}
		}
	}
	else
	{
		return false;
	}
	if (result != NULL)
	{
		mysql_free_result(result);
	}
	return true;
}


/**
 * @brief 更新用户的其他信息
 * 
 * @param bean 用户的其他信息
 * @return true 成功
 * @return false 失败
 */
bool CMySqlConnect::UpdateUserInfo(const T_USER_INFO_BEAN& bean)
{
	int res = 0;
	std::string strTemplate2 = "UPDATE T_USER SET F_ADDRESS='{0}',F_BIRTH_DATE='{1}',F_EMAIL_ADDR='{2}',F_NICK_NAME='{3}',F_SIGNATURE='{4}',F_FACE_ID='{5}' WHERE F_USER_NAME='{6}';";
	std::string strSql = fmt::format(strTemplate2,bean.m_strF_ADDRESS,
		bean.m_strF_BIRTH_DATE,
		bean.m_strF_EMAIL_ADDR,
		bean.m_strF_NICK_NAME,
		bean.m_strF_SIGNATURE,
		bean.m_strF_FACE_ID,
		bean.m_strF_USER_NAME);
	LOG_INFO(m_loger, "SQL:{} [{}  {} ]", strSql, __FILENAME__, __LINE__);
	res = mysql_query(&m_mysql, strSql.c_str());//查询
	if (!res)
	{
		return true;
	}
	else
	{
		return false;
	}
	return false;
}

/**
 * @brief 插入用户的其他信息
 * 
 * @param bean 用户的其他信息
 * @return true 成功
 * @return false 失败
 */
bool CMySqlConnect::InsertUserInfo(const T_USER_INFO_BEAN& bean)
{
	int res = 0;
	std::string strTemplate2 = "INSERT INTO T_USER(\
F_USER_NAME,\
F_ADDRESS,\
F_BIRTH_DATE,\
F_EMAIL_ADDR,\
F_NICK_NAME,\
F_SIGNATURE,\
F_FACE_ID) VALUES('{0}','{1}','{2},'{3}','{4}','{5}','{6}');";
	std::string strSql = fmt::format(strTemplate2, bean.m_strF_USER_NAME, bean.m_strF_ADDRESS,bean.m_strF_BIRTH_DATE,bean.m_strF_EMAIL_ADDR,bean.m_strF_NICK_NAME,bean.m_strF_SIGNATURE,bean.m_strF_FACE_ID);

	LOG_INFO(m_loger, "SQL:{} [{}  {} ]", strSql, __FILENAME__, __LINE__);
	res = mysql_query(&m_mysql, strSql.c_str());//查询
	if (!res)
	{
		return true;
	}
	else
	{
		return false;
	}

}


/**
 * @brief 插入好友文本聊天消息到数据库
 * 
 * @param chatMsg 聊天消息
 * @return true 插入成功
 * @return false 失败
 */
bool CMySqlConnect::InsertFriendChatMsg(const T_USER_CHAT_MSG& chatMsg) {

	int res = 0;
	std::string strTemplate2 = "INSERT INTO T_FRIEND_CHAT_MSG(F_MSG_ID,\
F_MSG_TYPE,\
F_FROM_ID,\
F_TO_ID,\
F_MSG_CONTEXT,\
F_OTHER_INFO) VALUES('{0}','{1}','{2}','{3}','{4}','{5}');";

	std::string strSql = fmt::format(strTemplate2,chatMsg.m_strF_MSG_ID,ChatType(chatMsg.m_eChatMsgType),chatMsg.m_strF_FROM_ID,chatMsg.m_strF_TO_ID,chatMsg.m_strF_MSG_CONTEXT,chatMsg.m_strF_OTHER_INFO);
	LOG_INFO(m_loger, "SQL:{} [{}  {} ]", strSql, __FILENAME__, __LINE__);
	res = mysql_query(&m_mysql, strSql.c_str());//查询
	if (!res)
	{
		return true;
	}
	else
	{
		int nError = mysql_errno(&m_mysql);
		LOG_INFO(m_loger, "SQL_ERROR:{} [{}  {} ]", nError, __FILENAME__, __LINE__);
		return false;
	}
}


/**
 * @brief 根据消息ID更新消息的状态
 * 
 * @param strMsgId 消息ID
 * @param msgState 消息的状态，为未读('UN_READ')或者已读('READ')
 * @return true 成功
 * @return false 失败
 */
bool CMySqlConnect::UpdateFriendChatMsgState(const std::string& strMsgId, const std::string msgState)
{
	int res = 0;
	std::string strTemplate2 = "UPDATE T_FRIEND_CHAT_MSG SET F_READ_FLAG='{0}',F_READ_TIME=now() WHERE F_MSG_ID='{1}';";
	std::string strSql = fmt::format(strTemplate2, msgState, strMsgId);
	
	res = mysql_query(&m_mysql, strSql.c_str());//查询
	if (!res)
	{
		LOG_INFO(m_loger, "SQL:{} [{}  {} ]", strSql, __FILENAME__, __LINE__);
		return true;
	}
	else
	{
		LOG_ERR(m_loger, "SQL:{} [{}  {} ]", strSql, __FILENAME__, __LINE__);
		return false;
	}

}

/**
 * @brief 选择未读的聊天消息
 * 
 * @param strToID 接收方用户名
 * @param chatMsg 聊天消息
 * @return true 成功
 * @return false 失败
 */
bool CMySqlConnect::SelectUnReadFriendChatMsg(const std::string& strToID, T_USER_CHAT_MSG& chatMsg)
{
	bool bResult = false;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	int res = 0;
	std::string strTemplate2 = "SELECT F_MSG_ID,F_MSG_TYPE,F_FROM_ID,F_TO_ID,F_MSG_CONTEXT,F_OTHER_INFO,F_CREATE_TIME FROM T_FRIEND_CHAT_MSG WHERE F_TO_ID='{0}' AND F_READ_FLAG='UNREAD' ORDER BY F_MSG_ID LIMIT 1;";
	std::string strSql = fmt::format(strTemplate2,strToID);
	LOG_INFO(m_loger, "SQL:{} [{}  {} ]", strSql, __FILENAME__, __LINE__);
	res = mysql_query(&m_mysql, strSql.c_str());
	if (!res)
	{
		result = mysql_store_result(&m_mysql);
		if (result)
		{
			while (sql_row = mysql_fetch_row(result),sql_row != nullptr)
			{
				chatMsg.m_strF_MSG_ID = (sql_row[0]);
				chatMsg.m_eChatMsgType = ChatType(sql_row[1]);
				chatMsg.m_strF_FROM_ID = sql_row[2];
				chatMsg.m_strF_TO_ID = sql_row[3];
				chatMsg.m_strF_MSG_CONTEXT = sql_row[4];
				chatMsg.m_strF_OTHER_INFO = sql_row[5];
				chatMsg.m_strF_CREATE_TIME = sql_row[6];
				bResult = true;
				break;
			}
		}
	}
	else
	{
		return bResult;
	}
	if (result != NULL)
	{
		mysql_free_result(result);
		return bResult;
	}
	return bResult;
}

/**
 * @brief 删除好友聊天消息
 * 
 * @param msgId 消息ID
 * @return true 成功
 * @return false 失败
 */
bool CMySqlConnect::DeleteFriendChatMsg(const uint64_t msgId){
	int res = 0;
	std::string strTemplate2 = "DELETE FROM T_FRIEND_CHAT_MSG WHERE F_MSG_ID='{0}';";
	std::string strSql = fmt::format(strTemplate2, msgId);
	LOG_INFO(m_loger, "SQL:{} [{}  {} ]", strSql, __FILENAME__, __LINE__);
	res = mysql_query(&m_mysql, strSql.c_str());//查询
	if (!res)
	{

	}
	else
	{
		return false;
	}
	return true;
}


/**
 * @brief 获取某个用户的好友ID列表
 * 
 * @param strUserName 用户名
 * @param friendList 好友列表
 * @return true 成功
 * @return false 失败
 */
bool CMySqlConnect::GetUserFriendList(const std::string strUserName,std::vector<std::string>& friendList)
{
	bool bResult = false;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	int res = 0;
	std::string strTemplate2 = "SELECT F_FRIEND_ID FROM T_FRIEND_RELATION WHERE F_USER_ID='{0}';";
	std::string strSql = fmt::format(strTemplate2, strUserName);
	LOG_INFO(m_loger, "SQL:{} [{}  {} ]", strSql, __FILENAME__, __LINE__);
	res = mysql_query(&m_mysql, strSql.c_str());
	if (!res)
	{
		result = mysql_store_result(&m_mysql);
		if (result)
		{
			while (sql_row = mysql_fetch_row(result),sql_row != nullptr)
			{
				std::string strResult = sql_row[0];
				friendList.push_back(strResult);
				bResult = true;
			}
		}
	}
	else
	{
		return bResult;
	}
	if (result != NULL)
	{
		mysql_free_result(result);
		return bResult;
	}
	return bResult;
}

/**
 * @brief 插入好友关系
 * 
 * @param strUser 用户名
 * @param strFriend 好友用户名
 * @param relationType 关系类型(好友或者黑名单)
 * @return true 成功
 * @return false 失败
 */
bool CMySqlConnect::InsertFriendRelation(const std::string strUser, const std::string strFriend, const E_FRIEND_RELATION relationType)
{
	int res = 0;
	std::string strTemplate2 = "INSERT INTO T_FRIEND_RELATION(F_USER_ID,\
F_FRIEND_ID,\
F_TEAM_NAME,\
F_STATUS,F_CREATE_TIME) VALUES('{0}','{1}','MY Friend','{2}',now());";
	std::string strRelation = "FRIEND";
	if (relationType == E_FRIEND_RELATION::E_BLACK_TYPE)
	{
		strRelation = "BLACK";
	}
	std::string strSql = fmt::format(strTemplate2, strUser, strFriend, strRelation);
	LOG_INFO(m_loger, "SQL:{} [{}  {} ]", strSql, __FILENAME__, __LINE__);
	res = mysql_query(&m_mysql, strSql.c_str());//查询
	if (!res)
	{

	}
	else
	{
		return false;
	}
	return true;
}

/**
 * @brief 删除好友关系
 * 
 * @param strUser 用户名
 * @param strFriend 好友用户名
 * @return true 成功
 * @return false 失败
 */
bool CMySqlConnect::DeleteFriendRelation(const std::string strUser, const std::string strFriend)
{
	int res = 0;
	std::string strTemplate2 = "DELETE FROM T_FRIEND_RELATION WHERE F_USER_ID='{0}' AND F_FRIEND_ID='{1}';";
	std::string strSql = fmt::format(strTemplate2, strUser,strFriend);
	LOG_INFO(m_loger, "SQL:{} [{}  {} ]", strSql, __FILENAME__, __LINE__);
	res = mysql_query(&m_mysql, strSql.c_str());//查询
	if (!res)
	{

	}
	else
	{
		return false;
	}
	return true;
}

/**
 * @brief 查询A用户和B用户的好友关系
 * 
 * @param strUser 用户名
 * @param strFriend 好友用户名
 * @param relationType 关系类型
 * @return true 成功
 * @return false 失败
 */
bool CMySqlConnect::SelectFriendRelation(const std::string strUser, const std::string strFriend, E_FRIEND_RELATION& relationType)
{
	bool bResult = false;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	int res = 0;
	std::string strTemplate2 = "SELECT F_STATUS FROM T_FRIEND_RELATION WHERE F_USER_NAME='{0}' AND F_FRIEND_NAME='{1}';";
	std::string strSql = fmt::format(strTemplate2, strUser, strFriend);
	LOG_INFO(m_loger, "SQL:{} [{}  {} ]", strSql, __FILENAME__, __LINE__);
	res = mysql_query(&m_mysql, strSql.c_str());
	if (!res)
	{
		result = mysql_store_result(&m_mysql);
		if (result)
		{
			while (sql_row = mysql_fetch_row(result),sql_row != nullptr)
			{
				if(std::string(sql_row[0])=="FRIEND")
				{
					relationType = E_FRIEND_RELATION::E_FRIEND_TYPE;
				}
				else if(std::string(sql_row[0])=="BLACK")
				{
					relationType = E_FRIEND_RELATION::E_BLACK_TYPE;
				}
				else
				{
					relationType = E_FRIEND_RELATION::E_STRANGER_TYPE;
				}
				bResult = true;
				break;
			}
		}
	}
	else
	{
		return bResult;
	}
	if (result != NULL)
	{
		mysql_free_result(result);
		return bResult;
	}
	return bResult;
}

/**
 * @brief 更新好友关系
 * 
 * @param strUser 用户名
 * @param strFriend 好友用户名
 * @param relationType 好友类型 
 * @return true 成功
 * @return false 失败
 */
bool CMySqlConnect::UpdateFriendRelation(const std::string strUser, const std::string strFriend, const E_FRIEND_RELATION relationType)
{
	DeleteFriendRelation(strUser, strFriend);
	return InsertFriendRelation(strUser, strFriend, relationType);
}


/**
 * @brief 插入添加好友的消息
 * 
 * @param msgBean 添加好友消息的内容
 * @return true 成功
 * @return false 失败
 */
bool CMySqlConnect::InsertAddFriendMsg(const T_ADD_FRIEND_MSG_BEAN msgBean)
{
	int res = 0;
	std::string strTemplate2 = "INSERT INTO T_ADD_FRIEND_MSG(F_MSG_ID,\
F_USER_ID,\
F_FRIEND_ID,\
F_ADD_FRIEND_STATUS,\
F_FRIEND_OPTION,F_CREATE_TIME)\
VALUES('{0}','{1}','{2}','{3}','{4}',now());";

	std::string strSql = fmt::format(strTemplate2, 
								msgBean.m_strF_MSG_ID,
								msgBean.m_strF_USER_ID,
								msgBean.m_strF_FRIEND_ID,
								FriendStatus(msgBean.m_eF_ADD_FRIEND_STATUS),
		                        FriendOption(msgBean.m_eF_FRIEND_OPTION));
	LOG_INFO(m_loger, "SQL:{} [{}  {} ]", strSql, __FILENAME__, __LINE__);
	res = mysql_query(&m_mysql, strSql.c_str());//查询
	if (!res)
	{

	}
	else
	{
		return false;
	}
	return true;
}

/**
 * @brief 选择没有读取的添加好友消息[发送方发起了申请，但是接收方还没有收到的]
 * 
 * @param strUserName 用户名
 * @param msgBean 添加好友消息
 * @return true 成功
 * @return false 失败
 */
bool CMySqlConnect::SelectUnReadAddFriendMsg(const std::string strUserName, T_ADD_FRIEND_MSG_BEAN& msgBean)
{
	bool bResult = false;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	int res = 0;
	std::string strTemplate2 = "SELECT F_MSG_ID,F_USER_ID FROM T_ADD_FRIEND_MSG WHERE F_FRIEND_ID='{0}' AND F_ADD_FRIEND_STATUS='UN_READ';";
	std::string strSql = fmt::format(strTemplate2, strUserName);
	LOG_INFO(m_loger, "SQL:{} [{}  {} ]", strSql, __FILENAME__, __LINE__);
	res = mysql_query(&m_mysql, strSql.c_str());
	if (!res)
	{
		result = mysql_store_result(&m_mysql);
		if (result)
		{
			while (sql_row = mysql_fetch_row(result),sql_row != nullptr)
			{
				msgBean.m_strF_MSG_ID = sql_row[0];
				msgBean.m_strF_FRIEND_ID = sql_row[1];
				msgBean.m_strF_USER_ID = strUserName;
				bResult = true;
				break;
			}
		}
	}
	else
	{
		return bResult;
	}
	if (result != NULL)
	{
		mysql_free_result(result);
		return bResult;
	}
	return bResult;
}


/**
 * @brief 选择没有通知的添加好友消息[被添加方已经回复，但是发送方还没有收到通知]
 * 
 * @param strUserName 用户名
 * @param msgBean 添加好友消息
 * @return true 成功
 * @return false 失败
 */
bool CMySqlConnect::SelectUnNotifyAddFriendMsg(const std::string strUserName, T_ADD_FRIEND_MSG_BEAN& msgBean)
{
	bool bResult = false;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	int res = 0;
	std::string strTemplate2 = "SELECT F_MSG_ID,\
F_FRIEND_ID,F_FRIEND_OPTION  FROM T_ADD_FRIEND_MSG WHERE F_USER_ID='{0}' AND F_ADD_FRIEND_STATUS='READ_UN_NOTIFY';";
	std::string strSql = fmt::format(strTemplate2, strUserName);
	LOG_INFO(m_loger, "SQL:{} [{}  {} ]", strSql, __FILENAME__, __LINE__);
	res = mysql_query(&m_mysql, strSql.c_str());
	if (!res)
	{
		result = mysql_store_result(&m_mysql);
		if (result)
		{
			while (sql_row = mysql_fetch_row(result),sql_row != nullptr)
			{
				msgBean.m_strF_MSG_ID = sql_row[0];
				msgBean.m_strF_USER_ID = strUserName;
				msgBean.m_strF_FRIEND_ID = sql_row[1];
				msgBean.m_eF_FRIEND_OPTION = FriendOption(sql_row[2]);
				bResult = true;
				break;
			}
		}
	}
	else
	{
		return bResult;
	}
	if (result != NULL)
	{
		mysql_free_result(result);
		return bResult;
	}
	return bResult;
}

/**
 * @brief 更新添加好友消息为通知的状态[发送方已经接收到添加好友的通知]
 * 
 * @param strMsgId 消息ID
 * @return true 成功
 * @return false 失败
 */
bool CMySqlConnect::UpdateToNotifyAddFriendMsg(const std::string strMsgId)
{
	int res = 0;
	std::string strTemplate2 = "UPDATE T_ADD_FRIEND_MSG SET F_ADD_FRIEND_STATUS='NOTIFY',F_NOTIFY_TIME=now() WHERE F_MSG_ID='{0}';";
	std::string strSql = fmt::format(strTemplate2, strMsgId);
	LOG_INFO(m_loger, "SQL:{} [{}  {} ]", strSql, __FILENAME__, __LINE__);
	res = mysql_query(&m_mysql, strSql.c_str());//查询
	if (!res)
	{

	}
	else
	{
		return false;
	}
	return true;
}

/**
 * @brief 更新添加好友消息的状态为已读但是未通知的状态
 * 
 * @param strMsgId 消息ID
 * @param option 用户选择
 * @return true 成功
 * @return false 失败
 */
bool CMySqlConnect::UpdateToReadUnNotifyAddFriendMsg(const std::string strMsgId,const E_FRIEND_OPTION option)
{
	int res = 0;
	std::string strTemplate2 = "UPDATE T_ADD_FRIEND_MSG SET F_ADD_FRIEND_STATUS='READ_UN_NOTIFY',F_FRIEND_OPTION='{0}',F_OPTION_TIME=now() WHERE F_MSG_ID='{1}';";
	std::string strSql = fmt::format(strTemplate2, FriendOption(option), strMsgId);
	LOG_INFO(m_loger, "SQL:{} [{}  {} ]", strSql, __FILENAME__, __LINE__);
	res = mysql_query(&m_mysql, strSql.c_str());//查询
	if (!res)
	{

	}
	else
	{
		return false;
	}
	return true;
}

/**
 * @brief 插入用户分组
 * 
 * @param teamBean 用户分组
 * @return true 成功
 * @return false 失败
 */
bool CMySqlConnect::InsertUserTeam(const T_USER_TEAM_BEAN& teamBean)
{
	int res = 0;
	std::string strTemplate2 = "INSERT INTO T_USER_TEAM(F_TEAM_ID,F_USER_NAME,F_TEAM_NAME,F_CREATE_TIME) VALUES('{0}','{1}','{2}',now());";
	std::string strSql = fmt::format(strTemplate2, teamBean.m_strF_TEAM_ID, teamBean.m_strF_USER_NAME, teamBean.m_strF_TEAM_NAME);

	LOG_INFO(m_loger, "SQL:{} [{}  {} ]", strSql, __FILENAME__, __LINE__);
	res = mysql_query(&m_mysql, strSql.c_str());//查询
	if (!res)
	{

	}
	else
	{
		return false;
	}
	return true;
}


/**
 * @brief 删除用户分组
 * 
 * @param teamBean 用户分组
 * @return true 成功
 * @return false 失败
 */
bool CMySqlConnect::DeleteUserTeam(const T_USER_TEAM_BEAN& teamBean)
{
	int res = 0;
	std::string strTemplate2 = "DELETE FROM T_USER_TEAM WHERE F_TEAM_ID='{0}' AND F_USER_NAME='{1}';";
	std::string strSql = fmt::format(strTemplate2, teamBean.m_strF_TEAM_ID,teamBean.m_strF_USER_NAME);
	LOG_INFO(m_loger, "SQL:{} [{}  {} ]", strSql, __FILENAME__, __LINE__);
	res = mysql_query(&m_mysql, strSql.c_str());//查询
	if (!res)
	{

	}
	else
	{
		return false;
	}
	return true;
}

/**
 * @brief 查找用户的所有分组
 * 
 * @param strUserName 用户名
 * @param teamBeans 该用户的所有分组
 * @return true 成功
 * @return false 失败
 */
bool CMySqlConnect::SelectUserTeams(const std::string strUserName, std::vector<T_USER_TEAM_BEAN>& teamBeans)
{
	bool bResult = false;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	int res = 0;
	std::string strTemplate2 = "SELECT F_TEAM_ID,F_USER_NAME,F_TEAM_NAME FROM T_USER_TEAM WHERE F_USER_NAME='{0}';";
	std::string strSql = fmt::format(strTemplate2, strUserName);
	LOG_INFO(m_loger, "SQL:{} [{}  {} ]", strSql, __FILENAME__, __LINE__);
	res = mysql_query(&m_mysql, strSql.c_str());
	if (!res)
	{
		result = mysql_store_result(&m_mysql);
		if (result)
		{
			T_USER_TEAM_BEAN bean;
			while (sql_row = mysql_fetch_row(result),sql_row != nullptr)
			{
				bean.m_strF_TEAM_ID = sql_row[0];
				bean.m_strF_USER_NAME = sql_row[1];
				bean.m_strF_TEAM_NAME = sql_row[2];
				teamBeans.push_back(bean);
				bResult = true;
			}
		}
	}
	else
	{
		return bResult;
	}
	if (result != NULL)
	{
		mysql_free_result(result);
		return bResult;
	}
	return bResult;
}


/**
 * @brief 更新用户的分组名
 * 
 * @param teamBean 用户分组信息
 * @return true 成功
 * @return false 失败
 */
bool CMySqlConnect::UpdateUserTeamName(const T_USER_TEAM_BEAN& teamBean)
{
	int res = 0;
	std::string strTemplate2 = "UPDATE T_USER_TEAM SET F_TEAM_NAME='{0}' WHERE F_TEAM_ID='{1}' AND F_USER_NAME='{2}";
	std::string strSql = fmt::format(strTemplate2, teamBean.m_strF_TEAM_NAME,teamBean.m_strF_TEAM_ID, teamBean.m_strF_USER_NAME);
	LOG_INFO(m_loger, "SQL:{} [{}  {} ]", strSql, __FILENAME__, __LINE__);
	res = mysql_query(&m_mysql, strSql.c_str());//查询
	if (!res)
	{

	}
	else
	{
		return false;
	}
	return true;
}


/**
 * @brief 创建群聊
 * 
 * @param groupBean 群聊信息 
 * @return true 成功
 * @return false 失败
 */
bool CMySqlConnect::InsertGroup(const T_GROUP_BEAN& groupBean)
{
	int res = 0;
	std::string strTemplate2 = "INSERT INTO T_GROUP(F_GROUP_ID,F_GROUP_NAME,F_CREATE_TIME,F_GROUP_INFO) VALUES('{0}','{1}',now(),'{2}');";
	std::string strSql = fmt::format(strTemplate2, groupBean.m_strF_GROUP_ID, groupBean.m_strF_GROUP_NAME, "NO INFO");

	LOG_INFO(m_loger, "SQL:{} [{}  {} ]", strSql, __FILENAME__, __LINE__);
	res = mysql_query(&m_mysql, strSql.c_str());//查询
	if (!res)
	{

	}
	else
	{
		return false;
	}
	return true;
}

bool CMySqlConnect::SelectGroupById(const std::string groupId, T_GROUP_BEAN& groupBean)
{
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	bool bResult = false;
	int res = 0;
	std::string strTemplate2 = "SELECT F_GROUP_ID,F_GROUP_NAME FROM T_GROUP WHERE F_GROUP_ID = '{0}';";
	std::string strSql = fmt::format(strTemplate2, groupId);
	LOG_INFO(m_loger, "SQL:{} [{}  {} ]", strSql, __FILENAME__, __LINE__);
	res = mysql_query(&m_mysql, strSql.c_str());
	T_GROUP_BEAN bean;
	if (!res)
	{
		result = mysql_store_result(&m_mysql);
		if (result)
		{
			while (sql_row = mysql_fetch_row(result),sql_row != nullptr)
			{
				groupBean.m_strF_GROUP_ID = sql_row[0];
				groupBean.m_strF_GROUP_NAME = sql_row[1];
				bResult = true;
			}
		}
	}
	else
	{
		return bResult;
	}
	if (result != NULL)
	{
		mysql_free_result(result);
	}
	return bResult;
}


/**
 * @brief 解散群聊
 * 
 * @param strGroupId 群聊ID  
 * @return true 成功
 * @return false 失败
 */
bool CMySqlConnect::DeleteGroup(const std::string strGroupId)
{
	int res = 0;
	std::string strTemplate2 = "DELETE FROM T_GROUP WHERE F_GROUP_ID='{0}';";
	std::string strSql = fmt::format(strTemplate2, strGroupId);
	LOG_INFO(m_loger, "SQL:{} [{}  {} ]", strSql, __FILENAME__, __LINE__);
	res = mysql_query(&m_mysql, strSql.c_str());//查询
	if (!res)
	{

	}
	else
	{
		return false;
	}
	return true;
}

/**
 * @brief 根据群组名查找群组
 * 
 * @param strGroupName 群组名
 * @param groupBeans 查找到的所有群组
 * @return true 查找成功
 * @return false 查找失败
 */
bool CMySqlConnect::SelectGroups(const std::string strGroupName, std::vector<T_GROUP_BEAN>& groupBeans)
{
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	bool bResult = false;
	int res = 0;
	std::string strTemplate2 = "SELECT F_GROUP_ID,F_GROUP_NAME FROM T_GROUP WHERE F_GROUP_NAME LIKE '{0}' OR F_GROUP_ID LIKE '{0}';";
	std::string strSql = fmt::format(strTemplate2, strGroupName);
	LOG_INFO(m_loger, "SQL:{} [{}  {} ]", strSql, __FILENAME__, __LINE__);
	res = mysql_query(&m_mysql, strSql.c_str());
	T_GROUP_BEAN bean;
	if (!res)
	{
		result = mysql_store_result(&m_mysql);
		if (result)
		{
			while (sql_row = mysql_fetch_row(result),sql_row != nullptr)
			{
				bean.m_strF_GROUP_ID = sql_row[0];
				bean.m_strF_GROUP_NAME = sql_row[1];
				groupBeans.push_back(bean);
				bResult = true;
			}
		}
	}
	else
	{
		return bResult;
	}
	if (result != NULL)
	{
		mysql_free_result(result);
	}
	return bResult;
}


/**
 * @brief 插入用户和群组的关系
 * 
 * @param memBean　用户群组消息
 * @return true 成功
 * @return false 失败
 */
bool CMySqlConnect::InsertGroupRelation(const T_GROUP_RELATION_BEAN& memBean)
{
	int res = 0;
	std::string strTemplate2 = "INSERT INTO T_GROUP_RELATION(F_GROUP_ID,F_USER_ID,F_ROLE_TYPE,F_CREATE_TIME) VALUES('{0}','{1}','{2}',now());";
	std::string strSql = fmt::format(strTemplate2, memBean.m_strF_GROUP_ID, memBean.m_strF_USER_ID,MemberRole(memBean.m_eRole));

	LOG_INFO(m_loger, "SQL:{} [{}  {} ]", strSql, __FILENAME__, __LINE__);
	res = mysql_query(&m_mysql, strSql.c_str());//查询
	if (!res)
	{

	}
	else
	{
		return false;
	}
	return true;
}


/**
 * @brief 更新用户和群组关系
 * 
 * @param memBean 新的用户群组关系
 * @return true 成功
 * @return false 失败
 */
bool CMySqlConnect::UpdateGroupRelation(const T_GROUP_RELATION_BEAN& memBean)
{
	int res = 0;
	std::string strTemplate2 = "UPDATE T_GROUP_RELATION SET F_ROLE_TYPE='{0}' WHERE F_GROUP_ID='{1}' AND F_USER_ID='{2}';";
	std::string strSql = fmt::format(strTemplate2,MemberRole(memBean.m_eRole),memBean.m_strF_GROUP_ID, memBean.m_strF_USER_ID);
	LOG_INFO(m_loger, "SQL:{} [{}  {} ]", strSql, __FILENAME__, __LINE__);
	res = mysql_query(&m_mysql, strSql.c_str());//查询
	if (!res)
	{

	}
	else
	{
		return false;
	}
	return true;
}

/**
 * @brief 根据群组ID和用户ID，更新该用户的最后已读消息
 * 
 * @param memBean 传入群组ID，用户ID和已读消息ID
 * @return true 更新成功
 * @return false 更新失败
 */
bool CMySqlConnect::UpdateGroupRelationLastReadId(const T_GROUP_RELATION_BEAN& memBean)
{
	int res = 0;
	std::string strTemplate2 = "UPDATE T_GROUP_RELATION SET F_LAST_READ_MSG_ID='{0}' WHERE F_GROUP_ID='{1}' AND F_USER_ID='{2}';";
	std::string strSql = fmt::format(strTemplate2, memBean.m_strF_LAST_READ_MSG_ID, memBean.m_strF_GROUP_ID, memBean.m_strF_USER_ID);
	LOG_INFO(m_loger, "SQL:{} [{}  {} ]", strSql, __FILENAME__, __LINE__);
	res = mysql_query(&m_mysql, strSql.c_str());//查询
	if (!res)
	{

	}
	else
	{
		return false;
	}
	return true;
}

/**
 * @brief 删除用户和群组关系，退出群组和解散群组的时候使用
 * 
 * @param memBean 用户群组关系
 * @return true 成功
 * @return false 失败
 */
bool CMySqlConnect::DeleteGroupRelation(const T_GROUP_RELATION_BEAN& memBean)
{
	int res = 0;
	std::string strTemplate2 = "DELETE FROM T_GROUP_RELATION WHERE F_GROUP_ID='{0}' AND F_USER_ID='{1}';";
	std::string strSql = fmt::format(strTemplate2, memBean.m_strF_GROUP_ID,memBean.m_strF_USER_ID);
	LOG_INFO(m_loger, "SQL:{} [{}  {} ]", strSql, __FILENAME__, __LINE__);
	res = mysql_query(&m_mysql, strSql.c_str());//查询
	if (!res)
	{

	}
	else
	{
		return false;
	}
	return true;
}


/**
 * @brief 查找某个用户所在的所有群组
 * 
 * @param strUserName 用户名
 * @param memBeans 所在的全部群组
 * @return true 成功
 * @return false 失败
 */
bool CMySqlConnect::SelectUserGroupRelation(const std::string strUserName, std::vector<T_GROUP_RELATION_BEAN>& memBeans)
{
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	int res = 0;
	std::string strTemplate2 = "SELECT F_GROUP_ID,F_ROLE_TYPE FROM T_GROUP_RELATION WHERE F_USER_ID='{0}';";
	std::string strSql = fmt::format(strTemplate2, strUserName);
	LOG_INFO(m_loger, "SQL:{} [{}  {} ]", strSql, __FILENAME__, __LINE__);
	res = mysql_query(&m_mysql, strSql.c_str());
	if (!res)
	{
		result = mysql_store_result(&m_mysql);
		if (result)
		{
			T_GROUP_RELATION_BEAN bean;
			bean.m_strF_USER_ID = strUserName;
			while (sql_row = mysql_fetch_row(result),sql_row != nullptr)
			{
				bean.m_strF_GROUP_ID = sql_row[0];
				bean.m_eRole = MemberRole(sql_row[1]);
				memBeans.push_back(bean);
			}
		}
	}
	else
	{
		return false;
	}
	if (result != NULL)
	{
		mysql_free_result(result);
	}
	return true;
}

/**
 * @brief 查找某个群组中的全部成员
 * 
 * @param strGroupId 群组ID
 * @param memBeans 群组的全部成员
 * @return true 成功
 * @return false 失败
 */
bool CMySqlConnect::SelectGroupRelation(const std::string strGroupId, std::vector<T_GROUP_RELATION_BEAN>& memBeans)
{
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	int res = 0;
	std::string strTemplate2 = "SELECT F_USER_ID,F_ROLE_TYPE,F_LAST_READ_MSG_ID FROM T_GROUP_RELATION WHERE F_GROUP_ID='{0}';";
	std::string strSql = fmt::format(strTemplate2, strGroupId);
	LOG_INFO(m_loger, "SQL:{} [{}  {} ]", strSql, __FILENAME__, __LINE__);
	res = mysql_query(&m_mysql, strSql.c_str());
	if (!res)
	{
		result = mysql_store_result(&m_mysql);
		if (result)
		{
			T_GROUP_RELATION_BEAN bean;
			while (sql_row = mysql_fetch_row(result),sql_row != nullptr)
			{
				bean.m_strF_USER_ID = sql_row[0];
				bean.m_eRole = MemberRole(sql_row[1]);
				bean.m_strF_LAST_READ_MSG_ID = sql_row[2];
				memBeans.push_back(bean);
			}
		}
	}
	else
	{
		return false;
	}
	if (result != NULL)
	{
		mysql_free_result(result);
	}
	return true;
}



/**
 * @brief 根据群组ID和消息ID,查询该群组下该消息以后的新消息，
 * 
 * @param chatMsg 传入群组ID和消息ID,同时传回消息内容和发送者
 * @return true 成功
 * @return false 失败
 */
bool CMySqlConnect::SelectGroupChatText(T_GROUP_CHAT_MSG& chatMsg)
{
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	int res = 0;
	std::string strTemplate2 = "SELECT F_MSG_ID,\
F_MSG_TYPE,\
F_SENDER_ID,\
F_MSG_CONTEXT,\
F_OTHER_INFO,\
F_CREATE_TIME \
FROM T_GROUP_CHAT_MSG WHERE F_GROUP_ID='{0}' AND F_MSG_ID > '{1}' LIMIT 1;";
	std::string strSql = fmt::format(strTemplate2, chatMsg.m_strF_GROUP_ID,chatMsg.m_strF_MSG_ID);
	LOG_INFO(m_loger, "SQL:{} [{}  {} ]", strSql, __FILENAME__, __LINE__);
	res = mysql_query(&m_mysql, strSql.c_str());
	if (!res)
	{
		result = mysql_store_result(&m_mysql);
		if (result)
		{
			while (sql_row = mysql_fetch_row(result),sql_row != nullptr)
			{
				chatMsg.m_strF_MSG_ID = sql_row[0];
				chatMsg.m_eChatMsgType = ChatType(sql_row[1]);
				chatMsg.m_strF_SENDER_ID = sql_row[2];
				chatMsg.m_strF_MSG_CONTEXT = sql_row[3];
				chatMsg.m_strF_OTHER_INFO = sql_row[4];
				chatMsg.m_strF_CREATE_TIME = sql_row[5];
				break;
			}
		}
	}
	else
	{
		return false;
	}
	if (result != NULL)
	{
		mysql_free_result(result);
	}
	return true;
}


/**
 * @brief 插入群组聊天文本消息
 * 
 * @param chatMsg 群组聊天消息
 * @return true 插入成功
 * @return false 插入失败
 */
bool CMySqlConnect::InsertGroupChatText(const T_GROUP_CHAT_MSG& chatMsg)
{
	int res = 0;
	std::string strTemplate2 = "INSERT INTO T_GROUP_CHAT_MSG(F_MSG_ID,\
F_MSG_TYPE,\
F_SENDER_ID,\
F_GROUP_ID,\
F_MSG_CONTEXT,\
F_OTHER_INFO,\
F_CREATE_TIME) VALUES('{0}','{1}','{2}','{3}','{4}','{5}',now());";
	std::string strSql = fmt::format(strTemplate2, chatMsg.m_strF_MSG_ID,
		ChatType(chatMsg.m_eChatMsgType), 
		chatMsg.m_strF_SENDER_ID,
		chatMsg.m_strF_GROUP_ID,
		chatMsg.m_strF_MSG_CONTEXT,
		chatMsg.m_strF_OTHER_INFO);

	LOG_INFO(m_loger, "SQL:{} [{}  {} ]", strSql, __FILENAME__, __LINE__);
	res = mysql_query(&m_mysql, strSql.c_str());//查询
	if (!res)
	{

	}
	else
	{
		return false;
	}
	return true;
}