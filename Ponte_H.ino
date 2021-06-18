void MotorCommand(double cmd) {


  if (cmd > 0) {
    analogWrite(IA, 0);
    analogWrite(IB, abs(cmd));
    analogWrite(IC, abs(cmd));
    analogWrite(ID, 0);
  }
  else {

    analogWrite(IA, abs(cmd));
    analogWrite(IB, 0);
    analogWrite(IC, 0);
    analogWrite(ID, abs(cmd));
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
