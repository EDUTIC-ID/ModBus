/*
Membaca nilai sensor XY-MD02 menggunakan ESP8266 yang terintegrasi dengan uart_RS485 pada pin
RX = 12/D6
TX = 14/D5
dengan supply uart_rs485 3.3 VOLT
*/

#include <ModbusMaster.h>
#include <SoftwareSerial.h>
SoftwareSerial SwSerial(12, 14);  //ESP8266 (D6,D5) RX,TX
// Inisialisasi objek ModbusMaster
ModbusMaster node;

void setup() {
  Serial.begin(9600); // Inisialisasi Serial Monitor
  SwSerial.begin(9600);
  node.begin(1, SwSerial); // Inisialisasi ID slave dan Serial untuk komunikasi Modbus
}

void loop() {
  uint8_t result;
  uint16_t data[2];

  // Membaca data dari register Modbus slave (contoh: register 0 hingga 1)
  result = node.readInputRegisters(1, 2);

  // Cek apakah pembacaan berhasil
  if (result == node.ku8MBSuccess) {
    // Menampilkan data yang dibaca
    Serial.print("Data dari register 0: ");
    Serial.println(node.getResponseBuffer(0), DEC);
    Serial.print("Data dari register 1: ");
    Serial.println(node.getResponseBuffer(1), DEC);
  } else {
    // Menampilkan pesan kesalahan
    Serial.println("Gagal membaca data Modbus");
  }

  delay(1000); // Menunggu 1 detik sebelum membaca lagi
}
