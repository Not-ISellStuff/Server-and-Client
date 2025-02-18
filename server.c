#include <winsock2.h>
#include <stdio.h>
#include <string.h>  
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

#define SERVER "127.0.0.1"
#define PORT 65432
#define MAX_CONNECTIONS 5

#include "Server/recv.c"
#include "Server/send.c"
#include "Server/setup.c"

typedef struct Server {
    SOCKET server;

    SOCKET connections[MAX_CONNECTIONS];
    int conn;
};

struct Server Server;

HANDLE t;
DWORD tid;

// if you're wondering why i'm not using a lib like pthread for threading
// i had some trouble using pthread, so i just used the windows api for threading

DWORD WINAPI LISTEN() {
    while (1) {
        if (Server.conn == MAX_CONNECTIONS) {
            printf("\n[!] Failed To Establish Connection Between Client and Server Due To The %d Limit For Connections.\n", MAX_CONNECTIONS);
            return 0;
        }

        SOCKET client = accept(Server.server, NULL, NULL);

        Server.connections[Server.conn] = client;
        Server.conn += 1;

        printf("\n[+] A client has connected!\n");
    }
}

int main() {
    printf("[+] Setting Things Up...\n");

    if (wins() == 1) {
        printf("[!] Failed To Start Server. | Winsock Initialization Failure");
        exit(EXIT_FAILURE);
    }

    Server.server = Cserver();

    if (Server.server == INVALID_SOCKET) {
        printf("[!] Failed To Create Server Socket | Invalid Server Address/Failed To Bind");
        exit(EXIT_FAILURE);
    }

    if (listen(Server.server, MAX_CONNECTIONS) == INVALID_SOCKET) {
        printf("[!] Failed To Start Listening For Connections | %d", WSAGetLastError());
        WSACleanup();
        closesocket(Server.server);
        exit(EXIT_FAILURE);
    }

    Server.conn = 0;
    printf("[+] Started Listening. | Server Address: %s | Server Port: %d\n", SERVER, PORT);
    t = CreateThread(NULL, 0, LISTEN, NULL, 0, &tid);

    while (1) {
        int option;

        printf("\n\nTotal Connections: %d | Max Connections: %d\n\n[1] Troll | Message Box\n[99] Exit\n\n> ", Server.conn, MAX_CONNECTIONS);
        scanf("%d", &option);

        //////////////////////////////////////

        if (option == 0) {
            printf("\n[!] Invalid Command\n");
        }

        if (option == 99) {
            break;
        }

        if (option == 1) {
            int sent = Send(Server.connections, Server.conn, option);
            printf("\n[+] Waiting for a response from %d clients | Sent Commands To %d Clients. | Failed To Send Commands To %d Clients.\n", Server.conn, Server.conn - sent, sent);
        }

        /////////////////////////////////////

        if (option != 0) {
            if (option < 2) {
                int errors = rec(Server.connections, Server.conn, option);

                printf("\n[+] Failed to get a response from %d clients.\n\n", Server.conn - errors);
            }
        }

        ////////////////////////////////////
    }

    closesocket(Server.server);
    WSACleanup();

    return 0;
}


