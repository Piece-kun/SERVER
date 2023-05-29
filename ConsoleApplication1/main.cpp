#undef UNICODE

#define WIN32_LEAN_AND_MEAN
#include<fstream>
#include<iostream>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <locale>
#include <vector>
#include <string>


using namespace std;
fstream bw;

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
#define DEFAULT_IP "127.0.0.1"
#define MAX_MEMBERS 64
int ClientCount = 0;

SOCKET ListenSocket = INVALID_SOCKET;
SOCKET ClientSocket = INVALID_SOCKET;
SOCKET* ClientSockets;

void SendMessageToClient(int ID)
{
    bool flag = true, mflag;
    char name[11];
    strcpy_s(name, "<<");
    char buffer[DEFAULT_BUFLEN];
    char a[11], b[11], expr;
    fstream bw, br;
    for (;; Sleep(75))
    {

        std::memset(buffer, 0, sizeof(buffer));
        if (recv(ClientSockets[ID], buffer, DEFAULT_BUFLEN, 0))
        {
            
            bw.open("history.txt", ios::app);
            if (!bw) {
                cout << "File not created!";
            }


            if (flag)
            {
                strcat_s(name, buffer);
                strcat_s(buffer, " has joined the chat");
                bw << buffer << '\n';
                for (int i = 0; i <= ClientCount; i++)
                {
                    send(ClientSockets[i], buffer, strlen(buffer), 0);
                }
                
                flag = false;
                goto end;
            }
            if (!strcmp(buffer, "MATH"))
            {
                b[0] = a[0] = '\0';
                mflag = true;
                send(ClientSockets[ID], "Plese input your math problem.", strlen("Plese input your math problem."), 0);
                recv(ClientSockets[ID], buffer, DEFAULT_BUFLEN, 0);
                for (int i = 0;; i++)
                {
                    switch (buffer[i]) {
                    case '\0':
                    {
                        goto endOfLoop;
                    }
                    case '1':
                    {
                        if (mflag) strcat_s(a, "1");
                        else strcat_s(b, "1");
                        break;
                    }
                    case '2':
                    {
                        if (mflag) strcat_s(a, "2");
                        else strcat_s(b, "2");
                        break;
                    }
                    case '3':
                    {
                        if (mflag) strcat_s(a, "3");
                        else strcat_s(b, "3");
                        break;
                    }
                    case '4':
                    {
                        if (mflag) strcat_s(a, "4");
                        else strcat_s(b, "4");
                        break;
                    }
                    case '5':
                    {
                        if (mflag) strcat_s(a, "5");
                        else strcat_s(b, "5");
                        break;
                    }
                    case '6':
                    {
                        if (mflag) strcat_s(a, "6");
                        else strcat_s(b, "6");
                        break;
                    }
                    case '7':
                    {
                        if (mflag) strcat_s(a, "7");
                        else strcat_s(b, "7");
                        break;
                    }
                    case '8':
                    {
                        if (mflag) strcat_s(a, "8");
                        else strcat_s(b, "8");
                        break;
                    }
                    case '9':
                    {
                        if (mflag) strcat_s(a, "9");
                        else strcat_s(b, "9");
                        break;
                    }
                    case '0':
                    {
                        if (mflag) strcat_s(a, "0");
                        else strcat_s(b, "0");
                        break;
                    }
                    case'+':
                    {
                        if (!mflag) break;
                        expr = buffer[i];
                        mflag = false;
                        break;
                    }
                    case'-':
                    {
                        if (!mflag) break;
                        expr = buffer[i];
                        mflag = false;
                        break;
                    }
                    case'*':
                    {
                        if (!mflag) break;
                        expr = buffer[i];
                        mflag = false;
                        break;
                    }
                    case'/':
                    {
                        if (!mflag) break;
                        expr = buffer[i];
                        mflag = false;
                        break;
                    }

                    }

                }
            endOfLoop:
                switch (expr) {
                case '+': {
                    strcpy_s(buffer, a);
                    strcat_s(buffer, " + ");
                    strcat_s(buffer, b);
                    strcat_s(buffer, " = ");
                    _itoa_s((atoi(a) + atoi(b)), a, 10);
                    strcat_s(buffer, a);
                    send(ClientSockets[ID], buffer, strlen(buffer), 0);
                    bw <<"MATH " << buffer << '\n';
                    goto end;
                    break;
                }
                case '-': {
                    strcpy_s(buffer, a);
                    strcat_s(buffer, " - ");
                    strcat_s(buffer, b);
                    strcat_s(buffer, " = ");
                    _itoa_s((atoi(a) - atoi(b)), a, 10);
                    strcat_s(buffer, a);
                    send(ClientSockets[ID], buffer, strlen(buffer), 0);
                    bw << "MATH " << buffer << '\n';
                    goto end;

                    break;
                }
                case '*': {
                    strcpy_s(buffer, a);
                    strcat_s(buffer, " * ");
                    strcat_s(buffer, b);
                    strcat_s(buffer, " = ");
                    _itoa_s((atoi(a) * atoi(b)), a, 10);
                    strcat_s(buffer, a);
                    send(ClientSockets[ID], buffer, strlen(buffer), 0);
                    bw << "MATH " << buffer << '\n';
                    goto end;
                    break;
                }
                case '/': {
                    strcpy_s(buffer, a);
                    strcat_s(buffer, " / ");
                    strcat_s(buffer, b);
                    strcat_s(buffer, " = ");
                    _itoa_s((atoi(a) / atoi(b)), a, 10);
                    strcat_s(buffer, a);
                    send(ClientSockets[ID], buffer, strlen(buffer), 0);
                    bw << "MATH " << buffer << '\n';
                    goto end;
                    break;
                }
                }

            }
            if (!strcmp(buffer, "HIST"))
            {
                bw.close();
                
                br.open("history.txt", ios::in);
                br.seekg(0);
                if (!br) {
                    cout << "File not found!";
                }
                while (true)
                {
                    if (br.eof()) break;
                    br.read(buffer,512);
                    send(ClientSockets[ID], buffer, strlen(buffer), 0);
                }
                br.close();
            }
            else
            {
                printf(buffer);
                strcat_s(buffer, name);
                printf("\n");
                for (int i = 0; i <= ClientCount; i++)
                {
                    send(ClientSockets[i], buffer, strlen(buffer), 0);
                }
                if (strcmp(buffer, name))
                bw << buffer << '\n';
            }
        end:;
            
        }
        if (bw) bw.close();
    }
    delete buffer;
}

int __cdecl main(void)
{

    setlocale(LC_ALL, "russian");
    WSADATA wsaData;
    int iResult;

    struct addrinfo* result = NULL;
    struct addrinfo hints;

    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }


    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(DEFAULT_IP, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }


    // Create a SOCKET for the server to listen for client connections.
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    printf("Server start\n");

    ClientSockets = new SOCKET[MAX_MEMBERS];

    char m_connet[] = "Connected ";
    // Accept a client sockets
    for (;; Sleep(75))
    {
        ClientSocket = accept(ListenSocket, NULL, NULL);
        if (ClientSocket == INVALID_SOCKET) {
            printf("accept failed with error: %d\n", WSAGetLastError());
            closesocket(ListenSocket);
            WSACleanup();
            return 1;
        }
        else
        {
            printf("client connect\n");
            ClientSockets[ClientCount] = ClientSocket;
            send(ClientSockets[ClientCount], m_connet, (int)strlen(m_connet), NULL);
            ClientCount++;

            CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)SendMessageToClient,
                (LPVOID)(ClientCount - 1), NULL, NULL);
        }

    }


    // No longer need server socket
    closesocket(ListenSocket);

    // shutdown the connection since we're done
    iResult = shutdown(ClientSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        return 1;
    }

    // cleanup
    closesocket(ClientSocket);
    WSACleanup();

    return 0;
}
