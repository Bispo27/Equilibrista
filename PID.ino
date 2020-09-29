double PID(double angle) {
  digitalWrite(13, HIGH);
  double Erro = setPoint - angle;
  iE += micros() * Erro / 1000000.00;
  //Serial.println(iE);
  if (iE > 200)
    iE = 200.00;
  if (iE < -200)
    iE = -200.00;

  double dE = (angle - lastAngle)/((micros() / 1000000.00) - lastTime);
  //Serial.println(dE);
  lastTime = micros() / 1000000.00;
  double force = Kp * Erro + Ki * iE + Kp * Kd * dE;

  if (force > 200)
    force = 200.00;
  if (force < -200)
    force = -200.00;
    
  lastAngle = angle;
  return force;
}
