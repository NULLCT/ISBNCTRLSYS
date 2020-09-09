#pragma once

#include <time.h>

#include <random>

#include "ofMain.h"

class Piyo {
public:
  Piyo();
  void run();
  
  double noisex = 0, noisey = 0;

private:
  ofImage piyoimage;
  int lim = 200;
  int x, y, w, h;
  int replaceframe = 60 * 10;
};