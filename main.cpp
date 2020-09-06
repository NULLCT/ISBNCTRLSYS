#include "ofApp.h"
#include "ofMain.h"

int main() {
  ofSetEscapeQuitsApp(false);
  ofGLFWWindowSettings settings; // OpenFrameWorks setting

  settings.title =
      "ISBNCTRLSYS(github.com/NULLCT/ISBNCTRLSYS) | Made by NULLCT"; // Title
  settings.setSize(1200, 600);                                       // Size
  settings.resizable = false; // non resiable

  ofCreateWindow(settings);     // attach settings
  return ofRunApp(new ofApp()); // create ofApp
}
