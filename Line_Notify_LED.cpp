#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define LINE_TOKEN "Token" 

void Line_Notify(String message);
char auth[] = "Blynk-token";
String message1 = "%E0%B8%AB%E0%B8%A5%E0%B8%AD%E0%B8%94%E0%B9%84%E0%B8%9F%E0%B8%95%E0%B8%B4%E0%B8%94%E0%B9%81%E0%B8%A5%E0%B9%89%E0%B8%A7%E0%B8%84%E0%B8%A3%E0%B8%B1%E0%B8%9A";
String message2 = "%E0%B8%AB%E0%B8%A5%E0%B8%AD%E0%B8%94%E0%B9%84%E0%B8%9F%E0%B8%94%E0%B8%B1%E0%B8%9A%E0%B9%81%E0%B8%A5%E0%B9%89%E0%B8%A7%E0%B8%84%E0%B8%A3%E0%B8%B1%E0%B8%9A";
//https://meyerweb.com/eric/tools/dencoder/

BLYNK_CONNECTED(){
   Blynk.syncAll();
  }
 
BLYNK_WRITE(V1)
{ 
  int buttonState = param.asInt();
   if (param.asInt() == 0)
   {
    digitalWrite(D1,HIGH);
     Line_Notify(message1);
   
    }
    if(param.asInt() == 1)
   {
    digitalWrite(D1,LOW);
      Line_Notify(message2);
  }
}


void setup()
{
  Serial.begin(115200);
  pinMode(D1,OUTPUT);
  digitalWrite(D1,HIGH);
  Blynk.begin(auth, "your-ssid", "your-password");
}
 
void loop()
{
  Blynk.run();
}

void Line_Notify(String message) {
  WiFiClientSecure client;

  if (!client.connect("notify-api.line.me", 443)) {
    Serial.println("connection failed");
    return;
  }

  String req = "";
  req += "POST /api/notify HTTP/1.1\r\n";
  req += "Host: notify-api.line.me\r\n";
  req += "Authorization: Bearer " + String(LINE_TOKEN) + "\r\n";
  req += "Cache-Control: no-cache\r\n";
  req += "User-Agent: ESP8266\r\n";
  req += "Connection: close\r\n";
  req += "Content-Type: application/x-www-form-urlencoded\r\n";
  req += "Content-Length: " + String(String("message=" + message).length()) + "\r\n";
  req += "\r\n";
  req += "message=" + message;
  // Serial.println(req);
  client.print(req);

  delay(20);

  // Serial.println("-------------");
  while(client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      break;
    }
    //Serial.println(line);
  }
  // Serial.println("-------------");
}


