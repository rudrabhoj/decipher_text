#include <Document/Page.hh>

Page::Page(QString prjRoot, int pgIndex){
  projectRoot = prjRoot;
  index = pgIndex;

  setOcrStatus(false);

  setImagePaths();
}

void Page::setImagePaths(){
  imageRoot = projectRoot + "/images";
  imageFull = imageRoot + "/full";
  imageRefined = imageRoot + "/refined";
  imageThumbnail = imageRoot + "/thumbnail";
}

void Page::setFileName(QString fname){
  realName = fname;
  fullLink = imageFull + "/" + fname;
  thumbLink = imageThumbnail + "/" + fname;
}

QString Page::getFullDisplayLink(){
  return fullLink;
}

QString Page::getThumbLink(){
  return thumbLink;
}

void Page::setDisplayHead(int dHead){
  displayHead = dHead;
}

void Page::setFullDisplay(){
  setDisplayHead(0);
}

void Page::setRefinedDisplay(){
  setDisplayHead(1);
}

QString Page::getText(){
  int i, lim;
  QString out;

  lim = content.length();

  for(i = 0; i < lim; i++){
    out += content[i].data;
    out += " ";
  }

  return out;
}

void Page::appendWord(QString data, int x1, int y1, int x2, int y2){
  wordUnit tmpWord;

  tmpWord.data = data;
  tmpWord.x1 = x1;
  tmpWord.y1 = y1;
  tmpWord.x2 = x2;
  tmpWord.y2 = y2;

  content.push_back(tmpWord);
}

void Page::createText(){
  int i, lim;

  lim = content.length();
  dataX = "";

  for (i = 0; i < lim; i++) dataX += content[i].data;
}

void Page::setOcrStatus(bool staat){
  ocrStatus = staat;
}

bool Page::getOcrStatus(){
  return ocrStatus;
}

void Page::importOcr(QVector<wordUnit> ocrImport){
  this->content = ocrImport;
  setOcrStatus(true);
}