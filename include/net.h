#ifndef NET_H
#define NET_H

#include <stdint.h>
#include <arpa/inet.h>

int setup_udp_socket(const char* ip_str, uint16_t port, struct sockaddr_in* server_address);
int send_packet(int sockfd, const void* buf, size_t len, const struct sockaddr_in* server_address); 

#endif
