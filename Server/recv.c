#include <winsock2.h>
#include <stdio.h>
#include <string.h>  
#include <windows.h>

DWORD WINAPI get(LPVOID lpParam) {
    SOCKET client = ((SOCKET*)lpParam)[0];       
    int number = ((SOCKET*)lpParam)[1];          
    const char *command = (const char*)(((SOCKET*)lpParam)+2); 
    
    char buffer[1024];
    int bytes = recv(client, buffer, sizeof(buffer), 0);

    if (bytes == 0) {
        return 1;
    }

    if (bytes == SOCKET_ERROR) {
        return 1;
    }

    printf("\n[+] Response From Client #%d | Command: %s: %s\n", number, command, buffer);
    return 0;
}


int rec(SOCKET clients[], int ammount, const int command) {
    int errors = 0;
    HANDLE thread;
    DWORD threadId;

    // since i had trouble using the pthread lib
    // i had to use the windows api to create the threads for each client

    for (int i = 0; i < ammount; i++) {
        SOCKET params[3] = { clients[i], i, (SOCKET)command };

        thread = CreateThread(
            NULL,               
            0,                 
            get,               
            params,            
            0,                  
            &threadId          
        );

        if (thread == NULL) {
            errors++;
        } else {
            CloseHandle(thread);
        }
    }
    return errors;
}
