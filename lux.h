BH1750 lightMeter;

void lux_setup() {
  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  Wire.begin();
  // On esp8266 you can select SCL and SDA pins using Wire.begin(D4, D3);
  // For Wemos / Lolin D1 Mini Pro and the Ambient Light shield use Wire.begin(D2, D1);

  lightMeter.begin();

  Serial.println(F("BH1750 Test begin"));
}

void read_lux() {
  float lux = lightMeter.readLightLevel();
  g_lux = lux;
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.print(" lx\t");
}
