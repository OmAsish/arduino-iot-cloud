#include "arduino_secrets.h"
/*
  Sketch generated by the Arduino IoT Cloud Thing "Untitled"
  https://create.arduino.cc/cloud/things/db6b6c7b-8a9f-4229-99e8-d4605d4c864d

  Arduino IoT Cloud Variables description

  The following variables are automatically generated and updated when changes are made to the Thing

  CloudTemperatureSensor temp;
  CloudRelativeHumidity humid;

  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/

#include "thingProperties.h"
#include "DHT.h"

#define DHTPIN 13     // Digital pin connected to the DHT sensor

#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float temperature;
int humidity;

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  delay(1500);
  pinMode(13, OUTPUT);
  dht.begin();
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
  */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  float temperature = dht.readTemperature();
  int humidity = dht.readHumidity();
  // Serial.print("Temperature=");Serial.println(temperature);
  // Serial.print("Humidity=");Serial.println(humidity);
  delay(1000);
  onHumidityChange();
  onTemperatureChange();
}

void onHumidityChange()  {
  humid = dht.readHumidity(); // Add your code here to act upon Humidity change
}

void onTemperatureChange()  {
  temp = dht.readTemperature(); // Add your code here to act upon Temperature change
}

