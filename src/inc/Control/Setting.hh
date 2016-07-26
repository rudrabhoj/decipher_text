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
  QString getTesseractPath();
  QString getTessdataPath();

  QString getLang1();
  QString getLang2();
  QString getLang3();
  QString getLang4();
  QString getLang5();

  QString getAppName();
  QString getInterfaceLanguage();

  bool getWindowState();
  int getWindowXPos();
  int getWindowYPos();
  int getWindowWidth();
  int getWindowHeight();

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