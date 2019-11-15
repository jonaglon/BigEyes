void doNormalEyes() {

  for(int j = 0; j < numLeds; j++) {
    setPixel(j, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
  }

  // iris
  drawEyeHexagon(55+eyeX, 55-eyeY, 26, 42, eyeSecondaryR, eyeSecondaryG, eyeSecondaryB, 0);

  // pupil
  drawEyeSquare(55+eyeX, 55-eyeY, 7, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);

  // doBlinking();
}

void drawEyeHexagon(int xCoord, int  yCoord, int pupilRadius, int maxRadius, int r, int g, int b, int w) {
  for (int j = 0; j < 93; j++) { 
    if ((eyeCoords[j][0] < (xCoord+pupilRadius)) && (eyeCoords[j][1] < (yCoord+pupilRadius))) {
      if ((eyeCoords[j][0] > (xCoord-pupilRadius)) && (eyeCoords[j][1] > (yCoord-pupilRadius))) {
        int x = quickAbsolute(xCoord-eyeCoords[j][0]);
        int y = quickAbsolute(yCoord-eyeCoords[j][1]);
        if (x + y < maxRadius) {
          setPixel(j+93, r, g, b, w);
        }
      }
    }
  }
}

void drawEyeSquare(int xCoord, int  yCoord, int radius, int r, int g, int b, int w) {
  for(int j = 0; j < 93; j++) { 
    if ((eyeCoords[j][0] < (xCoord+radius)) && (eyeCoords[j][1] < (yCoord+radius))) {
      if ((eyeCoords[j][0] > (xCoord-radius)) && (eyeCoords[j][1] > (yCoord-radius))) {
        setPixel(j+93, r, g, b, w);
      }
    }
  }
}
