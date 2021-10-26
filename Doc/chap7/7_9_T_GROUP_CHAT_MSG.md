# 7.9 群聊信息表 T_GROUP_CHAT_MSG

## 1. 设计目的
记录群组聊天消息。

## 2. 表字段介绍

| 字段名称      | 字段类型 | 长度 | 主键 | 注释                                     |
| ------------- | -------- | ---- | ---- | ---------------------------------------- |
| F_INDEX       | int      | 255  | Y    | 自增ID                                   |
| F_MSG_ID      | char     | 64   | Y    | 消息ID,由程序生成                        |
| F_SENDER_ID   | char     | 8    | N    | 消息发送者ID,外键链接到T_USER的F_USER_ID |
| F_GROUP_ID    | char     | 8    | N    | 群组ID，外键链接到T_GROUP的F_GROUP_ID    |
| F_MSG_CONTEXT | blob     |      |      | 消息内容,JSON格式                        |
| F_CREATE_TIME | datetime |      | N    | 创建时间                                 |

## 3. SQL语句

```SQL
SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for t_group_chat_msg
-- ----------------------------
DROP TABLE IF EXISTS `t_group_chat_msg`;
CREATE TABLE `t_group_chat_msg`  (
  `F_INDEX` int(255) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '自增ID',
  `F_MSG_ID` char(64) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT NULL COMMENT '消息ID,由程序生成 ',
  `F_SENDER_ID` char(8) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT NULL COMMENT '消息发送者ID,外键链接到T_USER的F_USER_ID',
  `F_GROUP_ID` char(8) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT NULL COMMENT '群组ID，外键链接到T_GROUP的F_GROUP_ID',
  `F_MSG_CONTEXT` blob COMMENT '消息内容',
  `F_CREATE_TIME` datetime(0) DEFAULT NULL COMMENT '创建时间',
  PRIMARY KEY (`F_INDEX`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 201 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_bin ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;

```