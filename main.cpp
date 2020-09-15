#include "ofApp.h"
#include "ofAppRunner.h"
#include "ofMain.h"
#include "ofWindowSettings.h"

int main() {
  srand(time(NULL));
  ofSetEscapeQuitsApp(false);

  ofSetupOpenGL(1200,600,OF_WINDOW);
  ofSetWindowTitle("ISBNCTRLSYSv1.1(github.com/NULLCT/ISBNCTRLSYS) | Made by NULLCT");

  return ofRunApp(new ofApp()); // create ofApp
}
