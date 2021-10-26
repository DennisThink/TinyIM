# 7.4 添加好友消息表 T_ADD_FRIEND_MSG

## 1. 设计目的
记录好友添加请求、添加确认的相关消息。

## 2. 表字段介绍

| 字段名称            | 字段类型 | 长度 | 主键 | 注释                                | 备注                                                                             |
| ------------------- | -------- | ---- | ---- | ----------------------------------- | -------------------------------------------------------------------------------- |
| F_INDEX             | int      | 255  | Y    | 自增ID                              |                                                                                  |
| F_MSG_ID            | char     | 64   | Y    | 消息ID,由程序生成                   |                                                                                  |
| F_USER_ID           | char     | 8    | N    | 请求添加好友的用户ID                | 外键到T_USER表的F_USER_ID                                                        |
| F_FRIEND_ID         | char     | 8    | N    | 被添加好友的用户                    | 外键到T_USER表的F_USER_ID                                                        |
| F_ADD_FRIEND_STATUS | enum     |      | N    | 添加消息的状态，                    | 'UN_KNOWN','UN_READ','READ_UN_NOTIFY','NOTIFY' 未读----->已读未通知------>已通知 |  |  |
| F_FRIEND_OPTION     | enum     |      |      | 'UN_KNOWN','AGREE_ADD','REFUSE_ADD' |                                                                                  |  |
| F_CREATE_TIME       | datetime |      | N    | 创建时间                            |
| F_OPTION_TIME       | datetime |      | N    | 对方回复的时间                      |
| F_NOTIFY_TIME       | datetime |      | N    | 通知发送方的时间                    |


## 3. SQL语句

```SQL
SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for t_add_friend_msg
-- ----------------------------
DROP TABLE IF EXISTS `t_add_friend_msg`;
CREATE TABLE `t_add_friend_msg`  (
  `F_INDEX` int(255) NOT NULL AUTO_INCREMENT,
  `F_MSG_ID` char(64) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT NULL COMMENT '消息ID',
  `F_USER_ID` char(8) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT NULL COMMENT '请求添加好友的用户',
  `F_FRIEND_ID` char(8) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT NULL COMMENT '被添加好友的用户',
  `F_ADD_FRIEND_STATUS` enum('UN_KNOWN','UN_READ','READ_UN_NOTIFY','NOTIFY') CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT 'UN_KNOWN' COMMENT '添加消息的状态，\r\n未读----->已读未通知------>已通知',
  `F_FRIEND_OPTION` enum('UN_KNOWN','AGREE_ADD','REFUSE_ADD') CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT 'UN_KNOWN' COMMENT '同意，未同意',
  `F_CREATE_TIME` datetime(0) DEFAULT NULL COMMENT '创建的时间',
  `F_OPTION_TIME` datetime(0) DEFAULT NULL COMMENT '对方回复的时间',
  `F_NOTIFY_TIME` datetime(0) DEFAULT NULL COMMENT '通知发送方的时间',
  PRIMARY KEY (`F_INDEX`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 214 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_bin ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
```