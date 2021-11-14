
/*
 * Content: class that measures voltage using voltage dividers
 * Author : Forbes Choy
 * Team   : Sustaingineering UBC
 */

#pragma once
#include <Arduino.h>
#include <FarmSensor.h>

class Voltage : public FarmSensor 
{
private:
    int m_higherResistor; // voltage divider, higher resistor value [ohms]
    int m_lowerResistor; // voltage divider, lower resistor value [ohms]
    float m_maximumVoltage; // Maximum Voltage (specific to board)
protected:
    float readRaw() override; 
public:
    static const int analogDigitalConversionResolution = 4095; // ESP32 ADC resolution is 12 bits
    Voltage(int pin, int lowerResistor, int higherResistor, float maximumVoltage);
    bool initialize() override;
};

