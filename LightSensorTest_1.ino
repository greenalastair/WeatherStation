// This #include statement was automatically added by the Particle IDE.
#include "Adafruit_DHT/Adafruit_DHT.h"
// Variables
int light;
// Pins
int light_sensor_pin = A0;



#define publish_cycle 5000 // Only publish every 60 seconds
const String key = "BSM96CCWGQHO0AXF"; // Change this to your Thingspeak api write key
unsigned int lastPublish = 0;
void setup() {
Particle.variable("Light", &light, INT);

}

void loop() {
   unsigned long now = millis();
   // Light level measurement
float light_measurement = analogRead(light_sensor_pin);
light = (int)(light_measurement/4096*100);

// Publish data
Particle.publish("light", String(light) + "%");

if ((now - lastPublish) > publish_cycle) {
    Particle.publish("thingSpeakWrite_All", "{ \"1\": \"" + String(light) + "\"," +
       "\"k\": \"" + key + "\" }", 60, PRIVATE);
    lastPublish = now;
    Serial.println(" - Published!");
  } else {
      Serial.println();
}
delay(2000);

}
