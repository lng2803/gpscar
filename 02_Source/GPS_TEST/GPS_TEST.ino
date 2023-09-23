#include <HardwareSerial.h>
#include <TinyGPS++.h>

HardwareSerial ss(2);

TinyGPSPlus gps;

void setup() {
  // put your setup code here, to run once:
  ss.begin(9600, SERIAL_8N1, 16, 17);
  Serial.begin(115200);

}

void loop() {
  // while (ss.available() > 0){
  //   // get the byte data from the GPS
  //   byte gpsData = ss.read();
  //   Serial.write(gpsData);
  // }
    while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
      Serial.print("Latitude= "); 
      Serial.print(gps.location.lat(), 6);
      Serial.print(" Longitude= "); 
      Serial.println(gps.location.lng(), 6);
    }
  }
}
