#ifndef __DOCUMENT_WORDUNIT_HH__
#define __DOCUMENT_WORDUNIT_HH__
#include <QString>

struct wordUnit{
  wordUnit() : lineNo(0), wordNo(0), newLine(false) {}
  QString data;
  int x1;
  int y1;
  int x2;
  int y2;
  int lineNo;
  int wordNo;
  bool newLine;
};
#endif
