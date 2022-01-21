#ifndef _TINY_IM_SERVER_DB_INTERFACE_H_
#define _TINY_IM_SERVER_DB_INTERFACE_H_
#include "CDataBaseStruct.h"
class CDbInterface
{
public:
    virtual bool InitDataBase()=0;
    virtual bool SelectUserByName(const std::string userName,T_USER_BEAN& bean)=0;
    
	virtual bool UpdateUser(const T_USER_BEAN& bean)=0;
    
	virtual bool DeleteUser(const std::string strUserId)=0;

    virtual bool InsertUser(const T_USER_BEAN& bean)=0;
	
	virtual bool IsUserExist(const std::string strUserId)=0;
};
#endif    
