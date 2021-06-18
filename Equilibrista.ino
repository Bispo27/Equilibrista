#include <Wire.h>
#include <Kalman.h>
#include <TimerOne.h>
#include "MPU6050_6Axis_MotionApps_V6_12.h"
#include "I2Cdev.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif


MPU6050 mpu;


double gyXangle;
double gyYangle;
double gyZangle;

double posAngleX = 0;
double posAngleY = 0;
double posAngleZ = 0;

/**funções e variáveis MPU6050***/


#define Range 2

#define MPU 0x68


void MPURequestData();
void MPUInit();

double dTime = micros() / 1000000.00;
int16_t Ax, Ay, Az, T, Gx, Gy, Gz;
volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
mpuInterrupt = true;
};


void MPUInitQuaternions();



/**funções e variáveis MPU6050***/

/**funções e variáveis PONTE-H***/
#define IA     6
#define IB     3
#define IC     5
#define ID     11


void PonteInit();
void MotorCommand(double cmd);

/**fim funções e variáveis PONTE-H***/

/**funções e variáveis PD***/
double KD = 0.2;
double KP = 7.500;

double setPoint = 0.00;
float lastAngle = 0.00;
double lastTime = 0.00;
double iE = 0.00;

void Controler(double angle, int tickA, int tickB);


/****************fim variáveis do timer*****************************/
void setup() {
pinMode(13, OUTPUT);
Serial.begin(115200);
PonteInit();
MPUInit();
delay(100);

 // mpu.getIntStatus();
}

void loop() {
  if(!mpuInterrupt)
    return;
    
  MPURequestData();
  double t = micros() / 1000000.00 - dTime;
  posAngleY += micros()*gyYangle/1000000.00;
  double vel = (KD * (gyYangle) +  KP * posAngleY)/t;
  Serial.print("dTime: "); Serial.print(t, 10);Serial.print("    Gy: ");Serial.print(gyYangle); Serial.print("  posAngleY: "); Serial.print(posAngleY); 
  Serial.print("  Vel: "); Serial.print(vel);Serial.print("  KP: "); Serial.print(KP);Serial.print("  KD: "); Serial.println(KD);
  MotorCommand(vel);
  dTime = micros() / 1000000.00;

}
