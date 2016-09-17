#include <Document/TessRecognizeBox.hh>
#include <iostream>

TessRecognizeBox::TessRecognizeBox(){
  process = new tesseract::TessBaseAPI();
  inputImage = nullptr;
}

void TessRecognizeBox::destroyImage(){
  delete inputImage;
  inputImage = nullptr;
}

void TessRecognizeBox::destroyProcess(){
  std::cout << "Destroying Process" << std::endl;

  process->Clear();
  process->End();
  //delete process;

  delete voyager;

  process = nullptr;
  voyager = nullptr;

  destroyImage();
}
