#ifndef __CONTROL_TESSERACTRECOGNIZE_HH__
#define __CONTROL_TESSERACTRECOGNIZE_HH__

#include <QString>
#include <QVector>
#include <QList>

#include <Document/wordUnit.hh>
#include <Control/ControlData.hh>
#include <Document/Page.hh>

class TesseractRecognize{

public:
  TesseractRecognize(ControlData *ctrData);
  void recognize(QString pageLink, int pageIndex);

private:
  ControlData *localControl;
  int pageNumber;
  QVector<wordUnit> wordList;

  void doRecognize(QString page);
  void pushNewLine();
  void appendWord(char* inputWord, int a, int b, int c, int d);

  void pushToPage();
  QList<Page> *getStoredPages();
  void sendDoneMessge();

  //Foreign Dependents
  char* getLanguageSettings();
};

#endif