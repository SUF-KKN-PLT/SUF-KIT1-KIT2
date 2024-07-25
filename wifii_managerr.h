#include <WiFiManager.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
// https://github.com/tzapu/WiFiManager

WiFiManager wm; // global wm instance
WiFiManagerParameter custom_field; // global param ( for non blocking w params )

WiFiClientSecure espClient;


String getParam(String name) {
  String value;
  if (wm.server->hasArg(name)) {
    value = wm.server->arg(name);
  }
  return value;
}

void saveParamCallback() {
  Serial.println("[CALLBACK] saveParamCallback fired");
  Serial.println("PARAM customfieldid = " + getParam("customfieldid"));
}
void wifii_managerr_setup() {
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP


  pinMode(TRIGGER_PIN, INPUT);

  if (wm_nonblocking) wm.setConfigPortalBlocking(false);

  const char* custom_radio_str = "<br/><label for='customfieldid'>Custom Field Label</label><input type='radio' name='customfieldid' value='1' checked> One<br><input type='radio' name='customfieldid' value='2'> Two<br><input type='radio' name='customfieldid' value='3'> Three";
  new (&custom_field) WiFiManagerParameter(custom_radio_str); // custom html input

  wm.addParameter(&custom_field);
  wm.setSaveParamsCallback(saveParamCallback);

  std::vector<const char *> menu = {"wifi", "info", "param", "sep", "restart", "exit"};
  wm.setMenu(menu);

  wm.setClass("invert");

  wm.setConfigPortalTimeout(30); // auto close configportal after n seconds

  if (!wm.autoConnect(kit_id)) {
    Serial.println("Failed to connect and hit timeout");
    ESP.restart();
    delay(1000);
  }
  Serial.println("Connected.");
}
void checkButton() {
  if ( digitalRead(TRIGGER_PIN) == LOW ) {
    delay(50);
    if ( digitalRead(TRIGGER_PIN) == LOW ) {
      Serial.println("Button Pressed");
      delay(3000); // reset delay hold
      if ( digitalRead(TRIGGER_PIN) == LOW ) {
        Serial.println("Button Held");
        Serial.println("Erasing Config, restarting");
        wm.resetSettings();
        ESP.restart();
      }

      Serial.println("Starting config portal");
      wm.setConfigPortalTimeout(120);

      if (!wm.startConfigPortal("OnDemandAP", "password")) {
        Serial.println("failed to connect or hit timeout");
        delay(3000);
      } else {
        Serial.println("connected...yeey :)");
      }
    }
  }
}
