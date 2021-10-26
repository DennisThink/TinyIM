# 7.7 群基本信息表T_GROUP

## 1. 设计目的
记录每个用户其好友分组的消息

## 2. 表字段介绍

| 字段名称      | 字段类型 | 长度 | 主键 | 注释     | 备注                     |
| ------------- | -------- | ---- | ---- | -------- | ------------------------ |
| F_INDEX       | int      | 255  | Y    | 自增ID   |                          |
| F_GROUP_ID    | char     | 8    | N    | 群组ID   | 由程序生成               |
| F_GROUP_NAME  | varchar  | 255  | N    | 群组名称 | 用户在创建群组的时候填写 |
| F_CREATE_TIME | datetime |      |      | 创建时间 |                          |
| F_GROUP_INFO  | varchar  | 255  | N    | 群组简介 |      群组信息             |

## 3. SQL语句

```sql
SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for t_group
-- ----------------------------
DROP TABLE IF EXISTS `t_group`;
CREATE TABLE `t_group`  (
  `F_INDEX` int(255) NOT NULL AUTO_INCREMENT COMMENT '自增ID',
  `F_GROUP_ID` char(8) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL COMMENT '群组ID',
  `F_GROUP_NAME` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT 'https://www.dennisthink.com' COMMENT '群组名称',
  `F_CREATE_TIME` datetime(0) DEFAULT NULL COMMENT '创建时间',
  `F_GROUP_INFO` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT 'https://www.dennisthink.com' COMMENT '群组简介',
  PRIMARY KEY (`F_INDEX`, `F_GROUP_ID`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 33 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_bin ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
```