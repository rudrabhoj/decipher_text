#include <Control/Setting.hh>
#include <Control/ControlData.hh>

#include <iostream>
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>


Setting::Setting(){
  setDefaults();
}

void Setting::setDefaults(){
  setTessdataDefault();
  setTesseractDefaults();
  setInterfaceDefaults();
  setResourceDefaults();
}

void Setting::setInterfaceDefaults(){
  appName = "Decipher Text";
  interfaceLanguage = "en_US";
  windowState = false;
  windowXPos = 0;
  windowYPos = 0;
  windowWidth = 0;
  windowHeight = 0;
}

void Setting::setResourceDefaults(){
  binRoot = QCoreApplication::applicationDirPath();
  decipherDataPath = binRoot + "/../share/decipher_text";
  iconDir = decipherDataPath + "/icons";
}

void Setting::setTessdataDefault(){
  /*
    ALERT: Make this cross platform!!
  */

  QString path;

  if (QDir("/usr/share/tessdata").exists()){
    path = "/usr/share";
  } else if(QDir("/usr/local/share/tessdata").exists()){
    path = "/usr/local/share";
  } else {
    path = "";
  }

  setTessdataPath(path);
}

void Setting::setTesseractDefaults(){
  /*
    ALERT: Make this cross platform!!
  */
  QFileInfo location1;
  QFileInfo location2;
  QString path;

  location1.setFile("/usr/bin/tesseract");
  location2.setFile("/usr/local/bin/tesseract");

  if(location1.exists() && location1.isFile()){
    path = "/usr/bin/tesseract";
  } else if(location2.exists() && location2.isFile()) {
    path = "/usr/local/bin/tesseract";
  } else {
    path = "";
  }

  setTessdataPath(path);
}

//Getters
QString Setting::getTesseractPath(){
  return tesseractPath;
}

QString Setting::getTessdataPath(){
  return tessdataPath;
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

QString Setting::getDecipherDataPath(){
  return decipherDataPath;
}

QString Setting::getIconDir(){
  return iconDir;
}

//Setters
void Setting::setTesseractPath(QString path){
  tesseractPath = path;
}

void Setting::setTessdataPath(QString path){
  tessdataPath = path;
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

void Setting::setDecipherDataPath(QString path){
  decipherDataPath = path;
}