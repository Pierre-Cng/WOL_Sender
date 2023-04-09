#include <WinSock2.h>
#include <Ws2tcpip.h>
#include <iostream>
#include <string>
#include "main.hpp"

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main()
{
    socket_send();
    return 0;
}

int socket_send()
{
    // Initialize Winsock
    WSADATA wsaData;
    int error = WSAStartup(MAKEWORD(2, 2), &wsaData);
    error_check(error, "WSAStartup");

    // Create a socket for sending the magic packet
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET)
    {
        error_check(-1, "Socket");
    }

   // Set the socket options
    BOOL bOptVal = TRUE;
    int bOptLen = sizeof(BOOL);
    error = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char*)&bOptVal, bOptLen);
    error_check(error, "SetSockOpt");
    
    // Build the magic packet
    int const message_size(102);
    int const macaddress_size(6);
    unsigned char message[message_size];
    unsigned char macaddress[macaddress_size];
    magic_packet(macaddress, message);

    // Set the target address
    SOCKADDR_IN targetAddr;
    targetAddr.sin_family = AF_INET;
    targetAddr.sin_port = htons(9); // the WOL port is 9 or = htons(4148)?
    targetAddr.sin_addr.s_addr = INADDR_BROADCAST; // broadcast address or = inet_addr("127.0.0.1")?

    // Send the magic packet
    error = sendto(sock, (char*)message, sizeof(message), 0, (SOCKADDR*)&targetAddr, sizeof(targetAddr));
    error_check(error, "Sendto");
    
    // Cleanup
    closesocket(sock);
    WSACleanup();

    cout << "Magic packet sent successfully!" << endl;

    return 0;
}

void magic_packet(unsigned char macaddress[], unsigned char message[])
{
    memset(message, 0xFF, 6);
    for(int i(1); i<=16; i++)
    {
        memcpy(message + i * 6, macaddress, 6);
    }
}

int error_check(int error, string function_name)
{
    if (error != 0 || error == SOCKET_ERROR)
    {
        cerr << function_name << " failed with error: " << WSAGetLastError() << endl;
        WSACleanup();
        return 1;
    }
}