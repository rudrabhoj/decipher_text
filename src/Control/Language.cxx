#include <Control/Language.hh>
#include <iostream>

Language::Language(){
  searchLanguages();

  //tmp demo code
  requestEnable("eng");
  requestEnable("hin");
}

void Language::searchLanguages(){
  languageList.clear();

	languageList.push_back("eng");
  languageList.push_back("hin");
  languageList.push_back("ara");
}

void Language::refreshLanguageList(){
  searchLanguages();
}

void Language::requestEnable(QString lang){
  int i, lim;
  lim = languageList.length();
  for (i = 0; i < lim; i++ ){
    if (languageList[i] == lang && !checkEnabled(lang) ){
      enableLanguage(lang);
      break;
    }
  }
}

void Language::enableLanguage(QString lang){
  enabledLanguages.push_back(lang);
}

bool Language::checkEnabled(QString lang){
  int i, lim;
  bool rVal;

  rVal = false;
  lim = enabledLanguages.length();

  for(i = 0; i < lim; i++){
    if (enabledLanguages[i] == lang) rVal = true;
  }

  return rVal;
}

QString Language::getLanguageArgument(){
  int i, lim;
  QString arg;

  lim = enabledLanguages.length();

  if (enabledLanguages.isEmpty()) return "";

  arg = "-l " + enabledLanguages[0];

  for (i = 1; i < lim; i++){
    arg = arg + "+" + enabledLanguages[i];
  }

  return arg;
}

QVector<QString> Language::getAll(){
  return languageList;
}

QVector<QString> Language::getEnabled(){
  return enabledLanguages;
}