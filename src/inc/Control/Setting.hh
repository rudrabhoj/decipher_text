#ifndef __CONTROL_SETTING_H__
#define __CONTROL_SETTING_H__

#include <QString>
#include <QCoreApplication>

class Setting{
private:

  //Tesseract Preferances
  QString tesseractPath;
  QString tessdataPath;

  //GUI Preferences
  QString appName;
  QString interfaceLanguage;
  bool windowState; //True for maximized window. False for otherwise.
  int windowXPos;
  int windowYPos;
  int windowWidth;
  int windowHeight;

  //Resource paths
  QString binRoot;
  QString decipherDataPath;
  QString iconDir;

  void setDefaults();
  QString getCurrentState();
  QString getDefaultState();
  void setTessdataDefault();
  void setTesseractDefaults();
  void setLanguageDefaults();
  void setInterfaceDefaults();
  void setResourceDefaults();

  bool configExists();
  QString getConfigDir();
  QString getConfigFile();
  void newConfigFile();
  void overrideConfig();
  void interpretConfig(QString textToPrint);
  void editConfigFile(QString label, QString value);

public:
  Setting();
  //Getters
  QString getTesseractPath();
  QString getTessdataPath();

  QString getAppName();
  QString getInterfaceLanguage();

  bool getWindowState();
  int getWindowXPos();
  int getWindowYPos();
  int getWindowWidth();
  int getWindowHeight();

  QString getDecipherDataPath();
  QString getIconDir();

  //Setters
  void setTesseractPath(QString path);
  void setTessdataPath(QString path);

  void setAppName(QString name);
  void setInterfaceLanguage(QString lang);

  void setWindowState(bool state);
  void setWindowXPos(int pos);
  void setWindowYPos(int pos);
  void setWindowWidth(int width);
  void setWindowHeight(int height);

  void setDecipherDataPath(QString path);
  void setIconDir(QString path);
};

#endif
