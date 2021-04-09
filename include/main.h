#if !defined(_MAIN_H)
#define _MAIN_H
#include <Arduino.h>
#include <EEPROM.h>


void BOOTSTRAP_MODEM();
boolean StartConnection();
void MessageHandler(char* topic, byte* payload, unsigned int len);



#endif // _MAIN_H
