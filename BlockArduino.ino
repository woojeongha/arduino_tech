#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

#include <SoftwareSerial.h>
#include <ArduinoJson.h>

#include <Wire.h>
#include <math.h>

#define          BT_RXD 8
#define          BT_TXD 7
#define          TIME   1
#define          SIZE   100

SoftwareSerial   bluetooth(BT_RXD, BT_TXD);        
Adafruit_MPU6050 mpu;
String           jsonString;

sensors_event_t  a;
sensors_event_t  g;
sensors_event_t  temp;

void setup(void) 
{
    //jObject = new JSONVar();

    bluetooth.begin(9600);
    Serial.begin(9600);
    if (!mpu.begin()) 
    {
        exit(-1);
    }

    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

    delay(TIME);
}

void loop()
{
    mpu.getEvent(&a, &g, &temp);
    
    String contents = CreateJsonString(a, g, temp);
    if(bluetooth)
    {
      bluetooth.write(contents.c_str());
    }

    delay(TIME);
}
