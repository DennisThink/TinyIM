/**
 * @file CommonMsg.h
 * @author DennisMi (https://www.dennisthink.com/)
 * @brief 定义交互消息的头文件，包括了序列化和反序列化
 * @version 0.1
 * @date 2019-07-18
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef _COMMON_MSG_H_
#define _COMMON_MSG_H_
#include "json11.hpp"
#include "CommonDef.h"
#include <stdlib.h>
#include <string.h>
 //用户基本信息
struct UserBaseInfo {
	std::string m_strUserId;    //用户编号
	std::string m_strUserName;  //用户名称
	std::string m_strSignature; //用户签名
	std::string m_strNickName;  //用户备注
	std::string m_strFaceId;    //用户头像
	std::string m_strAddress;   //用户住址
	std::string m_strBirthDate; //用户出生日期
	std::string m_strEmail;     //用户邮箱
	std::string m_strGender;    //用户性别
	CLIENT_ONLINE_TYPE m_eOnlineState;
};

/**
 * @brief 群组信息结构体
 * 
 */
struct GroupInfo {
	std::string m_strGroupId;//群组ID
	std::string m_strGroupName;//群昵称
	std::string m_strGroupImage;//群头像
	std::vector<UserBaseInfo> m_GroupUsers;//群组成员
};
/**
 * @brief 消息体的头部
 * 
 */
struct Header
{
	//消息类型
	int32_t   m_type;
	//消息长度
	int32_t    m_length;
};



/**
 * @brief 用来传输消息的类型，将消息先转化为字符串，然后放入这个类型中，在实际的代码中使用std::shared_ptr来保存
 * 
 */
struct TransBaseMsg_t
{
public:
	/**
	 * @brief 获取消息类型
	 * 
	 * @return MessageType 
	 */
	MessageType GetType() const;

	/**
	 * @brief 获取消息体的长度
	 * 
	 * @return std::size_t 
	 */
	std::size_t GetSize() const;

	/**
	 * @brief 获取消息的字符串内容
	 * 
	 * @return std::string 
	 */
	std::string to_string() const;

	/**
	 * @brief 获取消息的实际数据
	 * 
	 * @return const char* 
	 */
	const char * GetData() const;

	/**
	 * @brief 使用消息类型和字符串构造传输的消息,发送消息的时候使用
	 * 
	 * @param type 消息类型
	 * @param strMsg  消息字符串
	 */
	/*explicit TransBaseMsg_t(const MessageType& type,const std::string& strMsg)
	{
		std::size_t strLen = strMsg.length();
		Header head;
		head.m_type = type;
		head.m_length = static_cast<uint32_t>(strLen+sizeof(head));
		m_data = new char[head.m_length];
		memset(m_data,0,head.m_length);
		memcpy(m_data,&head,sizeof(head));
		memcpy(m_data+sizeof(head),strMsg.c_str(),strLen);
		m_selfData = true;
	}*/
	

	/**
	 * @brief 使用消息类型和字符串构造传输的消息,发送消息的时候使用
	 *
	 * @param type 消息类型
	 * @param strMsg  消息字符串
	 */
	explicit TransBaseMsg_t(const MessageType& type, const std::string& strMsg);
	/**
	 * @brief 从内存直接构造消息，接收消息的时候使用
	 * 
	 * @param data 消息接收端的内存
	 */
	explicit TransBaseMsg_t(const char * data);

	virtual ~TransBaseMsg_t();
protected:
	//数据块内容
	char *   m_data;
	//是否自己保存了数据
	bool m_selfData = false;
};

/**
 * @brief 用来传输消息的类型，将消息先转化为字符串，然后放入这个类型中，在实际的代码中使用std::shared_ptr来保存
 *
 */
class CTransMessage final
{
public:
	

	/**
	 * @brief 获取消息体的长度
	 *
	 * @return std::size_t
	 */
	int GetSize() const
	{
		return m_dataLen;
	}

	
	/**
	 * @brief 获取消息的实际数据
	 *
	 * @return const char*
	 */
	const char * GetData() const
	{
		return m_data;
	}

	/**
	 * @brief 使用消息类型和字符串构造传输的消息,发送消息的时候使用
	 *
	 * @param type 消息类型
	 * @param strMsg  消息字符串
	 */
	explicit CTransMessage(const char * data,const int length)
	{
		if (length > 0)
		{
			m_data = new char[length];
			memcpy(m_data, data, length);
			m_dataLen = length;
			m_selfData = true;
		}
		else
		{
			m_dataLen = 0;
			m_data = nullptr;
			m_selfData = false;
		}
	}

	/**
	 * @brief 从内存直接构造消息，接收消息的时候使用
	 *
	 * @param data 消息接收端的内存
	 */
	explicit CTransMessage(char * data)
	{
		m_data = data;
		m_selfData = false;
	}

	virtual ~CTransMessage()
	{
		if (m_selfData)
		{
			if (nullptr != m_data)
			{
				delete m_data;
				m_data = nullptr;
			}
		}
	}


	std::string ToHexString() const {
		if (m_dataLen > 0 && m_data != nullptr)
		{
			const std::string HEX_ARRAY = "0123456789ABCDEF";
			std::string strResult;
			unsigned char * pChar = reinterpret_cast<unsigned char *>(m_data);
			for (int i = 0; i < m_dataLen; i++) {
				strResult += HEX_ARRAY[(*(pChar + i))%256 / 16];
				strResult += HEX_ARRAY[(*(pChar + i)) % 16];
			}

			return strResult;
		}
		else
		{
			return "";
		}
	}

	/*bool FromHexString(const std::string strHex) const {
		return false;
	}*/
protected:
	//数据块内容
	char *   m_data;
	int   m_dataLen;
	//是否自己保存了数据
	bool m_selfData = false;
};

using CTransMsg_SHARED_PTR = std::shared_ptr<CTransMessage>;
/**
 * @brief Ip端口配置类
 * 
 */
struct IpPortCfg
{
	std::string m_strServerIp;
	int 		m_nPort;
	/**
	 * @brief 获取配置的字符串表示，类似于 127.0.0.1:80
	 * 
	 * @return std::string 
	 */
	std::string to_string();

	/**
	 * @brief 检查配置是否有效
	 * 
	 * @return true 配置有效
	 * @return false 配置无效
	 */
	bool Valid();
};

/**
 * @brief 基础消息类型，所有的消息从该类型继承
 * 
 */
struct BaseMsg
{
protected:
	MessageType m_type;
public:
	/**
	 * @brief 获取消息类型
	 * 
	 * @return MessageType 
	 */
	MessageType GetMsgType() const 
	{
		return m_type;
	}

	explicit BaseMsg()
	{
		m_type=MessageType::Base_Type;
	}
	
	/**
	 * @brief 消息序列化,需要子类继承
	 * 
	 * @return std::string 序列化以后的字符串
	 */
	virtual std::string ToString() const
	{
		return "";
	}

	/**
	 * @brief 消息反序列化，需要子类继承
	 * 
	 * @param strJson 待反序列化的子串
	 * @return true 反序列化成功
	 * @return false 反序列化失败
	 */
    virtual bool FromString(const std::string& strJson)
	{
		if(strJson.empty())
		{
			return false;
		}
		return true;
	}

	virtual bool Valid() const {
		return false;
	}

	virtual std::string ToPrintString() const {
		return ToString();
	}
};


/**
 * @brief 网络连接断开上报消息
 * 
 */
struct NetFailedReportMsg final :public BaseMsg
{
public:
	std::string m_strClientId;//客户端标识，用来标识是哪个客户端的发送的心跳请求
public:
	explicit NetFailedReportMsg();

	explicit NetFailedReportMsg(const std::string& clientId);
	
	virtual bool FromString(const std::string& strJson) override;

	virtual std::string ToString() const override;
};


/**
 * @brief 网络连接恢复上报消息
 * 
 */
struct NetRecoverReportMsg final :public BaseMsg
{
public:
	std::string m_strClientId;//客户端标识，用来标识是哪个客户端的发送的心跳请求
public:
	explicit NetRecoverReportMsg();

	explicit NetRecoverReportMsg(const std::string& clientId);

	virtual std::string ToString() const override;
	
	virtual bool FromString(const std::string& strJson) override;
};

/**
 * @brief 心跳请求消息
 * 
 */
struct KeepAliveReqMsg final:public BaseMsg
{
	std::string m_strClientId;//客户端标识，用来标识是哪个客户端的发送的心跳请求
public:
	explicit KeepAliveReqMsg();

	explicit KeepAliveReqMsg(const std::string& clientId);

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;
};

/**
 * @brief 心跳回复消息
 * 
 */
class KeepAliveRspMsg final:public BaseMsg
{
private:
	std::string m_strClientId;//心跳请求中携带的客户端标识
public:
	explicit KeepAliveRspMsg();

	explicit KeepAliveRspMsg(const std::string& clientId);

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;
};


/**
 * @brief 登录请求消息
 *
 */
class UserLoginReqMsg final :public BaseMsg
{
public:
	std::string m_strMsgId;//消息ID
	std::string m_strUserName;//用户名
	std::string m_strPassword;//密码
	CLIENT_OS_TYPE m_eOsType;//操作系统类型
	CLIENT_NET_TYPE m_eNetType;//网络类型
	CLIENT_ONLINE_TYPE m_eOnlineType;//在线类型
public:
	explicit UserLoginReqMsg();

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;

	virtual bool Valid() const override;
};


/**
 * @brief 用户登录回复消息
 *
 */
class UserLoginRspMsg final :public BaseMsg
{
public:
	std::string m_strMsgId;
	ERROR_CODE_TYPE m_eErrCode; //错误代码
	std::string m_strErrMsg; //错误信息
	std::string m_strUserId;//用户ID
	std::string m_strUserName; //用户名
	UserBaseInfo m_userInfo;//用户的基本信息
	
public:
	explicit UserLoginRspMsg();

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;

	virtual bool Valid() const override;
};


/**
 * @brief 用户退出登录消息
 *
 */
class UserLogoutReqMsg final :public BaseMsg
{
public:
	std::string m_strMsgId;
	std::string m_strUserName; //用户名
	std::string m_strPassword; //密码
	CLIENT_OS_TYPE m_eOsType;  //操作系统平台类型
public:
	explicit UserLogoutReqMsg();

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;
	
	virtual bool Valid() const override;
};


/**
 * @brief 用户退出登录回复消息
 * 
 */
class UserLogoutRspMsg final :public BaseMsg
{
public:
	std::string m_strMsgId;
	ERROR_CODE_TYPE m_eErrCode; //错误代码
	std::string m_strErrMsg;    //错误消息
	std::string m_strUserName;  //用户名
public:
	UserLogoutRspMsg();

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;

	virtual bool Valid() const override;
	
};


/**
 * @brief 用户注册请求消息
 * 
 */
class UserRegisterReqMsg final :public BaseMsg
{
public:
	std::string m_strMsgId;//请求消息ID，在同样的消息回复的时候，会带回来
	std::string m_strUserName;//用户名
	std::string m_strPassword;//密码
	std::string m_strNickName;//昵称

public:
	UserRegisterReqMsg();

	std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;

	virtual bool Valid() const override;
	
};


/**
 * @brief 用户注册回复消息
 * 
 */
class UserRegisterRspMsg final :public BaseMsg
{
public:
	std::string m_strMsgId;//消息ID
	ERROR_CODE_TYPE m_eErrCode; //错误代码
	std::string m_strErrMsg;   //错误消息
	std::string m_strUserName; //用户名
public:
	UserRegisterRspMsg();

	virtual std::string ToString() const override;
	
	virtual bool FromString(const std::string& strJson) override;

	virtual bool Valid() const override;
	
};


/**
 * @brief 用户注销请求消息
 * 
 */
class UserUnRegisterReqMsg final :public BaseMsg
{
public:
	std::string m_strMsgId;
	std::string m_strUserName;//用户名
	std::string m_strPassword;//密码
	std::string m_strVerifyCode;//验证码，暂不使用

public:
	UserUnRegisterReqMsg();

	std::string ToString() const override;
	
	virtual bool FromString(const std::string& strJson) override;

	virtual bool Valid() const override;

};


/**
 * @brief 用户注销回复消息
 * 
 */
class UserUnRegisterRspMsg final :public BaseMsg
{
public:
	ERROR_CODE_TYPE m_eErrCode; //错误代码
	std::string m_strErrMsg;    //错误信息
	std::string m_strMsgId;     //消息ID
	std::string m_strUserName;  //用户名

public:
	UserUnRegisterRspMsg();
	
	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;

	virtual bool Valid() const override;
	
};
const int E_FONT_BOLD = 1;
const int E_FONT_ITALIC = 2;
const int E_FONT_UNDER_SCORE = 4;
struct FontInfo_s
{
public:
	std::string m_strFontName; //字体名称
	int			m_nFontSize;   //字体大小
	std::string m_strFontColorHex;  //字体颜色
	int         m_nFontStyle;
	explicit FontInfo_s();
	bool IsBold() const ;//是否粗体
	bool IsItalic() const ;//是否斜体
	bool IsUnderScore() const ;//是否是下划线
	void SetBold();
	void SetItalic();
	void SetUnderScore();
	bool FromString(const std::string& strJson);
	std::string ToString() const;

public:

};

/**
 * @brief 好友聊天发送文字消息，发送方到服务器
 * 
 */
class FriendChatSendTxtReqMsg final :public BaseMsg
{
public:
	std::string m_strMsgId;//消息ID
	std::string m_strSenderId;   //发送者
	std::string m_strReceiverId; //接收者
	std::string m_strContext;  //信息内容
	FontInfo_s  m_fontInfo;
public:
	FriendChatSendTxtReqMsg();

	virtual std::string ToString() const override;
	
	virtual bool FromString(const std::string& strJson) override;

	virtual bool Valid() const override;
	
};

/**
 * @brief 好友聊天发送文字消息的回复消息，服务器到发送方
 * 
 */
class FriendChatSendTxtRspMsg final :public BaseMsg {
public:
	std::string m_strMsgId; //消息ID，由服务器生成
	std::string m_strSenderId; //发送方ID
	std::string m_strReceiverId;//接收方ID
	ERROR_CODE_TYPE m_eErrCode;//错误代码
	std::string m_strErrMsg;  //错误信息

	std::string m_strContext ;  //信息内容
	FontInfo_s  m_fontInfo   ;  //字体信息
	std::string m_strMsgTime ;  //消息接收时间
public:
	FriendChatSendTxtRspMsg();
	
	virtual std::string ToString() const override;
	
	virtual bool FromString(const std::string& strJson) override;

	virtual bool Valid() const override;

};


/**
 * @brief 好友聊天接收文字消息，服务器到接收方
 * 
 */
class FriendChatRecvTxtReqMsg final :public BaseMsg {

public:
	std::string m_strMsgId;    //消息ID
	std::string m_strFromId;   //发送者ID
	std::string m_strToId;     //接收方ID
	std::string m_strContext;  //消息内容
	std::string m_strRecvTime; //消息接收时间
	FontInfo_s  m_fontInfo;    //字体信息
public:
	FriendChatRecvTxtReqMsg();

	virtual std::string ToString() const override;
	
	virtual bool FromString(const std::string& strJson) override;

	virtual bool Valid() const override;
	
};


/**
 * @brief 好友聊天接收文字消息的回复消息，接收方到服务器
 * 
 */
class FriendChatRecvTxtRspMsg final :public BaseMsg {
public:
	std::string m_strMsgId;    //消息ID
	std::string m_strFromId; //发送方
	std::string m_strToId;   //接收方
public:
	FriendChatRecvTxtRspMsg();

	virtual std::string ToString() const override;
	
	virtual bool FromString(const std::string& strJson) override;

	virtual bool Valid() const override;
	
};



/**
获取好友列表请求
*/
class GetFriendListReqMsg :public BaseMsg {
public:
	std::string m_strMsgId;
	std::string m_strUserId;
public:
	GetFriendListReqMsg();
	
	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;

	virtual bool Valid() const override;
};

/**
 * @brief 获取好友列表回复
 * 
 */
class GetFriendListRspMsg :public BaseMsg
{
public:
	std::string m_strMsgId;
	std::string m_strUserId;
	std::vector<UserBaseInfo> m_friendInfoVec;//好友信息列表
public:
	GetFriendListRspMsg();

	virtual std::string ToString() const override;
	
	virtual bool FromString(const std::string& strJson) override;

	virtual bool Valid() const override; 
};



/**
 * @brief 添加好友请求
 * 
 */
class AddFriendSendReqMsg :public BaseMsg
{
public:
	std::string m_strMsgId;
	std::string m_strUserId;
	std::string m_strFriendId;
public:
	AddFriendSendReqMsg();

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;

	virtual bool Valid() const override;
};


/**
 * @brief 添加好友回复
 * 
 */
class AddFriendSendRspMsg :public BaseMsg
{
public:
	std::string m_strMsgId;
	ERROR_CODE_TYPE m_eErrCode; //错误码
	std::string m_strErrMsg; //错误信息
	std::string m_strUserId;     //
	std::string m_strFriendId;   //

public:
	AddFriendSendRspMsg();

	virtual std::string ToString() const override;
	
	virtual bool FromString(const std::string& strJson) override;

	virtual bool Valid() const override;

};



/**
 * @brief 添加好友朋友接收方请求消息
 * 
 */
class AddFriendRecvReqMsg :public BaseMsg {
public:
	std::string m_strMsgId; //消息ID
	std::string m_strUserId;
	std::string m_strFriendId;
public:
	AddFriendRecvReqMsg();
	
	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;


	virtual bool Valid() const override;
	
};

/**
 * @brief 被添加好友回复消息
 * 
 */
class AddFriendRecvRspMsg :public BaseMsg {
public:
	std::string m_strMsgId; //消息ID
	std::string m_strUserId; //用户ID
	std::string m_strFriendId; //好友ID
	E_FRIEND_OPTION m_option;//用户选择[同意/拒绝]
public:
	AddFriendRecvRspMsg();

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;

	virtual bool Valid() const override;

};


/**
 * @brief 通知添加好友的结果通知请求
 * 
 */
class AddFriendNotifyReqMsg :public BaseMsg {
public:
	std::string m_strMsgId;//消息ID
	std::string m_strUserId;
	std::string m_strFriendId;
	
	E_FRIEND_OPTION m_option;//用户选择[同意/拒绝]
public:
	AddFriendNotifyReqMsg();
	

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;

	virtual bool Valid() const override;
	
};

/**
 * @brief 添加好友通知回复
 * 
 */
class AddFriendNotifyRspMsg :public BaseMsg {
public:
	std::string m_strMsgId;//消息ID
public:
	AddFriendNotifyRspMsg();

	virtual std::string ToString() const override;
	
	virtual bool FromString(const std::string& strJson) override;

	virtual bool Valid() const override;
};


/**
 * @brief 删除好友请求
 * 
 */
class RemoveFriendReqMsg :public BaseMsg {
public:
	std::string m_strMsgId;//消息ID
	std::string m_strUserId; //用户ID
	std::string m_strFriendId; //好友ID
public:
	RemoveFriendReqMsg();
	
	virtual std::string ToString() const override;
	
	virtual bool FromString(const std::string& strJson) override;

	virtual bool Valid() const override;
};

/**
 * @brief 删除好友回复
 * 
 */
class RemoveFriendRspMsg :public BaseMsg {
public:
	ERROR_CODE_TYPE m_eErrCode; //错误码
	std::string m_strErrMsg; //错误信息
	std::string m_strMsgId;
	std::string m_strUserId; //用户名
	std::string m_strFriendId; //好友用户名
public:
	RemoveFriendRspMsg();
	
	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;

	virtual bool Valid() const override;
	
};


/**
 * @brief 查找好友请求
 * 
 */
class FindFriendReqMsg :public BaseMsg {
public:
	std::string m_strMsgId;
	std::string m_strUserId;
	std::string m_strWantedName;//被查找的用户名
public:
	FindFriendReqMsg();

	virtual std::string ToString() const override;


	virtual bool FromString(const std::string& strJson) override;


	virtual bool Valid() const override;
};


/**
 * @brief 查找好友回复
 * 
 */
class FindFriendRspMsg :public BaseMsg
{
public:
	std::string m_strMsgId;
	ERROR_CODE_TYPE m_eErrCode;//错误码
	std::string m_strUserId;//用户名
	std::vector<UserBaseInfo> m_friendInfoVec;//符合的所有用户
public:
	FindFriendRspMsg();
	
	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;

};

/* 添加好友分组请求*/
class AddTeamReqMsg :public BaseMsg {
public:
	std::string m_strMsgId;
	std::string m_strUserId; //用户名
	std::string m_strTeamName; //群组名称
public:
	AddTeamReqMsg();
	
	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;

};


/* 添加好友分组回复*/
class AddTeamRspMsg :public BaseMsg {
public:
	std::string m_strMsgId;
	ERROR_CODE_TYPE m_eErrCode; //错误码
	std::string m_strErrMsg; //错误信息

	std::string m_strUserId;//用户名
	std::string m_strTeamId; //分组编号

	std::string m_strTeamName;//分组名称
public:
	AddTeamRspMsg();

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;
};


/* 删除好友分组请求*/
class RemoveTeamReqMsg :public BaseMsg {
public:
	std::string m_strMsgId;
	std::string m_strUserId;//用户名
	std::string m_strTeamId;//分组编号
public:
	RemoveTeamReqMsg();
	
	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;
};

/* 删除好友分组回复*/
class RemoveTeamRspMsg :public BaseMsg {
public:
	ERROR_CODE_TYPE m_eErrorCode;//错误码
	std::string m_strErrMsg;//错误信息
	std::string m_strMsgId;
	std::string m_strUserId;//用户名
	std::string m_strTeamId;//分组编号
	std::string m_strTeamName;//分组名
public:
	RemoveTeamRspMsg();

	virtual std::string ToString() const override;
	
	virtual bool FromString(const std::string& strJson) override;

};



/* 移动好友分组请求*/
class MoveFriendToTeamReqMsg :public BaseMsg {
public:
	std::string m_strMsgId;
	std::string m_strUserId;//用户名
	std::string m_strFriendId;//好友用户名
	std::string m_strSrcTeamId;//现在的分组ID
	std::string m_strDstTeamId;//新的分组ID
public:
	MoveFriendToTeamReqMsg();

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;

};


/* 移动好友分组回复*/
class MoveFriendToTeamRspMsg :public BaseMsg {
public:
	ERROR_CODE_TYPE m_eErrCode;//错误码
	std::string m_strErrMsg;//错误信息
	std::string m_strMsgId;
	std::string m_strUserId;//用户名
	std::string m_strFriendId;//好友用户名
	std::string m_strSrcTeamId;//原来的分组ID
	std::string m_strDstTeamId;//目标的分组ID
public:
	MoveFriendToTeamRspMsg();

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;
};




/* 创建群聊请求*/
class CreateGroupReqMsg :public BaseMsg {
public:
	std::string m_strMsgId;
	std::string m_strUserId;
	std::string m_strGroupName;
public:
	CreateGroupReqMsg();

	virtual std::string ToString() const override;
	
	virtual bool FromString(const std::string& strJson) override;

	virtual bool Valid() const override;

};




/* 添加好友分组回复*/
class CreateGroupRspMsg :public BaseMsg {
public:
	ERROR_CODE_TYPE m_eErrCode;
	std::string m_strErrMsg;
	std::string m_strMsgId;
	std::string m_strGroupId;
	std::string m_strGroupName;
	std::string m_strUserId;
public:
	CreateGroupRspMsg();

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;

	virtual bool Valid() const override;

};





/* 删除好友分组请求*/
class DestroyGroupReqMsg :public BaseMsg {
public:
	std::string m_strMsgId;
	std::string m_strUserId;
	std::string m_strGroupId;
	std::string m_strGroupName;
public:
	DestroyGroupReqMsg();

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;

	virtual bool Valid() const override;
};

/* 删除群聊回复*/
class DestroyGroupRspMsg :public BaseMsg {
public:
	ERROR_CODE_TYPE m_eErrorCode;
	std::string m_strErrMsg;
	std::string m_strMsgId;
	std::string m_strUserId;
	std::string m_strGroupId;
	std::string m_strGroupName;
public:
	DestroyGroupRspMsg();

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;

	virtual bool Valid() const override;
};


/**
 * @brief 查找群组请求消息
 * 
 */
class FindGroupReqMsg :public BaseMsg 
{
public:
	std::string m_strMsgId;
	std::string m_strUserId;//用户名
	std::string m_strGroupName;//被查找的用户名
public:
	FindGroupReqMsg();

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;

	virtual bool Valid() const override;
};


/**
 * @brief 查找群组回复消息
 * 
 */
class FindGroupRspMsg :public BaseMsg
{
public:
	ERROR_CODE_TYPE m_eErrCode;
	std::string m_strUserId;
	std::string m_strMsgId;
	std::string m_strGroupId;
	std::string m_strGroupName;
	std::string m_strGroupOwner;
public:
	FindGroupRspMsg();

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;

	virtual bool Valid() const override;
};


/**
 * @brief 添加用户到群组的请求消息
 * 
 */
class AddToGroupReqMsg :public BaseMsg 
{
public:
	std::string m_strMsgId;
	std::string m_strUserId;//请求者的用户名
	std::string m_strGroupId; //要加入的群组的ID
public:
	AddToGroupReqMsg();

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;

	virtual bool Valid() const override;

};


/**
 * @brief 添加用户到群组的回复消息
 * 
 */
class AddToGroupRspMsg :public BaseMsg
{
public:
	ERROR_CODE_TYPE m_eErrCode;//错误码
	std::string m_strMsgId;//消息ID
	std::string m_strUserId;//用户ID
	std::string m_strGroupId;//群组ID

public:
	AddToGroupRspMsg();
	
	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;

	virtual bool Valid() const override;
	
};


/**
 * @brief 管理员或者群主收到的添加申请
 * 
 */
class AddToGroupRecvReqMsg :public BaseMsg {
public:
	std::string m_strMsgId;
	std::string m_strAdminId;//群组的管理者
	std::string m_strUserId;//请求者的用户名
	std::string m_strGroupId; //要加入的群组的ID
public:
	AddToGroupRecvReqMsg();

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;

	virtual bool Valid() const override;

};


/**
 * @brief 管理员或者群主是否通过申请
 * 
 */
class AddToGroupRecvRspMsg :public BaseMsg
{
public:
	ERROR_CODE_TYPE m_eErrCode;
	E_FRIEND_OPTION m_eOption;
	std::string m_strAdminId;
	std::string m_strUserId;
	std::string m_strGroupId;
public:
	AddToGroupRecvRspMsg();

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;

	virtual bool Valid() const override;
	
};


/**
 * @brief 添加到群组的申请结果通知消息
 * 
 */
class AddToGroupNotifyReqMsg :public BaseMsg {
public:
	std::string m_strMsgId;//
	std::string m_strAdminId;//群组的管理者
	std::string m_strUserId;//请求者的用户名
	std::string m_strGroupId; //要加入的群组的ID
	E_FRIEND_OPTION m_eOption;//是否同意
public:
	AddToGroupNotifyReqMsg();

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;

	virtual bool Valid() const override;

};


/**
 * @brief 添加到群组的申请消息回复
 * 
 */
class AddToGroupNotifyRspMsg :public BaseMsg
{
public:
	ERROR_CODE_TYPE m_eErrCode;
	E_FRIEND_OPTION m_eOption;
	std::string m_strMsgId;
	std::string m_strAdminId;
	std::string m_strUserId;
	std::string m_strGroupId;
public:
	AddToGroupNotifyRspMsg();
	
	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;

	virtual bool Valid() const override;
};


/**
 * @brief 邀请好友到群组的申请
 * 
 */
class InviteFriendToGroupReqMsg :public BaseMsg {
public:
	std::string m_strSenderId;//请求的发送者
	std::string m_strReciverId;//被请求的用户名
	std::string m_strGroupId; //要加入的群组的ID
public:
	InviteFriendToGroupReqMsg();

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;

};


/**
 * @brief 邀请好友到群组的回复
 * 
 */
class InviteFriendToGroupRspMsg :public BaseMsg
{
public:
	ERROR_CODE_TYPE m_eErrCode;
	std::string m_strMsgId;
	std::string m_strSenderId;
	std::string m_strReciverId;
	std::string m_strGroupId;
public:
	InviteFriendToGroupRspMsg();

	virtual std::string ToString() const override;
	
	virtual bool FromString(const std::string& strJson) override;

};


/**
 * @brief 被邀请方收到的邀请请求
 * 
 */
class InviteFriendToGroupRecvReqMsg :public BaseMsg
{
public:
	std::string m_strMsgId;
	std::string m_strSenderId;
	std::string m_strReciverId;
	std::string m_strGroupId;
public:
	InviteFriendToGroupRecvReqMsg();
	
	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;

};


/**
 * @brief 被邀请方的回复消息
 * 
 */
class InviteFriendToGroupRecvRspMsg :public BaseMsg
{
public:
	E_FRIEND_OPTION m_eOption;
	std::string m_strMsgId;
	std::string m_strSenderId;
	std::string m_strReciverId;
	std::string m_strGroupId;
public:
	InviteFriendToGroupRecvRspMsg();

	virtual std::string ToString() const override;
	
	virtual bool FromString(const std::string& strJson) override;

};


/**
 * @brief 邀请方收到被邀请的方加入群组的通知请求
 * 
 */
class InviteFriendToGroupNotifyReqMsg :public BaseMsg
{
public:
	E_FRIEND_OPTION m_eOption;
	std::string m_strMsgId;
	std::string m_strSenderId;
	std::string m_strReciverId;
	std::string m_strGroupId;
public:
	InviteFriendToGroupNotifyReqMsg();

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;

};

/**
 * @brief 邀请方收被邀请方加入群组的通知回复
 * 
 */
class InviteFriendToGroupNotifyRspMsg :public BaseMsg
{
public:
	std::string m_strMsgId;
	std::string m_strSenderId;
	std::string m_strReciverId;
	std::string m_strGroupId;
public:
	InviteFriendToGroupNotifyRspMsg();

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;

};


/**
 * @brief 发送群组文本消息请求[发送方--->服务器]
 * 
 */
class SendGroupTextMsgReqMsg :public BaseMsg
{
public:
	std::string m_strMsgId;
	std::string m_strSenderId;
	std::string m_strGroupId;
	std::string m_strContext;
	FontInfo_s m_stFontInfo;
public:
	SendGroupTextMsgReqMsg();

	virtual std::string ToString() const override;
	
	virtual bool FromString(const std::string& strJson) override;

};


/**
 * @brief 发送群组文本消息回复[服务器--->发送方]
 * 
 */
class SendGroupTextMsgRspMsg :public BaseMsg
{
public:
	ERROR_CODE_TYPE m_eErrCode;
	std::string m_strMsgId;
	std::string m_strSenderId;
	std::string m_strGroupId;

	std::string m_strContext;  //信息内容
	FontInfo_s  m_fontInfo;  //字体信息
	std::string m_strMsgTime;  //消息接收时间
public:
	SendGroupTextMsgRspMsg();

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;

};


/**
 * @brief 接收群组的文本聊天消息请求[服务器--->接收方]
 * 
 */
class RecvGroupTextMsgReqMsg :public BaseMsg
{
public:
	std::string m_strMsgId;
	std::string m_strSenderId;
	std::string m_strGroupId;
	std::string m_strContext;
	FontInfo_s  m_stFontInfo;
	std::string m_strMsgTime;
public:
	RecvGroupTextMsgReqMsg();

	virtual std::string ToString() const override;
	
	virtual bool FromString(const std::string& strJson) override;

};

/**
 * @brief 接收群组的文本聊天消息的回复[接收方--->服务器]
 * 
 */
class RecvGroupTextMsgRspMsg :public BaseMsg
{
public:
	std::string m_strMsgId;
	std::string m_strSenderId;
	std::string m_strGroupId;
public:
	RecvGroupTextMsgRspMsg();

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;

};

/**
 * @brief 好友发送文件请求[发送方--->服务器]
 * 
 */
class FriendSendFileMsgReqMsg :public BaseMsg
{
public:
	std::string m_strMsgId;//消息ID
	std::string m_strFromId;//发送方ID
	std::string m_strToId;//接收方ID
	std::string m_strFileName;//文件名
	CLIENT_ONLINE_TYPE m_eOnlineType;//是否是在线文件
public:
	FriendSendFileMsgReqMsg();

	virtual std::string ToString() const override;
	
	virtual bool FromString(const std::string& strJson) override;

};


/**
 * @brief 好友发送文件回复[服务器--->发送方]
 * 
 */
class FriendSendFileMsgRspMsg :public BaseMsg
{
public:
	ERROR_CODE_TYPE m_eErrCode;//错误码
	std::string m_strMsgId;//消息ID
	std::string m_strFromId;//发送者ID
	std::string m_strToId;//接受者ID
	std::string m_strFileName;//文件名称
	CLIENT_ONLINE_TYPE m_eOnlineType;//在线类型
public:
	FriendSendFileMsgRspMsg();

	virtual std::string ToString() const override;
	
	virtual bool FromString(const std::string& strJson) override;

};

/**
 * @brief 好友发送文件接收请求[服务器---->接收方]
 * 
 */
class FriendRecvFileMsgReqMsg :public BaseMsg
{
public:
	std::string m_strMsgId;//消息ID
	std::string m_strFromId;//发送方ID
	std::string m_strToId;//接收方Id
	std::string m_strFileName;//文件名称
	CLIENT_ONLINE_TYPE m_eOnlineType;//在线类型
public:
	FriendRecvFileMsgReqMsg();
	
	virtual std::string ToString() const override;
	
	virtual bool FromString(const std::string& strJson) override;
};

/**
 * @brief 好友发送文件的接收回复[接收方--->服务器]
 * 
 */
class FriendRecvFileMsgRspMsg :public BaseMsg
{
public:
	ERROR_CODE_TYPE m_eErrCode;
	std::string m_strMsgId;//消息ID
	std::string m_strFromId;//文件发送者ID
	std::string m_strToId;//文件接收者ID
	std::string m_strFileName;//文件名
	int m_nFileId;
	CLIENT_ONLINE_TYPE m_eOnlineType;//在线类型
	E_FRIEND_OPTION m_eOption;//用户选择
public:
	FriendRecvFileMsgRspMsg();

	virtual std::string ToString() const override;
	
	virtual bool FromString(const std::string& strJson) override;
};


/**
 * @brief 好友接受文件通知请求[服务器---->发送方]
 * 
 */
class FriendNotifyFileMsgReqMsg :public BaseMsg
{
public:
	std::string m_strMsgId;
	std::string m_strFromId;
	std::string m_strToId;
	std::string m_strFileName;
	int m_nFileId;
	CLIENT_ONLINE_TYPE m_eOnlineType;
	E_FRIEND_OPTION m_eOption;
public:
	FriendNotifyFileMsgReqMsg();

	virtual std::string ToString() const override;
	
	virtual bool FromString(const std::string& strJson) override;
};


/**
 * @brief 好友接受文件通知回复[发送方---->服务器]
 * 
 */
class FriendNotifyFileMsgRspMsg :public BaseMsg
{
public:
	std::string m_strMsgId;
public:
	FriendNotifyFileMsgRspMsg();

	virtual std::string ToString() const override;
	
	virtual bool FromString(const std::string& strJson) override;

};


/**
 * @brief 获取群组列表请求[发送方--->服务器]
 * 
 */
class GetGroupListReqMsg :public BaseMsg
{
public:
	std::string m_strMsgId;//消息Id
	std::string m_strUserId;//用户ID
public:
	GetGroupListReqMsg();

	virtual std::string ToString() const override;
	
	virtual bool FromString(const std::string& strJson) override;

};


/**
 * @brief 获取群组列表回复[服务器--->发送方]
 * 
 */
class GetGroupListRspMsg :public BaseMsg
{
public:
	std::string m_strMsgId;
	std::string m_strUserId;
	std::vector<GroupInfo> m_GroupList;
public:
	GetGroupListRspMsg();

	virtual std::string ToString() const override;
	
	virtual bool FromString(const std::string& strJson) override;

};


/**
 * @brief 文件数据发送请求[发送方--->服务器]
 * 
 */
class FileDataSendReqMsg :public BaseMsg
{
public:
	std::string m_strMsgId;//消息ID
	std::string m_strFromId;//发送者ID
	std::string m_strToId;//接受者ID
	int		    m_nFileId;//文件ID
	int			m_nDataTotalCount;//文件总数据包数
	int			m_nDataIndex;//文件数据包索引
	int			m_nDataLength;//文件数据长度
	char		m_szData[1024];//实际数据
public:
	FileDataSendReqMsg();

	virtual std::string ToString() const override;


	virtual bool FromString(const std::string& strJson) override;

};

/**
 * @brief 文件数据发送回复[服务器---->发送方]
 * 
 */
class FileDataSendRspMsg :public BaseMsg
{
public:
	std::string m_strMsgId;//消息ID
	std::string m_strFromId;//发送者ID
	std::string m_strToId;//接受者ID
	int		    m_nFileId;//文件ID
	int			m_nDataTotalCount;//文件总数据包数
	int			m_nDataIndex;//文件数据包索引
public:
	FileDataSendRspMsg();

	virtual std::string ToString() const override;
	
	virtual bool FromString(const std::string& strJson) override;
};


/**
 * @brief 文件数据接收请求[服务器---->接收方]
 * 
 */
class FileDataRecvReqMsg :public BaseMsg
{
public:
	std::string m_strMsgId;//消息ID
	std::string m_strFromId;//发送者ID
	std::string m_strToId;//接受者ID
	int		    m_nFileId;//文件ID
	int			m_nDataTotalCount;//文件总数据包数
	int			m_nDataIndex;//文件数据包索引
	int			m_nDataLength;//文件数据长度
	char		m_szData[1024];//实际数据
public:
	FileDataRecvReqMsg();

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;
};


/**
 * @brief 文件数据接收回复[接收方---->服务器]
 * 
 */
class FileDataRecvRspMsg :public BaseMsg
{
public:
	std::string m_strMsgId;//消息ID
	std::string m_strFromId;//发送者ID
	std::string m_strToId;//接受者ID
	int		    m_nFileId;//文件ID
	int			m_nDataTotalCount;//文件总数据包数
	int			m_nDataIndex;//文件数据包索引
public:
	FileDataRecvRspMsg();

	virtual std::string ToString() const override;
	
	virtual bool FromString(const std::string& strJson) override;
};



/**
 * @brief 文件校验请求消息[文件发送方]---->[服务器]---->[文件接收方]
 * 
 */
class FileVerifyReqMsg:public BaseMsg
{
public:
	std::string m_strMsgId;//消息ID
	std::string m_strFromId;//发送者ID
	std::string m_strToId;//接受者ID
	std::string m_strFileName;//文件名称
	int		    m_nFileId;//文件ID
	int			m_nFileSize;//文件大小
	std::string m_strFileHash;//文件的Hash值
public:
	FileVerifyReqMsg();

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;

};

/**
 * @brief 文件校验回复消息[文件接收方]--->[服务器]--->[文件发送方]
 * 
 */
class FileVerifyRspMsg :public BaseMsg
{
public:
	ERROR_CODE_TYPE m_eErrCode;//错误码
	std::string m_strMsgId;//消息ID
	std::string m_strFromId;//发送者ID
	std::string m_strToId;//接受者ID
	std::string m_strFileName;//文件名称
	int		    m_nFileId;//文件ID
public:
	FileVerifyRspMsg();

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;
};

/* 用户被踢出的请求消息 */
class UserKickOffReqMsg : public BaseMsg
{
public:
	std::string m_strMsgId;			//消息ID
	std::string m_strUserId;		//用户ID
	std::string m_strNewLoginIp;    //新登录的IP地址D
public:
	UserKickOffReqMsg();

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;
};


/* 用户被踢出的消息的回复 */
class UserKickOffRspMsg :public BaseMsg
{
public:
	std::string m_strMsgId;			//消息ID
	std::string m_strUserId;		//用户ID
public:
	UserKickOffRspMsg();

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;
};


/**
 * @brief 用户有未读消息的通知 [服务器]--->[接收方]
 * 
 */
class FriendUnReadNotifyReqMsg :public BaseMsg
{
public:
	std::string m_strMsgId;			//消息ID
	std::string m_strUserId;		//用户ID
public:
	FriendUnReadNotifyReqMsg();

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;
};

/**
 * @brief 用户有未读消息的通知回复 [接收方]--->[服务器]
 * 
 */
class FriendUnReadNotifyRspMsg :public BaseMsg
{
public:
	std::string m_strMsgId; //消息ID
	std::string m_strUserId;//用户ID
	FriendUnReadNotifyRspMsg();

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;
};
/**
 * @brief 服务器配置
 * 
 */
class CServerConfig
{
public:
	std::vector<IpPortCfg> m_clientCfgVec;
	IpPortCfg              m_serverCfg;
	explicit CServerConfig()
	{
		m_serverCfg.m_strServerIp = "127.0.0.1";
		m_serverCfg.m_nPort = 9000;

		m_clientCfgVec.push_back({"127.0.0.1",8000});
	}
};

#endif
