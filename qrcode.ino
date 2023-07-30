#include <Arduino.h>
#include <ESP32QRCodeReader.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char * ssid = "M20";
const char * password = "12345678";

String server = "http://maker.ifttt.com";
String eventName = "qrcode_input";
String IFTTT_Key = "oJAQihdQXeOzQAWLB6D80I8gHpjhLrDROFjFAKyWw48";
String IFTTTUrl="https://maker.ifttt.com/trigger/qrcode_input/json/with/key/oJAQihdQXeOzQAWLB6D80I8gHpjhLrDROFjFAKyWw48";

String val;


ESP32QRCodeReader reader(CAMERA_MODEL_AI_THINKER);

void onQrCodeTask(void *pvParameters)
{
  struct QRCodeData qrCodeData;

  while (true)
  {
    if (reader.receiveQrCode(&qrCodeData, 100))
    {
      Serial.println("Found QRCode");
      if (qrCodeData.valid)
      {
        Serial.print("Payload: ");
        Serial.println((const char *)qrCodeData.payload);
        String url = server + "/trigger/" + eventName + "/with/key/" + IFTTT_Key + "?value1=" + (const char *)qrCodeData.payload ; 
        Serial.println(url);
        //Start to send data to IFTTT
        HTTPClient http;
        Serial.print("[HTTP] begin...\n");
        http.begin(url); //HTTP

        Serial.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();
        // httpCode will be negative on error
        if(httpCode > 0) {
          // HTTP header has been send and Server response header has been handled
          Serial.printf("[HTTP] GET... code: %d\n", httpCode);
          // file found at server
            if(httpCode == HTTP_CODE_OK) {
              String payload = http.getString();
              Serial.println(payload);
            }
          } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
      }
      else
      {
        Serial.print("Invalid: ");
        Serial.println((const char *)qrCodeData.payload);
      }
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Viola, Connected !!!");


  reader.setup();

  Serial.println("Setup QRCode Reader");

  reader.beginOnCore(1);

  Serial.println("Begin on Core 1");

  xTaskCreate(onQrCodeTask, "onQrCode", 4 * 1024, NULL, 4, NULL);
}

void loop()
{
  delay(100);
}

