#include <time.h>
#include <stdio.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "thermometer.h"
#include "net.h"

int main(int argc, char* argv[]) {
  if(argc != 3) {
    printf("Wrong number of arguments. Usage: %s <server_ip> <port> <interval>", argv[0]);
    return 1;
  }
  const char* ip = argv[1];
  const uint16_t port = atoi(argv[2]);


  struct sockaddr_in server_address;
  int sockfd = setup_udp_socket(ip, port, &server_address);

  srand(time(NULL));

  ThermometerPacket packet = simulated_thermometer_data();

  if(send_packet(sockfd, &packet, sizeof(packet), &server_address) < 0) {
    perror("Error appeared while sending a packet");
    return 1;
  }

  printf("Timestamp: %u | Temp: %.1f°C | Power: %s | ID: %u | Checksum: 0x%02X\n",
         packet.timestamp,
         packet.temperature / 10.0,
         packet.power_state ? "POWER_AC" : "POWER_BATTERY",
         packet.measurement_id,
         packet.checksum);

  return 0;
}
