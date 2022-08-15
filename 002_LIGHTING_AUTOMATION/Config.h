/*Relay Pins Defined*/

#define RELAY_1                       05
#define RELAY_2                       19
#define RELAY_3                       02

/*System Baud Rate*/

#define SYSTEM_BAUD                   9600

/*Bluetooth Name*/

#define BLUETOOTH_NAME                "ADMIN_ZONE"

/*EEPROM Size*/

#define EEPROM_SIZE                   512
           

/*EEPROM Addresses*/

#define EEPROM_RELAY_1_ADDR           0x100
#define EEPROM_RELAY_2_ADDR           0x101
#define EEPROM_RELAY_3_ADDR           0x102
#define DEVICE_MODE_ADDRESS           0x110               

/*LDR Module*/

#define LDR_SENSOR_PIN                33
#define ANALOG_READ_BIT_RESOLUTION    12

/*PIR Sensor Module*/

#define PIR_SENSOR_PIN                4
#define COUNTER                       10                          

/*Mode Setting*/

#define MANUAL_MODE                   1            
#define LOW_POWER_MODE                2
#define ULTRA_LOW_POWER_MODE          3

/*LOW POWER MODE SETTINGS*/

#define LOW_POWER_MAX                 3500
#define LOW_POWER_MID_RANGE_1         3500
#define LOW_POWER_MID_RANGE_2         2000
#define LOW_POWER_MIN                 2000
#define LOW_POWER_MODE_DELAY          5*1000

/*Functions or Prototypes*/

void Manual_Mode();
void Low_Power_Mode();
void Ultra_Low_Power_Mode();
void EEPROM_status_update();
