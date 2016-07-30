#ifndef __CONTROL_LANGUAGE_H__
#define __CONTROL_LANGUAGE_H__
#include <QString>
#include <QVector>
#include <QDirIterator>

#include <Control/Setting.hh>

class Language{
public:
  Language();
  void disableLanguage(QString lang);
  QString getLanguageArgument();
  void refreshLanguageList();
  bool checkEnabled(QString lang);
  void requestEnable(QString lang);

  QVector<QString> getAll();
  QVector<QString> getEnabled();

private:
  QVector<QString> languageList;
  QVector<QString> enabledLanguages;
  void allocateResources();
  void searchLanguages();
  void enableLanguage(QString lang);

  Setting *localSetting;
};

#endif