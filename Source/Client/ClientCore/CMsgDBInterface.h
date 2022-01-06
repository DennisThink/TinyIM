#ifndef _TINY_IM_MSG_DB_INTERFACE_H_
#define _TINY_IM_MSG_DB_INTERFACE_H_
#include "CommonMsg.h"
#include "Log.h"
class CMsgDbInterface {
public:
  virtual bool InitDataBase();
  virtual bool
  Save_RecvGroupTextMsgReqMsg(const RecvGroupTextMsgReqMsg &reqMsg);
  virtual bool
  Save_FriendRecvFileMsgReqMsg(const FriendRecvFileMsgReqMsg &reqMsg);
  virtual bool
  Save_FriendNotifyFileMsgReqMsg(const FriendNotifyFileMsgReqMsg &reqMsg);
  virtual bool Save_AddFriendRecvReqMsg(const AddFriendRecvReqMsg &reqMsg);
  virtual bool Save_AddFriendNotifyReqMsg(const AddFriendNotifyReqMsg &reqMsg);
  virtual bool
  Save_FriendChatRecvTxtReqMsg(const FriendChatRecvTxtReqMsg &reqMsg);
};
#endif