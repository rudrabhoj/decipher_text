#include <Control/Setting.hh>
#include <iostream>

Setting::Setting(){
  std::cout << "Setting is working" << std::endl;
}


QString Setting::getTesseractPath(){
  return tesseractPath;
}

QString Setting::getTessdataPath(){
  return tessdataPath;
}

QString Setting::getLang1(){
  return lang1;
}

QString Setting::getLang2(){
  return lang2; 
}

QString Setting::getLang3(){
  return lang3; 
}

QString Setting::getLang4(){
  return lang4; 
}

QString Setting::getLang5(){
  return lang5; 
}

QString Setting::getAppName(){
  return appName;
}

QString Setting::getInterfaceLanguage(){
  return interfaceLanguage;
}

bool Setting::getWindowState(){
  return windowState;
}

int Setting::getWindowXPos(){
  return windowXPos;
}

int Setting::getWindowYPos(){
  return windowYPos;
}

int Setting::getWindowWidth(){
  return windowWidth;
}

int Setting::getWindowHeight(){
  return windowHeight;
}
/*

  //Setters
void Setting::setTesseractPath(QString path);
void Setting::setTessdataPath(QString path);

void Setting::setLang1(QString lang);
void Setting::setLang2(QString lang);
void Setting::setLang3(QString lang);
void Setting::setLang4(QString lang);
void Setting::setLang5(QString lang);

void Setting::setAppName(QString name);
void Setting::setInterfaceLanguage(QString lang);

void Setting::setWindowState(bool state);
void Setting::setWindowXPos(int pos);
void Setting::setWindowYPos(int pos);
void Setting::setWindowWidth(int width);
void Setting::setWindowHeight(int height);
*/