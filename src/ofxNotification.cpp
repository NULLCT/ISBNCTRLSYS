#include "ofxNotification.h"

void ofxNotification::set(ofTrueTypeFont &_font) { font = _font; }

void ofxNotification::notice(ofColor _back, ofColor _word, string _text) {
  back = _back;
  word = _word;
  text = _text;

  drawtrigger = true;
  countframe = 0;
  ypos = -font.stringHeight(text);
  alpha = 200;
}

void ofxNotification::draw() {
  if (drawtrigger) {
    countframe++;
    if (countframe <= animelim) {
      ypos /= 1.2;
    } else {
      if (animelim * 1.5 < countframe) {
        drawtrigger = false;
      }
      alpha /= 1.2;
    }
    ofSetColor(back, alpha);
    ofDrawRectRounded(ofRectangle(100, ypos, ofGetWidth() - 200, 64), 16);
    ofSetColor(word, alpha);
    font.drawString(text,
                    ((ofGetWidth() - 200) - font.stringWidth(text)) / 2 + 100,
                    (64 + font.stringHeight(text)) / 2 + ypos);
  }
}