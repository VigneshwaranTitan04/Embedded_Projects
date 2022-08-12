/*
 * 
 * 
PROJECT NAME: LIGHTING AUTOMATION
AUTHOR: VIGNESHWARAN SAMINATHAN
COMPANY NAME: TITAN COMPANY LIMITED
DEPARTMENT: PROJECTS AND MAINTENANCE
FIRMWARE REVISION: V0.0 (BASE REVISION)

FILE AND NAMES

001_LIGHTING_AUTOMATION.ino
Config.h
prototype_dev.ino

 *
 *
 *
*/

#include <BluetoothSerial.h>

/*Bluetooth Serial Defined*/

#include "Config.h"   // Editor File
#include <EEPROM.h>   // EEPROM Memory

/*Helper Variables*/

int8_t MODE_STATUS;

BluetoothSerial SerialBT;

void setup() {
  // put your setup code here, to run once:

Serial.begin(SYSTEM_BAUD);                              //  Beginning Serial Communication
SerialBT.begin(BLUETOOTH_NAME);                         //  Assigning Bluetooth Name


if(EEPROM.begin(EEPROM_SIZE)){                          //  EEPROM Size
    Serial.println("EEPROM Memory Begin Successful!");    
  }

else{
    Serial.println("EEPROM Memory Begin Not Successful!");
  }

/* Configuring Three Pins as an Output*/

pinMode(RELAY_1, OUTPUT);
pinMode(RELAY_2, OUTPUT);
pinMode(RELAY_3, OUTPUT);
pinMode(LDR_SENSOR_PIN, INPUT);

delay(2000);

digitalWrite(RELAY_1, EEPROM.read(EEPROM_RELAY_1_ADDR));
digitalWrite(RELAY_2, EEPROM.read(EEPROM_RELAY_2_ADDR));
digitalWrite(RELAY_3, EEPROM.read(EEPROM_RELAY_3_ADDR));

/* FOR SETTING MODES MANUALLY 
 *  
EEPROM.write(DEVICE_MODE_ADDRESS, MANUAL_MODE); 
EEPROM.commit();
 *
*/

MODE_STATUS = EEPROM.read(DEVICE_MODE_ADDRESS);
Serial.println(MODE_STATUS);

}

void loop() {
  // put your main code here, to run repeatedly:

/*Accepting Data from the two UART Pins Available*/

if(MODE_STATUS == 1)
{
Serial.println("Manual Mode Activated!");

 while(1){ 
    Manual_Mode();
 }
}

if(MODE_STATUS == 2)
{
Serial.println("LOW Power Mode is Activated!");

while(1){ 
  Low_Power_Mode();    
 }
}

if(MODE_STATUS == 3)
{
Serial.println("Ultra LOW Power Mode is Activated!");

while(1){ 
  Ultra_Low_Power_Mode();   
 }
}
}
