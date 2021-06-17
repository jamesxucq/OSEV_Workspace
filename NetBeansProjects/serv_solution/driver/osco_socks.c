
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "osco_socks.h"

//
#define CONNE_SOCKS_DATSIZ               0x2000  // 8K

//
int osco_connect(serv_addr *saddr) {
    int conne_sock;
    if ((conne_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
printf("    osco socket create error!\n");
        return -1;
    }
    //
    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(saddr->sin_port);
    sin.sin_addr.s_addr = inet_addr(saddr->sin_addr);
    bzero(&(sin.sin_zero), 8);
    if (connect(conne_sock, (struct sockaddr *) &sin, sizeof (struct sockaddr)) == -1) {
printf("    osco socket connect error!\n");
printf("    sin_addr:%s sin_port:%d\n", saddr->sin_addr, saddr->sin_port);
        return -1;
    }
printf("    sin_addr:%s sin_port:%d\n", saddr->sin_addr, saddr->sin_port);
printf("    osco socket connect ok!\n");
    //
    return conne_sock;
}

//
int send_receive(char *recv_buffer, char *send_buffer, int slen, int conne_sock) {
    int bytes_sent, bytes_recv;
    //
    bytes_sent = send(conne_sock, send_buffer, slen, 0);
    if (bytes_sent != slen) { // reconnect to server
printf("    osco send failed!\n");
        return -1;
    }
    //    
    bytes_recv = recv(conne_sock, recv_buffer, CONNE_SOCKS_DATSIZ, 0);
    if (0 >= bytes_recv) { // bytes_recv = 0; bytes_recv < 0;
printf("    osco recv failed!\n");
        return -1;
    }
    return bytes_recv;
}

//
int osco_send(char *send_buffer, int slen, int conne_sock) {
    int bytes_sent;
    //
    bytes_sent = send(conne_sock, send_buffer, slen, 0);
    if (bytes_sent != slen) { // reconnect to server
printf("    osco send failed!\n");
        return -1;
    }
    //
    return bytes_sent;
}

//
int receive(char *recv_buffer, int conne_sock) {
    int bytes_recv;
    //    
    bytes_recv = recv(conne_sock, recv_buffer, CONNE_SOCKS_DATSIZ, 0);
    if (0 >= bytes_recv) { // bytes_recv = 0; bytes_recv < 0;
printf("    osco recv failed!\n");
        return -1;
    }
    return bytes_recv;
}