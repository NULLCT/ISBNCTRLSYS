#pragma once
#include "ofMain.h"
#include <limits>

#include "ofxButton.h"
#include "ofxNotification.h"
#include "ofxNumSetter.h"
#include "ofxPiyo.h"
/*
TODO:

*/
class ofApp : public ofBaseApp {
public:
  void setup();
  void update();
  void draw();
  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y);
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void mouseEntered(int x, int y);
  void mouseExited(int x, int y);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);

  /*Made by myself functions*/
  void buttonSet();
  void showISBNList(ofTrueTypeFont &_font);
  void showUnixTime(ofTrueTypeFont &_font);
  void showMousePos(ofTrueTypeFont &_font);
  void updateISBNShowList();
  void removeISBNShowList();
  void decisionISBN();
  void writeNowUnixTime();
  ~ofApp();

private:
  /*Screen control*/
  int screen = 0; // 0=>welcome page, 1=>sold page
  bool fullscreentr = false;

  /*Splash Image*/
  ofImage splash;
  int splashtime = 120;

  /*ISBN Date*/
  vector<string> isbnraw;      // List of isbn numbers in shop (isbnraw.txt)
  vector<string> isbnsold;     // List of sold book's isbn (isbnsold.txt)
  vector<string> isbnsoldtime; // List of the time when the book was sold
                               // (isbnsoldtime.txt)
  int isbncoupon = 0;          // Count how many coupon used (isbncoupon.txt)
  const int bookcost = 100;

  ofFile isbnsoldstr, isbnsoldtimestr, isbncouponstr;

  /*ISBN input system*/
  string isbninputbuf = ""; // type num will in this
  vector<string> isbnlist;  // isbninputbuf will in this when type return(enter)

  /*Font*/
  ofTrueTypeFont font32jp; // Font for ofxButton
  ofTrueTypeFont font16;   // Font for ofApp::showunixtime()

  /*Piyo*/
  Piyo piyo[15];
  bool piyotr = true;

  /*Me*/
  ofImage me;

  /*Buttons*/
  // screen: 0
  ofxButton welcome;      // "お仕事をはじめる" button
  ofxButton saveunixtime; // for save unix time
  ofxButton about;        // about me
  // screen: 1
  vector<ofxButton> isbnshowlist;      // is 5 best?
  vector<ofxButton> isbnshowlistatpos; // is 5 best?
  int isbnshowliststartpos = 0;

  ofxButton allremove;

  ofxNumSetter couponnumsetter;
  ofxButton subtotal;
  ofxButton coupontotal;
  ofxButton total;
  ofxButton decision;

  ofxNotification notification;
};
