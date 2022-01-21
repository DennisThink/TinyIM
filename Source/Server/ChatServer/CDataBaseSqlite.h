#ifndef _TINY_IM_SERVER_DATABASE_SQLITE_H_
#define _TINY_IM_SERVER_DATABASE_SQLITE_H_
#include "CDataBaseInterface.h"
#include "SQLiteCpp/SQLiteCpp.h"
#include "SQLiteCpp/VariadicBind.h"
class CDbSqlite:public CDbInterface
{
    public:
    CDbSqlite();      
    virtual bool InitDataBase();
    virtual bool SelectUserByName(const std::string userName,T_USER_BEAN& bean);
    
	virtual bool UpdateUser(const T_USER_BEAN& bean);
    
	virtual bool DeleteUser(const std::string strUserId);

    virtual bool InsertUser(const T_USER_BEAN& bean);
	
	virtual bool IsUserExist(const std::string strUserId);
private:
    SQLite::Database*    m_pDb;    ///< Database connection
    std::string m_strDataBaseFileName;
	//FriendChat Msg
	//SQLite::Statement*   m_pFriendChatCreate; ///< Database prepared SQL query

	//GroupChatMsg Msg
	/*SQLite::Statement*   m_pGroupChatCreate; ///< Database prepared SQL query

	SQLite::Statement*   m_pGroupChatInsert; ///< Database prepared SQL query

	SQLite::Statement*   m_pGroupChatSelect; ///< Database prepared SQL query

	SQLite::Statement*   m_pGroupChatUpdate; ///< Database prepared SQL query*/
};
#endif