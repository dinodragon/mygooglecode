这原本是协同编辑系统中发送邮件的模块，这只是一个原型。
使用前需要在系统中创建mailmessage的专有的事务型队列。


服务端设计Windows服务的形式运行，为简化调试这里有一个MailServiceStart
的工程用于启动服务程序，MailServiceClient用于模拟客户端，客户端和服务端以
消息队列的形式通信，使用了WCF的消息订阅机制。