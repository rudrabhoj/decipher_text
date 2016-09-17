#ifndef __DOCUMENT_TESSRECOGNIZEBOX_HH__
#define __DOCUMENT_TESSRECOGNIZEBOX_HH__
#include <tesseract/baseapi.h>
#include <QImage>

class TessRecognizeBox{
public:
  TessRecognizeBox();

  QImage *inputImage;
  tesseract::TessBaseAPI *process;
  tesseract::ResultIterator *voyager;
  tesseract::PageIteratorLevel wordLevel;

  void destroyProcess();
  void destroyImage();

};

#endif
