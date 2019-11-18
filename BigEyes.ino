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

byte goodColR, goodColG, goodColB, goodColW;

int eyeX, eyeY; 
byte eyePrimaryR, eyePrimaryG, eyePrimaryB;
byte eyeSecondaryR, eyeSecondaryG, eyeSecondaryB;

// Adafruit_NeoPixel strip = Adafruit_NeoPixel(numLeds, PIN, NEO_RGB + NEO_KHZ800);
const int numLeds = 362;
CRGB rgbwLeds[362]; // 181 * 2

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

  eyeX=0;
  eyeY=0; 
  eyePrimaryR=80; 
  eyePrimaryG=80; 
  eyePrimaryB=80;
  eyeSecondaryR=0; 
  eyeSecondaryG=0; 
  eyeSecondaryB=0;   
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
 *     squiggles, shere khan eyes.
 * 
 * Fix stripes.
 *     
 * x Finish inputting coordinates
 * Some Christmassy patterns. Look at pac man animation, do 2 or 3 masks with 9 or 12, 4, 3 steps so they don't always concur.
 * do green blue white version of r g b 
 * Import the eye stuff, pac man etc, get it working
 * Stripes and others from 
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
    // doTwinkles();
    doSnowflake();
    //doConcentricRainbow2();
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

byte circleFirstLeds[9] = {0,48,88,120,144,160,172,180,181};

byte eyeCoords[181][2] = {
{100,178}, {110,177}, {119,175}, {129,172}, {137,168}, {145,162}, {153,155}, {159,148}, {164,141}, {168,132}, 
{171,123}, {172,114}, {173,105}, {172, 95}, {170, 87}, {167, 77}, {164, 68}, {158, 61}, {152, 53}, {145, 47}, 
{136, 42}, {127, 37}, {118, 35}, {109, 33}, {100, 32}, { 92, 33}, { 82, 35}, { 72, 37}, { 64, 42}, { 55, 47}, 
{ 49, 53}, { 43, 61}, { 38, 68}, { 34, 77}, { 30, 87}, { 28, 95}, { 27,105}, { 28,114}, { 30,123}, { 34,132}, 
{ 38,141}, { 43,148}, { 49,155}, { 55,162}, { 64,168}, { 72,172}, { 82,175}, { 92,177}, {100,167}, {110,166}, 
{120,164}, {130,160}, {138,155}, {146,147}, {152,140}, {157,132}, {160,124}, {162,114}, {163,105}, {162, 95}, 
{160, 86}, {157, 77}, {152, 68}, {146, 60}, {138, 54}, {130, 49}, {120, 45}, {110, 43}, {100, 42}, { 91, 43}, 
{ 81, 45}, { 72, 49}, { 63, 54}, { 56, 60}, { 49, 68}, { 44, 77}, { 41, 86}, { 39, 95}, { 38,105}, { 39,114}, 
{ 41,124}, { 44,132}, { 49,140}, { 56,147}, { 63,155}, { 72,160}, { 81,164}, { 91,167}, {100,157}, {112,156}, 
{122,153}, {130,148}, {140,141}, {145,133}, {150,124}, {152,114}, {154,105}, {152, 94}, {150, 85}, {145, 75}, 
{140, 68}, {130, 62}, {122, 56}, {112, 54}, {100, 52}, { 90, 54}, { 80, 56}, { 71, 62}, { 63, 68}, { 56, 75}, 
{ 52, 85}, { 49, 95}, { 48,105}, { 49,116}, { 52,126}, { 56,135}, { 63,143}, { 71,149}, { 80,154}, { 90,157}, 
{100,148}, {112,146}, {123,142}, {131,134}, {138,126}, {142,114}, {143,105}, {142, 93}, {138, 83}, {131, 74}, 
{123, 67}, {113, 63}, {100, 62}, { 88, 63}, { 79, 67}, { 70, 74}, { 63, 83}, { 59, 93}, { 57,105}, { 59,117}, 
{ 63,127}, { 70,136}, { 79,142}, { 88,146}, {100,138}, {113,137}, {124,128}, {132,118}, {134,105}, {132, 93}, 
{124, 83}, {112, 75}, {100, 72}, { 88, 75}, { 79, 83}, { 71, 93}, { 70,105}, { 71,118}, { 79,128}, { 88,137}, 
{100,127}, {112,125}, {122,112}, {124,105}, {122, 94}, {112, 86}, {100, 83}, { 90, 86}, { 82, 94}, { 80,105}, 
{ 82,112}, { 90,125}, {100,117}, {110,114}, {115,105}, {110, 97}, {100, 93}, { 94, 97}, { 89,105}, { 94,114}, 
{100,105} };
