#include <Wire.h>           // Library komunikasi I2C
#include <LiquidCrystal_I2C.h> // Library modul I2C LCD
#include <SoftwareSerial.h> // Library komunikasi Software Serial

// Inisialisasi SoftwareSerial pada pin 2 (RX) dan 3 (TX)
SoftwareSerial myserial(2, 3);

// Inisialisasi LCD I2C dengan alamat 0x27 dan ukuran layar 16x2
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

const int relayPin = 6; // Pin untuk mengontrol relay (pintu)
String kode;             // Variabel untuk menyimpan data dari QR Code Reader

// Daftar ID atau nama valid
const String validIDs[] = {"KELVIN", "ANDRI", "DANI", "QRTEST", "IVAN", "DINO", "SANDI", "SYAIPUL", "IFA'ANO", "LOI", "LALA", "RIZAL", "HADI", "DINA", "1234", "IKMAL", "KUKUH", "IPANG", "ELDIEN"};
const int totalValidIDs = sizeof(validIDs) / sizeof(validIDs[0]); // Hitung jumlah ID/nama valid

bool isProcessing = false; // Flag untuk mencegah pembacaan berulang

// Fungsi untuk menampilkan pesan standby
void tampilkanStandby() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Dekatkan QR Code");
  lcd.setCursor(0, 1);
  lcd.print("Scan QR Code...");
}

void setup() {
  // Inisialisasi komunikasi serial
  Serial.begin(9600);
  
  // Inisialisasi SoftwareSerial dengan baud rate 9600
  myserial.begin(9600);
  myserial.setTimeout(100); // Set timeout untuk pembacaan data

  // Inisialisasi relay
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Pastikan relay awalnya mati (pintu tertutup)

  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();

  // Tampilkan pesan standby saat pertama kali dijalankan
  tampilkanStandby();
}

void loop() {
  // Jika ada data tersedia dari SoftwareSerial
  if (myserial.available() > 0 && !isProcessing) {
    isProcessing = true; // Aktifkan flag untuk mencegah pembacaan berulang

    kode = myserial.readString(); // Baca data dari QR Code Reader
    kode.trim(); // Hapus karakter spasi atau newline yang tidak perlu

    // Debugging: Tampilkan data QR Code ke Serial Monitor
    Serial.print("QR Code Dibaca: [");
    Serial.print(kode);
    Serial.println("]");

    // Periksa apakah kode sesuai dengan salah satu ID valid
    bool isValid = false;
    String namaPengguna = ""; // Variabel untuk menyimpan nama pengguna yang discan
    for (int i = 0; i < totalValidIDs; i++) {
      if (kode == validIDs[i]) {
        isValid = true;
        namaPengguna = validIDs[i]; // Simpan nama pengguna yang cocok
        break; // Keluar dari loop jika ID ditemukan
      }
    }

    if (isValid) {
      // Aktifkan relay untuk membuka pintu
      digitalWrite(relayPin, HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Selamat Datang,");
      lcd.setCursor(0, 1);
      lcd.print(namaPengguna); // Tampilkan nama pengguna di LCD

      // Debugging: Tampilkan status relay ke Serial Monitor
      Serial.println("Relay ON - Pintu Terbuka");

      delay(5000); // Relay tetap aktif selama 5 detik (pintu terbuka)

      // Matikan relay setelah waktu tertentu (pintu tertutup)
      digitalWrite(relayPin, LOW);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Pintu Tertutup");
      lcd.setCursor(0, 1);
      lcd.print("Scan QR Code...");

      // Debugging: Tampilkan status relay ke Serial Monitor
      Serial.println("Relay OFF - Pintu Tertutup");

      delay(2000); // Tunggu sebentar sebelum kembali ke status standby
    } else {
      // Jika kode tidak valid
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Akses Ditolak!");
      lcd.setCursor(0, 1);
      lcd.print("QR Code Salah");

      // Debugging: Tampilkan pesan ke Serial Monitor
      Serial.println("QR Code Salah - Akses Ditolak");

      delay(2000); // Tunggu sebentar sebelum kembali ke status standby
    }

    // Kembali ke status standby
    tampilkanStandby();

    // Tambahkan delay untuk mencegah pembacaan berulang
    delay(1000); // Tunggu 1 detik sebelum memproses pembacaan berikutnya

    isProcessing = false; // Reset flag setelah selesai
  }
}
