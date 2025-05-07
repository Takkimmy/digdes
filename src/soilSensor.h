#pragma once

class SoilSensor {
    public:
        static int getSoilMoisturePercentage();
        static int getSoilMoistureCapacitance();
        static int getMaxSoilMoisture();
        static int setMaxSoilMoisture(int val);
    };
