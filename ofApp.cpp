#include "ofApp.h"
#include "ofAppRunner.h"
#include "ofColor.h"
#include "ofGraphics.h"
#include "ofLog.h"
#include <climits>
#include <string>
//#define DEBUG_SHOWMOUSEPOS
//#define DEBUG_NOLOADJAPANESE

using namespace std;

//--------------------------------------------------------------
void ofApp::setup() {
  // Log
  ofLogToFile("Logs\\ISBNCTRLSYS.log", true);

  /*Me*/
  me.load("icon.png");
  /*Splash*/
  splash.load("splash.png");

  /*Load files*/
  // Put logo
  {
    ofBuffer buf = ofBufferFromFile("logo.txt");
    for (auto line : buf.getLines()) {
      cout << line << "\n";
    }
  }
  // isbnraw
  {
    ofBuffer buf = ofBufferFromFile("isbnraw.txt");
    for (auto line : buf.getLines()) {
      isbnraw.push_back(line);
    }
  }
  // isbnsold
  {
    ofBuffer buf = ofBufferFromFile("isbnsold.txt");
    isbnsoldstr.open("isbnsold.txt", ofFile::Append);
    for (auto line : buf.getLines()) {
      isbnsold.push_back(line);
    }
  }
  // isbnsoldtime
  {
    ofBuffer buf = ofBufferFromFile("isbnsoldtime.txt");
    isbnsoldtimestr.open("isbnsoldtime.txt", ofFile::Append);
    for (auto line : buf.getLines()) {
      isbnsoldtime.push_back(line);
    }
  }
  // isbncoupon
  {
    ofBuffer buf = ofBufferFromFile("isbncoupon.txt");
    isbncouponstr.open("isbncoupon.txt", ofFile::WriteOnly);
    cout << buf.getText() << "\n";
    for (auto line : buf.getLines()) {
      isbncoupon = stoi(line);
      break;
      // TODO: What the heck this code. I cant use iterator
    }
    if (isbncoupon < 0) { // If isbncoupon is undefined
      isbncoupon = 0;
    }
  }

  // Put sizes
  {
    cout << "isbnraw.size: " << isbnraw.size() << "\n";
    cout << "isbnsold.size: " << isbnsold.size() << "\n";
    cout << "isbnsoldtime.size: " << isbnsoldtime.size() << "\n";
    cout << "isbncoupon: " << isbncoupon << "\n";

    ofLogNotice() << "isbnraw.size: " << isbnraw.size();
    ofLogNotice() << "isbnsold.size: " << isbnsold.size();
    ofLogNotice() << "isbnsoldtime.size: " << isbnsoldtime.size();
    ofLogNotice() << "isbncoupon: " << isbncoupon;
  }

  // Error check
  {
    if (isbnsold.size() != isbnsoldtime.size()) {
      ofLogFatalError() << "isbnsold.size != isbnsoldtime.size";
      cout << "something wrong\n";
      ofExit();
    }
  }

  /*Font*/
  cout << "Load font(It may take some time. Solve maze pls)\n";
  {
    // buttonfont
    ofTrueTypeFontSettings fontsetting("Cica.ttf", 32);
    fontsetting.addRanges(ofAlphabet::Latin);
#ifndef DEBUG_NOLOADJAPANESE
    fontsetting.addRanges(
        ofAlphabet::Japanese); // ISSUE: This is toooooo heavy. idk light way
#endif
    font32jp.load(fontsetting);

    // showunixtimefont
    font16.load("Cica.ttf", 16);
  }

  /*button vars set*/
  buttonSet();
}

//--------------------------------------------------------------
void ofApp::update() {}

//--------------------------------------------------------------
void ofApp::draw() {
  if (0 < splashtime) {
    splashtime--;
    if (splashtime < 30)
      ofColor(0, 0, 0, (splashtime / 30.0) * 255);
    else
      ofColor(0, 0, 0);

    splash.draw(0, 0, ofGetWidth(), ofGetHeight());

    return;
  }
  if (screen == 0) { // Welcome page
    ofBackground(ofColor(0x28, 0x28, 0x28));
    if (welcome.run()) {
      screen = 1;
    }
    if (saveunixtime.run()) {
      writeNowUnixTime();
    }
    about.run();
  }
  if (screen == 1) { // Sold page
    ofBackground(ofColor(0x28, 0x28, 0x28));
    showISBNList(font32jp);

    if (allremove.run()) {
      removeISBNShowList();
    } // allremove button

    //    ofSetColor(0x92, 0x83, 0x74, 100);
    //    ofDrawLine(755, 0, 755, ofGetHeight()); // partation between left to
    //    right

    ofSetColor(0xeb, 0xdb, 0xb2);
    font32jp.drawString(u8"クーポンの数", 850,
                        40); // TODO: not perfect. use stringwidth

    if (couponnumsetter.run()) {
      updateISBNShowList();
    } // change coupon num

    subtotal.run();
    coupontotal.run();
    total.run();
    if (decision.run()) {
      cout << "do decision\n";
      decisionISBN();
    }

    notification.draw();

    me.draw(665, 380, 100, 100);
  }

  showUnixTime(font16);

  if (piyotr) {
    for (int i = 0; i < 15; i++)
      piyo[i].run();
  }

#ifdef DEBUG_SHOWMOUSEPOS
  showMousePos(font16);
#endif
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  if (key == 'h') {
    screen = 0;
  }

  if (key == 'p') {
    piyotr = !piyotr;
  }

  if (screen == 1) {
    if (key == '0') { isbninputbuf += "0"; }
    if (key == '1') { isbninputbuf += "1"; }
    if (key == '2') { isbninputbuf += "2"; }
    if (key == '3') { isbninputbuf += "3"; }
    if (key == '4') { isbninputbuf += "4"; }
    if (key == '5') { isbninputbuf += "5"; }
    if (key == '6') { isbninputbuf += "6"; }
    if (key == '7') { isbninputbuf += "7"; }
    if (key == '8') { isbninputbuf += "8"; }
    if (key == '9') { isbninputbuf += "9"; }

    if (key == ofKey::OF_KEY_UP) {
      if (0 < isbnshowliststartpos)
        isbnshowliststartpos--;
      updateISBNShowList();
    }
    if (key == ofKey::OF_KEY_DOWN) {
      if (isbnshowliststartpos < int(isbnlist.size()) - 5)
        isbnshowliststartpos++;
      updateISBNShowList();
    }

    if (key == ofKey::OF_KEY_RETURN) {
      if (isbninputbuf != "") {           // if isbninputbuf is not empty
        isbnlist.push_back(isbninputbuf); // add to isbnlist
        isbninputbuf = "";                // clear isbninputbuf
        updateISBNShowList();             // update isbn show list
        isbnshowliststartpos =
            max(0, int(isbnlist.size()) - 5); // Update isbnsholiststartpos
      }
    }

    if (key == ofKey::OF_KEY_ESC) {
      removeISBNShowList();
    }

    if (key == ofKey::OF_KEY_F11) {
      fullscreentr = !fullscreentr;
      ofSetFullscreen(fullscreentr);
    }
  }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}

/*Made by myself functions*/

//--------------------------------------------------------------
void ofApp::buttonSet() {
  // Screen 0
  welcome.set(ofGetWidth() / 2 - 200, ofGetHeight() / 2 - 100, 400, 200,
              ofColor(0xeb, 0xdb, 0xb2), ofColor(0x28, 0x28, 0x28), font32jp,
              u8"お仕事をはじめる");
  saveunixtime.set(900, 450, 200, 100, ofColor(0xeb, 0xdb, 0xb2),
                   ofColor(0x28, 0x28, 0x28), font16, u8"Save unixtime");
  about.set(100, 450, 350, 100, ofColor(0xeb, 0xdb, 0xb2),
            ofColor(0x28, 0x28, 0x28), font16, "github.com/NULLCT/ISBNCTRLSYS");

  // Screen 1
  isbnshowlist.resize(5);
  isbnshowlistatpos.resize(5);
  for (int i = 0; i < isbnshowlist.size(); i++) {
    isbnshowlist[i].set(100, 50 + i * 100, 500, 64, ofColor(0xeb, 0xdb, 0xb2),
                        ofColor(0x28, 0x28, 0x28), font16, "");
    isbnshowlistatpos[i].set(50, 50 + i * 100, 90, 64,
                             ofColor(0xa8, 0x99, 0x84),
                             ofColor(0x28, 0x28, 0x28), font16, "");
  }

  allremove.set(650, 50, 125, 300, ofColor(0xd7, 0x99, 0x21),
                ofColor(0x28, 0x28, 0x28), font32jp, u8"入力\n削除");

  couponnumsetter.set(800, 50, 350, 75, 0, INT_MAX, ofColor(0xa8, 0x99, 0x84),
                      font32jp);

  subtotal.set(800, 150, 350, 50, ofColor(0xeb, 0xdb, 0xb2),
               ofColor(0x28, 0x28, 0x28), font32jp, u8"小計:0円");
  coupontotal.set(800, 250, 350, 50, ofColor(0xeb, 0xdb, 0xb2),
                  ofColor(0x28, 0x28, 0x28), font32jp, u8"クーポン:0円");
  total.set(800, 350, 350, 50, ofColor(0x68, 0x9d, 0x6a),
            ofColor(0x28, 0x28, 0x28), font32jp, u8"総計:0円");
  decision.set(800, 450, 350, 100, ofColor(0x45, 0x85, 0x88),
               ofColor(0x28, 0x28, 0x28), font32jp, u8"確定");

  notification.set(font32jp);
}

//--------------------------------------------------------------
void ofApp::showISBNList(ofTrueTypeFont &_font) {
  ofSetColor(255, 255, 255, 100);
  for (int i = 1; i < isbnshowlist.size(); i++) { // show patation
    ofDrawLine(40, 32 + i * 100, 610, 32 + i * 100);
  }

  for (auto i : isbnshowlist) { // show isbnlist
    i.run();
  }

  for (auto i : isbnshowlistatpos) { // show isbnlistatpos
    i.run();
  }

  ofSetColor(255, 255, 255, 200);
  ofDrawLine(30, 532, 620, 532); // show underline of list

  _font.drawString(to_string(isbnlist.size()) + u8"冊", 60, 575);
}

//--------------------------------------------------------------
void ofApp::showUnixTime(ofTrueTypeFont &_font) {
  ofSetColor(255, 255, 255, 100);
  _font.drawString("UnixTime: " + to_string(time(NULL)), 0, 15);
}

//--------------------------------------------------------------
void ofApp::showMousePos(ofTrueTypeFont &_font) {
  ofSetColor(255, 255, 255, 100);
  ofDrawLine(0, ofGetMouseY(), ofGetWidth(), ofGetMouseY());  // x // line
  ofDrawLine(ofGetMouseX(), 0, ofGetMouseX(), ofGetHeight()); // y // line

  _font.drawString(to_string(ofGetMouseX()) + ":" + to_string(ofGetMouseY()), 0,
                   ofGetHeight());
}

void ofApp::updateISBNShowList() {
  // reset isbnshowlist* text
  for (auto i : isbnshowlist) {
    i.text = "";
  }
  for (auto i : isbnshowlistatpos) {
    i.text = "";
  }

  isbninputbuf = "";

  for (int i = 0; i < min(5, int(isbnlist.size())); i++) {
    isbnshowlist[i].text = isbnlist[i + isbnshowliststartpos];
    isbnshowlistatpos[i].text = to_string(isbnshowliststartpos + i + 1);
  }

  subtotal.text = u8"小計:" + to_string(isbnlist.size() * bookcost) + u8"円";
  coupontotal.text =
      u8"クーポン:" + to_string(couponnumsetter.getNum() * bookcost) + u8"円";
  total.text =
      u8"総計:" +
      to_string((int(isbnlist.size()) - couponnumsetter.getNum()) * bookcost) +
      u8"円";
}

void ofApp::removeISBNShowList() {
  isbnlist.clear();
  isbnshowlist.clear();
  isbnshowlistatpos.clear();

  isbninputbuf.clear();
  isbnshowliststartpos = 0;

  couponnumsetter.setNum(0);

  isbnshowliststartpos = max(0, int(isbnlist.size()) - 5);

  buttonSet(); // TODO: is it true way? it can work but I dont like
  updateISBNShowList();
}

void ofApp::decisionISBN() {
  ofLogNotice() << "decisionISBN";

  if (isbnlist.size() == 0) {
    // ERROR
    cout << "isbnlist.size is 0\n";
    notification.back = ofColor(255, 0, 0);
    notification.notice(ofColor(0xcc, 0x24, 0x1d), ofColor(0xeb, 0xdb, 0xb2),
                        u8"入力が何もありません");
    ofLogError() << "isbnlist.size is 0";

    removeISBNShowList();
    return;
  }

  if (isbnlist.size() < couponnumsetter.getNum()) {
    cout << "too much coupon\n";
    notification.notice(ofColor(0xcc, 0x24, 0x1d), ofColor(0xeb, 0xdb, 0xb2),
                        u8"クーポン使いすぎ");
    ofLogError() << "too much coupon";

    removeISBNShowList();
    return;
  }

  // Check input nums
  for (auto i : isbnlist) {
    if (find(isbnraw.begin(), isbnraw.end(), i) != isbnraw.end() and
        find(isbnsold.begin(), isbnsold.end(), i) == isbnsold.end()) {
      cout << i << " is ACCEPT\n";
    } else {
      // ERROR
      cout << i << " is ERROR\n";
      notification.notice(
          ofColor(0xcc, 0x24, 0x1d), ofColor(0xeb, 0xdb, 0xb2),
          u8"本は登録されていないか既に売れています"); // TODO: more information
      ofLogError() << "not found in isbnraw or isbnsold";

      removeISBNShowList();
      return;
    }
  }

  for (auto i : isbnlist) {
    isbnsoldstr << i << "\n";
    isbnsold.push_back(i);
    isbnsoldtimestr << time(NULL) << "\n";
    isbnsoldtime.push_back(to_string(time(NULL)));
  }
  isbncoupon += couponnumsetter.getNum();
  cout << "coupon: " << isbncoupon << "\n";
  notification.notice(ofColor(0x98,0x97,0x1a), ofColor(0xeb, 0xdb, 0xb2), u8"売却しました");
  removeISBNShowList();
}

void ofApp::writeNowUnixTime() {
  ofLogNotice() << "writeNowUnixTime";

  ofFile timefile;
  timefile.open("Times\\Time_" + ofGetTimestampString() + ".txt",
                ofFile::WriteOnly);
  timefile << time(NULL);
}

ofApp::~ofApp() {
  isbncouponstr << isbncoupon; // save coupon
  ofLogNotice() << "ofApp's destructor was called";
}