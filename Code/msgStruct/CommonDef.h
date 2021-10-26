#ifndef _COMMON_DEF_H_
#define _COMMON_DEF_H_
#include <string.h>
#include <string>
/**
 * @brief 定义消息的类型，
 *        如果您需要定义新的消息，可以直接在后面添加
 *
 */
enum class MessageType :uint32_t
{
	Base_Type,
	//心跳请求消息
	KeepAliveReq_Type,
	//心跳回复消息
	KeepAliveRsp_Type,


	//登录请求
	UserLoginReq_Type,
	//登录回复
	UserLoginRsp_Type,

	//登出请求
	UserLogoutReq_Type,
	//登出回复
	UserLogoutRsp_Type,

	//注册请求
	UserRegisterReq_Type,
	//注册回复
	UserRegisterRsp_Type,

	//注销请求
UserUnRegisterReq_Type,

//注销回复
UserUnRegisterRsp_Type,


//好友聊天之文本消息接收请求 Server--->Receiver
FriendChatReceiveTxtMsgReq_Type,

//Receiver--->Server
FriendChatReceiveTxtMsgRsp_Type,

//好友聊天之文本消息请求 Sender---->Server
FriendChatSendTxtMsgReq_Type,

//好友聊天之文本消息回复 Server----->Sender
FriendChatSendTxtMsgRsp_Type,

//表情消息请求   Sender--->Server
FriendChatSendEmojiMsgReq_Type,

//表情消息回复   Server--->Server
FriendChatSendEmojiMsgRsp_Type,

//图片消息请求
FriendChatSendImageMsgReq_Type,

//图片消息回复
FriendChatSendImageMsgRsp_Type,


//发送文件请求
FriendSendFileMsgReq_Type,

//发送文件回复
FriendSendFileMsgRsp_Type,

//接收文件请求
FriendRecvFileMsgReq_Type,

//接收文件请求
FriendRecvFileMsgRsp_Type,

//接收文件通知请求
FriendNotifyFileMsgReq_Type,

//接收文件通知回复
FriendNotifyFileMsgRsp_Type,

//好友发送在线文件数据回复
FriendChatSendFileDataOnLineRsp_Type,

//好友发送离线文件数据请求
FriendChatSendFileDataOffLineReq_Type,

//好友发送离线文件回复
FriendChatSendFileDataOffLineRsp_Type,

//查找好友请求
FindFriendReq_Type,

//查找好友回复
FindFriendRsp_Type,

//添加好友请求[请求者--->服务器]
AddFriendSendReq_Type,

//添加好友回复[服务器--->请求者]
AddFriendSendRsp_Type,

//接收添加好友请求[服务器-->接收者]
AddFriendRecvReq_Type,

//发送添加好友回复[接收者-->服务器]
AddFriendRecvRsp_Type,

//添加好友回复通知[服务器-->发送者]
AddFriendNotifyReq_Type,

//添加好友回复通知[发送者-->服务器]
AddFriendNotifyRsp_Type,

//删除好友请求
RemoveFriendReq_Type,

//删除好友回复
RemoveFriendRsp_Type,

//获取好友列表请求消息
GetFriendListReq_Type,

//获取好友列表回复消息
GetFriendListRsp_Type,

//获取群组列表请求消息
GetGroupListReq_Type,

//获取群组列表回复消息
GetGroupListRsp_Type,

//网络失去连接
NetFailedReport_Type,

//网络连接恢复正常
NetRecoverReport_Type,

//增加分组请求消息
AddTeamReq_Type,

//增加分组回复消息
AddTeamRsp_Type,

//删除分组请求消息
RemoveTeamReq_Type,

//删除分组回复消息
RemoveTeamRsp_Type,

//添加好友到分组的请求
AddFriendToTeamReq_Type,

//添加好友到分组的回复
AddFriendToTeamRsp_Type,

//移动好友到分组请求
MoveFriendToTeamReq_Type,

//移动好友到分组回复
MoveFriendToTeamRsp_Type,

//修改分组名称请求
ModifyTeamNameReq_Type,

//修改分组名称回复
ModifyTeamNameRsp_Type,

//创建群聊请求
CreateGroupReq_Type,

//创建群聊回复
CreateGroupRsp_Type,

//解散群聊请求
DestroyGroupReq_Type,

//解散群聊回复
DestroyGroupRsp_Type,

//查找群组请求
FindGroupReq_Type,

//查找群组回复
FindGroupRsp_Type,

//加入群组请求[请求者--->服务器]
AddToGroupReq_Type,

//加入群组回复[服务器--->请求者]
AddToGroupRsp_Type,

//加入群组通过请求[服务器-->管理员]
AddToGroupRecvReq_Type,

//加入群组通过回复[管理员-->服务器]
AddToGroupRecvRsp_Type,

//加入群组结果通知请求[服务器--->请求方]
AddToGroupNotifyReq_Type,

//加入群组结果通知回复[服务器--->请求方]
AddToGroupNotifyRsp_Type,


//邀请加入群组请求[发起请求方--->服务器]
InviteFriendToGroupReq_Type,

//邀请加入群组回复[服务器--->发起请求方]
InviteFriendToGroupRsp_Type,


//邀请请求送达对方[服务器--->被请求方]
InviteToGroupRecvReq_Type,

//邀请请求送达对方后，对方的回复[被请求方---->服务器]
InviteToGroupRecvRsp_Type,

//邀请结果通知[服务器-->发起方]
InviteResultNotifyReq_Type,

//邀请结果通知回复[发起方---->服务器]
InviteResultNotifyRsp_Type,

//群组文本聊天消息请求
SendGroupTextMsgReq_Type,

//群组文本聊天消息回复
SendGroupTextMsgRsp_Type,

//群组文本聊天消息请求
RecvGroupTextMsgReq_Type,

//群组文本聊天消息回复
RecvGroupTextMsgRsp_Type,

//退出群请求
QuitGroupReq_Type,

//退出群回复
QuitGroupRsp_Type,

//文件发送数据请求 [发送方]---->[服务器]
FileSendDataReq_Type,

//文件发送数据回复 [服务器]----->[接收方]
FileSendDataRsp_Type,

//文件接收数据请求 [服务器]----->[接收方]
FileRecvDataReq_Type,

//文件接收数据回复 [接收方]----->[服务器]
FileRecvDataRsp_Type,

//文件验证请求 [文件发送方]----->[文件接收方]
FileVerifyReq_Type,

//文件验证回复 [文件接收方]----->[文件发送方]
FileVerifyRsp_Type,

//用户被踢出消息请求(用户的账号在其他地点登录) [服务器]---->[接收方]
UserKickOffReq_Type,

//用户被踢出消息回复(用户的账号在其他地点登录) [接收方]---->[服务器]
UserKickOffRsp_Type,

//用户有好友未读消息通知[服务器]---->[接收方]
FriendUnReadMsgNotifyReq_Type,

//用户有好友未读消息通知回复[接收方]---->[服务器]
FriendUnReadMsgNotifyRsp_Type,

//群组未读消息通知
GroupUnReadMsgNotifyReq_Type,

//群组未读消息通知回复
GroupUnReadMsgNotifyRsp_Type,


};

//客户端会话状态
enum class CLIENT_SESS_STATE
{
	SESS_UN_LOGIN,//用户未登陆
	SESS_LOGIN_SEND,//用户已经发起登陆请求
	SESS_LOGIN_FINISHED,//用户登录完成
	SESS_LOGOUT_SEND,//用户已经发起退出登录请求
	SESS_LOGOUT,//用户已经登出
	SESS_IDLE_STATE,//处于空闲状态
	SESS_RELATION_SEND_RECV, //关系消息收发状态
	SESS_RELATION_FINISH,
	SESS_FRIEND_MSG_SEND_RECV_STATE,//好友信息收发状态
	SESS_FRIEND_FINISH,
	SESS_GROUP_MSG_SEND_RECV_STATE,//群组消息收发状态
	SESS_GROUP_FINISH,
};
//操作系统类型
enum class CLIENT_OS_TYPE {
	//未知类型
	OS_TYPE_UNKNOWN,
	
	//Windows
	OS_TYPE_WINDOWS,
	
	//Linux
	OS_TYPE_LINUX,

	//苹果电脑系统
	OS_TYPE_MAC,

	//安卓手机
	OS_TYPE_ANDROID,
	
	//Iphone手机
	OS_TYPE_IOS,
};

//网络类型
enum class CLIENT_NET_TYPE {
	C_NET_TYPE_UNKNOWN,
	C_NET_TYPE_WIFI,//WIFI网络
	C_NET_TYPE_3G,//3G网络
	C_NET_TYPE_4G,//4G网络
	C_NET_TYPE_5G,//5G网络
};

//在线类型
enum class CLIENT_ONLINE_TYPE {
	//未知
	C_ONLINE_TYPE_UNKNOWN,
	
	//在线
	C_ONLINE_TYPE_ONLINE,
	
	//离线
	C_ONLINE_TYPE_OFFLINE,
	
	//隐身
	C_ONLINE_TYPE_INVISIBLE,
};

//操作返回的错误代码
enum class ERROR_CODE_TYPE {
	E_CODE_SUCCEED = 0,//成功

	//通用错误
	E_CODE_CONNECT_FAILED,//网络已经断开

	//用户注册错误码
	E_CODE_USER_HAS_EXIST, //用户已存在
	//
	E_CODE_LOGIN_FAILED,//登录失败
	E_CODE_NO_SUCH_USER,//没有此用户
	E_CODE_USER_NAME_PASS_WORD_NOT_MATCH, //用户名密码不匹配
	E_CODE_VERIFY_CODE_NOT_MATCH,         //验证码不匹配
	E_CODE_USER_OFF_LINE,//用户不在线
	E_CODE_EMPTY_GROUP_NAME,//群组名称为空

	E_CODE_ADD_SELF_AS_FRIEND,//添加自己为好友
};

//好友关系类型
enum class E_FRIEND_RELATION {
	E_FRIEND_TYPE,//好友
	E_BLACK_TYPE,  //黑名单
	E_STRANGER_TYPE, //陌生人
};

//添加朋友选择
enum class E_FRIEND_OPTION {
	E_UN_KNOWN, //未知
	E_AGREE_ADD,//同意添加
	E_REFUSE_ADD,//拒绝添加
};

//添加好友的状态
enum class E_ADD_FRIEND_STATUS {
	E_UN_KNOWN, //未知
	E_UN_READ,//未通知接收方
	E_READ_UN_NOTIFY, //已通知接收方，未通知发送方
	E_NOTIFY,//已通知发送方
};

//群组成员的角色
enum class E_GROUP_MEMBER_ROLE {
	E_ROLE_CREATER, //群主
	E_ROLE_MANAGER, //管理员
	E_ROLE_MEMBER,  //群成员
	E_ROLE_UNKNOWN, //未知错误
};

enum class CHAT_MSG_TYPE
{
	E_CHAT_UNKNOWN_TYPE,//未知类型
	E_CHAT_TEXT_TYPE,//文本消息
	E_CHAT_FILE_TYPE,//文件消息
	E_CHAT_EMOJI_TYPE,//表情消息
	E_CHAT_IMAGE_TYPE,//图片消息
};

std::string FriendOption(const E_FRIEND_OPTION& option);
E_FRIEND_OPTION FriendOption(const std::string strOption);

std::string FriendStatus(const E_ADD_FRIEND_STATUS relation);
E_ADD_FRIEND_STATUS FriendStatus(const std::string strStatus);

E_GROUP_MEMBER_ROLE MemberRole(const std::string strRole);
std::string MemberRole(const E_GROUP_MEMBER_ROLE role);

std::string MsgType(const MessageType& msgType);


std::string   ChatType(const CHAT_MSG_TYPE& chatType);
CHAT_MSG_TYPE ChatType(const std::string strType);



std::string StringToHex(const std::string& strInput);
std::string HexToString(const std::string& strInput);

std::string OnLineType(const CLIENT_ONLINE_TYPE onlineType);
CLIENT_ONLINE_TYPE OnLineType(const std::string strOnlineType);
#endif