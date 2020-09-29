void MPUInit() {
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);

  Wire.write(0);
  Wire.endTransmission(true);

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

  double dt = (double)(micros() - timer) / 1000000;
  timer = micros();

  gyXangle = Gx / 131.0;
  gyYangle = Gy / 131.0;

  double pitch = atan(Ax / sqrt(Ay * Ay + Az * Az)) * RAD_TO_DEG;
  double roll = atan(Ay / sqrt(Ax * Ax + Az * Az)) * RAD_TO_DEG;

  kalAngleX = kalmanX.getAngle(roll, gyXangle, dt);
  kalAngleY = kalmanY.getAngle(pitch, gyYangle, dt);
  
  //Serial.print("Kalman X: "); Serial.println(kalAngleX);
  //Serial.print("Kalman Y: "); Serial.print(kalAngleY);
}
