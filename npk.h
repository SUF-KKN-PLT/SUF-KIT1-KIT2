// github link: https://github.com/4-20ma/ModbusMaster
#include <ModbusMaster.h>

/* Modbus stuff */
#define MODBUS_DIR_PIN  4 // connect DR, RE pin of MAX485 to gpio 4
#define MODBUS_RX_PIN 18 // Rx pin  
#define MODBUS_TX_PIN 19 // Tx pin 
#define MODBUS_SERIAL_BAUD 4800 // Baud rate for esp32 and max485 communication

#define num_parameters 9
// voltage, current and frequency data register of DDM18SD
uint16_t data_register[num_parameters] = {0x0000,  //moisture
                                          0x0001,  //temperature
                                          0x0002,  //conductivity
                                          0x0003,  //ph
                                          0x0004,  //nitrogent
                                          0x0005,  //phosporus
                                          0x0006,  //potassium
                                          0x0007,  //salinity
                                          0x0008   //tds
                                         };

//Initialize the ModbusMaster object as node
ModbusMaster node;

// Pin 4 made high for Modbus transmision mode
void modbusPreTransmission()
{
  delay(500);
  digitalWrite(MODBUS_DIR_PIN, HIGH);
}
// Pin 4 made low for Modbus receive mode
void modbusPostTransmission()
{
  digitalWrite(MODBUS_DIR_PIN, LOW);
  delay(500);
}


void npk_setup()
{
  //  esp serial communication
  Serial.begin(115200);
  pinMode(MODBUS_DIR_PIN, OUTPUT);
  digitalWrite(MODBUS_DIR_PIN, LOW);

  //Serial2.begin(baud-rate, protocol, RX pin, TX pin);.
  Serial2.begin(MODBUS_SERIAL_BAUD, SERIAL_8E1, MODBUS_RX_PIN, MODBUS_TX_PIN);
  Serial2.setTimeout(200);
  //modbus slave ID 14
  node.begin(14, Serial2);

  //  callbacks allow us to configure the RS485 transceiver correctly
  node.preTransmission(modbusPreTransmission);
  node.postTransmission(modbusPostTransmission);

}

void read_npk()
{
  uint8_t result;
  uint16_t data[2];
  int i;
  float reading;
  for (i = 0; i <= num_parameters; i++) {
    //Modbus function 0x04 Read Input Registers according to energy meter datasheet
    result = node.readInputRegisters(data_register[i], 1);
    if (result == node.ku8MBSuccess) {
      Serial.println("Success, Received data: ");

      //Retrieve the data from getResponseBuffer(uint8_t u8Index) function.
      //that is return 16-bit data. our energy meter return 32-bit data everytime.
      //that's why, we take the value to a array called data
      data[0] = node.getResponseBuffer(0x00);
      data[1] = node.getResponseBuffer(0x01);

      //read voltage
      if (data_register[i] == 0x0000) {
        Serial.print("Moisture: ");
        // we just convert the uint16_t type data array to float type using type casting
        reading = *((float *)data);
        Serial.print(reading);
        Serial.println(" %");
      }
      //read current
      if (data_register[i] == 0x0001) {
        Serial.print("Temperature: ");
        // we just convert the uint16_t type data array to float type using type casting
        reading = *((float *)data);
        Serial.print(reading);
        Serial.println(" C");
      }
      //read Frequency
      if (data_register[i] == 0x0002) {
        Serial.print("Conductivity: ");
        // we just convert the uint16_t type data array to float type using type casting
        reading = *((float *)data);
        Serial.print(reading);
        Serial.println(" us/cm");
      }
      //read voltage
      if (data_register[i] == 0x0003) {
        Serial.print("pH: ");
        // we just convert the uint16_t type data array to float type using type casting
        reading = *((float *)data);
        Serial.print(reading);
        Serial.println(" PH");
      }
      //read current
      if (data_register[i] == 0x0004) {
        Serial.print("Nitrogent: ");
        // we just convert the uint16_t type data array to float type using type casting
        reading = *((float *)data);
        Serial.print(reading);
        Serial.println(" mg/L");
      }
      //read Frequency
      if (data_register[i] == 0x0005) {
        Serial.print("Phosphorus: ");
        // we just convert the uint16_t type data array to float type using type casting
        reading = *((float *)data);
        Serial.print(reading);
        Serial.println(" mg/L");
      }
      //read voltage
      if (data_register[i] == 0x0006) {
        Serial.print("Potassium: ");
        // we just convert the uint16_t type data array to float type using type casting
        reading = *((float *)data);
        Serial.print(reading);
        Serial.println(" mg/L");
      }
      //read current
      if (data_register[i] == 0x0007) {
        Serial.print("Salinity: ");
        // we just convert the uint16_t type data array to float type using type casting
        reading = *((float *)data);
        Serial.print(reading);
        Serial.println(" ppt");
      }
      //read Frequency
      if (data_register[i] == 0x0008) {
        Serial.print("TDS: ");
        // we just convert the uint16_t type data array to float type using type casting
        reading = *((float *)data);
        Serial.print(reading);
        Serial.println(" mg/L");
      }
    }
    else {
      Serial.print("Failed, Response Code: ");
      Serial.print(result, HEX);
      Serial.println("");
      delay(5000);
    }

  }

  delay(1000);
}
