#include <ModbusMaster.h>
#include <SoftwareSerial.h>
SoftwareSerial SwSerial(12, 14);  //ESP8266 (D6,D5) RX,TX
ModbusMaster node1;
uint8_t result1;
uint16_t data[6];
unsigned int regs1[6];
long previousMillis;
#define PUBLISH_DELAY   1000
float temp, humi;

void setup() {
  Serial.begin(9600);
  SwSerial.begin(9600, SWSERIAL_8N1);//baud rate slave modbus
  node1.begin(1, SwSerial);//1 = slave id pzem016
}

void loop() {
  if (millis() - previousMillis > PUBLISH_DELAY) {
    sendData();
    previousMillis = millis();
  }
}
void sendData() {
  result1 = node1.readInputRegisters(0x0001, 2);
  if (result1 == node1.ku8MBSuccess) {
    temp = (node1.getResponseBuffer(0x00) / 10.0f);
    humi = (node1.getResponseBuffer(0x01) / 10.0f);

  }
  Serial.print("temp = ");
  Serial.println(temp);
  Serial.print("humi = ");
  Serial.println(humi);
}
