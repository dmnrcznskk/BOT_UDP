#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "thermometer.h"

static uint8_t current_measurement_id = 1;

uint8_t compute_checksum(const ThermometerPacket* packet) {
  uint8_t sum = 0;
  const uint8_t* data = (const uint8_t*)packet;

  for (size_t i = 0; i < sizeof(ThermometerPacket) - 1; ++i) {
    sum += data[i];
  }
  return sum;
}

ThermometerPacket simulated_thermometer_data(void) {
  ThermometerPacket packet;

  packet.timestamp = time(NULL);
  packet.temperature = simulate_temperature();
  packet.power_state = simulate_power_status();
  packet.measurement_id = current_measurement_id++;

  if(current_measurement_id == 0) { current_measurement_id = 1; }

  packet.checksum = compute_checksum(&packet);

  return packet;
}
