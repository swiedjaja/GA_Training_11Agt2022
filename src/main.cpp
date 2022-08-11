#include <Arduino.h>
#include "DHTesp.h"

// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID           "TMPLvUmztoOi"
#define BLYNK_DEVICE_NAME           "Quickstart Device"
#define BLYNK_AUTH_TOKEN            "Uo87H983eJqzbsaI83_EfbYCiZkgXckc"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "SteffN9";
char pass[] = "steff123";

// char ssid[] = "PRAKTIKUMIOT";
// char pass[] = "celab123";

BlynkTimer timer;
DHTesp dht;

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();

  // Update state
  Blynk.virtualWrite(V1, value);
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Serial.println("Hello World!");
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();

  Serial.print("Humidity: ");
  Serial.print(humidity, 1);
  Serial.print(", Temperature: ");
  Serial.println(temperature, 1);

  Blynk.virtualWrite(V2, millis() / 1000);
  Blynk.virtualWrite(V4, humidity);
  Blynk.virtualWrite(V5, temperature);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(D8, OUTPUT);
  Serial.begin(115200);
  dht.setup(D3, DHTesp::DHT11);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  // Blynk.begin(auth, ssid, pass, "blynk.cloud", 8000);
  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

void loop() {

  Blynk.run();
  timer.run();

  // put your main code here, to run repeatedly:
  /*
  Serial.println("Hello World!");
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();

  Serial.print("Humidity: ");
  Serial.print(humidity, 1);
  Serial.print(", Temperature: ");
  Serial.println(temperature, 1);

  digitalWrite(D8, HIGH);
  delay(200);
  digitalWrite(D8, LOW);
  delay(1800);
  */
}