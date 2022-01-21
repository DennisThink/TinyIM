#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>
#include "CDataBaseSqlite.h"
TEST_CASE("DemoTest"){
    int x = 1+2;
    int y = 2+1;
    CHECK_EQ(x,y);
    CDbSqlite dbUtil;
    CHECK(dbUtil.InitDataBase());
}