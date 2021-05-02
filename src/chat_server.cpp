#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include "chat_server.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

namespace tcp_sample
{
    ChatServer::ChatServer()
    {
        
    }
    ChatServer::~ChatServer()
    {
        worker_thread_.join();
        cout << "server is stopped" << endl;
    };
    
    void ChatServer::run()
    {
        state_ = ThreadState::Running;
        worker_thread_ = std::thread([this](){this->workerTask();});                
    }
    void ChatServer::stop()
    {
        state_ = ThreadState::Stop;   
    }

    void ChatServer::workerTask()
    {
        /* ソケットの作成 */
        sock0 = socket(AF_INET, SOCK_STREAM, 0);

        /* ソケットの設定 */
        addr.sin_family = AF_INET;
        addr.sin_port = htons(TCP_PORT_NUMBER);
        addr.sin_addr.s_addr = INADDR_ANY;
        bind(sock0, (struct sockaddr *)&addr, sizeof(addr));

        /* TCPクライアントからの接続要求を待てる状態にする */
        listen(sock0, 5);

        /* TCPクライアントからの接続要求を受け付ける */
        len = sizeof(client);
        sock = accept(sock0, (struct sockaddr *)&client, (socklen_t*)&len);

        while(state_ == ThreadState::Running){
            /* サーバからデータを受信 */
            memset(buf, 0, sizeof(buf));
            n = read(sock, buf, sizeof(buf));

            if(n < 0){
                /* エラー */
                cout << "error !!" << endl;
                break;
            }
            if(n == 0){
                cout << "connection closed !!" << endl;
                break;
            }
            cout << "> " << n << "," << buf << endl;
        }
        /* TCPセッションの終了 */
        close(sock);

        /* listen するsocketの終了 */
        close(sock0);

        state_ = ThreadState::Stop;
    }

    ThreadState ChatServer::getState()
    {
        return state_;
    }

}// end of namespace tcp_sample