# QrCode_Scanner_Doorlock

## Deskripsi
Sistem ini adalah prototipe doorlock otomatis berbasis Arduino yang menggunakan QR Code sebagai autentikasi akses. Pengguna yang memiliki QR Code valid dapat membuka pintu secara otomatis. Sistem menampilkan status pada LCD dan mengontrol relay untuk membuka/menutup pintu.

---

## Komponen Hardware
- Arduino (Uno/Nano/Sejenisnya)
- QR Code Reader (output serial, TTL)
- Relay Module (untuk mengontrol kunci pintu)
- LCD 16x2 I2C
- Kabel Jumper, Breadboard, dan Power Supply

### Wiring (Pinout)
- QR Code Reader: RX ke pin 2 Arduino, TX ke pin 3 Arduino (SoftwareSerial)
- Relay: IN ke pin 6 Arduino
- LCD I2C: SDA ke A4, SCL ke A5 (default Arduino Uno)

Lihat gambar wiring berikut untuk referensi visual:
- Wiring Doorlock Qrcode.png
- Gambar Tampak Dalam.png
- Gambar Tampak Depan.png

---

## Library yang Digunakan
- Wire.h : Komunikasi I2C
- LiquidCrystal_I2C.h : Kontrol LCD I2C
- SoftwareSerial.h : Komunikasi serial tambahan

---

## Cara Kerja
1. Inisialisasi LCD, relay, dan komunikasi serial.
2. LCD menampilkan pesan standby "Dekatkan QR Code".
3. Ketika QR Code Reader mengirim data, Arduino membaca string QR.
4. String QR dibandingkan dengan daftar ID/nama yang valid.
5. Jika QR cocok, relay aktif (pintu terbuka), LCD menampilkan nama pengguna. Setelah 5 detik, relay mati (pintu tertutup), LCD kembali ke standby.
6. Jika QR tidak cocok, LCD menampilkan "Akses Ditolak!". Setelah 2 detik, kembali ke standby.

---

## Daftar ID/Nama Valid
Tersimpan dalam array validIDs[] di kode. Contoh:
KELVIN, ANDRI, DANI, QRTEST, IVAN, DINO, SANDI, SYAIPUL, IFA'ANO, LOI, LALA, RIZAL, HADI, DINA, 1234, IKMAL, KUKUH, IPANG, ELDIEN

---

## Penjelasan Fungsi Utama
- tampilkanStandby(): Menampilkan pesan standby di LCD.
- loop(): Proses utama, membaca QR, validasi, kontrol relay, dan update LCD.
- setup(): Inisialisasi hardware dan tampilan awal.

---

## Flowchart Sederhana
1. Mulai
2. Inisialisasi LCD, relay, serial
3. Tampilkan "Dekatkan QR Code"
4. Jika QR Code terbaca:
   - Jika valid: Buka pintu, tampilkan nama, tutup pintu
   - Jika tidak valid: Tampilkan "Akses Ditolak!"
5. Kembali ke standby

---

## Troubleshooting
- LCD tidak tampil: Cek wiring I2C dan alamat (0x27 bisa berbeda)
- Relay tidak aktif: Cek wiring, pastikan pin 6 benar
- QR tidak terbaca: Cek baudrate dan wiring QR Code Reader

---

## Catatan Penggunaan
- Pastikan QR Code Reader mengirim data dalam format string tanpa karakter aneh.
- Tambahkan/mengubah ID valid di array validIDs[] sesuai kebutuhan.
- Gunakan power supply yang cukup untuk relay dan Arduino.
- Simpan file wiring dan contoh kartu nama sebagai referensi saat instalasi atau pelatihan pengguna.

---

## Lisensi
Proyek ini untuk pembelajaran dan pengembangan prototipe.
