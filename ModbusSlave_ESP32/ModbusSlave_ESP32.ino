#include <ModbusRTUSlave.h>
#include <DHT.h> //Versi Adafruit Coeg

#define RELAY 26
#define LED1 32
#define BT1 34
#define BT2 35
 

DHT dht(1, DHT11);
ModbusRTUSlave modbus(Serial2);

uint16_t holdingRegisters[6];


void setup()
{
  //Serial.begin(115200);
  dht.begin();
  modbus.configureHoldingRegisters(holdingRegisters, 6);
  modbus.begin(2, 9600, SERIAL_8N1);
  pinMode(BT1, INPUT_PULLUP);
  pinMode(BT2, INPUT_PULLUP);
  pinMode(RELAY, OUTPUT);
  pinMode(LED1, OUTPUT);
}

void loop()
{
  modbusUpdateData();
  modbus.poll();
  relayControl();
}

void modbusUpdateData()
{
  float temp = dht.readTemperature() * 10;
  float humidity = dht.readHumidity() * 10;

  holdingRegisters[0] = temp;
  holdingRegisters[1] = humidity;
  holdingRegisters[4] = !digitalRead(BT1);
  holdingRegisters[5] = !digitalRead(BT2);
}

void relayControl()
{
  digitalWrite(RELAY, holdingRegisters[2]);
  digitalWrite(LED1, holdingRegisters[3]);
}
