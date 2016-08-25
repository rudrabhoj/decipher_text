#include <Document/Page.hh>
#include <iostream>

Page::Page(QString prjRoot, int pgIndex){
  projectRoot = prjRoot;
  index = pgIndex;

  setOcrStatus(false);

  setImagePaths();

  defaultCurrentWord();
}

void Page::setImagePaths(){
  imageRoot = projectRoot + "/images";
  imageFull = imageRoot + "/full";
  imageRefined = imageRoot + "/refined";
  imageThumbnail = imageRoot + "/thumbnail";
}

void Page::defaultCurrentWord(){
  currentWord.data = " ";
  currentWord.x1 = 0;
  currentWord.y1 = 0;
  currentWord.x2 = 0;
  currentWord.y2 = 0;
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

void Page::interpretCurrentWord(int line, int pos){
  QList<wordUnit> myLine;

  myLine = getLine(line);

  std::cout << "Line: " << line << " Pos: " << pos << "Word: " << convertWord(myLine, pos).data.toUtf8().data() << std::endl;

  currentWord = convertWord(myLine, pos);
}

wordUnit Page::convertWord(QList<wordUnit> myLine, int position){

  int size, lim, i;

  lim = myLine.length();
  size = 0;

  for(i = 0; i < lim; i++){
    size += (myLine[i].data.length() + 1);
    if (size > position) return myLine[i];
  }

}

QList<wordUnit> Page::getLine(int line){
  int c, i, j, lim;
  QList<wordUnit> myLine;
  QString localData;

  lim = content.length();

  for(i = 0; i < lim; i++){
    if( content[i].lineNo <= line  ){

      if(content[i].lineNo == line){
        myLine.push_back(content[i]);
      }

    } else {
      break;
    }
  }

  return myLine;

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
