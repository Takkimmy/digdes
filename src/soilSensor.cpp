#include "soilSensor.h"
#include <Arduino.h>
#include "config.h"

#define analogPin 34

// Based on joseph testing, approx min = 2100, approx max = 3000
int maxSensorValue = MAX_SOIL_MOISTURE_VALUE;
int minSensorValue = MIN_SOIL_MOISTURE_VALUE;
int maxSoilMoisture = 60;

int sensorValue = 0;
int moisturePercent = 0;

int SoilSensor::getSoilMoisturePercentage(){
    sensorValue = analogRead(analogPin);
    moisturePercent = constrain(map(sensorValue, maxSensorValue, minSensorValue, 0, 100), 0, 100);
    return moisturePercent;
}
int SoilSensor::getSoilMoistureCapacitance(){
    return analogRead(analogPin);  
}
int SoilSensor::getMaxSoilMoisture(){
    return maxSoilMoisture;
}
int SoilSensor::setMaxSoilMoisture(int val){
    if (val>=0 && val <= 100){
        maxSoilMoisture = val;
        return true;
    }
    else{
        return false;
    }
}