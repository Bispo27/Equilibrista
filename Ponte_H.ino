void MotorCommand(double cmdL, double cmdR) {
if(cmdR > 255) cmdR = 255.00;
if(cmdR < -255) cmdR = -255.00;
if(cmdL > 255) cmdL = 255.00;
if(cmdL < -255) cmdL = -255.00;

  if (cmdR > 0 && cmdL > 0) {
    analogWrite(IA, 0);
    analogWrite(IB, abs(cmdR));
    analogWrite(IC, abs(cmdL));
    analogWrite(ID, 0);
  }
  else if (cmdR < 0 && cmdL < 0) {
    analogWrite(IA, abs(cmdR));
    analogWrite(IB, 0);
    analogWrite(IC, 0);
    analogWrite(ID, abs(cmdL));
  }
  else if (cmdR > 0 && cmdL < 0) {
    analogWrite(IA, 0);
    analogWrite(IB, abs(cmdR));
    analogWrite(IC, 0);
    analogWrite(ID, abs(cmdL));
  }
  else if (cmdR < 0 && cmdL > 0) {
    analogWrite(IA, abs(cmdR));
    analogWrite(IB, 0);
    analogWrite(IC, abs(cmdL));
    analogWrite(ID, 0);
  }
  

  //Serial.print("angle: "); Serial.print(kalAngleY);
  //Serial.print(" force: "); Serial.println(cmd);

}
void PonteInit() {
  pinMode(IA, OUTPUT);
  pinMode(IB, OUTPUT);
  pinMode(IC, OUTPUT);
  pinMode(ID, OUTPUT);

  analogWrite(IA, HIGH);
  analogWrite(IB, HIGH);
  analogWrite(IC, HIGH);
  analogWrite(ID, HIGH);

  delay(1000);
}
