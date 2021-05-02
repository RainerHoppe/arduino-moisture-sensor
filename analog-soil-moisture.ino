// Simple code for Measuring Voltage
// analog sensor, 5 Volt
// Rainer Hoppe, https://test-wetterstation.de


int soil_moisture_pin = A0; // AOUT pin on sensor
int iSoil_moisture=0;

void setup() {
  Serial.begin(9600); // serial port setup
}

void loop() {
  iSoil_moisture=analogRead(soil_moisture_pin); 

  Serial.print("Soil moisture Sensor Voltage: ");
  Serial.print((float(iSoil_moisture)/1023.0)*5); // read sensor
  Serial.println(" V");

  Serial.print("Soil moisture: ");
  Serial.println(iSoil_moisture);
  

  delay(1000); // slight delay between readings
}
