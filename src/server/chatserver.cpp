#include "chatserver.hpp"
#include "json.hpp"
#include "chatservice.hpp"
#include <functional>
using namespace std;
using namespace placeholders;

// 初始化聊天服务器对象
ChatServer::ChatServer(EventLoop* loop, 
        const InetAddress& listenAddr,
        const string& nameArg)
        : _loop(loop)
        , _server(loop, listenAddr, nameArg)
        {
            _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));
            _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));
            // 设置线程数量
            _server.setThreadNum(4);
        }

// 启动服务
void ChatServer::start()
{
    _server.start();
}
  

// 上报链接相关信息的回调函数
void ChatServer::onConnection(const TcpConnectionPtr& conn)
{
    if (!conn->connected())
    {
        ChatService::instance()->clientCloseException(conn);

        conn->shutdown();
    }
}
// 上报读写事件相关信息的回调函数
void ChatServer::onMessage(const TcpConnectionPtr& conn,
                        Buffer* buffer,
                        Timestamp time)
{
    string buf = buffer->retrieveAllAsString();
    // 数据的反序列化
    json js = json::parse(buf);
    // 达到目的地：完全解耦网络模块的代码和业务模块的代码
    // 通过js["msgid"]获取=》业务handler=》conn js time
    auto msgHandler = ChatService::instance()->getHandler(js["msgid"].get<int>());
    // 回调消息绑定好的事件处理器，来执行相应的业务处理
    msgHandler(conn, js, time);
}