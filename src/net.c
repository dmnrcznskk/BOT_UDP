#include <stdint.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "net.h"

int setup_udp_socket(const char* ip_str, uint16_t port, struct sockaddr_in* server_address) {

  memset(server_address, 0, sizeof(*server_address));
  server_address->sin_family = AF_INET;
  server_address->sin_port = htons(port);

  int res = inet_pton(AF_INET, ip_str, &server_address->sin_addr);
  if (res == 0) {
    fprintf(stderr, "Invalid IP address format: %s\n", ip_str);
    exit(1);
  }
  if (res == -1) {
    perror("inet_pton failed");
    exit(1);
  }

  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if(sockfd <= 0) {
    perror("Error appeared in <socket()>");
    exit(1);
  }

  return sockfd;
}

int send_packet(int sockfd, const void* buf, size_t len, const struct sockaddr_in* server_address) {
  return sendto(sockfd, buf, len, 0, (const struct sockaddr*)server_address, sizeof(*server_address));
}
