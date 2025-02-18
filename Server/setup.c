#include <winsock2.h>

#define SERVER "127.0.0.1"
#define PORT 65432

int wins() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        return 1;
    }

    return 0;
}

SOCKET Cserver() {
    SOCKET server;
    struct sockaddr_in sa;

    server = socket(AF_INET, SOCK_STREAM, 0);
    if (server == INVALID_SOCKET) {
        WSACleanup();
        return INVALID_SOCKET;
    }

    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr(SERVER);  
    sa.sin_port = htons(PORT);       

    if (bind(server, (struct sockaddr *)&sa, sizeof(sa)) == SOCKET_ERROR) {
        closesocket(server);
        WSACleanup();
        return INVALID_SOCKET;
    }

    return server;
}
