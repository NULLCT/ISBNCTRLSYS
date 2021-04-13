#include "ofxButton.h"

ofxButton::ofxButton() { // Initialize vars
  x = y = w = h = 0;
  backcolor.r = backcolor.g = backcolor.b = 0;
  wordcolor.r = wordcolor.g = wordcolor.b = 0;
  text = "";
}

void ofxButton::set(
    int _x, int _y, int _w, int _h, ofColor _backcolor, ofColor _wordcolor,
    ofTrueTypeFont &_font,
    std::string _text) { // Set Button size pos color font and text
  x = _x;
  y = _y;
  w = _w;
  h = _h;
  backcolor = _backcolor;
  wordcolor = _wordcolor;
  font = _font;
  text = _text;
}

bool ofxButton::isfocus(void) { // if this focus => True
  return (x <= ofGetMouseX() and ofGetMouseX() <= x + w) and
         (y <= ofGetMouseY() and ofGetMouseY() <= y + h);
}

bool ofxButton::run(void) { // draw button and return bool if this click => True
  if (isfocus()) {
    ofSetColor(backcolor.r + 10, backcolor.g + 10, backcolor.b + 10);
    ofDrawRectangle(x, y, w, h);
    ofSetColor(wordcolor.r + 10, wordcolor.g + 10, wordcolor.b + 10);
    font.drawString(text, (w - font.stringWidth(text)) / 2 + x,
                    (h + font.stringHeight(text)) / 2 + y);
    if (ofGetMousePressed()) {
      if (!clicktriger) { // If this is not clicked befor
        clicktriger = true;
        return true;
      }
    } else {
      clicktriger = false;
    }
  } else {
    ofSetColor(backcolor);
    ofDrawRectangle(x, y, w, h);
    ofSetColor(wordcolor);
    font.drawString(text, (w - font.stringWidth(text)) / 2 + x,
                    (h + font.stringHeight(text)) / 2 + y);
  }
  return false;
}
