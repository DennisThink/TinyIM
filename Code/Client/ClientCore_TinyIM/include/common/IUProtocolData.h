//协议及状态常量

#ifndef _MEDIUM_SERVER_C_IU_PROTOCAL_DATA_H_
#define _MEDIUM_SERVER_C_IU_PROTOCAL_DATA_H_
#ifndef WIN32
#include <string.h>
#endif
#include "json11.hpp"
#include <list>
#include <map>
#include <set>
#include <stdint.h>
#include <string>

#define DEFAULT_TEAMNAME _T("My Friends")
#define MAX_PATH_LENGTH 250
//客户端类型
enum CLIENT_TYPE {
  CLIENT_TYPE_UNKNOWN = 0,
  CLIENT_TYPE_PC = 1,
  CLIENT_TYPE_IOS = 2,
  CLIENT_TYPE_ANDROID = 3
};

//在线状态
enum ONLINE_STATUS {
  STATUS_OFFLINE = 0,        //离线
  STATUS_ONLINE = 1,         //在线
  STATUS_INVISIBLE = 2,      //隐身
  STATUS_BUSY = 3,           //忙碌
  STATUS_AWAY = 4,           //离开
  STATUS_MOBILE_ONLINE = 5,  //移动版在线
  STATUS_MOBILE_OFFLINE = 6, //移动版下线
  STATUS_BOTH = 7            //手机和电脑同时在线
};

enum ONLINE_CLIENT_TYPE {
  ONLINE_CLIENT_UNKONWN,
  ONLINE_CLIENT_PC,
  ONLINE_CLIENT_MOBILE,
  ONLINE_CLIENT_BOTH,
  OFFLINE_CLIENT_BOTH
};

enum LOGIN_TYPE {
  LOGIN_USE_MOBILE_NUMBER = 0, //使用手机号登录
  LOGIN_USE_ACCOUNT = 1,       //使用账号登录
};

enum LOGIN_RESULT_CODE // 登录结果代码
{
  LOGIN_SUCCESS,            // 登录成功
  LOGIN_FAILED,             // 登录失败
  LOGIN_UNREGISTERED,       // 用户未注册
  LOGIN_PASSWORD_ERROR,     // 密码错误
  LOGIN_USER_CANCEL_LOGIN,  // 用户取消登录
  LOGIN_SERVER_REFUSED,     // 服务器拒绝
  LOGIN_SERVER_NOT_RESPONSE // 服务器未响应
};

enum REGISTER_RESULT_CODE //注册结果代码
{
  REGISTER_SUCCESS,            //注册成功
  REGISTER_EXIST,              //账号已经存在
  REGISTER_FAILED,             //注册失败
  REGISTER_SERVER_NOT_RESPONSE //服务器未响应
};

enum HEARTBEAT_RESULT_CODE {
  HEARTBEAT_ALIVE, //仍然保持连接
  HEARTBEAT_DEAD,  //已经断开连接
};

//加好友状态
enum OPERATE_FRIEND { Apply, Agree, Refuse, Delete };

enum ADD_FRIEND_RESULT //添加好友结果
{
  FIND_FRIEND_NOT_FOUND,
  FIND_FRIEND_FOUND,
  FIND_FRIEND_FAILED,

  ADD_FRIEND_SUCCESS,
  ADD_FRIEND_FAILED
};

enum DELETE_FRIEND_RESULT { DELETE_FRIEND_SUCCESS, DELETE_FRIEND_FAILED };

enum SEND_CHAT_MSG_RESULT //发送聊天消息结果
{
  SEND_MSG_SUCESS,
  SEND_WHOLE_MSG_FAILED, //发送整个消息失败
  SEND_IMGAE_FAILED,     //发送图片失败
                         // SEND_FILE_FAILED			//发送文件失败
};

enum UPLOAD_USER_THUMB_RESULT {
  UPLOAD_USER_THUMB_RESULT_SUCCESS,
  UPLOAD_USER_THUMB_RESULT_FAILED
};

enum SEND_FILE_RESULT { SEND_FILE_FAILED, SEND_FILE_SUCCESS };

enum RECV_FILE_RESULT { RECV_FILE_FAILED, RECV_FILE_SUCCESS };

enum GET_USER_INFO_TYPE {
  USER_INFO_TYPE_SELF,
  USER_INFO_TYPE_FRIENDS,
  USER_INFO_TYPE_GROUP,
  USER_INFO_TYPE_GROUP_MEMBER
};

struct FindUserOrGroupResult {
  long nType; //个人还是群组
  uint32_t uAccountID;
  char szAccountName[32];
  char szNickName[32];
};

//记录当前添加好友的状态信息
struct AddFriendInfo {
  char nCmd;              //操作类型（Apply/Agree/Refuse）
  uint32_t uAccountID;    //账户ID
  char szAccountName[32]; //账户名
  char szNickName[32];    //昵称
};

enum CHAT_MSG_TYPE_t {
  FMG_MSG_TYPE_UNKNOWN,
  FMG_MSG_TYPE_BUDDY,
  FMG_MSG_TYPE_GROUP,
  FMG_MSG_TYPE_MULTI, //群发消息
  FMG_MSG_TYPE_SESS
};

struct UserBasicInfo {
  uint32_t uAccountID;
  char szAccountName[32];
  char szNickName[64];
  char szMarkName[64];
  char szSignature[256];
  char szAddress[51225];
  uint32_t uFaceID;
  int nStatus;    //在线状态
  int clientType; //客户端类型
  char customFace[64];
  int nGender;
  int nBirthday;
  char szPhoneNumber[64];
  char szMail[64];
};

struct UserExtendInfo {
  uint32_t uAccountID;
  uint32_t uGender;
  uint32_t uShengXiao;
  uint32_t uConstel;
  uint32_t uBlood;
  uint32_t uBirthday;

  char szCountry[32];                 // 国家
  char szProvince[32];                // 省份
  char szCity[32];                    // 城市
  char szPhone[32];                   // 电话
  char szMobile[32];                  // 手机
  char szOccupation[32];              // 职业
  char szCollege[32];                 // 毕业院校
  char szEmail[48];                   // 邮箱
  char szHomepage[64];                // 个人主页
  char szSignature[256];              // 个性签名
  char szPersonal[512];               // 个人说明
  char szCustomFace[MAX_PATH_LENGTH]; // 自定义头像名
};

//文件上传下载类型
enum FILE_ITEM_TYPE {
  FILE_ITEM_UNKNOWN,
  FILE_ITEM_UPLOAD_CHAT_IMAGE,
  FILE_ITEM_UPLOAD_CHAT_OFFLINE_FILE,
  FILE_ITEM_UPLOAD_USER_THUMB,

  FILE_ITEM_DOWNLOAD_CHAT_IMAGE,
  FILE_ITEM_DOWNLOAD_CHAT_OFFLINE_FILE,
  FILE_ITEM_DOWNLOAD_USER_THUMB,
};

//文件下载返回结果码
enum FILE_DOWNLOAD_RETCODE {
  FILE_DOWNLOAD_FAILED,
  FILE_DOWNLOAD_SUCCESS,
  FILE_DOWNLOAD_USERCANCEL //用户取消下载
};

//文件上传返回结果码
enum FILE_UPLOAD_RETCODE {
  FILE_UPLOAD_FAILED,
  FILE_UPLOAD_SUCCESS,
  FILE_UPLOAD_USERCANCEL //用户取消上传
};

//获取文件md5值结果码
enum GET_FILE_MD5_RETCODE {
  GET_FILE_MD5_FAILED,
  GET_FILE_MD5_SUCESS,
  GET_FILE_MD5_USERCANCEL
};

//修改个人信息详情
enum MODIFY_USER_INFO_TYPE {
  MODIFY_NICKNAME = 0x0001,
  MODIFY_GENDER = 0x0002,
  MODIFY_BIRTHDAY = 0x0004,
  MODIFY_SIGNATRUE = 0x0008,
  MODIFY_ADDRESS = 0x0010,
  MODIFY_PHONE = 0x0020,
  MODIFY_EMAIL = 0x0040,
  MODIFY_THUMB = 0x0080
};

enum CHAT_CONFIRM_TYPE {
  CHAT_CONFIRM_TYPE_SINGLE, //单聊（包括群组）确认消息类型
  CHAT_CONFIRM_TYPE_MULTI   //群发确认消息类型
};

enum NET_DATA_TYPE {
  NET_DATA_UNKNOWN,
  NET_DATA_REGISTER,
  NET_DATA_LOGIN,
  NET_DATA_USER_BASIC_INFO,
  NET_DATA_CHANGE_STATUS,
  NET_DATA_GROUP_BASIC_INFO,
  NET_DATA_USER_EXTEND_INFO,
  NET_DATA_FRIENDS_ID,
  NET_DATA_FRIENDS_STATUS,
  NET_DATA_CHAT_MSG,
  NET_DATA_CHAT_CONFIRM_IMAGE_MSG, //聊天发送完图片后追加的确认信息
  NET_DATA_FIND_FRIEND,
  NET_DATA_OPERATE_FRIEND,
  NET_DATA_HEARTBEAT,
  NET_DATA_UPDATE_LOGON_USER_INFO,
  NET_DATA_TARGET_INFO_CHANGE,
  NET_DATA_MODIFY_PASSWORD,
  NET_DATA_CREATE_NEW_GROUP,
  NET_DATA_OPERATE_TEAM,           //添加新的好友分组
  NET_DATA_MODIFY_FRIEND_MARKNAME, //修改好友备注名
  NET_DATA_MOVE_FRIEND,            //移动好友至其他分组

  NET_DATA_FILE,
};

class CNetData {
public:
  CNetData();
  virtual ~CNetData();

public:
  uint32_t m_uType;   //数据类型
  long m_nRetryTimes; //当作为发送数据项时重试次数。
};

class CRegisterRequest : public CNetData {
public:
  CRegisterRequest();
  ~CRegisterRequest();

public:
  char m_szAccountName[64];
  char m_szNickName[64];
  char m_szPassword[64];

  bool FromJsonString(const std::string &msgJson) {

    std::string err;
    using namespace json11;
    auto json = Json::parse(msgJson, err);
    if (!err.empty()) {
      return false;
    }

    if (json["username"].is_string()) {
#ifdef WIN32
      //strcpy_s(m_szAccountName, json["username"].string_value().c_str());
#else
      strcpy(m_szAccountName, json["username"].string_value().c_str());
#endif
    } else {
      return false;
    }

    if (json["password"].is_string()) {
#ifdef WIN32
      //strcpy_s(m_szPassword, json["password"].string_value().c_str());
#else
#endif
    } else {
      return false;
    }

    if (json["nickname"].is_string()) {
		#ifdef WIN32
      //strcpy_s(m_szNickName, json["nickname"].string_value().c_str());
	  #endif
    } else {
      return false;
    }
    return true;
  }

  std::string ToString() const {
    using namespace json11;
    Json clientObj = Json::object({
        {"username", m_szAccountName},
        {"password", m_szPassword},
        {"nickname", m_szNickName},
    });
    return clientObj.dump();
  }
};

class CRegisterResult : public CNetData {
public:
  CRegisterResult();
  ~CRegisterResult();

public:
  long m_nResultCode;
  char m_szMobile[64];
  char m_szAccount[64];
};

class CLoginRequest : public CNetData {
public:
  CLoginRequest();
  ~CLoginRequest();

public:
  char m_szAccountName[64];
  char m_szPassword[64];
  long m_nStatus;
  LOGIN_TYPE m_nLoginType; //登录类型：0表示使用手机号登入，1表示使用账号登入

  bool FromJsonString(const std::string &msgJson) {

    std::string err;
    using namespace json11;
    auto json = Json::parse(msgJson, err);
    if (!err.empty()) {
      return false;
    }

    if (json["username"].is_string()) {
      //strcpy_s(m_szAccountName, json["username"].string_value().c_str());
    } else {
      return false;
    }

    if (json["password"].is_string()) {
      //strcpy_s(m_szPassword, json["password"].string_value().c_str());
    } else {
      return false;
    }

    if (json["status"].is_number()) {
      m_nStatus = (json["status"].int_value());
    } else {
      return false;
    }

    if (json["clienttype"].is_number()) {
      m_nLoginType = static_cast<LOGIN_TYPE>(json["clienttype"].int_value());
    } else {
      return false;
    }
    return true;
  }
};

class CLoginResult : public CNetData {
public:
  CLoginResult();
  ~CLoginResult();

public:
  long m_LoginResultCode;
  uint32_t m_uAccountID;
  char m_szAccountName[32];
  char m_szNickName[32];
  char m_szSignature[256];
  long m_nFace;
  char m_szCustomFace[64];
  int m_nGender;
  int m_nBirthday;
  char m_szAddress[512];
  char m_szPhoneNumber[64];
  char m_szMail[256];
  long m_nStatus;

  bool FromJsonString(const std::string &msgJson) {

    std::string err;
    using namespace json11;
    auto json = Json::parse(msgJson, err);
    if (!err.empty()) {
      return false;
    }

    if (json["code"].is_number()) {
      m_LoginResultCode = json["code"].int_value();
    } else {
      return false;
    }

    if (m_LoginResultCode != 0) {
      return false;
    }

    if (json["userid"].is_number()) {
      m_uAccountID = json["userid"].int_value();
    } else {
      return false;
    }

    if (json["username"].is_string()) {
		
      ////strcpy_s(m_szAccountName, json["username"].string_value().c_str());
    } else {
      return false;
    }

    if (json["nickname"].is_string()) {
      ////strcpy_s(m_szNickName, json["nickname"].string_value().c_str());
    } else {
      return false;
    }

    if (json["facetype"].is_number()) {
      this->m_nFace = json["facetype"].int_value();
    } else {
      return false;
    }

    if (json["gender"].is_number()) {
      this->m_nGender = (json["gender"].int_value());
    } else {
      return false;
    }

    if (json["birthday"].is_number()) {
      this->m_nBirthday = (json["birthday"].int_value());
    } else {
      return false;
    }

    if (json["signature"].is_string()) {
      //strcpy_s(m_szSignature, json["signature"].string_value().c_str());
      ;
    } else {
      return false;
    }

    if (json["address"].is_string()) {
      //strcpy_s(m_szAddress, json["address"].string_value().c_str());
      ;
    } else {
      return false;
    }

    if (json["customface"].is_string()) {
      //strcpy_s(m_szCustomFace, json["customface"].string_value().c_str());
      ;
    } else {
      return false;
    }

    if (json["phonenumber"].is_string()) {
      //strcpy_s(m_szPhoneNumber, json["phonenumber"].string_value().c_str());
      ;
    } else {
      return false;
    }

    if (json["mail"].is_string()) {
      //strcpy_s(m_szMail, json["mail"].string_value().c_str());
      ;
    } else {
      return false;
    }

    return true;
  }
};

class CUserBasicInfoRequest : public CNetData {
public:
  CUserBasicInfoRequest();
  ~CUserBasicInfoRequest();

public:
  std::set<uint32_t> m_setAccountID;
};
/*
class CUserBasicInfoResult : public CNetData
{
public:
        CUserBasicInfoResult();
        ~CUserBasicInfoResult();

public:
    //key是分组的名字，value是该组好友的集合
        std::map<std::string, std::list<UserBasicInfo*>> m_mapUserBasicInfo;
};

class CChangeUserStatusRequest : public CNetData
{
public:
    CChangeUserStatusRequest();
    ~CChangeUserStatusRequest();

public:
    int32_t m_nNewStatus;
};

class CGroupBasicInfoRequest : public CNetData
{
public:
    CGroupBasicInfoRequest();
    ~CGroupBasicInfoRequest();

public:
    int  m_groupid;
};

class CGroupBasicInfoResult : public CNetData
{
public:
    CGroupBasicInfoResult();
    ~CGroupBasicInfoResult();

public:
    int                       m_groupid;
    std::list<UserBasicInfo*> m_listUserBasicInfo;
};

class CUserExtendInfoRequest : public CNetData
{
public:
        CUserExtendInfoRequest();
        ~CUserExtendInfoRequest();

public:
        std::set<uint32_t> m_setAccountID;
};

class CUserExtendInfoResult : public CNetData
{
public:
        CUserExtendInfoResult();
        ~CUserExtendInfoResult();
public:
        std::list<UserExtendInfo*> m_listUserExtendInfo;
};

class CLoginUserFriendsIDRequest : public CNetData
{
public:
        CLoginUserFriendsIDRequest();
        ~CLoginUserFriendsIDRequest();

public:
        uint32_t m_uAccountID;
};

class CLoginUserFriendsIDResult : public CNetData
{
public:
        CLoginUserFriendsIDResult();
        ~CLoginUserFriendsIDResult();

public:
        uint32_t				m_uAccountID;
        std::set<uint32_t>		m_setFriendIDs;
        std::set<uint32_t>		m_setGroupIDs;
};

class CFriendStatus : public CNetData
{
public:
        CFriendStatus();
        ~CFriendStatus();

public:
        uint32_t	m_uAccountID;
        long	m_nStatus;
    long    m_nClientType;
    int     m_type;
};

class CFindFriendRequest : public CNetData
{
public:
        CFindFriendRequest();
        ~CFindFriendRequest();

public:
        char m_szAccountName[64];
        long m_nType;				//查找类型
};

class CFindFriendResult : public CNetData
{
public:
        CFindFriendResult();
        ~CFindFriendResult();

public:
        long m_nResultCode;
        uint32_t m_uAccountID;
        char m_szAccountName[64];
        char m_szNickName[64];
};

class COperateFriendRequest : public CNetData
{
public:
        COperateFriendRequest();
        ~COperateFriendRequest();

public:
        uint32_t m_uAccountID;
        uint32_t m_uCmd;
};

class COperateFriendResult : public CNetData
{
public:
        COperateFriendResult();
        ~COperateFriendResult();

public:
        uint32_t m_uAccountID;
        uint32_t m_uCmd;
        char m_szAccountName[64];
        char m_szNickName[64];
};

class CAddTeamInfoRequest : public CNetData
{
public:
    CAddTeamInfoRequest();
    ~CAddTeamInfoRequest();

public:
    int          m_opType;          //操作类型
    std::wstring m_strNewTeamName;
    std::wstring m_strOldTeamName;
};

class CAddTeamInfoResult : public CNetData
{
public:
    CAddTeamInfoResult();
    ~CAddTeamInfoResult();

public:
    int          m_opType;          //操作类型
};

class CMoveFriendRequest : public CNetData
{
public:
    CMoveFriendRequest();
    ~CMoveFriendRequest();

public:
    int          m_nFriendID;          //操作类型
    std::wstring m_strNewTeamName;
    std::wstring m_strOldTeamName;
};

class CMsgItem;





class CRecvChatMessage : public CNetData
{
public:
        CRecvChatMessage();
        ~CRecvChatMessage();

public:
        uint32_t  m_uMsgID;			//消息ID
        uint32_t  m_uSenderID;		//发送人ID
        uint32_t  m_uTargetID;		//接收者ID
        uint32_t  m_uMsgBodySize;	//消息正文内容长度
        char* m_pszMsgBody;		//消息正文内容
};

class CModifyPasswordRequest : public CNetData
{
public:
        CModifyPasswordRequest();
        ~CModifyPasswordRequest();

public:
        char m_szOldPassword[64];
        char m_szNewPassword[64];
};

class CModifyPasswordResult : public CNetData
{
public:
        CModifyPasswordResult();
        ~CModifyPasswordResult();

public:
        long	m_nResultCode;
};

//class CCreateNewGroupRequest
class CCreateNewGroupRequest : public CNetData
{
public:
        CCreateNewGroupRequest();
        ~CCreateNewGroupRequest();

public:
        char m_szGroupName[64];
};

//class CCreateGroupResult
class CCreateNewGroupResult : public CNetData
{
public:
        CCreateNewGroupResult();
        ~CCreateNewGroupResult();

public:
        uint32_t	m_uError;
        uint32_t	m_uAccountID;
        char	m_szGroupName[64];
        char	m_szAccount[32];
};

//class CModifyFriendMakeNameRequest
class CModifyFriendMakeNameRequest : public CNetData
{
public:
    CModifyFriendMakeNameRequest();
    ~CModifyFriendMakeNameRequest();

public:
    uint32_t	m_uFriendID;
    char   m_szNewMarkName[64];
};

//class CModifyFriendMakeNameResult
class CModifyFriendMakeNameResult : public CNetData
{
public:
    CModifyFriendMakeNameResult();
    ~CModifyFriendMakeNameResult();

public:
    uint32_t	m_uFriendID;
    //char	m_szNewMarkName[64];
};

class CHeartbeatMessageRequest : public CNetData
{
public:
        CHeartbeatMessageRequest();
        ~CHeartbeatMessageRequest();
};

class CHeartbeatMessageResult : public CNetData
{
public:
        ~CHeartbeatMessageResult();
        CHeartbeatMessageResult();
};

//class CUpdateLogonUserInfoRequest
class CUpdateLogonUserInfoRequest : public CNetData
{
public:
        CUpdateLogonUserInfoRequest();
        ~CUpdateLogonUserInfoRequest();

public:
        char	m_szNickName[64];
        char    m_szSignature[512];
        uint32_t	m_uGender;
        long	m_nBirthday;
        char    m_szAddress[64];
        char    m_szPhone[32];
        char    m_szMail[48];
        uint32_t	m_uFaceID;
        char   m_szCustomFace[MAX_PATH];
        bool    m_bUseCustomThumb;
//是否使用自定义头像
};

//class CUpdateLogonUserInfoResult
class CUpdateLogonUserInfoResult : public CNetData
{
public:
        CUpdateLogonUserInfoResult();
        ~CUpdateLogonUserInfoResult();

public:
    char	m_szNickName[64];
    char    m_szSignature[512];
    uint32_t	m_uGender;
    long	m_nBirthday;
    char    m_szAddress[64];
    char    m_szPhone[32];
    char    m_szMail[48];
    uint32_t	m_uFaceID;
    char    m_szCustomFace[MAX_PATH];
    bool    m_bUseCustomThumb;
};

//class CTargetInfoChangeResult
class CTargetInfoChangeResult : public CNetData
{
public:
        CTargetInfoChangeResult();
        ~CTargetInfoChangeResult();

public:
        uint32_t m_uAccountID;

};

class CScreenshotInfo
{
public:
    CScreenshotInfo();
    ~CScreenshotInfo();

public:
    std::string m_strBmpHeader;
    std::string m_strBmpData;
    uint32_t        m_targetId;
};


/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
// 文件传输内容
/////////////////////////////////////////////////////
class CBuddyMessage;
class CFileItemRequest : public CNetData
{
public:
        CFileItemRequest();
        ~CFileItemRequest();

public:
        long			m_nID;
        char			m_szUtfFilePath[MAX_PATH];
//文件utf8路径（用于下载，下载时必填）
        char			m_szFilePath[MAX_PATH];
//文件全饰路径（用于上传，上传时必填, 下载时作为目标文件路径） HWND
m_hwndReflection;			//
(非必须字段)
        HANDLE			m_hCancelEvent; // 取消事件
(非必须字段) uint32_t			m_uSenderID; std::set<uint32_t>
m_setTargetIDs; uint32_t			m_uAccountID;
//账户id，用于下载头像 long			m_nFileType;
//目前有聊天图片、离线文件和自定义头像三种类型 CBuddyMessage*  m_pBuddyMsg;

        bool			m_bPending;
//当该项已经在下载或者上传为FALSE，反之为TRUE
};

class CUploadFileResult
{
public:
        CUploadFileResult();
        ~CUploadFileResult();

public:
        void Clone(const CUploadFileResult* pSource);

public:
        long			m_nFileType;
        bool			m_bSuccessful;
//是否上传成功 int64_t			m_nFileSize;
//文件大小 char			m_szLocalName[MAX_PATH];
//本地文件名

        char			m_szMd5[64];
//文件的md5值 char			m_szRemoteName[MAX_PATH];
//上传成功以后文件在服务器上的路径名

        uint32_t			m_uSenderID;
        std::set<uint32_t>	m_setTargetIDs;
        HWND			m_hwndReflection;
};

struct FileProgress
{
        char szDestPath[MAX_PATH];
        long  nPercent;
//百分比，0～100之间(值为-1时，为获取文件md5值) long  nVerificationPercent;
//获取md5值进度（0～100）
};
*/
#endif
