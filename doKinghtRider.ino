
void doKnightRiderLights() {
  int thing = (timey/10) % 200;
  int theLed = sineWaveLUT[thing];
  setPixel(theLed-11, 2, 0, 0, 0);
  setPixel(theLed-10, 10, 0, 0, 0);
  setPixel(theLed-9, 20, 0, 0, 0);
  setPixel(theLed-8, 40, 0, 0, 0);
  setPixel(theLed-7, 60, 0, 0, 0);
  setPixel(theLed-6, 90, 0, 0, 0);
  setPixel(theLed-5, 130, 0, 0, 0);
  setPixel(theLed-4, 180, 0, 0, 0);
  setPixel(theLed-3, 210, 0, 0, 0);
  setPixel(theLed-2, 255, 0, 0, 0);
  setPixel(theLed-1, 255, 0, 0, 0);
  setPixel(theLed, 255, 0, 0, 0);
  setPixel(theLed+1, 255, 0, 0, 0);
  setPixel(theLed+2, 255, 0, 0, 0);
  setPixel(theLed+3, 210, 0, 0, 0);
  setPixel(theLed+4, 180, 0, 0, 0);
  setPixel(theLed+5, 130, 0, 0, 0);
  setPixel(theLed+6, 90, 0, 0, 0);
  setPixel(theLed+7, 60, 0, 0, 0);
  setPixel(theLed+8, 40, 0, 0, 0);
  setPixel(theLed+9, 20, 0, 0, 0);
  setPixel(theLed+10, 10, 0, 0, 0);
  setPixel(theLed+11, 2, 0, 0, 0);
}


void doKnightRiderLightsRainbow() {
  int sinLookupTablePos = slowTimey % 200;
  int theLed = sineWaveLUT[sinLookupTablePos];

  SetRgbwWheelVars(slowTimey%255);

  setPixel(theLed-20, wheelR-145, wheelG-145, wheelB-145, 0);
  setPixel(theLed-19, wheelR-135, wheelG-135, wheelB-135, 0);
  setPixel(theLed-18, wheelR-125, wheelG-125, wheelB-125, 0);
  setPixel(theLed-17, wheelR-115, wheelG-115, wheelB-115, 0);
  setPixel(theLed-16, wheelR-105, wheelG-105, wheelB-105, 0);
  setPixel(theLed-15, wheelR-95, wheelG-95, wheelB-95, 0);
  setPixel(theLed-14, wheelR-85, wheelG-85, wheelB-85, 0);
  setPixel(theLed-13, wheelR-75, wheelG-75, wheelB-75, 0);
  setPixel(theLed-12, wheelR-65, wheelG-65, wheelB-65, 0);
  setPixel(theLed-11, wheelR-55, wheelG-55, wheelB-55, 0);
  setPixel(theLed-10, wheelR-50, wheelG-50, wheelB-50, 0);
  setPixel(theLed-9, wheelR-45, wheelG-45, wheelB-45, 0);
  setPixel(theLed-8, wheelR-40, wheelG-40, wheelB-40, 0);
  setPixel(theLed-7, wheelR-35, wheelG-35, wheelB-35, 0);
  setPixel(theLed-6, wheelR-30, wheelG-30, wheelB-30, 0);
  setPixel(theLed-5, wheelR-25, wheelG-25, wheelB-25, 0);
  setPixel(theLed-4, wheelR-20, wheelG-20, wheelB-20, 0);
  setPixel(theLed-3, wheelR-15, wheelG-15, wheelB-15, 0);
  setPixel(theLed-2, wheelR-10, wheelG-10, wheelB-10, 0);
  setPixel(theLed-1, wheelR-5, wheelG-5, wheelB-5, 0);
  setPixel(theLed, wheelR, wheelG, wheelB, 0);
  setPixel(theLed+1, wheelR-5, wheelG-5, wheelB-5, 0);
  setPixel(theLed+2, wheelR-10, wheelG-10, wheelB-10, 0);
  setPixel(theLed+3, wheelR-15, wheelG-15, wheelB-15, 0);
  setPixel(theLed+4, wheelR-20, wheelG-20, wheelB-20, 0);
  setPixel(theLed+5, wheelR-25, wheelG-25, wheelB-25, 0);
  setPixel(theLed+6, wheelR-30, wheelG-30, wheelB-30, 0);
  setPixel(theLed+7, wheelR-35, wheelG-35, wheelB-35, 0);
  setPixel(theLed+8, wheelR-40, wheelG-40, wheelB-40, 0);
  setPixel(theLed+9, wheelR-45, wheelG-45, wheelB-45, 0);
  setPixel(theLed+10, wheelR-50, wheelG-50, wheelB-50, 0);
  setPixel(theLed+11, wheelR-55, wheelG-55, wheelB-55, 0);
  setPixel(theLed+12, wheelR-65, wheelG-65, wheelB-65, 0);
  setPixel(theLed+13, wheelR-75, wheelG-75, wheelB-75, 0);
  setPixel(theLed+14, wheelR-85, wheelG-85, wheelB-85, 0);
  setPixel(theLed+15, wheelR-95, wheelG-95, wheelB-95, 0);
  setPixel(theLed+16, wheelR-105, wheelG-105, wheelB-105, 0);
  setPixel(theLed+17, wheelR-115, wheelG-115, wheelB-115, 0);
  setPixel(theLed+18, wheelR-125, wheelG-125, wheelB-125, 0);
  setPixel(theLed+19, wheelR-135, wheelG-135, wheelB-135, 0);
  setPixel(theLed+20, wheelR-145, wheelG-145, wheelB-145, 0);
}

void doKnightRiderLightsMultiRainbow() {
  int thing = (timey/10) % 200;
  int theLed1 = sineWaveLUT[thing];
  int theLed2 = (theLed1+35)%numLeds;
  int theLed3 = (theLed1+72)%numLeds;
  int theLed4 = (theLed1+108)%numLeds;

  SetRgbwWheelVars(slowTimey%255);
  knightRiderRainbowMultiInner(theLed1, wheelR, wheelG, wheelB);
  SetRgbwWheelVars((slowTimey+64)%255);
  knightRiderRainbowMultiInner(theLed2, wheelR, wheelG, wheelB);
  SetRgbwWheelVars((slowTimey+128)%255);
  knightRiderRainbowMultiInner(theLed3, wheelR, wheelG, wheelB);
  SetRgbwWheelVars((slowTimey+191)%255);
  knightRiderRainbowMultiInner(theLed4, wheelR, wheelG, wheelB);

}

void knightRiderRainbowMultiInner(byte theLed, byte rCol, byte gCol, byte bCol) {
  setPixel(theLed-11, rCol, gCol, bCol, 0);
  setPixel(theLed-10, rCol, gCol, bCol, 0);
  setPixel(theLed-9, rCol, gCol, bCol, 0);
  setPixel(theLed-8, rCol, gCol, bCol, 0);
  setPixel(theLed-7, rCol, gCol, bCol, 0);
  setPixel(theLed-6, rCol, gCol, bCol, 0);
  setPixel(theLed-5, rCol, gCol, bCol, 0);
  setPixel(theLed-4, rCol, gCol, bCol, 0);
  setPixel(theLed-3, rCol, gCol, bCol, 0);
  setPixel(theLed-2, rCol, gCol, bCol, 0);
  setPixel(theLed-1, rCol, gCol, bCol, 0);
  setPixel(theLed, rCol, gCol, bCol, 0);
  setPixel(theLed+1, rCol, gCol, bCol, 0);
  setPixel(theLed+2, rCol, gCol, bCol, 0);
  setPixel(theLed+3, rCol, gCol, bCol, 0);
  setPixel(theLed+4, rCol, gCol, bCol, 0);
  setPixel(theLed+5, rCol, gCol, bCol, 0);
  setPixel(theLed+6, rCol, gCol, bCol, 0);
  setPixel(theLed+7, rCol, gCol, bCol, 0);
  setPixel(theLed+8, rCol, gCol, bCol, 0);
  setPixel(theLed+9, rCol, gCol, bCol, 0);
  setPixel(theLed+10, rCol, gCol, bCol, 0);
  setPixel(theLed+11, rCol, gCol, bCol, 0);

}
