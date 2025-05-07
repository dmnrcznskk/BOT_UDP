#include <time.h>
#include <stdio.h>
#include "thermometer.h"
#include <unistd.h>

int main() {
  srand(time(NULL));

  while(1){
  ThermometerPacket packet = simulated_thermometer_data();

  printf("Timestamp: %u | Temp: %.1f°C | Power: %s | ID: %u | Checksum: 0x%02X\n",
         packet.timestamp,
         packet.temperature / 10.0,
         packet.power_state ? "POWER_AC" : "POWER_BATTERY",
         packet.measurement_id,
         packet.checksum);

  sleep(1);
  }

  return 0;
}
