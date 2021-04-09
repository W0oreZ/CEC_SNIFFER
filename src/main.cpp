#include <init.h>
#include <main.h>
#include <pclink.h>

char* DeviceID = "CECL-100";
char* topic = "exp/100/cec";
char* subTopic = "exp/100/in";
String imei = "";
uint32_t lastReconnectAttempt = 0;
uint32_t lastTransmition = 0;


void setup() {
  SETUP_HARDWARE();
  LOAD_CONFIGURATION();
  delay(1000);

  vLog("PROGRAME STARTING");

  BOOTSTRAP_MODEM();

}

void loop() {
  uint32_t time = millis();

  if (!Connection.connected()) 
  {
    if (time - lastReconnectAttempt > 5000) 
    {
      lastReconnectAttempt = time;
      if (StartConnection()) {
        lastReconnectAttempt = 0;
      }
    }
    delay(1000);
  }
  else
  {
    if(time - lastTransmition > simconfig.interval)
    {
      if(Serial3.available()>0)
      {
        byte rs[256];
        Serial3.readBytesUntil('#', rs, 256);
        if(Connection.beginPublish(topic,256,false) == 1)
        {
          
          Connection.write(rs,256);
          if(Connection.endPublish()==1)
          {
            vLog("SEND OK");
            lastTransmition = time;
          }
          else
          {
            vError("SEND FAIL");
          }
        }
      }
    }
  }
  Connection.loop();
}

void BOOTSTRAP_MODEM(){
  modem.init();
  imei = modem.getIMEI();
  Serial.println(imei);
  modem.gprsConnect(simconfig.apn, simconfig.gprsUser, simconfig.gprsPass);

  if (!modem.isNetworkConnected()) 
  {
    while(!modem.waitForNetwork(5000)) 
    {
      Serial.println("waiting for network");
      delay(1000);
    }
  }

  while(!modem.gprsConnect(simconfig.apn, simconfig.gprsUser, simconfig.gprsPass)) 
  {
    Serial.println("Connecting to server");
    delay(5000);
  }

  modem.isGprsConnected();
  Connection.setServer(simconfig.broker, simconfig.port);
  Connection.setCallback(MessageHandler);
}

boolean StartConnection() 
{
  if (!Connection.connect(DeviceID)) {
    Serial.println("cant connect");
    return false;
  }

  Connection.publish("exp/event", "exp/rs232 connected");
  Connection.subscribe(subTopic);

  return Connection.connected();
}

void MessageHandler(char* topic, byte* payload, unsigned int len) 
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.write(payload, len);
  Serial.println();
  Serial3.write(payload,len);
  Serial3.println();
}