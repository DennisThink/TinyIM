#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>
#include "CommonMsg.h"


TEST_CASE("KeepAliveReqBase") {
    KeepAliveReqMsg reqMsg("UnitTest");
    KeepAliveReqMsg parseMsg;
    CHECK_EQ(true,parseMsg.FromString(reqMsg.ToString()));
    CHECK_EQ(reqMsg.ToString(),parseMsg.ToString());
    
}

TEST_CASE("KeepAliveReqBase") {
    KeepAliveReqMsg reqMsg("UnitTest");
    std::shared_ptr<TransBaseMsg_t> pMsg = std::make_shared<TransBaseMsg_t>(reqMsg.GetMsgType(),reqMsg.ToString());
    CHECK_EQ(reqMsg.GetMsgType(),pMsg->GetType());
    CHECK_EQ(reqMsg.ToString().length()+8,pMsg->GetSize());
    KeepAliveReqMsg parseMsg;

    CHECK_EQ(reqMsg.ToString(),pMsg->to_string());
    CHECK_EQ(true,parseMsg.FromString(pMsg->to_string()));
    CHECK_EQ(reqMsg.ToString(),parseMsg.ToString());
    
}