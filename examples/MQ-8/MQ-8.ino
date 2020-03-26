/*
  MQUnifiedsensor Library - reading an MQ8

  Demonstrates the use a MQ8 sensor.
  Library originally added 01 may 2019
  by Miguel A Califa, Yersson Carrillo, Ghiordy Contreras, Mario Rodriguez
 
  Added example
  modified 23 May 2019
  by Miguel Califa 

  Updated library usage
  modified 26 March 2020
  by Miguel Califa 

 This example code is in the public domain.

*/

//Include the library
#include <MQUnifiedsensor.h>

//Definitions
#define placa "Arduino UNO"
#define Voltage_Resolution 5
#define pin A0 //Analog input 0 of your arduino
#define type "MQ-8" //MQ8
#define ADC_Bit_Resolution 10 // For arduino UNO/MEGA/NANO
//#define calibration_button 13 //Pin to calibrate your sensor

//Declare Sensor
MQUnifiedsensor MQ8(placa, Voltage_Resolution, ADC_Bit_Resolution, pin, type);

void setup() {
  //Init the serial port communication - to debug the library
  Serial.begin(9600); //Init serial port

  //Set math model to calculate the PPM concentration and the value of constants
  MQ8.setRegressionMethod("Exponential"); //_PPM =  a*ratio^b
  MQ8.setA(976.97); MQ8.setB(-0.688); // Configurate the ecuation values to get H2 concentration

  /*
    Exponential regression:
  GAS     | a      | b
  H2      | 976.97  | -0.688
  LPG     | 10000000 | -3.123
  CH4     | 80000000000000 | -6.666
  CO      | 2000000000000000000 | -8.074
  Alcohol | 76101 | -1.86
  */
  
  // Calibration setup
  MQ8.setR0(1);

  /* 
    //If the RL value is different from 10K please assign your RL value with the following method:
    MQ8.setRL(10);
  */

  /*****************************  MQ Init ********************************************/ 
  //Remarks: Configure the pin of arduino as input.
  /************************************************************************************/ 
  MQ8.init(); 
  /*****************************  MQ Init ********************************************/ 
  //Input: setup flag, if this function are on setup will print the headers (Optional - Default value: False)
  //Output: print on serial port the information about sensor and sensor readings
  //Remarks: Configure the pin of arduino as input.
  /************************************************************************************/ 
  MQ8.serialDebug(true);
}

void loop() {
  MQ8.update(); // Update data, the arduino will be read the voltage on the analog pin
  MQ8.readSensor(); // Sensor will read PPM concentration using the model and a and b values setted before or in the setup
  MQ8.serialDebug(); // Will print the table on the serial port
  delay(500); //Sampling frequency
}