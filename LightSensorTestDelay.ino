// This #include statement was automatically added by the Particle IDE.

// Variables
int light;
// Pins
int light_sensor_pin = A0;




const String key = "BSM96CCWGQHO0AXF"; // Change this to your Thingspeak api write key

void setup() {
Particle.variable("Light", &light, INT);

}

void loop() {

float light_measurement = analogRead(light_sensor_pin);
light = (int)(light_measurement/4096*100);

// Publish data
Particle.publish("light", String(light) + "%");


Particle.publish("thingSpeakWrite_All", "{ \"1\": \"" + String(light) + "\"," +
"\"k\": \"" + key + "\" }", 60, PRIVATE);

Serial.println(" - Published!");


delay(5000); //leave on to enure it has time to connect and send data
System.sleep(SLEEP_MODE_DEEP, 60); // Set the sleep time
}
