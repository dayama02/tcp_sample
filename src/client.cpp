#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;
int main()
{
    struct sockaddr_in server;
    int sock;
    char buf[32];
    int n;

    /* ソケットの作成 */
    sock = socket(AF_INET, SOCK_STREAM, 0);

    /* 接続先指定用構造体の準備 */
    server.sin_family = AF_INET;
    server.sin_port = htons(12345);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    /* サーバに接続 */
    connect(sock, (struct sockaddr *)&server, sizeof(server));

    string message;

    cout << "Press \'q\' to enter" << endl;
    while(1){
        cout << "> " << std::flush;
        cin >> message;

        if(message == "q") break;

        /* 5文字送信 */
        write(sock, message.c_str(), message.length());
    }

    /* socketの終了 */
    close(sock);

    return 0;
}