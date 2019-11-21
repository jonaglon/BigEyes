
void allOff() {
  for(int j = 0; j < actualNumLeds; j++) {
    setLedDirect(j, 0, 0, 0, 0);
  }
}


void allOn(byte r, byte g, byte b, byte w) {
  for(int j = 0; j < numLeds; j++) {
    setLedDirect(j, r, g, b, w);
  }
}

int quickAbsolute(int number) {
  if (number < 0)
    return number * (-1);
  else
    return number;
}

void setGoodRandomColorVars() {
  int randomNum = random(20);
  switch (randomNum) {
    case 0: 
      goodColR = 255;
      goodColG = 0;
      goodColB = 0;
      goodColW = 0;
      break;
    case 1: 
      goodColR = 0;
      goodColG = 255;
      goodColB = 0;
      goodColW = 0;
      break;
    case 2: 
      goodColR = 0;
      goodColG = 0;
      goodColB = 255;
      goodColW = 0;
      break;
    case 3: 
      goodColR = 0;
      goodColG = 0;
      goodColB = 0;
      goodColW = 255;
      break;
    case 4: 
      goodColR = 245;
      goodColG = 7;
      goodColB = 225;
      goodColW = 0;
      break;
    case 5: 
      goodColR = 245;
      goodColG = 140;
      goodColB = 7;
      goodColW = 0;
      break;
    case 6: 
      goodColR = 2;
      goodColG = 133;
      goodColB = 142;
      goodColW = 0;
      break;
    case 7: 
      goodColR = 0;
      goodColG = 40;
      goodColB = 160;
      goodColW = 255;
      break;
    case 8: 
      goodColR = 82;
      goodColG = 104;
      goodColB = 4;
      goodColW = 0;
      break;
    case 9: 
      goodColR = 120;
      goodColG = 50;
      goodColB = 130;
      goodColW = 0;
      break;
    default: 
      SetRgbwWheelVars(random(255));
      goodColR = wheelR;
      goodColG = wheelG;
      goodColB = wheelB;
      goodColW = 0;
      break;
  }
}

void SetRgbwWheelVars(int WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    wheelR = 255 - WheelPos * 3;
    wheelG = 0;
    wheelB = WheelPos * 3;
    return;
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    wheelR = 0;
    wheelG = WheelPos * 3;
    wheelB = 255 - WheelPos * 3;
    return;
  }
  WheelPos -= 170;
  wheelR = WheelPos * 3;
  wheelG = 255 - WheelPos * 3;
  wheelB = 0;
  return;
}

void SetRgbwWhitePulse(int WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    wheelR = WheelPos * 3;
    wheelG = WheelPos * 3;
    wheelB = WheelPos * 3;
    return;
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    wheelR = 255 - WheelPos * 3;
    wheelG = 255 - WheelPos * 3;
    wheelB = 255 - WheelPos * 3;
    return;
  }
  wheelR = 0;
  wheelG = 0;
  wheelB = 0;
  return;
}

void SetRgbwWheelVarsBlueToWhite(int WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 128) {
    wheelR = 255 - WheelPos * 2;
    wheelG = 255 - WheelPos * 2;
    wheelB = WheelPos * 2;
    return;
  }
  WheelPos -= 128;
  wheelR = WheelPos * 2;
  wheelG = WheelPos * 2;
  wheelB = 255 - WheelPos * 3;
  return;
}

void setLedDirect(int led, byte r, byte g, byte b, int meh) {
  if (led > numLeds || led <0)
    return;
    
  setPixel(led, r, g, b, 0);  
  setPixel(led+181, r, g, b, 0);  
}

void setPixel(int pixNum, int r, int g, int b, int w) {

  r = r < 0 ? 0 : r;
  g = g < 0 ? 0 : g;
  b = b < 0 ? 0 : b;
  w = w < 0 ? 0 : w;

  r = r > 255 ? 255 : r;
  g = g > 255 ? 255 : g;
  b = b > 255 ? 255 : b;
  w = w > 255 ? 255 : w;

  // strip.setPixelColor(pixNum, r, g, b, w);
  rgbwLeds[pixNum].r = g;
  rgbwLeds[pixNum].g = r;
  rgbwLeds[pixNum].b = b;  
}
