#ifndef __CONTROL_TESSERACTRECOGNIZE_HH__
#define __CONTROL_TESSERACTRECOGNIZE_HH__

#include <QString>
#include <QVector>
#include <QList>

#include <thread>
#include <mutex>
#include <functional>

#include <Document/wordUnit.hh>
#include <Document/TessRecognizeBox.hh>
#include <Control/ControlData.hh>
#include <Document/Page.hh>
#include <vector>

class TesseractRecognize{

public:
  TesseractRecognize(ControlData *ctrData);
  void recognize(QString pageLink, int pageIndex, bool recAllPages);
  void setUpdateConnector(std::function<void(int)> *fooInput);

private:
  ControlData *localControl;
  QVector<wordUnit> wordList;
  int nextPage;
  int pageThreads;
  std::vector<std::thread> executionList;
  QList<TessRecognizeBox> tessRecList;
  std::mutex threadNumLock;
  QList<int> threadPattern;
  std::function<void(int)> *processUpdateConnector;

  int localLine;
  int localWord;

  int getLocalLine();
  int getLocalWord();
  void nextLine();
  void nextWord();
  void resetWord();
  void resetLine();

  void singlePageOcr(QString pageLink, int pageIndex);
  void multicoreBatchOcr();
  void implementOCR(QString pageLink, int pageIndex, int pageNo);
  void analyzePage(TessRecognizeBox *ocrUnit, int pageNo);
  void recDaemon(TessRecognizeBox *ocrUnit, QString page);
  void waitThreadsToFinish();

  void pushNewLine();
  void appendWord(char* inputWord, int a, int b, int c, int d, int lineNo, int wordNo);
  void clearWord();

  void createThreadPattern(int noPages);
  void reducePgThreads();
  void setPgThreads(int threadNum);
  int getPgThreads();
  void allocateOcrDT();
  void createThreads(int lim);
  void setNextPage(int val);
  int getNextPage();


  //Foreign Dependents
  QList<Page> *getStoredPages();
  char* getLanguageSettings();
  char* getTessDataSettings();
  QString getImageAt(int index);

  int getPagesLim();
  void pushToPage(int pageNo);
  void sendDoneMessge();
};

#endif
