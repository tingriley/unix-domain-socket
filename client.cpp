#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>

static const char *socket_path = "./mysocket";
static const unsigned int s_recv_len = 200;
static const unsigned int s_send_len = 100;

enum class CMD {
    INIT = 0,
    DATA = 1,
    FINISH = 2
};

int sendInit(int sock)
{
    CMD cmd = CMD::INIT;

    int data_len = 0;
    char send_msg[s_recv_len];
    char recv_msg[s_recv_len];
    memset(send_msg, 0, s_recv_len * sizeof(char));
    memset(recv_msg, 0, s_recv_len * sizeof(char));
    strcpy(send_msg, "1234");

    if (send(sock, &send_msg, sizeof(char)*strlen(send_msg), 0) == -1)
    {
        printf("Client: Error on send() call \n");
    }
   

    if ((data_len = recv(sock, recv_msg, s_recv_len, 0)) > 0)
    {
        printf("Client: Data received: %s \n", recv_msg);
    }
    else
    {
        if (data_len < 0)
        {
            printf("Client: Error on recv() call \n");
        }
        else
        {
            printf("Client: Server socket closed \n");
            close(sock);
        }
        return 1;
    }

    return 0;
}


int sendQuit(int sock)
{
    CMD cmd = CMD::INIT;

    int data_len = 0;
    char send_msg[s_recv_len];
    char recv_msg[s_recv_len];
    memset(send_msg, 0, s_recv_len * sizeof(char));
    memset(recv_msg, 0, s_recv_len * sizeof(char));
    strcpy(send_msg, "quit");

    if (send(sock, &send_msg, sizeof(char)*strlen(send_msg), 0) == -1)
    {
        printf("Client: Error on send() call \n");
    }
   

    if ((data_len = recv(sock, recv_msg, s_recv_len, 0)) > 0)
    {
        printf("Client: Data received: %s \n", recv_msg);
    }
    else
    {
        if (data_len < 0)
        {
            printf("Client: Error on recv() call \n");
        }
        else
        {
            printf("Client: Server socket closed \n");
            close(sock);
        }
        return 1;
    }

    return 0;
}

int main()
{
    int sock = 0;
    int data_len = 0;
    struct sockaddr_un remote;
    char recv_msg[s_recv_len];
    char send_msg[s_send_len];

    memset(recv_msg, 0, s_recv_len * sizeof(char));
    memset(send_msg, 0, s_send_len * sizeof(char));

    if ((sock = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
    {
        printf("Client: Error on socket() call \n");
        return 1;
    }

    remote.sun_family = AF_UNIX;
    strcpy(remote.sun_path, socket_path);
    data_len = strlen(remote.sun_path) + sizeof(remote.sun_family);

    printf("Client: Trying to connect... \n");
    if (connect(sock, (struct sockaddr *)&remote, sizeof(sockaddr)) == -1)
    {
        printf("Client: Error on connect call \n");
        return 1;
    }

    printf("Client: Connected \n");

    /*while (printf(">"), fgets(send_msg, s_send_len, stdin), !feof(stdin))
    {
        if (send(sock, send_msg, strlen(send_msg) * sizeof(char), 0) == -1)
        {
            printf("Client: Error on send() call \n");
        }
        memset(send_msg, 0, s_send_len * sizeof(char));
        memset(recv_msg, 0, s_recv_len * sizeof(char));

        if ((data_len = recv(sock, recv_msg, s_recv_len, 0)) > 0)
        {
            printf("Client: Data received: %s \n", recv_msg);
        }
        else
        {
            if (data_len < 0)
            {
                printf("Client: Error on recv() call \n");
            }
            else
            {
                printf("Client: Server socket closed \n");
                close(sock);
                break;
            }
        }
    }*/
   for(int i = 0; i < 3; i++){
    sendInit(sock);
    sleep(3);
   }
   sendQuit(sock);

    printf("Client: bye! \n");

    return 0;
}