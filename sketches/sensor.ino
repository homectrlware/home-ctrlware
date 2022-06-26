#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP_Mail_Client.h>
const char *ssid = "Your SSID";
const char *password = "Your Password";
#define SMTP_server "smtp.gmail.com"
#define SMTP_Port 465
#define sender_email "Sending E-Mail"
#define sender_password "E-mail password"
#define Recipient_email "Reciever E-Mail"
SMTPSession smtp;

void setup()
{
    Serial.begin(115200);
    pinMode(D6, INPUT);
    pinMode(A0, INPUT);
    pinMode(D5, OUTPUT);
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
    smtp.debug(1);
}

void loop()
{
    // Check WiFi connection status
    if (WiFi.status() == WL_CONNECTED)
    {
        WiFiClient client;
        HTTPClient http;
        //converting the input from the analog input to degree celsius 
        int temp = (analogRead(A0) * 330.0) / 1023.0;
        Serial.println(String(temp));
        // Your Domain name with URL path or IP address with path
        http.begin(client, "Your URL");
        // Send HTTP GET request
        int httpResponseCode = http.GET();
        if (httpResponseCode > 0)
        {
            Serial.print("HTTP Response code: ");
            Serial.println(httpResponseCode);
            String payload = http.getString();
            Serial.println(payload);
            digitalWrite(12, payload.toInt());
        }
        else
        {
            Serial.print("Error code: ");
            Serial.println(httpResponseCode);
        }
        // Free resources
        http.end();
        int gas = digitalRead(D6);
        int flag;
        if (gas == 1)
        {
            digitalWrite(D5, LOW);
            flag = 0;
        }
        else
        {
            // send en email
            // buzz
            digitalWrite(D5, HIGH);
            // email
            if (flag == 0)
            {
                ESP_Mail_Session session;
                session.server.host_name = SMTP_server;
                session.server.port = SMTP_Port;
                session.login.email = sender_email;
                session.login.password = sender_password;
                session.login.user_domain = "";
                /* Declare the message class */
                SMTP_Message message;
                message.sender.name = "Home Ctrlware";
                message.sender.email = sender_email;
                message.subject = "Smoke Detector !!!";
                message.addRecipient("Atit", Recipient_email);
                String textMsg = "Fire Detected";
                message.text.content = textMsg.c_str();
                message.text.charSet = "us-ascii";
                message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;
                if (!smtp.connect(&session))
                {
                    return;
                    flag = 1;
                }
                if (!MailClient.sendMail(&smtp, &message))
                    Serial.println("Error sending Email, " + smtp.errorReason());
                Serial.println(String(gas));
            }
            // Your Domain name with URL path or IP address with path
            http.begin(client, "Your URL");
            // Send HTTP GET request
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
    }
    else
    {
        Serial.println("WiFi Disconnected");
    }
}