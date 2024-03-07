#define BLYNK_TEMPLATE_ID "TMPL6PySbUpy5"
#define BLYNK_TEMPLATE_NAME "Monitoring Suhu dan Kelembaban Jamur"
#define BLYNK_AUTH_TOKEN "StffCel1PYXyO1Fwry5LTaZIufEqzZiL"
#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

//Password dan Nama Hostpot
char ssid[] = "briiann";
char pass[] = "NiellL12050";

// or Software Serial on Uno, Nano...

    
#include <SoftwareSerial.h>
SoftwareSerial EspSerial(12, 13); // RX, TX

// Your ESP8266 baud rate:
#define ESP8266_BAUD 9600
 
ESP8266 wifi(&EspSerial);   


#include <DHT.h>

#define DHT_PIN 7     // Pin data untuk sensor DHT11
#define DHT_TYPE DHT11 // Tipe sensor DHT11 (
#define kipas  3
#define pompa 2
DHT dht(DHT_PIN, DHT_TYPE);

void data(float suhu){
  if(suhu > 25){
    Blynk.logEvent("suhu","Suhu lebih dari 29°C");
  }
}

BLYNK_WRITE(V0){
 int SWkipas = param.asInt();
  if(SWkipas == 1){
    Serial.println("Kipas Menyala");
    digitalWrite(kipas, LOW);
  }
  else{
    Serial.println("Kipas Mati");
    digitalWrite(kipas, HIGH);
  }
}

BLYNK_WRITE(V1){
 int SWpompa = param.asInt();
  if(SWpompa == 1){
    Serial.println("Pompa Menyala");
    digitalWrite(pompa, LOW);
  }  
  else{
    Serial.println("Pompa Mati");
    digitalWrite(pompa, HIGH);
  }
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(BLYNK_AUTH_TOKEN, wifi, ssid, pass);

  pinMode(kipas, OUTPUT);
  pinMode(pompa, OUTPUT);
  digitalWrite(kipas, LOW); 
  digitalWrite(pompa, LOW);
  dht.begin();
 
}

void loop()
{
  float temperature =  dht.readTemperature();  // Baca suhu dalam derajat Celsius
  float humidity = dht.readHumidity();        // Baca kelembaban
  float suhu = temperature + 0.20;
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  Blynk.virtualWrite(V3, temperature); // menset pin virtual (V3) agar dapat menampilkan suhu ke aplikasi blynk
  Blynk.virtualWrite(V4, humidity); // menset pin Virtual (V4) agar dapat menampilkan kelembapan ke aplikasi blynk

  Blynk.run();
  
}

