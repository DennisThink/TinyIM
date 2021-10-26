## 1. 设计目的
记录每个用户其好友分组的消息

## 2. 表字段介绍

| 字段名称      | 字段类型 | 长度 | 主键 | 注释                 | 备注                      |
| ------------- | -------- | ---- | ---- | -------------------- | ------------------------- |
| F_INDEX       | int      | 255  | Y    | 自增ID               |                           |
| F_USER_ID     | char     | 8    | N    | 请求添加好友的用户ID | 外键到T_USER表的F_USER_ID |
| F_TEAM_ID     | char     | 8    | N    | 分组ID               |                           |
| F_TEAM_NAME   | varchar  | 255  |      | 分组名称             |                           |
| F_CREATE_TIME | datetime |      |      | 创建时间             |                           |

## 3. SQL语句

```SQL
SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for t_user_team
-- ----------------------------
DROP TABLE IF EXISTS `t_user_team`;
CREATE TABLE `t_user_team`  (
  `F_INDEX` int(255) NOT NULL AUTO_INCREMENT COMMENT '唯一ID',
  `F_USER_ID` char(8) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL COMMENT '用户ID',
  `F_TEAM_ID` char(8) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL COMMENT '分组编号',
  `F_TEAM_NAME` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT '我的好友' COMMENT '分组名称',
  `F_CREATE_TIME` datetime(0) DEFAULT NULL COMMENT '创建日期',
  PRIMARY KEY (`F_INDEX`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_bin ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
```