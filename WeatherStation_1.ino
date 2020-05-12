/*
 * Project WeatherStation_1
 * Description:
 * Author:
 * Date:
 */

 #define DHTPIN 2
 #define DHTTYPE DHT11 // DHT11 Module

 // Variables
 int light;
 // Pins
 int light_sensor_pin = A0;
 double tempF; // Temperature F
 double tempC; // Temperature C
 double humidity; // Humidity
DHT dht(DHTPIN, DHTTYPE);


 const String key = "BSM96CCWGQHO0AXF"; // Change this to your Thingspeak api write key

 void setup() {
 Particle.variable("Light", &light, INT);
 Particle.variable("tempF", &tempF, DOUBLE);
 Particle.variable("tempC", &tempC, DOUBLE);
 Particle.variable("humidity", &humidity, DOUBLE);
 dht.begin();
 Serial.begin(9600);
 }

 void loop() {
//light reading
 float light_measurement = analogRead(light_sensor_pin);
 light = (int)(light_measurement/4096*100);
//DHT readings
 humidity = dht.getHumidity();
 tempC = dht.getTempCelcius();
 tempF = dht.getTempFarenheit();
 // Publish data
 Particle.publish("light", String(light) + "%");
 Particle.publish("tempC", String(tempC) + "C");
 Particle.publish("humidity", String(humidity) + "%");

 Particle.publish("thingSpeakWrite_All", "{ \"1\": \"" + String(humidity) + "\"," +
       "\"2\": \"" + String(tempC) + "\"," +
       "\"3\": \"" + String(tempF) + "\"," +
       "\"4\": \"" + String(light) + "\"," +
       "\"k\": \"" + key + "\" }", 60, PRIVATE);

 Serial.publish("light", String(light) + "%");
 Serial.publish("tempC", String(tempC) + "C");
 Serial.publish("humidity", String(humidity) + "%");



 delay(10000); //leave on to enure it has time to connect and send data
// Set the sleep time
 }
