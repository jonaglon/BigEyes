void doRainbows1() {
  SetRgbwWheelVars(slowTimey%255);
  for (int pixNum = 0; pixNum < numLeds; pixNum++) {
    setLedDirect(pixNum, wheelR, wheelG, wheelB, 0);
  }  
}

void doRainbows2() {
  for (int pixNum = 0; pixNum < numLeds; pixNum++) {
    SetRgbwWheelVars((slowTimey+pixNum)%255);
    setLedDirect(pixNum, wheelR, wheelG, wheelB, 0);
  }  
}

void doRainbows3() {
  for (int pixNum = 0; pixNum < numLeds; pixNum = pixNum+2) {
    SetRgbwWheelVars((slowTimey+pixNum)%255);
    setLedDirect(pixNum, wheelR, wheelG, wheelB, 0);
  }  
}

// do a 20 rainbow strip moving along the strip
void doRainbows4() {
  int ledAdd = vSlowTimey%numLeds;
  for (int pixNum = 0; pixNum < 20; pixNum++) {
    SetRgbwWheelVars((slowTimey+pixNum)%255);
    setLedDirect((pixNum+ledAdd)%numLeds, wheelR, wheelG, wheelB, 0);
    setLedDirect((pixNum+ledAdd+36)%numLeds, wheelR, wheelG, wheelB, 0);
    setLedDirect((pixNum+ledAdd+72)%numLeds, wheelR, wheelG, wheelB, 0);
    setLedDirect((pixNum+ledAdd+108)%numLeds, wheelR, wheelG, wheelB, 0);
  }  
  for (int pixNum = 0; pixNum < numLeds; pixNum = pixNum+2) {
    SetRgbwWheelVars((slowTimey+pixNum)%255);
    setLedDirect(pixNum, wheelR, wheelG, wheelB, 0);
  }  
}

void allOverRainbow1() {
  for(int j = 0; j < 181; j++) {
    int xCoord = getCoord(j,0)-100;
    int yCoord = getCoord(j,1)-105;
    SetRgbwWheelVars((xCoord+yCoord+(timey/16))%256);
    setLedDirect(j, wheelR, wheelG, wheelB, 0);    
  }
}

void doConcentricRainbow1() {
  
  for (int j = 0; j < 181; j++) { 
    int x = quickAbsolute(100-eyeCoords[j][0]);
    int y = quickAbsolute(105-eyeCoords[j][1]);
    SetRgbwWheelVars((x-y-(timey/16))%256);
    setLedDirect(j, wheelR, wheelG, wheelB, 0);    
  }
}

void doConcentricRainbow2() {
  
  for (int j = 0; j < 181; j++) { 
    int x = quickAbsolute(100-eyeCoords[j][0]);
    int y = quickAbsolute(105-eyeCoords[j][1]);
    SetRgbwWheelVars(((timey/16)-x-y)%256);
    setLedDirect(j, wheelR, wheelG, wheelB, 0);    
  }
}

void doWhitePulse() {
  
  for (int j = 0; j < 181; j++) { 
    int x = quickAbsolute(100-eyeCoords[j][0]);
    int y = quickAbsolute(105-eyeCoords[j][1]);
    SetRgbwWhitePulse(((timey/16)-x-y)%256);
    setLedDirect(j, wheelR, wheelG, wheelB, 0);    
  }
}


int getCoord(int ledNum, int xOrY) {
  return eyeCoords[ledNum][xOrY];
}
