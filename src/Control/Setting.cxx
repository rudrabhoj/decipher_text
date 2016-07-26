#include <Control/Setting.hh>
#include <iostream>

Setting::Setting(){
  std::cout << "Setting is working" << std::endl;
}

//Getters
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


//Setters
void Setting::setTesseractPath(QString path){
  tesseractPath = path;
}

void Setting::setTessdataPath(QString path){
  tessdataPath = path;
}

void Setting::setLang1(QString lang){
  lang1 = lang;
}

void Setting::setLang2(QString lang){
  lang2 = lang;
}

void Setting::setLang3(QString lang){
  lang3 = lang;
}

void Setting::setLang4(QString lang){
  lang4 = lang;
}

void Setting::setLang5(QString lang){
  lang5 = lang;
}

void Setting::setAppName(QString name){
  appName = name;
}

void Setting::setInterfaceLanguage(QString lang){
  interfaceLanguage = lang;
}

void Setting::setWindowState(bool state){
  windowState = state;
}

void Setting::setWindowXPos(int pos){
  windowXPos = pos;
}

void Setting::setWindowYPos(int pos){
  windowYPos = pos;
}

void Setting::setWindowWidth(int width){
  windowWidth = width;
}

void Setting::setWindowHeight(int height){
  windowHeight = height;
}
