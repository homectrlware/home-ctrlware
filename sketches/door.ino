#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Servo.h>
const char* ssid = "Your SSID";
const char* password = "Your Password";
Servo servo;
void setup()
{
  Serial.begin(115200);
  pinMode(12, INPUT_PULLUP);
  servo.attach(5);
  servo.write(0);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  // Check WiFi connection status
  if (WiFi.status() == WL_CONNECTED)
  {
    WiFiClient client;
    HTTPClient http;
    // Your Domain name with URL path or IP address with path
    http.begin(client, "Your URL");
    Serial.println("in servo");
    // Send HTTP GET request
    int httpResponseCode = http.GET();
    if (httpResponseCode > 0)
    {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload);
      int flag = payload.substring(0, 1).toInt();
      if (flag == 0)
      {
        servo.write(0);
      }
      else
      {
        servo.write(180);
      }
    }
    else
    {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();

    int value;
    if (digitalRead(12) == HIGH)
    {
      value = 0;
    }
    else
    {
      value = 1;
    }
    // Your Domain name with URL path or IP address with path
    http.begin(client, "Your URL");
    Serial.println("in sensor");
    httpResponseCode = http.GET();
    if (httpResponseCode > 0)
    {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload);
    }
    else
    {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
  }
  else
  {
    Serial.println("WiFi Disconnected");
  }
}