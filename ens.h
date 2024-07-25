ScioSense_ENS160      ens160(ENS160_I2CADDR_1); //0x53..ENS160+AHT21=
void ens_setup() {
  Serial.print("ENS160...");
  ens160.begin();
  Serial.println(ens160.available() ? "done." : "failed!");
  if (ens160.available()) {
    // Print ENS160 versions
    Serial.print("\tRev: "); Serial.print(ens160.getMajorRev());
    Serial.print("."); Serial.print(ens160.getMinorRev());
    Serial.print("."); Serial.println(ens160.getBuild());

    Serial.print("\tStandard mode ");
    Serial.println(ens160.setMode(ENS160_OPMODE_STD) ? "done." : "failed!");
  }

}


void read_ens() {

  if (ens160.available()) {
    ens160.measure(true);
    ens160.measureRaw(true);

    g_tvoc = ens160.getTVOC();
    g_eco2 = ens160.geteCO2();
  
    Serial.print("AQI: ");Serial.print(ens160.getAQI());Serial.print("\t");
    Serial.print("TVOC: ");Serial.print(ens160.getTVOC());Serial.print("ppb\t");
    Serial.print("eCO2: ");Serial.print(ens160.geteCO2());Serial.println("ppm\t");
    //Serial.print("R HP0: ");Serial.print(ens160.getHP0());Serial.print("Ohm\t");
    //Serial.print("R HP1: ");Serial.print(ens160.getHP1());Serial.print("Ohm\t");
    //Serial.print("R HP2: ");Serial.print(ens160.getHP2());Serial.print("Ohm\t");
    //Serial.print("R HP3: ");Serial.print(ens160.getHP3());Serial.println("Ohm");
    Serial.println();
  }

  else {
    Serial.println("ERROR");
    }
}
