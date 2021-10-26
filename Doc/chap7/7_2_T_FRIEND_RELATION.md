# 7.2 好友关系表 T_FRIEND_RELATION

## 1. 设计目的
描述用户的好友关系

## 2. 表字段介绍

| 字段名称      | 字段类型 | 长度             | 主键 | 注释     | 备注                                       |
| ------------- | -------- | ---------------- | ---- | -------- | ------------------------------------------ |
| F_INDEX       | int      | 255              | Y    | 自增ID   |                                            |
| F_USER_ID     | char     | 8                | N    | 用户ID   | 外键到T_USER表的F_USER_ID                  |
| F_FRIEND_ID   | char     | 8                | N    | 好友ID   | 外键到T_USER表的F_USER_ID                  |
| F_TEAM_NAME   | char     | 128              | N    | 分组名   |                                            |
| F_STATUS      | enum     | 'FRIEND','BLACK' | N    | 好友状态 | 'FRIEND'表示为好友</br>'BLACK'表示为黑名单 |
| F_CREATE_TIME | datetime |                  | N    | 创建时间 |
| F_UPDATE_TIME | datetime |                  | N    | 更新时间 |


## 3. SQL语句

```SQL
SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for t_friend_relation
-- ----------------------------
DROP TABLE IF EXISTS `t_friend_relation`;
CREATE TABLE `t_friend_relation`  (
  `F_INDEX` int(255) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '自增ID',
  `F_USER_ID` char(8) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL COMMENT '用户ID,外键到T_USER表的F_USER_ID',
  `F_TEAM_ID` char(8) CHARACTER SET utf8 COLLATE utf8_bin DEFAULT '1000000' COMMENT '分组ID',
  `F_TEAM_NAME` char(128) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT NULL COMMENT '分组名',
  `F_FRIEND_ID` char(8) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL COMMENT '好友ID,外键到T_USER表的F_USER_ID',
  `F_STATUS` enum('FRIEND','BLACK') CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT NULL COMMENT '好友状态,\'FRIEND\',\'BLACK\'',
  `F_CREATE_TIME` datetime(0) DEFAULT NULL COMMENT '创建时间',
  `F_UPDATE_TIME` datetime(0) DEFAULT NULL COMMENT '更新时间',
  PRIMARY KEY (`F_INDEX`, `F_USER_ID`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 348 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_bin ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;

```