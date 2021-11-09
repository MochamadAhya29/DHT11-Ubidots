#include <DHT.h>
#include <UbidotsMicroESP8266.h> // Import File Ubidots

#define DHTPIN 4 //Mendefinisikan pin dht di nodemcu adalah 4, D2 = 4
#define DHTTYPE DHT11   // mendefinisikan tipe dht yang di gunakan 

char auth[] = "BBFF-lalMH5nAJeLRmM3A7WPXGvQerbr72U";
char ssid[] = "bangganteng";
char pass[] = "faruqiii";

DHT dht(DHTPIN, DHTTYPE);
Ubidots client(auth);   // setting token client di ubidots
unsigned long last = 0;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  dht.begin();
  delay(20);    //delay 0,02 detik
  client.wifiConnection(ssid, pass);   //menyambungkan ubidots dengan wifi

}

void loop() {
  // put your main code here, to run repeatedly:
  if(millis()-last>10000){   //jika sudah 10 detik

    float hum = dht.readHumidity();
    float temp = dht.readTemperature();

    last = millis();
    client.add("Kelembapan", hum);
    client.add("Temperature", temp);
    client.sendAll(true);    // ubidots mengirimkan semua data
    
  }
}
