#ifndef __DOCUMENT_PAGE_HH__
#define __DOCUMENT_PAGE_HH__

#include <QString>
#include <QVector>
#include <Document/wordUnit.hh>
//#include <QFileInfo>

class Page{
public:
  Page(QString prjRoot, int pgIndex);
  void setFullDisplay();
  void setRefinedDisplay();
  QString getText();
  void appendWord(QString data, int x1, int y1, int x2, int y2);

  void importOcr(QVector<wordUnit> ocrImport);

  void setFileName(QString fname);
  QString getFullDisplayLink();
  QString getThumbLink();
  void interpretCurrentWord(int line, int pos);

  bool getOcrStatus();
  void setOcrStatus(bool staat);

  wordUnit currentWord;

private:
  int displayHead;
  int index;
  bool ocrStatus;

  QString dataX;
  QString projectRoot;
  QString imageRoot;
  QString imageFull;
  QString imageRefined;
  QString imageThumbnail;

  QString realName;
  QString fullLink;
  QString thumbLink;

  QVector<wordUnit> content;

  void setImagePaths();
  void createText();
  void setDisplayHead(int dHead);

  void defaultCurrentWord();
  QList<wordUnit> getLine(int line);
  wordUnit convertWord(QList<wordUnit> myLine, int position);

  void createThumbnail(); //Unimplemented until Imagemagick integration
  void createRefined(); //Unimplemented until Imagemagick integration
};

#endif
