#include "CDataBaseSqlite.h"
#include <exception>
#include <iostream>
    CDbSqlite::CDbSqlite()
    {
        m_strDataBaseFileName="TinyImServer.db";
    }
bool CDbSqlite::InitDataBase() {
  bool bResult = true;
  try {
    SQLite::Database db("TinyImServer.db",
                        SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);

    {
        db.exec("CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT)");
    SQLite::Transaction transaction(db);

    transaction.commit();
    int nb = db.exec("INSERT INTO test VALUES (NULL, \"test\")");
    std::cout << "INSERT INTO test VALUES (NULL, \"test\")\", returned " << nb
              << std::endl;
                  SQLite::Transaction transaction2(db);

    transaction2.commit();
    }
    {
        db.exec("create table t_user(
                F_INDEX int(255) PRIMARY KEY NOT NULL ,
                F_USER_ID varchar(8)   NOT NULL,
                F_USER_NAME varchar(64)   NOT NULL,
                F_PASS_WORD varchar(128)   NOT NULL,
                F_ADDRESS varchar(255),
                F_BIRTH_DATE varchar(64)   ,
                F_EMAIL_ADDR varchar(64)  ,
                F_NICK_NAME varchar(64)   ,
                F_CREATE_TIME timestamp(0) ,
                F_UPDATE_TIME timestamp(0) ,
                F_SIGNATURE varchar(255)   ,
                F_ON_LINE_STATE int,
                F_FACE_ID int DEFAULT 2,
                F_GENDER int)";
                SQLite::Transaction transaction(db);
                transaction.commit();
    }
  } catch (std::exception &e) {
    bResult = false;
  }
  return bResult;
}
bool CDbSqlite::SelectUserByName(const std::string userName,
                                 T_USER_BEAN &bean) {
  return false;
}

bool CDbSqlite::UpdateUser(const T_USER_BEAN &bean) { return false; }

bool CDbSqlite::DeleteUser(const std::string strUserId) { return false; }

bool CDbSqlite::InsertUser(const T_USER_BEAN &bean) { return false; }

bool CDbSqlite::IsUserExist(const std::string strUserId) { return false; }