#ifndef __DOCUMENT_PAGE_H__
#define __DOCUMENT_PAGE_H__

#include <QString>
#include <QVector>
//#include <QFileInfo>

class Page{
public:
  Page(QString prjRoot, int pgIndex);
  void setFullDisplay();
  void setRefinedDisplay();
  QString getText();
  void appendWord(QString data, int x1, int y1, int x2, int y2);

private:
  struct wordUnit{
    QString data;
    int x1;
    int y1;
    int x2;
    int y2;
  };

  int displayHead;
  int index;
  QString dataX;
  QString projectRoot;
  QString imageRoot;
  QString imageFull;
  QString imageRefined;
  QString imageThumbnail;
  QVector<wordUnit> content;

  void setImagePaths();
  void createText();
  void setDisplayHead(int dHead);

  void createThumbnail(); //Unimplemented until Imagemagick integration
  void createRefined(); //Unimplemented until Imagemagick integration
};

#endif