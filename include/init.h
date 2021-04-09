#if !defined(_INIT_H)
#define _INIT_H
#include <Arduino.h>
#include <Serialization.h>
#include <pclink.h>

#define Serial Serial1

#define TINY_GSM_MODEM_SIM868     //SIM module Version
#define GSM_AUTOBAUD_MIN 115200   //BAUDRATE 
#define GSM_AUTOBAUD_MAX 115200   //BAUDRATE
#include <TinyGsmClient.h>
#include <PubSubClient.h>

extern HardwareSerial Serial2;
extern HardwareSerial Serial3;

extern TinyGsm modem;
extern TinyGsmClient client;
extern PubSubClient Connection;

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

extern SIM_CONFIG simconfig;
void SETUP_HARDWARE();
void LOAD_CONFIGURATION();

#endif // _INIT_H
