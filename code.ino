#include <Wire.h>
#include <SparkFun_SCD30_Arduino_Library.h>

// Create an instance of the SCD30 sensor
SCD30 scd30;

// I2C pins for ESP32-C6
#define SDA_PIN 5  // GPIO5 for SDA
#define SCL_PIN 6  // GPIO6 for SCL

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  
  // Wait for serial monitor to open
  while(!Serial) {
    delay(10);
  }
  
  Serial.println("SCD30 CO2, Temperature and Humidity Sensor Test");
  
  // Initialize I2C with custom pins
  Wire.begin(SDA_PIN, SCL_PIN);
  
  // Initialize the SCD30 sensor
  if (scd30.begin()) {
    Serial.println("SCD30 sensor found!");
    
    // Set measurement interval (2 seconds, can be 2-1800 seconds)
    scd30.setMeasurementInterval(2);
    
    // Set altitude compensation in meters (adjust for your location for better CO2 accuracy)
    scd30.setAltitudeCompensation(0); 
    
    // Optionally set ambient pressure compensation (default: 0 = disabled)
    // If you have a separate pressure sensor, you can use this value in mbar
    // scd30.setAmbientPressure(1013); // Standard sea level pressure is 1013.25 mbar
    
    // Start continuous measurements
    scd30.beginMeasuring();
  } else {
    Serial.println("SCD30 sensor not detected. Please check wiring!");
    while (1) {
      delay(10);
    }
  }
  
  Serial.println("Waiting for first measurement... (this might take ~2 seconds)");
  Serial.println("-----------------------------------");
}

void loop() {
  // Check if data is available
  if (scd30.dataAvailable()) {
    // Read measurements
    float co2 = scd30.getCO2();
    float temperature = scd30.getTemperature();
    float humidity = scd30.getHumidity();
    
    // Print readings to serial monitor
    Serial.print("CO2 Concentration: ");
    Serial.print(co2, 0); // 0 decimal places
    Serial.println(" ppm");
    
    Serial.print("Temperature: ");
    Serial.print(temperature, 1); // 1 decimal place
    Serial.println(" °C");
    
    Serial.print("Humidity: ");
    Serial.print(humidity, 1); // 1 decimal place
    Serial.println(" %");
    
    Serial.println("-----------------------------------");
  }
  
  // Small delay
  delay(100);
}