#pragma once

#define SOIL_MOISTURE_PIN 34
#define I2C_SDA 21
#define I2C_SCL 22
#define RELAY_PIN 25
#define BTN_INCREASE 12
#define BTN_DECREASE 14

// FOR SOIL MOISTURE SENSOR

// Based on joseph testing, approx min = 2100, approx max = 3000
static int marginOfError = 80;
#define MAX_SOIL_MOISTURE_VALUE 3000 -  marginOfError;
#define MIN_SOIL_MOISTURE_VALUE 2100 + marginOfError;