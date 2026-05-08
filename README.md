# Sistem Predictive Maintenance Mesin Industri

### Deskripsi
Alat ini memantau suhu dan getaran mesin secara real-time untuk mencegah kerusakan mendadak (predictive maintenance).

### Komponen Utama
* **ESP32**: Mikrokontroler & Modul Wi-Fi
* **DHT22**: Sensor Suhu
* **SW-420**: Sensor Getaran (Vibrasi)
* **OLED Display**: Monitoring Lokal
* **Buzzer**: Alarm Peringatan

### Cara Penggunaan
1. Sambungkan ESP32 ke jaringan Wi-Fi.
2. Pantau data melalui Serial Monitor pada Arduino IDE atau melalui Dashboard monitoring.
3. Jika suhu atau getaran melebihi ambang batas, Buzzer akan aktif otomatis.
