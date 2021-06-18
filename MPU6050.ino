

void MPUInit() {
int devStatus = mpu.dmpInitialize();

  // supply your own gyro offsets here, scaled for min sensitivity
  mpu.setXGyroOffset(220);
  mpu.setYGyroOffset(76);
  mpu.setZGyroOffset(-85);
  mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

  // make sure it worked (returns 0 if so)
  if (devStatus == 0) {
      // Calibration Time: generate offsets and calibrate our MPU6050
      mpu.CalibrateAccel(6);
      mpu.CalibrateGyro(6);
      mpu.PrintActiveOffsets();
      mpu.setDMPEnabled(true);

      attachInterrupt(digitalPinToInterrupt(2), dmpDataReady, RISING);
      mpu.getIntStatus();

      mpuInterrupt = true;
  } else {
      // ERROR!
      // 1 = initial memory load failed
      // 2 = DMP configuration updates failed
      // (if it's going to break, usually the code will be 1)
      Serial.print(F("DMP Initialization failed (code "));
      Serial.print(devStatus);
      Serial.println(F(")"));
  }

}

void MPURequestData() {
Wire.beginTransmission(MPU);
Wire.write(0x3B);
Wire.endTransmission(false);

Wire.requestFrom(MPU, 14, true);

Ax = ((Wire.read() << 8) | Wire.read());
Ay = ((Wire.read() << 8) | Wire.read());
Az = ((Wire.read() << 8) | Wire.read());
T  = ((Wire.read() << 8) | Wire.read());
Gx = ((Wire.read() << 8) | Wire.read());
Gy = ((Wire.read() << 8) | Wire.read());
Gz = ((Wire.read() << 8) | Wire.read());

gyXangle = Gx / 131.0;
gyYangle = Gy / 131.0;
gyZangle = Gz / 131.0;

}
