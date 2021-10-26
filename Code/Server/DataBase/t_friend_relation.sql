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

 Date: 27/08/2019 17:41:39
*/

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
