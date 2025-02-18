#include <winsock2.h>
#include <stdio.h>
#include <string.h>  

int Send(SOCKET clients[], int amount, int message) {
    int errors = 0;
    char buffer[sizeof(int)];

    memcpy(buffer, &message, sizeof(int));

    for (int i = 0; i < amount; i++) {
        if (send(clients[i], buffer, sizeof(int), 0) == SOCKET_ERROR) {
            errors++;
        }
    }

    return errors;
}
