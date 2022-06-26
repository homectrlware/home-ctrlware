#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "Your SSID";
const char* password = "Your Password";

uint8_t Pwm1 = D1; //Nodemcu PWM pin 
uint8_t Pwm2 = D2; //Nodemcu PWM pin
int a0 = 15;  //Gpio-15 of nodemcu esp8266  
int a1 = 13;  //Gpio-13 of nodemcu esp8266    
int a2 = 12;  //Gpio-12 of nodemcu esp8266   
int a3 = 14;  //Gpio-14 of nodemcu esp8266 


void setup() {
  Serial.begin(115200); 
  pinMode(a0, OUTPUT);     
  pinMode(a1, OUTPUT);     
  pinMode(a2, OUTPUT);
  pinMode(a3, OUTPUT);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;

      // Your Domain name with URL path or IP address with path
      http.begin(client, "Your URL");
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        //Serial.println(payload);
        // do some thing code
        String sta = payload.substring(0,1);
        String spd = payload.substring(2,3);
        int fan_onoff = sta.toInt();
        int fan_speed = spd.toInt();
        Serial.print("fan=");
        Serial.println(fan_onoff);
        Serial.print("speed=");
        Serial.println(fan_speed);
        // turn on fan
        if( fan_onoff == 1 ){
            digitalWrite(a0, HIGH);
            digitalWrite(a1, LOW);
            // speed check
            if(fan_speed == 1){
                analogWrite(Pwm1, 51);  //Pwm duty cycle 20%
                analogWrite(Pwm2, 51);
            }
            else if(fan_speed == 2){
                analogWrite(Pwm1, 102);  //Pwm duty cycle 40%
                analogWrite(Pwm2, 102);
            }
            else if(fan_speed == 3){
                analogWrite(Pwm1, 153);  //Pwm duty cycle 60%
                analogWrite(Pwm2, 153);
            }
            else if(fan_speed == 4){
                analogWrite(Pwm1, 204);  //Pwm duty cycle 80%
                analogWrite(Pwm2, 204);
            }
            else if(fan_speed == 5){
                analogWrite(Pwm1, 255);  //Pwm duty cycle 100%
                analogWrite(Pwm2, 255);
            }
        }
        else {
            digitalWrite(a0, LOW); 
            digitalWrite(a1, LOW);
        }
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }

}