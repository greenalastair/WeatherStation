
#include <math.h>
//only works in the particle IDE
int light;
double T;
int light_sensor_pin = A0;
int ThermistorPin = A5;
int Vo;
float R1 = 10000;
float logR2, R2;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

const String key = "BSM96CCWGQHO0AXF"; // Change this to your Thingspeak api write key

void setup() {
Serial.begin(9600);

}

void loop() {
//Temp Measure
Vo = analogRead(ThermistorPin);
R2 = R1 * (4095.0 / (float)Vo - 1.0);
logR2 = log(R2);
T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
T = T - 273.15;

//Light Measure
float light_measurement = analogRead(light_sensor_pin);
light = (int)(light_measurement/4096*100);

// Publish data
Particle.publish("light", String(light) + "%");
Particle.publish("temp", String(T, 1) + "C");
Serial.print(T);

Particle.publish("thingSpeakWrite_All", "{ \"1\": \"" + String(light) + "\"," +
 "\"2\": \"" + String(T, 1) + "\"," +
"\"k\": \"" + key + "\" }", 60, PRIVATE);

Serial.println(" - Published!");


delay(10000); //leave on to enure it has time to connect and send data

System.sleep(SLEEP_MODE_DEEP, 600); // Set the sleep time (seconds)
}
