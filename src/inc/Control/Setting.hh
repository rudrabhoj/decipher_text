#ifndef __CONTROL_SETTING_H__
#define __CONTROL_SETTING_H__

#include <QString>

class Setting{
private:
  //Tesseract Preferances
  QString tesseractPath;
  QString tessdataPath;
  QString lang1;
  QString lang2;
  QString lang3;
  QString lang4;
  QString lang5;

  //GUI Preferences
  QString appName;
  QString interfaceLanguage;
  bool windowState; //True for maximized window. False for otherwise.
  int windowXPos;
  int windowYPos;
  int windowWidth;
  int windowHeight;

public:
  Setting();
  //Getters
  void getTesseractPath(QString path);
  void getTessdataPath(QString path);

  void getLang1(QString lang);
  void getLang2(QString lang);
  void getLang3(QString lang);
  void getLang4(QString lang);
  void getLang5(QString lang);

  void getAppName(QString name);
  void getInterfaceLanguage(QString lang);

  void getWindowState(bool state);
  void getWindowXPos(int pos);
  void getWindowYPos(int pos);
  void getWindowWidth(int width);
  void getWindowHeight(int height);

  //Setters
  void setTesseractPath(QString path);
  void setTessdataPath(QString path);

  void setLang1(QString lang);
  void setLang2(QString lang);
  void setLang3(QString lang);
  void setLang4(QString lang);
  void setLang5(QString lang);

  void setAppName(QString name);
  void setInterfaceLanguage(QString lang);

  void setWindowState(bool state);
  void setWindowXPos(int pos);
  void setWindowYPos(int pos);
  void setWindowWidth(int width);
  void setWindowHeight(int height);
};

#endif