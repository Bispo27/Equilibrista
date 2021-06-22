void ReadRightTick(){
  bool clk[5];
  for(int i = 0; i < 5; i++){
    clk[i] = digitalRead(CLKR);
  }
  if(((clk[0] == clk[1] == clk[2] == clk[3] == clk[4]) != lastStateRight)){
    if(digitalRead(DTR) != digitalRead(CLKR))
      tickR--;
    else
      tickR++;
      lastStateRight = clk[0];
  }
}
void ReadLeftTick(){
  bool clk[5];
  for(int i = 0; i < 5; i++){
    clk[i] = digitalRead(CLKL);
  }
  if(((clk[0] == clk[1] == clk[2] == clk[3] == clk[4]) != lastStateLeft)){
    if(digitalRead(DTL) != digitalRead(CLKL))
      tickL++;
    else
      tickL--;

      lastStateLeft = clk;
  }
}

void UpdateTick(){
  bool clk[5];

  for(int i = 0; i < 5; i++){
    clk[i] = digitalRead(CLKR);
  }
  if(((clk[0] == clk[1] == clk[2] == clk[3] == clk[4]) != lastStateRight)){
    if(digitalRead(DTR) != digitalRead(CLKR))
      tickR--;
    else
      tickR++;
      lastStateRight = clk[0];
  }
  
  for(int i = 0; i < 5; i++){
    clk[i] = digitalRead(CLKL);
  }
  if(((clk[0] == clk[1] == clk[2] == clk[3] == clk[4]) != lastStateLeft)){
    if(digitalRead(DTL) != digitalRead(CLKL))
      tickL--;
    else
      tickL++;
      lastStateLeft = clk[0];
  }
  
}
