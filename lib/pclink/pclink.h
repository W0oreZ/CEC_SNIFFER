#ifndef PC_LINK_H
#define PC_LINK_H
#include "Arduino.h"
#include "Serialization.h"
#include "StringSplitter.h"

#define Serial Serial1

String jsonDebug(String msg, String type, bool obj);
void vLog(String msg);
void vWarn(String msg);
void vError(String msg);
void vInfo(String field,String value);
void vSensorLog(String type, String label, String value);
void vSendConfig(SIM_CONFIG* conf);
void vSetConfig(SIM_CONFIG* conf, String payload);
String jsonConfig(SIM_CONFIG* conf);

#endif