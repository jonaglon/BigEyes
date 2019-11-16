#include<Arduino.h>
#include<Wire.h>
#include<FastLED.h>

unsigned long timey, totalTimey, slowTimey, vSlowTimey, animLength;
int cycle;
const byte numPatterns = 25;
byte currentPattern = 0;
byte wheelR;
byte wheelG;
byte wheelB;
bool cycling = true;
const bool testMode = false;

int eyeX, eyeY; 
byte eyePrimaryR, eyePrimaryG, eyePrimaryB;
byte eyeSecondaryR, eyeSecondaryG, eyeSecondaryB;

// Adafruit_NeoPixel strip = Adafruit_NeoPixel(numLeds, PIN, NEO_RGB + NEO_KHZ800);
const int numLeds = 360;
CRGB rgbwLeds[360]; // 180 * 2

void setup() {
  pinMode(6, INPUT);
  digitalWrite(6, HIGH);
  randomSeed(analogRead(0));
  cycle=0;
  animLength=16384;   // 32864; // 8192; 
  LEDS.addLeds<WS2811, 25>(rgbwLeds, 360); // Hardcoded to ports:25,26,27,28,14,15
  LEDS.setBrightness(30); // 128 good max, 255 actual /max
  if (testMode) {
    Serial.begin(9600);
  }

  eyeX=50;
  eyeY=50; 
  eyePrimaryR=0; 
  eyePrimaryG=0; 
  eyePrimaryB=0;
  eyeSecondaryR=100; 
  eyeSecondaryG=100; 
  eyeSecondaryB=100;   
  setupNewTwinklePattern(1);
}
 
void loop() {
  setTimes();
  //checkButton();
  doLights();
  LEDS.show();
}

/*
 * Circle todo list
 * Make patterns which use the circles 
 *     concentric
 *     squiggles, shere khan eyes
 *     
 * Finish inputting coordinates
 * Some Christmassy patterns
 * Import the eye stuff and get it working
 */

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
    // doAllPatternsOnRotation();
    // TODO! This is just the test pattern.
    // doNormalEyes();
    // doRainbows2();
    doTwinkles();
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
94,97,100,103,106,109,112,115,117,120,
123,126,129,131,134,137,139,142,144,147,
149,152,154,156,158,160,163,165,166,168,
170,172,173,175,176,178,179,180,181,182,
183,184,185,186,186,187,187,188,188,188,
188,188,188,188,187,187,186,186,185,184,
183,182,181,180,179,178,176,175,173,172,
170,168,166,165,163,160,158,156,154,152,
149,147,144,142,139,137,134,131,129,126,
123,120,117,115,112,109,106,103,100,97,
94,91,88,85,82,79,76,73,71,68,
65,62,59,57,54,51,49,46,44,41,
39,36,34,32,30,28,25,23,22,20,
18,16,15,13,12,10,9,8,7,6,
5,4,3,2,2,1,1,0,0,0,
0,0,0,0,1,1,2,2,3,4,
5,6,7,8,9,10,12,13,15,16,
18,20,22,23,25,28,30,32,34,36,
39,41,44,46,49,51,54,57,59,62,
65,68,71,73,76,79,82,85,88,91 };


int eyeCoords[188][2] = {
  {  0,   0}, {  0,   0}, {  0,   0}, {  0,  0}, {  0,  0}, {  0,  0}, {  0,  0}, {  0,  0}, {  0,  0}, {  0,  0},
  {  0,   0}, {  0,   0}, {  0,   0}, {  0,  0}, {  0,  0}, {  0,  0}, {  0,  0}, {  0,  0}, {  0,  0}, {  0,  0},
  {  0,   0}, {  0,   0}, {  0,   0}, {  0,  0}, {  0,  0}, {  0,  0}, {  0,  0}, {  0,  0}, {  0,  0}, {  0,  0},
  {  0,   0}, {  0,   0}, {  0,   0}, {  0,  0}, {  0,  0}, {  0,  0}, {  0,  0}, {  0,  0}, {  0,  0}, {  0,  0},
  {  0,   0}, {  0,   0}, {  0,   0}, {  0,  0}, {  0,  0}, {  0,  0}, {  0,  0}, {  0,  0}, {  0,  0}, {  0,  0},
  {  0,   0}, {  0,   0}, {  0,   0}, {  0,  0}, {  0,  0}, {  0,  0}, {  0,  0}, {  0,  0}, {  0,  0}, {  0,  0},
  {  0,   0}, {  0,   0}, {  0,   0}, {  0,  0}, {  0,  0}, {  0,  0}, {  0,  0}, {  0,  0}, {  0,  0}, {  0,  0},
  {  0,   0}, {  0,   0}, {  0,   0}, {  0,  0}, {  0,  0}, {  0,  0}, {  0,  0}, {  0,  0}, {  0,  0}, {  0,  0},
  {  0,   0}, {  0,   0}, {  0,   0}, {  0,  0}, {  0,  0}, {  0,  0}, {  0,  0}, {  0,  0}, {  0,  0}, {  0,  0},
  {  0,   0}, {  0,   0}, {  0,   0}, {  0,  0}, {  0,  0},
  
  { 55, 107}, { 64, 106}, { 75, 104}, { 84, 98}, { 92, 93}, { 98, 85}, {103, 76}, {107, 66}, {108, 56}, {107, 45},
  {103, 35}, { 98, 27}, { 92, 18}, { 84, 12}, { 75,  7}, { 64,  3}, { 55,  2}, { 45,  3}, { 35,  7}, { 26, 12},
  { 18, 18}, { 12, 27}, {  7, 35}, {  4, 45}, {  3, 56}, {  4, 66}, {  7, 76}, { 12, 85}, { 18, 93}, { 26, 98},
  { 35, 104}, { 45, 106}, { 55, 98}, { 66, 97}, { 76, 92}, { 85, 86}, { 91, 77}, { 96, 66}, { 97, 55}, { 96, 44},
  { 91, 35}, { 84, 26}, { 76, 18}, { 66, 14}, { 55, 13}, { 45, 14}, { 34, 18}, { 26, 26}, { 18, 35}, { 14, 44},
  { 12, 55}, { 14, 66}, { 18, 77}, { 25, 85}, { 34, 92}, { 44, 97}, { 55, 88}, { 67, 86}, { 77, 78}, { 85, 68},
  { 87, 55}, { 85, 43}, { 77, 33}, { 67, 25}, { 55, 23}, { 43, 25}, { 32, 33}, { 25, 43}, { 23, 55}, { 25, 68},
  { 32, 78}, { 43, 86}, { 55, 78}, { 66, 75}, { 74, 67}, { 77, 55}, { 75, 44}, { 67, 36}, { 55, 33}, { 44, 36},
  { 36, 44}, { 33, 55}, { 35, 67}, { 43, 75}, { 55, 68}, { 64, 64}, { 67, 55}, { 64, 47}, { 55, 43}, { 46, 47},
  { 43, 55}, { 46, 64}, { 55, 55}
}; 
