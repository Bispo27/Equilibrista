#include <Wire.h>
#include <Kalman.h>
#include <TimerOne.h>



/*filtro de kalman n*/

void KalmanInit();

Kalman kalmanX;
Kalman kalmanY;
Kalman kalmanZ;

double kalAngleX;
double kalAngleY;
double kalAngleZ;

double gyXangle;
double gyYangle;

/**funções e variáveis MPU6050***/
#define Range 2
#define MPU 0x68
typedef struct {
  float AccX;
  float AccY;
  float AccZ;
} Quad;

double Ax, Ay, Az, T, Gx, Gy, Gz;
typedef struct {
  float r;
  float theta;
  float phi;
} Spheric;
Spheric lastSphSample;

void QuadToSph(Quad sample, Spheric *sph);
void MPURequestData();
void MPUInit();
/**funções e variáveis MPU6050***/

/**funções e variáveis PONTE-H***/
#define IA     6
#define IB     3
#define IC     5
#define ID     11


void PonteInit();
void MotorCommand(double cmd);

/**fim funções e variáveis PONTE-H***/

/**funções e variáveis PID***/
double Kp = 50.0;
double Ki = 0.5;
double Kd = 1.5;


/*
   esse ta "bão"
  double Kp = 20.0;
  double Ki = 0.35;
  double Kd = 0.75;

*/
double setPoint = 0.00;
float lastAngle = 0.00;
double lastTime = 0.00;
double iE = 0.00;

double PID(double angle);




uint32_t timer = 0;


/***********variáveis do Timer***********/


bool pin = false;

uint32_t e = micros();

void Rotine(void) {
  double val = PID(kalAngleY);
  MotorCommand(val);
  //Serial.print("rotine time: "); Serial.println((micros() - e) / 1000000.00, 10);
  e = micros();

}


/****************fim variáveis do timer*****************************/
void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(115200);
  PonteInit();
  MPUInit();

  delay(100);

  KalmanInit();

  Timer1.initialize(10000);
  Timer1.attachInterrupt(Rotine);
}

void loop() {
  MPURequestData();
}


void QuadToSph(Quad sample, Spheric *sph) {
  sph->r = sqrt((sample.AccX * sample.AccX) + (sample.AccY * sample.AccY) + (sample.AccZ * sample.AccZ));
  sph->phi = (atan((sample.AccY) / (sample.AccX))) * 180.00 / PI;
  sph->theta = (acos((sample.AccZ) / (sph->r))) * 180.00 / PI;
}
