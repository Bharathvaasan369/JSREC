#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const char* ssid = "Home";
const char* password = "PASSWORD";

const int buttonPin = D4;
int buttonState = 0;
int newState;
int oldState;
//int pos;
int count;

String apiKeyValue = "tPmAT5Ab3j7F9";
HTTPClient http;
WiFiClient client;

void setup() 
{
  lcd.init();
  lcd.backlight();
  
  Serial.begin(9600);
  Serial.println(ssid); 
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println(".");
    lcd.setCursor(0, 0);
    lcd.print("Connecting to");
    lcd.setCursor(0, 1);
    lcd.print("WiFi");
    delay(1000);
    lcd.setCursor(0, 0);
    lcd.print("Connecting to");
    lcd.setCursor(0, 1);
    lcd.print("WiFi.");
    delay(1000);
    lcd.setCursor(0, 0);
    lcd.print("Connecting to");
    lcd.setCursor(0, 1);
    lcd.print("WiFi..");
    delay(1000);
    lcd.setCursor(0, 0);
    lcd.print("Connecting to");
    lcd.setCursor(0, 1);
    lcd.print("WiFi...");
    delay(1000);
    lcd.clear();
  }
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, 0};
  int maxIndex = data.length()-1;
  for (int i=0; i<=maxIndex && found<=index; i++)
  {
    if (data.charAt(i)==separator || i==maxIndex)
    {
      found++;
      strIndex [0]= strIndex [1]+1;
      strIndex [1]= (i == maxIndex) ? i+1: i;
    }
  }
  String ketemu = found>index ? data.substring(strIndex[0], strIndex [1]) : "";
  return ketemu;
}

void loop()
{
  buttonState = digitalRead(buttonPin);
  if(WiFi.status() == WL_CONNECTED)
  {
    if(buttonState == LOW)
    {
      //count = count+1;
      Serial.println("Reciving Input");
      http.begin("http://192.168.17.148/counter/post/post-10.php");
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      String httpRequestData = "api_key=" + apiKeyValue + "&value1=" + count +"";
      Serial.print("httpRequestData: ");
      Serial.println(httpRequestData);
      int httpResponseCode = http.POST(httpRequestData);
      if (httpResponseCode>0)
      {
      
      }
      else
      {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
        Serial.println("Data not updated");
      }
      http.end();
    }
    else
    {
      //http.begin("http://192.168.126.148/presensi/fetcher1.php");
      http.begin("http://192.168.17.148/counter/recive/fetcher10.php");
      int httpCode = http.GET();
    
      if(httpCode > 0)
      {
        String status=http.getString();
        Serial.print("httpCode: ");
        Serial.println(httpCode);
        //Serial.println(status);
        String a =  status;
        //Serial.print(status);
        Serial.print("Status: ");
        Serial.println(a);
        //pos = a.toInt();
        lcd.setCursor(0, 0);
        lcd.print("Mch_id:1 status");
        lcd.setCursor(0,1);
        lcd.print(a);
      }//JUST CMD LINE FOR FILE CHECK UP
      http.end();
           }
  }
  else
  {
    Serial.println("WiFi Not Connected");
  }
}
