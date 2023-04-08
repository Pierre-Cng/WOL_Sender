#include <winsock2.h>
#include <string>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main()
{
    WSADATA WSAData;
    WSAStartup(MAKEWORD(2,0), &WSAData);
    
    SOCKET sock;
    SOCKADDR_IN sin;
    sin.sin_addr.s_addr    = inet_addr("127.0.0.1");
    sin.sin_family        = AF_INET;
    sin.sin_port        = htons(4148);
    sock = socket(AF_INET,SOCK_STREAM,0);
    bind(sock, (SOCKADDR *)&sin, sizeof(sin));

    connect(sock, (SOCKADDR *)&sin, sizeof(sin));

    string targetMACaddress("TBD");
    string message = "ffffffffffff" + targetMACaddress;
    int lenght = message.size();
    
    /* correct with const char*/
    send(sock, "message", lenght, 0);

    /* plus rapide avec sendto() */

    WSACleanup();
    return 0;
}