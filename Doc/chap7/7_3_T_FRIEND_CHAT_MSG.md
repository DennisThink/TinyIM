# 7.3 好友聊天消息表 T_FRIEND_CHAT_MSG
## 1. 设计目的

保存好友的聊天消息,支持保存文本，图片等多种聊天消息。


## 2. 表字段设计

| 字段名称      | 字段类型  | 长度 | 主键 | 注释                 | 备注                      |
| ------------- | --------- | ---- | ---- | -------------------- | ------------------------- |
| F_INDEX       | bigint    | 255  | Y    | 自增ID，由数据库产生 |                           |
| F_MSG_ID      | char      | 64   | Y    | 消息ID,由程序生成    |                           |
| F_FROM_ID     | char      | 8    | N    | 消息发送者ID         | 外键到T_USER表的F_USER_ID |
| F_TO_ID       | char      | 8    | N    | 消息接收者ID         | 外键到T_USER表的F_USER_ID |
| F_MSG_CONTEXT | blob      | 0    | N    | 消息内容             | JSON格式的消息内容        |
| F_READ_FLAG   | enum      |      | N    | 信息是否被读取       | 'READ','UNREAD',          |
| F_CREATE_TIME | timestamp | 0    | N    | 信息创建时间         | 默认值为当前时间          |
| F_READ_TIME   | timestamp | 0    | N    | 信息读取时间         |                           |

## 3. SQL语句

```SQL
SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for t_friend_chat_msg
-- ----------------------------
DROP TABLE IF EXISTS `t_friend_chat_msg`;
CREATE TABLE `t_friend_chat_msg`  (
  `F_INDEX` bigint(255) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '自增ID，由数据库产生',
  `F_MSG_ID` char(64) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL COMMENT '消息ID,由程序生成',
  `F_FROM_ID` char(8) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL COMMENT '消息发送者ID',
  `F_TO_ID` char(8) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL COMMENT '消息接收者ID',
  `F_MSG_CONTEXT` text CHARACTER SET utf8 COLLATE utf8_bin NOT NULL COMMENT '消息内容',
  `F_READ_FLAG` enum('UNREAD','READ') CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT 'UNREAD' COMMENT '信息是否被读取,\'READ\',\'UNREAD\'',
  `F_CREATE_TIME` timestamp(0) DEFAULT CURRENT_TIMESTAMP COMMENT '信息创建时间',
  `F_READ_TIME` timestamp(0) DEFAULT NULL COMMENT '信息读取时间',
  PRIMARY KEY (`F_INDEX`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 1235 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_bin ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
```