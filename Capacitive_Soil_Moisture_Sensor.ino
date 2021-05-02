// Simple code for Measuring Voltage from
// Capacitive soil moisture sensor
// Rainer Hoppe, https://test-wetterstation.de


int soil_moisture_pin = A0; // AOUT pin on sensor
int iSoil_moisture=0;

void setup() {
  Serial.begin(9600); // serial port setup
  analogReference(EXTERNAL); // set the analog reference to 3.3V
}

void loop() {

  iSoil_moisture = analogRead(soil_moisture_pin);
  Serial.print("Soil Moisture Sensor Voltage: ");
  Serial.print((float(iSoil_moisture)/1023.0)*3.3); // read sensor
  Serial.println(" V");

  Serial.print("Soil moisture: ");
  Serial.println(iSoil_moisture);
  
  delay(1000); // slight delay between readings
}
