#include <FastCRC.h>

FastCRC16 crc; 
String Separator = ",";
unsigned long lastDataReceivedTime = 0; 
unsigned long dataReceiveTimeout = 2000; 

Task telemetryPrint(1000, TASK_FOREVER, [](){
  Serial.println(telemetry);
  //Serial3.println(telemetry);
});

void setup() {
  Serial.begin(115200);
  Serial3.begin(115200);
}

void loop() {
  if (Serial3.available() > 0) {
    String receivedData1 = Serial3.readStringUntil('\n');
    receivedData1.trim();
    int separatorIndex1 = receivedData1.lastIndexOf(Separator);
    String telemetry1 = receivedData1.substring(0, separatorIndex1);
    uint16_t receivedCRC1 = strtol(receivedData1.substring(separatorIndex1 + 1).c_str(), NULL, 16);

    String receivedData2 = Serial3.readStringUntil('\n');
    receivedData2.trim();
    int separatorIndex2 = receivedData2.lastIndexOf(Separator);
    String telemetry2 = receivedData2.substring(0, separatorIndex2);
    uint16_t receivedCRC2 = strtol(receivedData2.substring(separatorIndex2 + 1).c_str(), NULL, 16);

    String receivedData3 = Serial3.readStringUntil('\n');
    receivedData3.trim();
    int separatorIndex3 = receivedData3.lastIndexOf(Separator);
    String telemetry3 = receivedData3.substring(0, separatorIndex3);
    uint16_t receivedCRC3 = strtol(receivedData3.substring(separatorIndex3 + 1).c_str(), NULL, 16);

    String receivedData4 = Serial3.readStringUntil('\n');
    receivedData4.trim();
    int separatorIndex4 = receivedData4.lastIndexOf(Separator);
    String telemetry4 = receivedData4.substring(0, separatorIndex4);
    uint16_t receivedCRC4 = strtol(receivedData4.substring(separatorIndex4 + 1).c_str(), NULL, 16);

    String receivedData5 = Serial3.readStringUntil('\n');
    receivedData5.trim();
    int separatorIndex5 = receivedData5.lastIndexOf(Separator);
    String telemetry5 = receivedData5.substring(0, separatorIndex5);
    uint16_t receivedCRC5 = strtol(receivedData5.substring(separatorIndex5 + 1).c_str(), NULL, 16);

    uint16_t calculatedCRC1 = crc.modbus((uint8_t *)telemetry1.c_str(), telemetry1.length());
    uint16_t calculatedCRC2 = crc.modbus((uint8_t *)telemetry2.c_str(), telemetry2.length());
    uint16_t calculatedCRC3 = crc.modbus((uint8_t *)telemetry3.c_str(), telemetry3.length());
    uint16_t calculatedCRC4 = crc.modbus((uint8_t *)telemetry4.c_str(), telemetry4.length());
    uint16_t calculatedCRC5 = crc.modbus((uint8_t *)telemetry5.c_str(), telemetry5.length());

    if (calculatedCRC1 == receivedCRC1 && calculatedCRC2 == receivedCRC2 && calculatedCRC3 == receivedCRC3 && calculatedCRC4 == receivedCRC4 && calculatedCRC5 == receivedCRC5) {
      Serial.println(telemetry1);
      Serial.println(telemetry2);
      Serial.println(telemetry3);
      Serial.println(telemetry4);
      Serial.println(telemetry5);
      
      lastDataReceivedTime = millis();
    } else {
      Serial.println("1,1,11111,1,1,1,1");
    }
  }

  unsigned long currentTime = millis();
  if (currentTime - lastDataReceivedTime > dataReceiveTimeout) {
    Serial.println("0,0,00000,0,0,0,0");
  }

  delay(1000);
}