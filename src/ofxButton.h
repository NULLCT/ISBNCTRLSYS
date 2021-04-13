#pragma once

#include <algorithm>
#include <iostream>
#include <string>

#include "ofMain.h"

class ofxButton {
public:
  std::string text;
  int x, y, w, h;
  ofColor backcolor, wordcolor;
  ofTrueTypeFont font;

  ofxButton();
  void set(int _x, int _y, int _w, int _h, ofColor _backcolor,
           ofColor _wordcolor, ofTrueTypeFont &_font, std::string _text);
  bool isfocus(void);
  bool run(void);

private:
  bool clicktriger;
};
