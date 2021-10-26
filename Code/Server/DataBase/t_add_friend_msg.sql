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

 Date: 27/08/2019 17:47:39
*/

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
