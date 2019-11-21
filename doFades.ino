long fadeLength = 2000;
int myCycle = 0;

void doCycles() {  

  myCycle = (totalTimey / fadeLength)%6;
  
  if (myCycle == 0) {
    doColour(245,140,7);
  } else if (myCycle == 1) {
    doColour(245,7,225);
  } else if (myCycle == 2) {
    doColour(2, 133, 142);
  } else if (myCycle == 3) {
    doColour(0,40,160);
  } else if (myCycle == 4) {    
    doColour(82,104,2);
  } else {    
    doColour(120,50,120);
  }
}

void doColour(byte r, byte g, byte b) {
  for (int pixNum = 0; pixNum < numLeds; pixNum++) {
    setLedDirect(pixNum, r, g, b, 0);
  }
}

void doColour(byte r, byte g, byte b, byte w) {
  for (int pixNum = 0; pixNum < numLeds; pixNum++) {
    setLedDirect(pixNum, r, g, b, w);
  }
}
