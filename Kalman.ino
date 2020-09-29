void KalmanInit(){
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);

  Wire.requestFrom(MPU, 14, true);
  Ax = ((Wire.read() << 8) | Wire.read());
  Ay = ((Wire.read() << 8) | Wire.read());
  Az = ((Wire.read() << 8) | Wire.read());
  double pitch = atan(Ax / sqrt(Ay * Ay + Az * Az)) * RAD_TO_DEG;
  double roll = atan(Ay / sqrt(Ax * Ax + Az * Az)) * RAD_TO_DEG;

  kalmanX.setAngle(roll);
  kalmanY.setAngle(pitch);

  gyXangle = roll;
  gyYangle = pitch;


  timer = micros();
}
