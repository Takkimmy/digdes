#include <Arduino.h>
#include <Wire.h>
#include "lcd_display.h"
#include "soilSensor.h"
#include "config.h"

// Based on joseph testing, approx min = 2100, approx max = 3000
#define relayPin RELAY_PIN


int soilMoisturePercentage = 0;

int previousSoilMoisturePercentage = -1;  // Initialize with a value that won't match the first reading
int previousMaxSoilMoisture = -1;  // Initialize with a value that won't match the first reading
void taskDisplay(void *parameter){
  while (true){
    // Get the current values
    int currentSoilMoisturePercentage = soilMoisturePercentage;
    int currentMaxSoilMoisture = SoilSensor::getMaxSoilMoisture();

    // Check if either value has changed
    if (currentSoilMoisturePercentage != previousSoilMoisturePercentage || currentMaxSoilMoisture != previousMaxSoilMoisture) {
      // Update the display only if the values have changed
      lcdDisplay::lcdPrintTopBottom("Moisture: " + String(currentSoilMoisturePercentage) + "%", "Threshold: " + String(currentMaxSoilMoisture) + "%");

      // Update the previous values
      previousSoilMoisturePercentage = currentSoilMoisturePercentage;
      previousMaxSoilMoisture = currentMaxSoilMoisture;
    }

    delay(150);  // Short delay to avoid rapid updates
  }
}

int lastButtonStateIncrease = LOW;
int lastButtonStateDecrease = LOW;
bool buttonPressedIncrease = false;
bool buttonPressedDecrease = false;
void taskButtons(void *parameters){
  while(true){
    // Read the current state of the buttons
    int readingIncrease = digitalRead(BTN_INCREASE);
    int readingDecrease = digitalRead(BTN_DECREASE);

    // Handle BTN_INCREASE
    if (readingIncrease == HIGH && lastButtonStateIncrease == LOW) {
      // Button was just pressed, increment soil moisture
      SoilSensor::setMaxSoilMoisture(SoilSensor::getMaxSoilMoisture() + 1);
      buttonPressedIncrease = true; // Mark the button as pressed
    }

    // Handle BTN_DECREASE
    if (readingDecrease == HIGH && lastButtonStateDecrease == LOW) {
      // Button was just pressed, decrement soil moisture
      SoilSensor::setMaxSoilMoisture(SoilSensor::getMaxSoilMoisture() - 1);
      buttonPressedDecrease = true; // Mark the button as pressed
    }

    // Reset button states after release
    if (readingIncrease == LOW && lastButtonStateIncrease == HIGH && buttonPressedIncrease) {
      buttonPressedIncrease = false;  // Reset press flag when the button is released
    }

    if (readingDecrease == LOW && lastButtonStateDecrease == HIGH && buttonPressedDecrease) {
      buttonPressedDecrease = false;  // Reset press flag when the button is released
    }

    // Save the current button states for the next loop iteration
    lastButtonStateIncrease = readingIncrease;
    lastButtonStateDecrease = readingDecrease;

    // Add a small delay to make the loop more stable
    delay(5); // Optional: you can tweak this delay based on responsiveness
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  // For initializing LCD display
  lcdDisplay::lcdInit();
  pinMode(relayPin, OUTPUT);
  lcdDisplay::lcdPrintTopBottom("Self Watering", "System");
  delay(2000);

  // For creating looping tasks
  xTaskCreate(taskDisplay, "Task 1", 2048, NULL, 1, NULL);
  xTaskCreate(taskButtons, "Task 2", 2048, NULL, 1, NULL);
  // For initializing buttons
  pinMode(BTN_INCREASE, INPUT);
  pinMode(BTN_DECREASE, OUTPUT);
}


int startTime = 0;
int duration = 0;

void loop() {
  Serial.println(SoilSensor::getSoilMoistureCapacitance());
  soilMoisturePercentage = SoilSensor::getSoilMoisturePercentage();
  if (soilMoisturePercentage <= SoilSensor::getMaxSoilMoisture()){
    digitalWrite(relayPin, HIGH);
  }
  if (soilMoisturePercentage > SoilSensor::getMaxSoilMoisture()){
    digitalWrite(relayPin, LOW);
  }

  delay(5);
}
