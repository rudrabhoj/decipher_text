#include <Control/TesseractRecognize.hh>

#include <iostream>
#include <tesseract/baseapi.h>
#include <algorithm>
#include <QApplication>
#include <QImage>

TesseractRecognize::TesseractRecognize(ControlData *ctrData){
  localControl = ctrData;
}

void TesseractRecognize::recognize(QString pageLink, int pageIndex, bool recAllPages){
  if(recAllPages){
    multicoreBatchOcr();
  } else{
    singlePageOcr(pageLink, pageIndex);
  }
}

void TesseractRecognize::setUpdateConnector(std::function<void(int)> *fooInput){
  processUpdateConnector = fooInput;
}

void TesseractRecognize::multicoreBatchOcr(){
  int tdPatternLim, analyzeLim, i, j;

  setNextPage(0);
  createThreadPattern(getPagesLim());
  allocateOcrDT();

  tdPatternLim = threadPattern.length();

  //std::cout << tdPatternLim << std::endl;

  for(i = 0; i < tdPatternLim; i++){
    createThreads(threadPattern[i]);
    waitThreadsToFinish();
  }

  analyzeLim = tessRecList.length();

  for(i = 0; i < analyzeLim; i++) analyzePage(&tessRecList[i], i);

  sendDoneMessge();
}

void TesseractRecognize::singlePageOcr(QString pageLink, int pageIndex){
  TessRecognizeBox ocrNode;

  setPgThreads(1); //single page to OCR
  std::thread recThread(&TesseractRecognize::recDaemon, this, &ocrNode, pageLink);
  recThread.detach();

  waitThreadsToFinish();

  analyzePage(&ocrNode, pageIndex);
  sendDoneMessge();
}

void TesseractRecognize::waitThreadsToFinish(){
  while( getPgThreads() > 0 ){
    qApp->processEvents();

    (*processUpdateConnector)(getNextPage());
  }
}

void TesseractRecognize::createThreads(int lim){
  int j, x;

  setPgThreads(lim);
  executionList.clear();
  x = getNextPage();

  for(j = 0; j < lim; j++){
    int currentCount = x + j;
    TessRecognizeBox *currentTessRec = &(tessRecList[currentCount]);
    QString currentImg =  getImageAt(currentCount);

    executionList.push_back(std::thread(&TesseractRecognize::recDaemon, this, currentTessRec, currentImg));
  }

  std::for_each(executionList.begin(), executionList.end(), [](std::thread &t){
    t.detach();
  });

  setNextPage( x + lim );

  std::cout << "Next Page:" << getNextPage() << std::endl;
}

void TesseractRecognize::analyzePage(TessRecognizeBox *ocrUnit, int pageNo){
  char *word;
  int x1, y1, x2, y2;

  resetWord();
  resetLine();

  ocrUnit->voyager = ocrUnit->process->GetIterator();
  ocrUnit->wordLevel = tesseract::RIL_WORD;

  if(ocrUnit->voyager != 0){
    do{
      word = ocrUnit->voyager->GetUTF8Text(ocrUnit->wordLevel);
      if (ocrUnit->voyager->IsAtBeginningOf(tesseract::RIL_TEXTLINE) ) pushNewLine();
      if (ocrUnit->voyager->IsAtBeginningOf(tesseract::RIL_PARA)) pushNewLine();

      ocrUnit->voyager->BoundingBox(ocrUnit->wordLevel, &x1, &y1, &x2, &y2);

      appendWord(word, x1, y1, x2, y2, getLocalLine(), getLocalWord());

      nextWord();
      delete []word;
      word = nullptr;

    } while(ocrUnit->voyager->Next(ocrUnit->wordLevel));
  }

  ocrUnit->destroyProcess();
  pushToPage(pageNo);
  clearWord();
}

void TesseractRecognize::recDaemon(TessRecognizeBox *ocrUnit, QString page){
  char languageArg[425];
  char tessDataPath[1024];

  strcpy(languageArg, getLanguageSettings());
  strcpy(tessDataPath, getTessDataSettings());

  //ocrUnit->inputImage = pixRead(page.toUtf8().data());

  ocrUnit->inputImage = new QImage(page); //pixRead(page.toUtf8().data());


  if (ocrUnit->process->Init(tessDataPath, languageArg )){
    //Again, handle error here
  }

  ocrUnit->process->SetImage(ocrUnit->inputImage->bits(), ocrUnit->inputImage->width(),
                ocrUnit->inputImage->height(), 4, ocrUnit->inputImage->bytesPerLine());
  ocrUnit->process->Recognize(0);

  reducePgThreads();
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

void TesseractRecognize::clearWord(){
  wordList.clear();
}

void TesseractRecognize::allocateOcrDT(){
  int i, lim;

  tessRecList.clear();
  lim = getPagesLim();

  for (i = 0; i < lim; i++){
    TessRecognizeBox dummyBox;
    tessRecList.push_back(dummyBox);
  }
}

void TesseractRecognize::setNextPage(int val){
  nextPage = val;
}

int TesseractRecognize::getNextPage(){
  return nextPage;
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

  //std::cout << "Buffer at origin = " << buffer << std::endl;

  return buffer;
}

char* TesseractRecognize::getTessDataSettings(){
  char *buffer;
  QString tessData;

  tessData = localControl->getSetting()->getTessdataPath();
  buffer = new char[tessData.length() + 8]; //extra space for same reason as above ^
  QByteArray array = tessData.toLocal8Bit();
  strcpy(buffer, array.data());

  //std::cout << "TessData Path = " << buffer << std::endl;

  return buffer;
}

void TesseractRecognize::createThreadPattern(int noPages){
  int threadLim = std::thread::hardware_concurrency();
  int pagesLeft;

  threadPattern.clear(); //Empty previous calculations
  pagesLeft = noPages;

  while(true){
    if (pagesLeft <= threadLim){
      threadPattern.push_back(pagesLeft);
      break;
    } else {
      threadPattern.push_back(threadLim);
      pagesLeft -= threadLim;
    }
  }
}

void TesseractRecognize::setPgThreads(int threadNum){
  pageThreads = threadNum;
}

int TesseractRecognize::getPgThreads(){
  return pageThreads;
}

void TesseractRecognize::reducePgThreads(){
  std::lock_guard<std::mutex> lg(threadNumLock);
  pageThreads -= 1;
}

//Secondary Foreign Dependents
int TesseractRecognize::getPagesLim(){
  QList<Page> *localPageList;
  localPageList = getStoredPages();
  return (*localPageList).length();
}

void TesseractRecognize::pushToPage(int pageNo){
  QList<Page> *localPageList;
  localPageList = getStoredPages();
  (*localPageList)[pageNo].importOcr(wordList);
}

void TesseractRecognize::sendDoneMessge(){
  localControl->getPubSub()->publish("ocrProcessed");
}

QString TesseractRecognize::getImageAt(int index){
  QList<Page> *localPageList;
  localPageList = getStoredPages();

  return (*localPageList)[index].getFullDisplayLink();
}
