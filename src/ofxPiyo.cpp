#include "ofxPiyo.h"

Piyo::Piyo() {
  x = rand() % ofGetWidth();
  y = rand() % ofGetHeight();
  w = rand() % lim;
  h = rand() % lim;
  noisex = (rand()%1000)/10;
  noisey = (rand()%1000)/10;
  piyoimage.load("Piyo.png");
}

void Piyo::run() {
  if (ofGetFrameNum() % replaceframe == 0) {
    x = rand() % ofGetWidth();
    y = rand() % ofGetHeight();
    w = rand() % lim;
    h = rand() % lim;
  }
  noisex += 0.02;
  noisey += 0.02;
  ofColor(0, 0, 0, 50);
  piyoimage.draw(int(x+ofNoise(noisex)*50), int(y+ofNoise(noisey)*50), w, h);
}