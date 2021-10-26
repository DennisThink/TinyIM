/*
 Navicat Premium Data Transfer

 Source Server         : Local
 Source Server Type    : MySQL
 Source Server Version : 80016
 Source Host           : 127.0.0.1:3306
 Source Schema         : imdev

 Target Server Type    : MySQL
 Target Server Version : 80016
 File Encoding         : 65001

 Date: 27/08/2019 17:33:35
*/

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
