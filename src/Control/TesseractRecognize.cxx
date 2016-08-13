#include <Control/TesseractRecognize.hh>

#include <iostream>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

TesseractRecognize::TesseractRecognize(ControlData *ctrData){
  localControl = ctrData;
}

void TesseractRecognize::recognize(QString pageLink, int pageIndex){
  pageNumber = pageIndex;

  doRecognize(pageLink);
}

void TesseractRecognize::doRecognize(QString page){
  Pix *inputImage;
  char *word;
  int x1, y1, x2, y2;
  tesseract::TessBaseAPI process;
  tesseract::ResultIterator *voyager;
  tesseract::PageIteratorLevel wordLevel;

  inputImage = pixRead(page.toUtf8().data());

  if (inputImage == 0){
    //Implement error handling
  }

  if (process.Init("/usr/local/share/tessdata", getLanguageSettings() )){
    //Again, handle error here
  }

  process.SetImage(inputImage);
  process.Recognize(0);

  voyager = process.GetIterator();
  wordLevel = tesseract::RIL_WORD;

  if(voyager != 0){
    do{
      word = voyager->GetUTF8Text(wordLevel);
      if (voyager->IsAtBeginningOf(tesseract::RIL_TEXTLINE) ) pushNewLine();
      if (voyager->IsAtBeginningOf(tesseract::RIL_PARA)) pushNewLine();

      voyager->BoundingBox(wordLevel, &x1, &y1, &x2, &y2);

      appendWord(word, x1, y1, x2, y2);

      delete []word;

    } while(voyager->Next(wordLevel));
  }

  delete voyager;
  process.End();
  pixDestroy(&inputImage);


  std::cout << "Doing Recognizing " << page.toUtf8().data() << std::endl;

  pushToPage();

  sendDoneMessge();
}

void TesseractRecognize::pushNewLine(){
  wordUnit tmpUnit;

  tmpUnit.data = '\n';
  tmpUnit.x1 = 0;
  tmpUnit.y1 = 0;
  tmpUnit.x2 = 0;
  tmpUnit.y2 = 0;

  wordList.push_back(tmpUnit);
}


void TesseractRecognize::appendWord(char* inputWord, int a, int b, int c, int d){
  wordUnit tmpUnit;

  tmpUnit.data = inputWord;
  tmpUnit.x1 = a;
  tmpUnit.y1 = b;
  tmpUnit.x2 = c;
  tmpUnit.y2 = d;

  wordList.push_back(tmpUnit);
}

/*void TesseractRecognize::displayOutput(){
  int i, lim;

  lim = wordList.length();

  for (i = 0; i < lim; i++){
    std::cout << wordList[i].data.toUtf8().data() << " ";
  }
}
*/

//Primary Foreign Dependents
QList<Page>* TesseractRecognize::getStoredPages(){
  return localControl->getProjectManager()->emitPages();
}

char* TesseractRecognize::getLanguageSettings(){
  QString lang = localControl->getLanguage()->getLanguageArgument();
  QByteArray array = lang.toLocal8Bit();
  char *buffer = array.data();
  return buffer;
}

//Secondary Foreign Dependents
void TesseractRecognize::pushToPage(){
  QList<Page> *localPageList;
  localPageList = getStoredPages();
  (*localPageList)[pageNumber].importOcr(wordList);
}

void TesseractRecognize::sendDoneMessge(){
  localControl->getPubSub()->publish("ocrProcessed");
}