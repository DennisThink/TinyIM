/**
 * @file CMySqlConnect.h
 * @author DennisMi (https://www.dennisthink.com/)
 * @brief 
 * @version 0.1
 * @date 2019-07-19
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef _DENNIS_C_MYSQL_CONNECT_H_
#define _DENNIS_C_MYSQL_CONNECT_H_
#include "mysql.h"
#include <string>
#include "CMysqlStruct.h"
#include "Log.h"
class CMySqlConnect
{
public:
    explicit CMySqlConnect();
    virtual ~CMySqlConnect();
    //bool ConnectToServer();
    bool ConnectToServer(const std::string userName,
                         const std::string passwd,
                         const std::string database,
                         const std::string strHost,
                         const int port=3306);
    
    bool SelectUserByName(const std::string userName,T_USER_BEAN& bean);
    
	bool UpdateUser(const T_USER_BEAN& bean);
    
	bool DeleteUser(const std::string strUserId);

    bool InsertUser(const T_USER_BEAN& bean);
	
	bool IsUserExist(const std::string strUserId);

	bool SelectUserInfoByName(const std::string userName, T_USER_INFO_BEAN& bean);
	bool UpdateUserInfo(const T_USER_INFO_BEAN& bean);
	bool UpdateUserOnlineState(const std::string strUserId, const CLIENT_ONLINE_TYPE);
	bool InsertUserInfo(const T_USER_INFO_BEAN& bean);


	bool InsertAddFriendMsg(const T_ADD_FRIEND_MSG_BEAN msgBean);
	bool SelectUnReadAddFriendMsg(const std::string strUserName, T_ADD_FRIEND_MSG_BEAN& msgBean);
	bool SelectUnNotifyAddFriendMsg(const std::string strUserName, T_ADD_FRIEND_MSG_BEAN& msgBean);
	bool UpdateToNotifyAddFriendMsg(const std::string strMsgId);
	bool UpdateToReadUnNotifyAddFriendMsg(const std::string strMsgId, const E_FRIEND_OPTION option);

	bool IsFriend(const std::string strUser, const std::string strFriend);
	bool InsertFriendRelation(const std::string strUser, const std::string strFriend, const E_FRIEND_RELATION relationType);
	bool DeleteFriendRelation(const std::string strUser, const std::string strFriend);
	bool SelectFriendRelation(const std::string strUser, const std::string strFriend, E_FRIEND_RELATION& relationType);
	bool UpdateFriendRelation(const std::string strUser, const std::string strFriend, const E_FRIEND_RELATION relationType);
	bool GetUserFriendList(const std::string strUser, std::vector<std::string>& friendList);
	
	bool InsertFriendChatMsg(const T_USER_CHAT_MSG& chatMsg);
	bool SelectUnReadFriendChatMsg(const std::string& strToId, T_USER_CHAT_MSG& chatMsg);
	bool UpdateFriendChatMsgState(const std::string& strMsgId, const std::string msgState);
	bool DeleteFriendChatMsg(const uint64_t msgId);

	bool InsertUserTeam(const T_USER_TEAM_BEAN& teamBean);
	bool DeleteUserTeam(const T_USER_TEAM_BEAN& teamBean);
	bool SelectUserTeams(const std::string strUserName, std::vector<T_USER_TEAM_BEAN>& teamBeans);
	bool UpdateUserTeamName(const T_USER_TEAM_BEAN& teamBean);

	//Group 
	bool InsertGroup(const T_GROUP_BEAN& groupBean);
	
	bool DeleteGroup(const std::string strGroupId);
	bool SelectGroupById(const std::string groupId, T_GROUP_BEAN& groupBean);
	bool SelectGroups(const std::string strGroupName, std::vector<T_GROUP_BEAN>& groupBeans);

	//Group Member
	bool InsertGroupRelation(const T_GROUP_RELATION_BEAN& memBean);

	bool UpdateGroupRelation(const T_GROUP_RELATION_BEAN& memBean);

	bool UpdateGroupRelationLastReadId(const T_GROUP_RELATION_BEAN& memBean);

	bool DeleteGroupRelation(const T_GROUP_RELATION_BEAN& memBean);

	bool SelectUserGroupRelation(const std::string strUserName, std::vector<T_GROUP_RELATION_BEAN>& memBeans);

	bool SelectGroupRelation(const std::string strGroupId, std::vector<T_GROUP_RELATION_BEAN>& memBeans);
	
	bool SelectGroupUsers(const std::string strGroupId, std::vector<std::string> groupUsers);
	//Group Chat Text Begin
	bool InsertGroupChatText(const T_GROUP_CHAT_MSG& chatMsg);
	
	bool SelectGroupChatText(T_GROUP_CHAT_MSG& chatMsg);

	bool DeleteGroupChatText(const std::string m_strMsgId);
	//Group Chat Text End
	
	static std::shared_ptr<spdlog::logger> m_loger;
private:
    MYSQL m_mysql;

};
#endif