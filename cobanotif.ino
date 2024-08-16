#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <BH1750.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#define BLYNK_TEMPLATE_ID "TMPL6uZkGE095"
#define BLYNK_TEMPLATE_NAME "test"
#define BLYNK_AUTH_TOKEN "OY6menvPmh0N2O3LaqHW8ogqNjrf8aWd"

#define ONE_WIRE_BUS 23 // Ubah pin data DS18B20 menjadi GPIO 23
#define BH1750_ADDRESS 0x23 // Alamat default sensor cahaya BH1750

#define RELAY1_PIN 5
#define RELAY2_PIN 17
#define RELAY3_PIN 16

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
BH1750 lightMeter;

LiquidCrystal_I2C lcd(0x27, 20, 4); // Alamat I2C LCD, dengan ukuran 20x4

char auth[] = "OY6menvPmh0N2O3LaqHW8ogqNjrf8aWd"; // Token autentikasi Blynk Anda
char ssid[] = "wkwk"; // Nama jaringan WiFi Anda
char pass[] = "12345678"; // Kata sandi WiFi Anda

bool manualMode = false;

BlynkTimer timer;

void setup() {
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  pinMode(RELAY3_PIN, OUTPUT);

  digitalWrite(RELAY1_PIN, HIGH);
  digitalWrite(RELAY2_PIN, HIGH);
  digitalWrite(RELAY3_PIN, HIGH);

  lcd.init();                      // Inisialisasi LCD
  lcd.backlight();                 // Nyalakan backlight LCD
  lcd.setCursor(0, 0);
  lcd.print("Sensor Projek");
  
  Serial.begin(9600);
  while (!Serial);

  Blynk.begin(auth, ssid, pass);
  lightMeter.begin(); // Gunakan mode default untuk memulai
  sensors.begin();

  // Memanggil fungsi untuk memperbarui status relay setiap detik
  timer.setInterval(100L, updateRelays);

  // Set default mode menjadi otomatis
  manualMode = false;
}

void loop() {
  Blynk.run(); // Proses koneksi Blynk
  timer.run(); // Jalankan BlynkTimer
  
  float lightLevel = lightMeter.readLightLevel(); // Baca tingkat cahaya
  sensors.requestTemperatures(); // Minta suhu dari sensor DS18B20
  float temperatureC = sensors.getTempCByIndex(0); // Baca suhu dalam Celcius
  
  lcd.clear(); // Bersihkan layar LCD
  lcd.setCursor(0, 0);
  lcd.print("Cahaya: ");
  lcd.print(lightLevel);
  lcd.print(" lx");
  
  lcd.setCursor(0, 2);
  lcd.print("Suhu: ");
  lcd.print(temperatureC);
  lcd.print(" C");

  // Tambahkan keterangan di LCD untuk suhu
  lcd.setCursor(0, 3);
  if (temperatureC < 25) {
    lcd.print("Suhu Terlalu Rendah");
  } else if (temperatureC >= 25 && temperatureC <= 28) {
    lcd.print("Suhu Normal");
  } else {
    lcd.print("Suhu Hangat");
  }

  // Tambahkan keterangan di LCD untuk intensitas cahaya
  lcd.setCursor(0, 1);
  if (lightLevel == 0) {
    lcd.print("Gelap");
  } else if (lightLevel < 210) {
    lcd.print("Kurang Cahaya");
  } else {
    lcd.print("Cahaya Cukup");
  }

  // Kirim data ke Blynk
  Blynk.virtualWrite(V0, temperatureC); // Kirim suhu ke virtual pin V0
  Blynk.virtualWrite(V1, lightLevel); // Kirim cahaya ke virtual pin V1

  // Tambahkan keterangan di Blynk untuk suhu
  if (temperatureC < 25) {
    Blynk.virtualWrite(V2, "Suhu Terlalu Rendah");
    Blynk.logEvent("suhu_rendah", String("Suhu terlalu rendah heater dinyalakan!"));
  } else if (temperatureC >= 25 && temperatureC <= 28) {
    Blynk.virtualWrite(V2, "Suhu Normal");
    Blynk.logEvent("suhu_normal", String("Suhu normal!"));
  } else {
    Blynk.virtualWrite(V2, "Suhu Hangat");
    Blynk.logEvent("suhu_tinggi", String("Suhu terlalu tinggi kipas dinyalakan!"));
  }

  // Tambahkan keterangan di Blynk untuk intensitas cahaya
  if (lightLevel == 0) {
    Blynk.virtualWrite(V3, "Gelap");
  } else if (lightLevel < 210) {
    Blynk.virtualWrite(V3, "Kurang Cahaya");
    Blynk.logEvent("cahaya_redup", String("Kurang Cahaya lampu dinyalakan!"));
  } else {
    Blynk.virtualWrite(V3, "Cahaya Cukup");
    Blynk.logEvent("cahaya_normal", String("cahaya normal!"));
  }
}

// Fungsi untuk memperbarui status relay berdasarkan tombol manual di Blynk
BLYNK_WRITE(V5) {
  int relay1Control = param.asInt(); // Membaca nilai dari tombol relay 1 di Blynk
  
  if (relay1Control == 1) {
    digitalWrite(RELAY1_PIN, LOW); // Hidupkan relay 1
  } else {
    digitalWrite(RELAY1_PIN, HIGH); // Matikan relay 1
  }

  Blynk.virtualWrite(V5, relay1Control); // Mengatur status tombol relay 1 di Blynk
}
// Fungsi untuk memperbarui status relay berdasarkan tombol manual di Blynk
BLYNK_WRITE(V6) {
  int relay2Control = param.asInt(); // Membaca nilai dari tombol relay 2 di Blynk
  
  if (relay2Control == 1) {
    digitalWrite(RELAY2_PIN, LOW); // Hidupkan relay 1
  } else {
    digitalWrite(RELAY2_PIN, HIGH); // Matikan relay 1
  }

  Blynk.virtualWrite(V6, relay2Control); // Mengatur status tombol relay 1 di Blynk
}
// Fungsi untuk memperbarui status relay berdasarkan tombol manual di Blynk
BLYNK_WRITE(V7) {
  int relay3Control = param.asInt(); // Membaca nilai dari tombol relay 1 di Blynk
  
  if (relay3Control == 1) {
    digitalWrite(RELAY3_PIN, LOW); // Hidupkan relay 1
  } else {
    digitalWrite(RELAY3_PIN, HIGH); // Matikan relay 1
  }

  Blynk.virtualWrite(V7, relay3Control); // Mengatur status tombol relay 3 di Blynk
}

// Fungsi untuk memperbarui status relay secara otomatis berdasarkan kondisi suhu dan intensitas cahaya
void updateRelays() {
  float lightLevel = lightMeter.readLightLevel(); // Baca tingkat cahaya
  sensors.requestTemperatures(); // Minta suhu dari sensor DS18B20
  float temperatureC = sensors.getTempCByIndex(0); // Baca suhu dalam Celcius

  if (!manualMode) {
    if (lightLevel < 210) {
      digitalWrite(RELAY1_PIN, LOW); // Hidupkan relay 1
    } else {
      digitalWrite(RELAY1_PIN, HIGH); // Matikan relay 1
    }
    if (temperatureC < 25){
      digitalWrite(RELAY2_PIN, LOW); //Hidupkan Relay 2
    } else {
      digitalWrite(RELAY2_PIN, HIGH); //Matikan Relay 2
    }
    if (temperatureC > 28){
      digitalWrite(RELAY3_PIN, LOW); //Hidupkan Relay 3
    } else {
      digitalWrite(RELAY3_PIN, HIGH); //Matikan Relay 3
    }
    // Mengatur status tombol relay di Blynk
    Blynk.virtualWrite(V5, !digitalRead(RELAY1_PIN));
    Blynk.virtualWrite(V6, !digitalRead(RELAY2_PIN));
    Blynk.virtualWrite(V7, !digitalRead(RELAY3_PIN));
  }
}

// Fungsi untuk mengatur mode relay
BLYNK_WRITE(V4) {
  manualMode = param.asInt();
  if (manualMode) {
    digitalWrite(RELAY1_PIN, HIGH); // Matikan relay 1 saat mode manual
    digitalWrite(RELAY2_PIN, HIGH); // Matikan relay 2 saat mode manual
    digitalWrite(RELAY3_PIN, HIGH); // Matikan relay 3 saat mode manual
    Blynk.virtualWrite(V5, LOW); // Mengatur status tombol relay 1 di Blynk
    Blynk.virtualWrite(V6, LOW); // Mengatur status tombol relay 1 di Blynk
    Blynk.virtualWrite(V7, LOW); // Mengatur status tombol relay 1 di Blynk
  }
}
