#include <init.h>

HardwareSerial Serial3(PA3, PA2);
HardwareSerial Serial2(PB11, PB10);

TinyGsm modem(Serial2);
TinyGsmClient client(modem);
PubSubClient Connection(client);
SIM_CONFIG simconfig;

void SETUP_HARDWARE()
{
  //SETUP UART
  Serial.begin(115200);
  Serial2.begin(115200);
  Serial3.begin(9600);
  
  while( !Serial || !Serial2 || !Serial3 );
  //SETUP IOs
}

void LOAD_CONFIGURATION()
{
  if(!vDeserialize(&simconfig))
  {
    vLog("No Configuration Detected");
    vLog("Creating Factory Default Configuration");
    strcpy(simconfig.apn,"www.inwi.ma");
    strcpy(simconfig.broker,"41.140.242.182");
    simconfig.port = 1338;
    simconfig.interval = 5000;
    strcpy(simconfig.gprsPass,"");
    strcpy(simconfig.gprsUser,"");

    vLog("Saving Configuration");
    vSerialize(&simconfig);
  }
  else
  {
    vLog("Configuration Loaded");
  }
}