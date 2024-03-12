#include <EEPROM.h>
#include <ModbusMaster.h>

ModbusMaster mb;

uint16_t data[2];
int i = EEPROM.read(6);

uint8_t result;
uint8_t x = 0;
void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  mb.begin(i, Serial2);
  Serial.println("Slave ID:" + String(i));
}

void loop() {
  result = mb.readInputRegisters(0x0001, 2);
  if (result == mb.ku8MBSuccess) {
    Serial.println(mb.getResponseBuffer(0x00));
    Serial.println(mb.getResponseBuffer(0x01));
    x = 123;
  } else {
    Serial.println("Error....");
    i++;
    delay(200);
    EEPROM.put(6, i);
    Serial.println("I ke: " + String(i));
    EEPROM.commit();
    delay(200);
  }
  delay(500);
  if (x == 123) {
    while (1) {
      Serial.println("Slave ID ketemu di:" + String(i));
      for (;;) {
      }
    }
  } else {
    Serial.println("sedang menyimpan variable i ke EEPROM");
    Serial.println("Slave ID selanjutnya:" + String(i));
    delay(5000);
    ESP.reset();
  }
}
