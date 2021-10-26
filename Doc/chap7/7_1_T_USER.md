# 7.1 用户信息表T_USER

## 1. 设计目的

用于表示用户的基本信息以及上线和下线状态。

## 2. 表格字段以及含义

| 字段名称        | 类型     | 长度 | 主键 | 注释           | 备注                                         |
| --------------- | -------- | ---- | ---- | -------------- | -------------------------------------------- |
| F_INDEX         | bigint   |      | Y    | 自动递增无符号 | 主键                                         |
| F_USER_ID       | char     | 8    | Y    | 用户编号       | 程序生成，服务器分配                         |
| F_USER_NAME     | char     | 128  | N    | 用户名称       | 由用户输入                                   |
| F_PASS_WORD     | char     | 128  | N    | 用户密码       | 由系统根据用户的输入和<br>系统的盐值共同生成 |
| F_ADDRESS       | varchar  | 255  | N    | 用户地址       | 由用户输入                                   |
| F_BIRTH_DATE    | datetime |      | N    |                | 出生日期                                     |
| F_EMAIL_ADDR    | varchar  | 64   | N    | 电子邮箱地址   |
| F_NICK_NAME     | varchar  | 64   | N    | 用户昵称       |                                              |
| F_SIGNATURE     | varchar  | 128  | N    | 用户签名       |
| F_ON_LINE_STATE | enum     |      | N    | 在线状态       | 'ON_LINE','OFF_LINE'                         |
| F_CREATE_TIME   | datetime |      | N    | 创建时间       |                                              |
| F_UPDATE_TIME   | datetime |      | N    | 更新时间       |                                              |


## 3. SQL语句


```sql
SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for t_user
-- ----------------------------
DROP TABLE IF EXISTS `t_user`;
CREATE TABLE `t_user`  (
  `F_INDEX` int(255) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '数据记录索引，自增',
  `F_USER_ID` char(8) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL DEFAULT '00000000' COMMENT '用户ID',
  `F_USER_NAME` varchar(64) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL DEFAULT '11111111' COMMENT '用户名',
  `F_PASS_WORD` varchar(128) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL DEFAULT '11111111' COMMENT '用户密码',
  `F_ADDRESS` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT '北京市昌平区定泗路' COMMENT '用户住址',
  `F_BIRTH_DATE` varchar(64) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT '19901010' COMMENT '出生日期',
  `F_EMAIL_ADDR` varchar(64) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT 'test@dennisthink.com' COMMENT '电子邮箱地址',
  `F_NICK_NAME` varchar(64) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT 'DennisThink.com' COMMENT '用户昵称',
  `F_CREATE_TIME` timestamp(0) DEFAULT NULL COMMENT '创建时间',
  `F_UPDATE_TIME` timestamp(0) DEFAULT NULL COMMENT '最后更新时间',
  `F_SIGNATURE` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT '个人博客 https://www.dennisthink.com/' COMMENT '用户签名',
  `F_ON_LINE_STATE` enum('ON_LINE','OFF_LINE') CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT 'OFF_LINE' COMMENT '用户在线状态，分为在线和离线',
  `F_FACE_ID` int(11) DEFAULT 2 COMMENT '头像编号',
  `F_GENDER` enum('MALE','FEMALE','UN_KNOWN') CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT 'UN_KNOWN' COMMENT '用户性别',
  PRIMARY KEY (`F_INDEX`, `F_USER_ID`) USING BTREE,
  UNIQUE INDEX `F_USER_NAME_INDEX`(`F_USER_NAME`) USING BTREE COMMENT '用户名做唯一索引'
) ENGINE = InnoDB AUTO_INCREMENT = 2022 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_bin ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
```