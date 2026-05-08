/*
 * Project: IoT Predictive Maintenance System
 * Author: Nova Afrianti (2522049)
 * Institution: Institut Teknologi Batam (ITEBA)
 * Year: 2026
 */

#include <WiFi.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Definisi Pin
#define DHTPIN 4          // Pin Sensor Suhu DHT22
#define DHTTYPE DHT22
#define VIBRATION_PIN 14  // Pin Sensor Getaran SW-420
#define BUZZER_PIN 13     // Pin Buzzer
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Ambang Batas (Threshold)
const float TEMP_THRESHOLD = 70.0; 

DHT dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Konfigurasi Wi-Fi (Sesuaikan dengan koneksi kampus/rumah)
const char* ssid = "NAMA_WIFI_KAMU";
const char* password = "PASSWORD_WIFI_KAMU";

void setup() {
  Serial.begin(115200);
  pinMode(VIBRATION_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  dht.begin();
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED gagal diinisialisasi"));
    for(;;);
  }
  
  // Hubungkan ke Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Wi-Fi Terhubung!");
}

void loop() {
  float temp = dht.readTemperature();
  int vibration = digitalRead(VIBRATION_PIN);

  // Cek jika pembacaan sensor gagal
  if (isnan(temp)) {
    Serial.println("Gagal membaca sensor DHT!");
    return;
  }

  // Tampilkan data ke Serial Monitor
  Serial.print("Suhu: "); Serial.print(temp); Serial.print("C | ");
  Serial.print("Vibrasi: "); Serial.println(vibration == HIGH ? "ABNORMAL" : "NORMAL");

  // Logika Alarm (Predictive Maintenance)
  if (temp > TEMP_THRESHOLD || vibration == HIGH) {
    digitalWrite(BUZZER_PIN, HIGH); // Alarm Bunyi
    updateOLED(temp, "WARNING!");
  } else {
    digitalWrite(BUZZER_PIN, LOW);  // Alarm Mati
    updateOLED(temp, "NORMAL");
  }

  delay(2000); // Tunggu 2 detik sebelum pembacaan berikutnya
}

void updateOLED(float t, String status) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("MONITORING MESIN");
  display.println("--------------------");
  display.print("Suhu  : "); display.print(t); display.println(" C");
  display.print("Status: "); display.println(status);
  display.display();
}
