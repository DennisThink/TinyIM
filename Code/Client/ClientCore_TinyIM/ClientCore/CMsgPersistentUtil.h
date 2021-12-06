
/**
 * @file CMsgPersistentUtil.h
 * @author DennisMi (https://www.dennisthink.com/)
 * @brief 客户端消息持久化的类
 * @version 0.1
 * @date 2019-09-12
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef _DENNIS_THINK_C_MSG_PERSISTENT_UTIL_H_
#define _DENNIS_THINK_C_MSG_PERSISTENT_UTIL_H_
#include <memory>
#include "CommonMsg.h"
#include "SQLiteCpp/SQLiteCpp.h"
#include "SQLiteCpp/VariadicBind.h"
#include "Log.h"

class CMsgPersistentUtil: public std::enable_shared_from_this<CMsgPersistentUtil>
{
public:
	bool InitDataBase();
	static std::shared_ptr<spdlog::logger> ms_logger;

private:

	
	SQLite::Database*    m_pDb;    ///< Database connection
	//FriendChat Msg
	SQLite::Statement*   m_pFriendChatCreate; ///< Database prepared SQL query

	//GroupChatMsg Msg
	SQLite::Statement*   m_pGroupChatCreate; ///< Database prepared SQL query

	SQLite::Statement*   m_pGroupChatInsert; ///< Database prepared SQL query

	SQLite::Statement*   m_pGroupChatSelect; ///< Database prepared SQL query

	SQLite::Statement*   m_pGroupChatUpdate; ///< Database prepared SQL query

};
using CMsgPersistentUtil_SHARED_PTR = std::shared_ptr<CMsgPersistentUtil>;
#endif