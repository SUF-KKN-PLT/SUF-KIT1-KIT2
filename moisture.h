// Deklarasi pin sensor
const int soilMoisturePin = 18; // Pin analog yang terhubung ke sensor kelembaban tanah

void moisture_setup() {
  // Inisialisasi komunikasi serial untuk debugging
  // Inisialisasi pin sensor sebagai input
  pinMode(soilMoisturePin, INPUT);
}

void read_moisture() {
  // Membaca nilai analog dari sensor kelembaban tanah
  int soilMoistureValue = analogRead(soilMoisturePin);
  
  // Mengkonversi nilai analog ke dalam persen (asumsi nilai maksimal 4095 untuk ESP32)
  float moisturePercent = (soilMoistureValue / 4095.0) * 100;
  g_soil_moist = soilMoistureValue;
  // Menampilkan nilai kelembaban tanah ke serial monitor
  Serial.print("Soil Moisture Value: ");
  Serial.print(soilMoistureValue);
  Serial.print(" | Soil Moisture (%): ");
  Serial.print(moisturePercent);
  Serial.println("%");

  // Delay untuk memberikan jeda antar pembacaan
  delay(1000);
}
