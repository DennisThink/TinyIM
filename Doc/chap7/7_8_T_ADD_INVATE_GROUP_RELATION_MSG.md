# 7.8 记录群组申请加入的信息表 T_ADD_INVATE_GROUP_RELATION_MSG

## 1. 设计目的 (暂不使用)
记录群组申请加入、邀请加入和通过以及拒绝的信息。

## 2. 表字段介绍

| 字段名称            | 字段类型 | 长度 | 主键 | 注释                                                                | 备注                                                                                   |
| ------------------- | -------- | ---- | ---- | ------------------------------------------------------------------- | -------------------------------------------------------------------------------------- |
| F_INDEX             | int      | 255  | Y    | 自增ID                                                              |                                                                                        |
| F_MSG_ID            | char     | 64   | Y    | 消息ID,由程序生成                                                   |                                                                                        |
| F_GROUP_ID          | char     | 8    | N    | 群组ID,由程序生成                                                   |
| F_ADD_TYPE          | enum     |      | N    | 添加类型，请求加入‘REQUEST_TO_INTO',</br>‘INVATE_TO_INTO’，邀请加入 |
| F_ADD_FRIEND_STATUS | enum     |      | N    | 添加消息的状态，                                                    | 'UN_KNOWN','UN_READ','READ_UN_NOTIFY',</br> 'NOTIFY' 未读----->已读未通知------>已通知 |  |  |
| F_FRIEND_OPTION     | enum     |      |      | 'UN_KNOWN','AGREE_ADD','REFUSE_ADD'                                 |                                                                                        |  |
| F_CREATE_TIME       | datetime |      |      | 创建时间                                                            |
| F_OPTION_TIME       | datetime |      |      | 用户选择时间                                                        |
| F_NOTIFY_TIME       | datetime |      |      | 通知申请者的时间                                                    |

## 3. SQL语句
