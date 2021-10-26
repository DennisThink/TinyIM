# 7.6 群组关系表 T_GROUP_RELATION

## 1. 设计目的
记录每个用户其好友分组的消息

## 2. 表字段介绍

| 字段名称           | 字段类型 | 长度 | 主键 | 注释                                 | 备注                        |
| ------------------ | -------- | ---- | ---- | ------------------------------------ | --------------------------- |
| F_INDEX            | int      | 255  | Y    | 自增ID                               |                             |
| F_GROUP_ID         | char     | 8    | N    | 群组ID                               | 外键到T_GROUP表的F_GROUP_ID |
| F_USER_ID          | char     | 8    | N    | 用户ID                               | 外键到T_USER表的F_USER_ID   |
| F_ROLE_TYPE        | enum     | 255  |      | 用户角色，'OWNER','MANAGER','MEMBER' |                             |
| F_LAST_READ_MSG_ID | char     | 64   |      | 阅读的最后一个消息的编号             |                             |
| F_CREATE_TIME      | datetime |      |      | 创建时间                             |                             |

## 3. SQL语句

```SQL
SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for t_group_relation
-- ----------------------------
DROP TABLE IF EXISTS `t_group_relation`;
CREATE TABLE `t_group_relation`  (
  `F_INDEX` int(255) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '自增ID',
  `F_GROUP_ID` char(64) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL COMMENT '群组ID',
  `F_USER_ID` char(64) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL COMMENT '用户ID',
  `F_ROLE_TYPE` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL COMMENT '用户角色，\'OWNER\',\'MANAGER\',\'MEMBER\' ',
  `F_LAST_READ_MSG_ID` char(64) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT '00000000' COMMENT '阅读的最后一个消息的编号',
  `F_CREATE_TIME` datetime(0) DEFAULT NULL COMMENT '创建时间',
  PRIMARY KEY (`F_INDEX`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 33 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_bin ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;

```