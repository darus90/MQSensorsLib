#ifndef MQUnifiedsensor_H
  #define MQUnifiedsensor_H

#include <Arduino.h>
#include <stdint.h>

/***********************Software Related Macros************************************/

#define ADC_RESOLUTION 10 // for 10bit analog to digital converter.
#define retries 5
#define retry_interval 20

class MQUnifiedsensor
{
  public:
    MQUnifiedsensor(String Placa = "Arduino", double Voltage_Resolution =  5, int ADC_Bit_Resolution = 10, int pin = 1, String type = "CUSTOM MQ");
    
    //Functions to set values
    void init();
    void update();
    void setR0(double R0 = 10);
    void setRL(double RL = 10);
    void setA(double a);
    void setB(double b);
    void setRegressionMethod(String regressionMethod);
    void setVoltResolution(double voltage_resolution =  5);
    void serialDebug(bool onSetup = false); //Show on serial port information about sensor
    
    //user functions
    float calibrate(float ratioInCleanAir);
    float readSensor();
    float calculatePPM(double ratio = 0);
    
    //get function for info
    double getR0();
    double getRL();
    double getVoltage(int read = true);
    
    double stringToDouble(String & str);    

  private:
    /************************Private vars************************************/
    byte _pin;
    byte _firstFlag = false;
    byte _VOLT_RESOLUTION  = 5.0; // if 3.3v use 3.3
    byte _RL = 10; //Value in KiloOhms
    byte _ADC_Bit_Resolution = 10;
    
    double _adc, _a, _b, _sensor_volt;
    float  _R0, RS_air, _ratio, _PPM, _RS_Calc;  
    
    String _type;
    String _placa; 
    String _regressionMethod;
};

#endif //MQUnifiedsensor_H
