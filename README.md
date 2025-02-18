# Server-and-Client
TCP Server &amp; Client for Windows in C 

# Setup

![image](https://github.com/user-attachments/assets/a112cc50-0688-4d9a-8d82-91add7c1432f)
1. Open client.c with notpad. Replace The Server Address with your actual server address, local host won't work since this is the client.

2. Compile client.c
   
**Make sure you are in the same directory with client.c and server.c**
```gcc client.c -o client -lws2_32```

3. Compile server.c

**Make sure you are in the same directory with client.c and server.c**
```gcc server.c -o server -lws2_32```

# Images
![Screenshot 2025-02-17 165600](https://github.com/user-attachments/assets/825edd85-f2df-4899-a1dd-ba0cede4af5e)

![Screenshot 2025-02-17 165713](https://github.com/user-attachments/assets/4c0ef391-0efe-4b7c-a623-12330805ef21)
