#pragma once
#include "ofMain.h"

class ofxNumSetter {
public:
  void set(int _x, int _y, int _w, int _h, int _limunder, int _limupper,
           ofColor _arrowcolor, ofTrueTypeFont &_font);
  bool run();
  bool isFocusRightArrow();
  bool isFocusLeftArrow();
  int getNum();
  void setNum(int _num);

private:
  int num = 0;
  int limunder = 0, limupper = 0;
  int x, y, w, h;
  bool clicktrigger = false;
  ofColor arrowcolor;
  ofTrueTypeFont font;
};