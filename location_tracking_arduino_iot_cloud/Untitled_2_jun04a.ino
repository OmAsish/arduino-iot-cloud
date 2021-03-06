#include "arduino_secrets.h"
// SoftwareSerial for esp8266 - Version: Latest 
#include <SoftwareSerial.h>

/* 
  Sketch generated by the Arduino IoT Cloud Thing "Untitled"
  https://create.arduino.cc/cloud/things/db6b6c7b-8a9f-4229-99e8-d4605d4c864d 

  Arduino IoT Cloud Variables description

  The following variables are automatically generated and updated when changes are made to the Thing

  CloudLocation location;

  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/

#include "thingProperties.h"
#include <TinyGPS++.h>

static const int RXPin = 4, TXPin = 5;
static const int GPSBaud = 9600;

TinyGPSPlus gps;
SoftwareSerial SerialGPS(RXPin, TXPin);

double lt,lg;
void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  SerialGPS.begin(GPSBaud);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 
  
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

void locate()
  {
   while (SerialGPS.available() > 0)
     if (gps.encode(SerialGPS.read()))
      if (gps.location.isValid())
      {
        gps.location.lat();
        // LatitudeString = String(lt , 6);
        gps.location.lng();
        // LongitudeString = String(lg , 6);
      }
    
    
  }

void loop() {
  ArduinoCloud.update();
  locate();
  location=Location(gps.location.lat(),gps.location.lng());
}

