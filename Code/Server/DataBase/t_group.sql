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

 Date: 28/08/2019 11:48:43
*/

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
