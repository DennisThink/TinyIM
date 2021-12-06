/**
 * @file CMsgPersistentUtil.cpp
 * @author DennisMi (https://www.dennisthink.com/)
 * @brief 消息持久化实现
 * @version 0.1
 * @date 2019-09-12
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "CMsgPersistentUtil.h"
#include "fmt/format.h"
#include <time.h>
/**
 * @brief 初始化数据库
 * 
 * @return true 
 * @return false 
 */

std::shared_ptr<spdlog::logger> CMsgPersistentUtil::ms_logger=nullptr;
bool CMsgPersistentUtil::InitDataBase()
{
	if (nullptr == ms_logger)
	{
		ms_logger = spdlog::default_logger();
	}
	m_pDb = new SQLite::Database("TinyDemo.db",SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
	if (m_pDb->tableExists("T_FRIEND_CHAT_MSG"))
	{
		LOG_INFO(ms_logger, "TABLE T_FRIEND_CHAT_MSG is Exist [ {} {} ]", __FILE__, __LINE__);
	}
	else
	{
		std::string strSQL = R"(CREATE TABLE T_FRIEND_CHAT_MSG(
		F_MSG_ID TEXT,
		F_MSG_TYPE TEXT,
        F_FROM_ID TEXT,
		F_TO_ID TEXT,
		F_MSG_CONTEXT TEXT,
        F_OTHER_INFO TEXT,
		F_READ_FLAG TEXT,
		F_CREATE_TIME TEXT))";
		m_pFriendChatCreate = new SQLite::Statement(*m_pDb, strSQL);
		m_pFriendChatCreate->executeStep();
		// Reset the query to be able to use it again later
		m_pFriendChatCreate->reset();
	}


	if (m_pDb->tableExists("T_GROUP_CHAT_MSG"))
	{
		LOG_INFO(ms_logger, "TABLE T_GROUP_CHAT_MSG is Exist [ {} {} ]", __FILE__, __LINE__);
	}
	else
	{
		std::string strSQL = R"(CREATE TABLE T_GROUP_CHAT_MSG(
		F_MSG_ID TEXT,
		F_MSG_TYPE TEXT,
        F_USER_ID TEXT,
		F_GROUP_ID TEXT,
		F_MSG_CONTEXT TEXT,
        F_OTHER_INFO TEXT,
		F_READ_FLAG TEXT,
		F_CREATE_TIME TEXT))";
		m_pGroupChatCreate = new SQLite::Statement(*m_pDb, strSQL);
		m_pGroupChatCreate->executeStep();
		// Reset the query to be able to use it again later
		m_pGroupChatCreate->reset();
	}

	if(nullptr == m_pGroupChatSelect)
	{
		std::string strSQL = R"(SELECT * FROM T_GROUP_CHAT_MSG WHERE F_READ_FLAG='UN_READ')";

		m_pGroupChatSelect = new SQLite::Statement(*m_pDb, strSQL);
	}


	return true;
}
