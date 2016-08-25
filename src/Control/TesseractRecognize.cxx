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
  char languageArg[425];
  int x1, y1, x2, y2;
  tesseract::TessBaseAPI process;
  tesseract::ResultIterator *voyager;
  tesseract::PageIteratorLevel wordLevel;

  resetWord();
  resetLine();

  /* Would be helpful to actually delete the dynamically allocated
   * string we get from getLanguageSettings,
   * but horrible errors I got while convertng QString to char *
   * safely, would want me to look at it later.
   * few bytes a session would leak otherwise.
   */
  strcpy(languageArg, getLanguageSettings());

  inputImage = pixRead(page.toUtf8().data());

  if (inputImage == 0){
    //Implement error handling
  }

  std::cout << "Buffer at function = " << languageArg << std::endl;

  if (process.Init("/usr/local/share/tessdata", languageArg )){
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

      appendWord(word, x1, y1, x2, y2, getLocalLine(), getLocalWord());

      nextWord();
      delete []word;

    } while(voyager->Next(wordLevel));
  }

  delete voyager;
  process.End();
  pixDestroy(&inputImage);


  std::cout << "Doing Recognizing " << page.toUtf8().data() << std::endl;

  pushToPage();

  resetWord();
  resetLine();

  sendDoneMessge();
}



int TesseractRecognize::getLocalLine(){
  return localLine;
}

int TesseractRecognize::getLocalWord(){
  return localWord;
}
void TesseractRecognize::nextLine(){
  localLine += 1;
  resetWord();
}

void TesseractRecognize::nextWord(){
  localWord += 1;
}

void TesseractRecognize::resetWord(){
  localWord = 0;
}

void TesseractRecognize::resetLine(){
  localLine = 0;
}

void TesseractRecognize::pushNewLine(){
  wordUnit tmpUnit;

  tmpUnit.data = '\n';
  tmpUnit.x1 = 0;
  tmpUnit.y1 = 0;
  tmpUnit.x2 = 0;
  tmpUnit.y2 = 0;
  tmpUnit.newLine = true;

  nextLine();

  wordList.push_back(tmpUnit);
}


void TesseractRecognize::appendWord(char* inputWord, int a, int b, int c, int d, int lineNo, int wordNo){
  wordUnit tmpUnit;

  tmpUnit.data = inputWord;
  tmpUnit.x1 = a;
  tmpUnit.y1 = b;
  tmpUnit.x2 = c;
  tmpUnit.y2 = d;

  tmpUnit.lineNo = lineNo;
  tmpUnit.wordNo = wordNo;

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
  char *buffer;

  QString lang = localControl->getLanguage()->getLanguageArgument();
  buffer = new char[lang.length() + 8]; //extra space for safety. Remove if you want.
  QByteArray array = lang.toLocal8Bit();
  strcpy(buffer, array.data());

  std::cout << "Buffer at origin = " << buffer << std::endl;

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
