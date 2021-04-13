#pragma once

#include "ofMain.h"

class ofxNotification {
public:
  void set(ofTrueTypeFont &_font);
  void notice(ofColor _back, ofColor _word, string _text);
  void draw();

  ofColor back, word;

private:
  const int animelim = 60 * 2;

  bool drawtrigger = false;

  int countframe;
  int ypos;
  int alpha;

  ofTrueTypeFont font;
  string text;
};