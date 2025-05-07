#ifndef THERMOMETER_H
#define THERMOMETER_H

#include <stdint.h>
#include <time.h>
#include <stdlib.h>

#pragma pack(push, 1)
typedef struct {
    uint32_t timestamp;         
    uint16_t temperature;  //For instance 342 degrees = 34.2 degrees    
    uint8_t power_state;      
    uint8_t measurement_id;    
    uint8_t checksum;         
} ThermometerPacket;
#pragma pack(pop)

ThermometerPacket simulated_thermometer_data(void);
uint8_t compute_checksum(const ThermometerPacket* packet);

static inline uint16_t simulate_temperature(void) {
  return 200 + (rand() % 1001);
}

static inline uint8_t simulate_power_status(void) {
  return rand() % 2;
}

uint8_t compute_checksum();


#endif
