#include "ofxNumSetter.h"

void ofxNumSetter::set(int _x, int _y, int _w, int _h, int _limunder,
                       int _limupper, ofColor _arrowcolor,
                       ofTrueTypeFont &_font) {
  x = _x;
  y = _y;
  w = _w;
  h = _h;
  limunder = _limunder;
  limupper = _limupper;
  arrowcolor = _arrowcolor;
  font = _font;
}

bool ofxNumSetter::run() {
  bool tr = false;
  // draw twice triangle
  ofSetColor(arrowcolor);
  if (isFocusRightArrow()) {
    ofSetColor(arrowcolor.r + 10, arrowcolor.g + 10, arrowcolor.b + 10);
    if (ofGetMousePressed()) {
      if (!clicktrigger) {
        clicktrigger = true;
        if (num < limupper) {
          num++;
          tr = true;
        }
      }
    } else {
      clicktrigger = false;
    }
  }
  ofDrawTriangle((x + w) - w * 0.2, y, (x + w) - w * 0.2, y + h, x + w,
                 y + h / 2); // right

  if (isFocusLeftArrow()) {
    ofSetColor(arrowcolor.r + 10, arrowcolor.g + 10, arrowcolor.b + 10);
    if (ofGetMousePressed()) {
      if (!clicktrigger) {
        clicktrigger = true;
        if (limunder < num) {
          num--;
          tr = true;
        }
      }
    } else {
      clicktrigger = false;
    }
  }
  ofDrawTriangle(x, y + h / 2, x + w * 0.2, y, x + w * 0.2, y + h); // left

  // draw center box
  ofSetColor(0xeb, 0xdb, 0xb2);
  ofDrawRectangle(x + w * 0.25, y, w * 0.5, h);

  // draw num
  ofSetColor(0x28, 0x28, 0x28);
  font.drawString(to_string(num),
                  ((w * 0.5) - font.stringWidth(to_string(num))) / 2 + x +
                      w * 0.25,
                  (h + font.stringHeight(to_string(num))) / 2 + y);

  return tr;
}

bool ofxNumSetter::isFocusLeftArrow() {
  return (x <= ofGetMouseX() and ofGetMouseX() <= x + w * 0.2) and
         (y <= ofGetMouseY() and ofGetMouseY() <= y + h);
}

bool ofxNumSetter::isFocusRightArrow() {
  return ((x + w * 0.8) <= ofGetMouseX() and ofGetMouseX() <= x + w) and
         (y <= ofGetMouseY() and ofGetMouseY() <= y + h);
}

int ofxNumSetter::getNum() { return num; }

void ofxNumSetter::setNum(int _num) { num = _num; }
