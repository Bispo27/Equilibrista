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

double lastTime = micros() / 1000000.00;
int16_t Ax, Ay, Az, T, Gx, Gy, Gz;
volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high



void MPUInitQuaternions();



/**funções e variáveis MPU6050***/

/**funções e variáveis PONTE-H***/
#define IA     6
#define IB     3
#define IC     5
#define ID     11


void PonteInit();
void MotorCommand(double cmdL, double cmdR);

/**fim funções e variáveis PONTE-H***/

/**funções e variáveis PD***/
double KD = 2.500; //10
double KP = 7500.0; //10000
double KDposTick = 0.00;
double KpTick = 0.00;//0.5;

double setPoint = 0.00;

volatile int32_t tickR = 0; 
#define CLKR  A0
#define DTR  A1
#define DWR  A2
volatile bool lastStateRight;
void ReadRightTick();

volatile int32_t tickL = 0; 
#define CLKL  8
#define DTL  9
#define DWL  10
volatile bool lastStateLeft;
void ReadLeftTick();


void UpdateTick();

 
void Controler(double angle, int tickA, int tickB);


/****************fim variáveis do timer*****************************/
void setup() {
  delay(1000);
  pinMode(CLKR, INPUT);
  pinMode(DTR, INPUT);
  pinMode(DWR, INPUT);
  pinMode(CLKL, INPUT);
  pinMode(DTL, INPUT);
  pinMode(DWL, INPUT);

  digitalWrite(CLKR, HIGH);
  digitalWrite(DTR, HIGH);
  digitalWrite(DWR, HIGH);
  digitalWrite(CLKL, HIGH);
  digitalWrite(DTL, HIGH);
  digitalWrite(DWL, HIGH);
  
  Serial.begin(115200);
  PonteInit();
  MPUInit();
  Timer1.initialize(10000);
  lastStateRight = digitalRead(CLKR);
  lastStateLeft = digitalRead(CLKL);
  Timer1.attachInterrupt(UpdateTick);  
  
}
double LT = 0;
void dmpDataReady() {
  mpuInterrupt = true;
};

void loop() {
  if(!mpuInterrupt)
    return;
    
  MPURequestData();
  double t = micros() / 1000000.00 - lastTime;
  posAngleY += t*gyYangle;
  int difTick = tickR - tickL;
  double posTick = (tickR + tickL) / 2;
  
  double SetPWMR = (KD * (gyYangle) +  KP * posAngleY + KDposTick*posTick - KpTick * difTick); // 
  double SetPWML = (KD * (gyYangle) +  KP * posAngleY + KDposTick*posTick + KpTick * difTick);
  MotorCommand(SetPWMR, SetPWML);
  Serial.print("t: "); Serial.print(t, 10);Serial.print("    Gy: ");Serial.print(gyYangle); Serial.print("  posAngleY: "); Serial.print(posAngleY); 
  Serial.print("  SetPWML: "); Serial.print(SetPWML);Serial.print("  SetPWMR: "); Serial.print(SetPWMR);
  Serial.print("  KP: "); Serial.print(KP);Serial.print("  KD: "); Serial.print(KD); 
  Serial.print("  posTick: "); Serial.print(posTick);Serial.print("  Delta Tick: "); Serial.println(difTick);

  lastTime = micros() / 1000000.00;
  

  
}
