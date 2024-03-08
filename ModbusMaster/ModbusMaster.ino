#include <ModbusMaster.h>

// Inisialisasi objek ModbusMaster
ModbusMaster node;

void setup() {
  Serial.begin(9600); // Inisialisasi Serial Monitor
  node.begin(1, Serial); // Inisialisasi ID slave dan Serial untuk komunikasi Modbus
}

void loop() {
  uint8_t result;
  uint16_t data[2];

  // Membaca data dari register Modbus slave (contoh: register 0 hingga 1)
  result = node.readHoldingRegisters(0, 2);

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
