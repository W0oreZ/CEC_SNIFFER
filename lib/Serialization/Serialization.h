#ifndef SERIALIZATION_H
#define SERIALIZATION_H
#include "Arduino.h"
#include "EEPROM.h"

#if !defined(_SIM_CONF)
#define _SIM_CONF

typedef struct SIM_CONFIG
{ 
  char apn[25];
  char gprsUser[15];
  char gprsPass[15];
  char broker[25];
  int port;
  int interval;
} SIM_CONFIG;

#endif // _SIM_CONF


void vSerialize( SIM_CONFIG* simco );
bool vDeserialize( SIM_CONFIG* simco );

#endif