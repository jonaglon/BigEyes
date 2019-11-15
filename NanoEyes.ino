#include <Adafruit_NeoPixel.h>
#define PIN 4

// TODO / ToTRY - https://learn.adafruit.com/led-tricks-gamma-correction/the-quick-fix
// you didn't follow all the instructions properly so try this to see if it makes the colours, particularly rainbowses more betterer.

unsigned long timey, totalTimey, slowTimey, vSlowTimey, animLength;
int cycle;
const byte numLeds = 144;
const byte numPatterns = 25;
byte currentPattern = 0
byte wheelG;
byte wheelB;
bool cycling = true;
const bool testMode = false;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numLeds, PIN, NEO_RGB + NEO_KHZ800);

void setup() {
  pinMode(6, INPUT);
  digitalWrite(6, HIGH);
  randomSeed(analogRead(0));
  cycle=0;
  animLength=16384;   // 32864; // 8192; 
  strip.begin();
  strip.setBrightness(5);
  if (testMode) {
    Serial.begin(9600);
  }
}
 
void loop() {
  setTimes();
  checkButton();
  doLights();
  strip.show();
}


void setTimes() {
  totalTimey = millis();
  cycle = totalTimey / animLength;
  timey = totalTimey % animLength;
  slowTimey = totalTimey / 10;
  vSlowTimey = totalTimey / 100;  
}


void doLights() {
  allOff();
  // patterns 0 off, 1-6 twinkles, 7 off, 8-10 knightRider, 11-14 rainbows, 15 off.

  if (currentPattern < 1) {
    doAllPatternsOnRotation();
  } else if (currentPattern < 7) {
    doTwinkles();
  } else if (currentPattern < 8) {
    return;
  } else if (currentPattern < 9) {
    doKnightRiderLights();
  } else if (currentPattern < 10) {
    doKnightRiderLightsRainbow();
  } else if (currentPattern < 11) {
    doKnightRiderLightsMultiRainbow();
  } else if (currentPattern < 12) {
    doRainbows1();
  } else if (currentPattern < 13) {
    doRainbows2();
  } else if (currentPattern < 14) {
    doRainbows3();
  } else if (currentPattern < 15) {
    doRainbows4();
  } else if (currentPattern < 16) {
    return;
  } else if (currentPattern < 17) {
    doCycles();
  } else if (currentPattern < 18) {
    allOn(255, 0, 0, 0);
  } else if (currentPattern < 19) {
    allOn(0, 255, 0, 0);
  } else if (currentPattern < 20) {
    allOn(0, 0, 255, 0);
  } else if (currentPattern < 21) {
    allOn(0, 0, 0, 255);
  } else if (currentPattern < 22) {
    allOn(245,140,7, 50);
  } else if (currentPattern < 23) {
    allOn(245,7,225, 0);
  } else if (currentPattern < 24) {
    allOn(40, 133, 142, 50);
  } else if (currentPattern < 25) {
    allOn(82,104,40, 25);
  } else {
    return;
  }
}

byte currentPatternCycle = 1;
void doAllPatternsOnRotation() {
  byte patternCycle = cycle%14;

  if (patternCycle != currentPatternCycle) {
    if (patternCycle == 0) {
      setupNewTwinklePattern(1);
    } else if (patternCycle == 3) {
      setupNewTwinklePattern(2);
    } else if (patternCycle == 7) {
      setupNewTwinklePattern(3);
    } else if (patternCycle == 9) {
      setupNewTwinklePattern(4);
    } else if (patternCycle == 11) {
      setupNewTwinklePattern(5);
    } else if (patternCycle == 13) {
      setupNewTwinklePattern(6);
    }
    currentPatternCycle = patternCycle;
  }

  if (patternCycle < 1) {
    doTwinkles();
  } else if (patternCycle < 2) {
    doRainbows2();
  } else if (patternCycle < 3) {
    doCycles();
  } else if (patternCycle < 4) {
    doTwinkles();
  } else if (patternCycle < 5) {
    doKnightRiderLightsRainbow();
  } else if (patternCycle < 6) {
    doRainbows1();
  } else if (patternCycle < 7) {
    doKnightRiderLightsMultiRainbow();
  } else if (patternCycle < 8) {
    doTwinkles();
  } else if (patternCycle < 9) {
    doRainbows4();
  } else if (patternCycle < 10) {
    doTwinkles();
  } else if (patternCycle < 11) {
    doKnightRiderLights();
  } else if (patternCycle < 12) {
    doTwinkles();
  } else if (patternCycle < 13) {
    doRainbows3();
  } else if (patternCycle < 14) {
    doTwinkles();
  }
 
}

bool buttonPressed = false;
void checkButton() {
  int buttonState = digitalRead(6);
  if (buttonState==0 && buttonPressed==false) {
    buttonPressed = true;
    currentPattern=(currentPattern+1)%(numPatterns+1);
    if (currentPattern < 7) {
      setupNewTwinklePattern(currentPattern);
    }
  } else if (buttonState!=0 && buttonPressed==true) {
    buttonPressed = false;    
  }
}

struct twinkle {
  short ledNum;
  byte rCol;
  byte gCol;
  byte bCol;
  byte rToCol;
  byte gToCol;
  byte bToCol;
  int start;
  int lengthy;
  short widthy;
  int fadeIn;
  int fadeOut;
  short speedy;
  short sideFade; 
  bool hasTwinked;

  twinkle(short aLedNum, byte aRCol, byte aGCol, byte aBCol, byte aToRCol, byte aToGCol, byte aToBCol, int aStart, int aLengthy, int aWidthy, int aFadeIn, int aFadeOut, short aSpeedy, short aSideFade, bool aHasTwinked) :
    ledNum(aLedNum), rCol(aRCol), gCol(aGCol), bCol(aBCol), rToCol(aToRCol), gToCol(aToGCol), bToCol(aToBCol), start(aStart), lengthy(aLengthy), widthy(aWidthy), fadeIn(aFadeIn), fadeOut(aFadeOut), speedy(aSpeedy), sideFade(aSideFade), hasTwinked(aHasTwinked) {  }

  twinkle() : ledNum(0), rCol(0), gCol(0), bCol(0), rToCol(0), gToCol(0), bToCol(0), start(0), lengthy(0), widthy(0), fadeIn(0), fadeOut(0), speedy(0), sideFade(0), hasTwinked(0) { }

};

const int numTwinks = 40;
twinkle myTwinkles[numTwinks];
const int usedTwinkleCount[] = {40, 40, 40, 40, 40, 40, 40, 40};

const byte sineWaveLUT[200] = {
72,74,77,79,81,83,85,88,90,92,
94,96,99,101,103,105,107,109,111,112,
114,116,118,120,121,123,124,126,127,129,
130,132,133,134,135,136,137,138,139,140,
140,141,142,142,143,143,143,144,144,144,
144,144,144,144,143,143,143,142,142,141,
140,140,139,138,137,136,135,134,133,132,
130,129,127,126,124,123,121,120,118,116,
114,112,111,109,107,105,103,101,99,96,
94,92,90,88,85,83,81,79,77,74,
72,70,67,65,63,61,59,56,54,52,
50,48,45,43,41,39,37,35,33,32,
30,28,26,24,23,21,20,18,17,15,
14,12,11,10,9,8,7,6,5,4,
4,3,2,2,1,1,1,0,0,0,
0,0,0,0,1,1,1,2,2,3,
4,4,5,6,7,8,9,10,11,12,
14,15,17,18,20,21,23,24,26,28,
30,32,33,35,37,39,41,43,45,48,
50,52,54,56,59,61,63,65,67,70 };
