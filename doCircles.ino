// TODO - do something good with me??

void doRainbowCircles() {
  for (int j = 1; j < 10; j++) { 
    int ledToLightFrom = circleFirstLeds[j-1];
    int ledToLightTo = circleFirstLeds[j];
    for (int led = ledToLightFrom; led < ledToLightTo; led++) { 
      SetRgbwWheelVars(((totalTimey/16)+(j*20))%256);
      setLedDirect(led, wheelR, wheelG, wheelB, 0, false);    
    }
  }  
}

void doCrazyCircles() {
  for (int j = 1; j < 10; j++) { 
    int ledToLightFrom = circleFirstLeds[j-1];
    int ledToLightTo = circleFirstLeds[j];
    for (int led = ledToLightFrom; led < ledToLightTo; led++) { 
      SetRgbwWheelVars(((timey/16)+(j*20))%256);
      int dimmer = ((timey/32)+(-j*20))%256;
      setLedDirect(led, wheelR-dimmer, (wheelG-dimmer)/2, wheelB-dimmer, 0, false);    
    }
  }  
}

/*
void doConcentricRainbow1() {
  
  for (int j = 0; j < 181; j++) { 
    int x = quickAbsolute(100-eyeCoords[j][0]);
    int y = quickAbsolute(105-eyeCoords[j][1]);
    SetRgbwWheelVars((x-y-(timey/16))%256);
    setLedDirect(j, wheelR, wheelG, wheelB, 0, false);    
  }
}
*/
