#define TRIGGER_PIN 0
#define DHTPIN 15     // Digital pin connected to the DHT sensor 
#define DHTTYPE    DHT22     // DHT 22 (AM2302)

const char* mqtt_server = "dimasalifta.tech";
const char* mqtt_topic = "smarturbanfarming/kit/1";

// Device credentials
const char *kit_id = "SUF-UINJKT-AW-H2JA8"; // Format Kit ID = SUF-UINJKT-{Type}-{Unique String}
const char *type = "AW"; //AW = Automatic Watering (1), LF = Liquid Fertilizer (2),  H = Hidroponik (3)

// MQTT broker credentials
const char *mqtt_broker = "bfc499f479f044b7945fbf144587e0f9.s1.eu.hivemq.cloud";
const char *topic = "conditions";
const char *mqtt_username = "administrator";
const char *mqtt_password = "P@ssw0rd";
const int mqtt_port = 8883;

float g_lux;
float g_tvoc;
float g_eco2;
float g_temperature;
float g_humidity;
float g_soil_moist;
float g_nitrogen;
float g_phosphorus;
float g_potassium;
float g_ph;
float g_water_flow;
float g_tds;
float g_ec;
float g_do;
float g_output;



bool wm_nonblocking = false; // change to true to use non blocking
