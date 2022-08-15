#include "Config.h"   // Editor File

/*Millis variables*/

unsigned long previousMillis = 0;        

const long interval_1 = 5000;  

_Bool sensor_read;

int count = 0;

void Manual_Mode(){

  if((SerialBT.available()>0) || (Serial.available()>0)){

  char x = SerialBT.read();    // Reading from Bluetooth
  char y = Serial.read();      // Reading from UART Pins

  if((x == 'a')||(y == 'a'))
  {
    digitalWrite(RELAY_1, digitalRead(RELAY_1)^1);
    Serial.println("RELAY_1 Toggled");
    SerialBT.println("RELAY_1 Toggled");
    EEPROM.write(EEPROM_RELAY_1_ADDR, digitalRead(RELAY_1));
    EEPROM.commit();
    }

  if((x == 'b')||(y == 'b'))
  {
    digitalWrite(RELAY_2, digitalRead(RELAY_2)^1);
    Serial.println("RELAY_2 Toggled");
    SerialBT.println("RELAY_2 Toggled");  
    EEPROM.write(EEPROM_RELAY_2_ADDR, digitalRead(RELAY_2));
    EEPROM.commit();
    }

  if((x == 'c')||(y == 'c'))
  {
    digitalWrite(RELAY_3, digitalRead(RELAY_3)^1);
    Serial.println("RELAY_3 Toggled");
    SerialBT.println("RELAY_3 Toggled");
    EEPROM.write(EEPROM_RELAY_3_ADDR, digitalRead(RELAY_3));
    EEPROM.commit();
    }

  if((x == '2') || (y == '2'))
  {

  EEPROM_status_update();
  Serial.println("Switching to the Low Power Mode Mode");
  SerialBT.println("Low Power Mode");
  EEPROM.write(DEVICE_MODE_ADDRESS, LOW_POWER_MODE);
  EEPROM.commit();
  delay(3000);
  Serial.println("Re-Starting the Lighting Automation Device");
  SerialBT.println("Re-Start");
  
  ESP.restart();
  }

  if((x == '3') || (y == '3'))
  {

  EEPROM_status_update();
  Serial.println("Switching to the Ultra Low Power Mode");
  SerialBT.println("Ultra Low Power Mode");
  EEPROM.write(DEVICE_MODE_ADDRESS, ULTRA_LOW_POWER_MODE);
  EEPROM.commit();
  delay(3000);
  Serial.println("Re-Starting the Lighting Automation Device");
  SerialBT.println("Re-Start");
  
  ESP.restart();
  
  }
}
}

void Low_Power_Mode(){

  uint32_t sensor_data;
  
  if((SerialBT.available()>0) || (Serial.available()>0)){

  char x = SerialBT.read();    // Reading from Bluetooth
  char y = Serial.read();      // Reading from UART Pins

  if((x == '1') || (y == '1'))
  {

  EEPROM_status_update();
  Serial.println("Switching to the Manual Mode");
  SerialBT.println("Manual Mode");
  EEPROM.write(DEVICE_MODE_ADDRESS, MANUAL_MODE);
  EEPROM.commit();
  delay(3000);
  Serial.println("Re-Starting the Lighting Automation Device");
  SerialBT.println("Re-Start");
  
  ESP.restart();
  }

  if((x == '3') || (y == '3'))
  {

  EEPROM_status_update();
  Serial.println("Switching to the Ultra Low Power Mode");
  SerialBT.println("Ultra Low Power Mode");
  EEPROM.write(DEVICE_MODE_ADDRESS, ULTRA_LOW_POWER_MODE);
  EEPROM.commit();
  delay(3000);
  Serial.println("Re-Starting the Lighting Automation Device");
  SerialBT.println("Re-Start");
  
  ESP.restart();
  
  }
  }

  unsigned long currentMillis_1 = millis();

  if (currentMillis_1 - previousMillis >= interval_1) {
    
  previousMillis = currentMillis_1;

  analogReadResolution(ANALOG_READ_BIT_RESOLUTION);
  sensor_data = analogRead(LDR_SENSOR_PIN);
  Serial.println("Sensor: " + String(sensor_data));
  SerialBT.println("Sensor: " + String(sensor_data));

}

if((sensor_data <= LOW_POWER_MID_RANGE_1) && (sensor_data >= LOW_POWER_MID_RANGE_2)){
    
  digitalWrite(RELAY_1, HIGH);
  digitalWrite(RELAY_2, LOW);
  digitalWrite(RELAY_3, HIGH);  
  
  }  

  if(sensor_data > LOW_POWER_MAX){
    
  digitalWrite(RELAY_1, HIGH);
  digitalWrite(RELAY_2, HIGH);
  digitalWrite(RELAY_3, HIGH);  
  
  }

  if(sensor_data < LOW_POWER_MIN){
    
  digitalWrite(RELAY_1, LOW);
  digitalWrite(RELAY_2, LOW);
  digitalWrite(RELAY_3, LOW);   
  }  
}

void Ultra_Low_Power_Mode(){
  
  if((SerialBT.available()>0) || (Serial.available()>0)){

  char x = SerialBT.read();    // Reading from Bluetooth
  char y = Serial.read();      // Reading from UART Pins

  if((x == '1') || (y == '1'))
  {
  EEPROM_status_update();
  Serial.println("Switching to the Manual Mode");
  SerialBT.println("Switching to the Manual Mode");
  EEPROM.write(DEVICE_MODE_ADDRESS, MANUAL_MODE);
  EEPROM.commit();
  delay(3000);
  Serial.println("Re-Starting the Lighting Automation Device");
  SerialBT.println("Re-Start");
  
  ESP.restart();
  }

  if((x == '2') || (y == '2'))
  {
  EEPROM_status_update();
  Serial.println("Switching to the Low Power Mode");
  SerialBT.println("Ultra Low Power Mode");
  EEPROM.write(DEVICE_MODE_ADDRESS, LOW_POWER_MODE);
  EEPROM.commit();
  delay(3000);
  Serial.println("Re-Starting the Lighting Automation Device");
  SerialBT.println("Re-Start");
  
  ESP.restart();
  }
  }

  sensor_read = digitalRead(PIR_SENSOR_PIN);
  Serial.println(sensor_read);

  if(sensor_read == true){
    digitalWrite(RELAY_1, HIGH);
    digitalWrite(RELAY_2, HIGH);
    digitalWrite(RELAY_3, HIGH);
    SerialBT.println("Motion Detected, Restarting Counter");
    delay(1000);
    count=0;
  }

  if(sensor_read == false){
    count++;
    Serial.println("Counter: " + String(count));
    SerialBT.println("No Motion Counter: " + String(count));
    delay(200);
  }

  if(count > COUNTER){
    digitalWrite(RELAY_1, LOW);
    digitalWrite(RELAY_2, LOW);
    digitalWrite(RELAY_3, LOW);
    count=0;
    delay(1000);
  }
    delay(1000);
}

void EEPROM_status_update(){

  EEPROM.write(EEPROM_RELAY_1_ADDR, digitalRead(RELAY_1));
  EEPROM.write(EEPROM_RELAY_2_ADDR, digitalRead(RELAY_2));
  EEPROM.write(EEPROM_RELAY_3_ADDR, digitalRead(RELAY_3));

}
