#ifndef __DOCUMENT_TESSRECOGNIZEBOX_HH__
#define __DOCUMENT_TESSRECOGNIZEBOX_HH__
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

class TessRecognizeBox{
public:
  Pix *inputImage;
  tesseract::TessBaseAPI process;
  tesseract::ResultIterator *voyager;
  tesseract::PageIteratorLevel wordLevel;
  
  void destroyImage();
  void destroyProcess();

};

#endif
