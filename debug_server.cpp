// server.cpp
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <string>
#include <pthread.h>

#include "sockop.h"

#define BUFSIZE 1024
using namespace std;

void* handleRequest(void* );

int main(int argc, char* argv[]) {
    int rc;
    pthread_t t[BUFSIZE]; // 宣告 pthread 變數

    if(argc != 2){
        errexit("Usage %s <host_port>\n", argv[0]);
    }

    int server_socket, new_client_socket[BUFSIZE];
    struct sockaddr_in addr_cln;
    socklen_t sLen;

    server_socket = passivesock(argv[1], "tcp", 10);
    sLen = sizeof(addr_cln);


    for(int i=0;i<BUFSIZE;i++){
        /* Wait for connection */
        // printf("start\n");
        new_client_socket[i] = accept(server_socket, (struct sockaddr*) &addr_cln, &sLen);
        if(new_client_socket[i] < 0) {
            syslog(LOG_ERR, "Failure in accept().");
            exit(EXIT_FAILURE);
        }
        // 建立子行程
        // printf("accept() success form fd %d !, %d\n", new_client_socket, addr_cln.sin_port);

        rc = pthread_create(&t[i], NULL, handleRequest, (void* )&new_client_socket[i]);
        if(rc){
            printf("ERROR; return coe form pthread_creat() is %d\n", rc);
            exit(-1);
        }

        // close(new_client_socket);
    }

    return 0;
}

void* handleRequest(void* c){
    int new_client_socket = *((int*)c);
    printf("Accept Client %d\n", new_client_socket-4);
    while(1){
        // printf("    start read from fd %d\n", new_client_socket);
        // close(server_socket);
        char rcv[BUFSIZE];
        memset(rcv, 0, BUFSIZE);
        if((read(new_client_socket, rcv, BUFSIZE)) == -1){
            errexit("   Error: read()\n");
        }
        string str(rcv);
        if(str == "")
            break;
        printf("%s", rcv);
        // printf("Received “%s”rom Client %d\n", rcv, new_client_socket-4);
        // if(write(new_client_socket, rcv, strlen(rcv)) == -1){
        //     errexit("   Error: write()\n");
        // }
    }
    close(new_client_socket);
}

