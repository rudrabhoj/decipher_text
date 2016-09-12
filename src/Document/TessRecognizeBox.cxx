#include <Document/TessRecognizeBox.hh>

void TessRecognizeBox::destroyImage(){
  pixDestroy(&inputImage);
}

void TessRecognizeBox::destroyProcess(){
  process.End();
  delete voyager;
}
