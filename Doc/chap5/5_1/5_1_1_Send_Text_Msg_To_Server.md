## 5.1.1 发送好友文本消息到服务器

1. 请求方式
POST

2. 请求URL
http://127.0.0.1:8000/send_friend_chat_text_msg

3. 请求JSON

* JSON字段

| 编号 | 字段       | 类型   | 含义                 | 备注 |
| ---- | ---------- | ------ | -------------------- | ---- |
| 1    | Context    | 字符串 | 文本消息内容UTF8格式 |      |
| 2    | FontInfo   | 字符串 | 字体信息的JSON字符串 |      |
| 3    | ReceiverId | 字符串 | 消息接受者的ID       |      |
| 4    | SenderId   | 字符串 | 发送者的消息ID       |      |

* JSON示例

```json
{
   "Context" : "23423424234234222222222222222222222222222222222222222222222222",
   "FontInfo" : "{\"FontColor\": \"000000\", \"FontName\": \"\", \"FontSize\": 9, \"FontStyle\": 0}",
   "ReceiverId" : "93755392",
   "SenderId" : "22106368"
}
```

4. 回复JSON

* JSON字段
  
| 编号 | 字段       | 类型   | 含义                 | 备注 |
| ---- | ---------- | ------ | -------------------- | ---- |
| 1    | Context    | 字符串 | 文本消息内容UTF8格式 |      |
| 2    | FontInfo   | 字符串 | 字体信息的JSON字符串 |      |
| 3    | ReceiverId | 字符串 | 消息接受者的ID       |      |
| 4    | SenderId   | 字符串 | 发送者的消息ID       |      |
| 5    | Code       | 整形   | 错误编码             |      |

* JSON示例

```json
{
   "Code" : 0,
   "Context" : "23423424234234222222222222222222222222222222222222222222222222",
   "FontInfo" : "{\"FontColor\": \"000000\", \"FontName\": \"\", \"FontSize\": 9, \"FontStyle\": 0}",
   "Message" : "Succeed",
   "MsgId" : "",
   "Receiver" : "93755392",
   "Sender" : "22106368"
}
```