#include <Control/Language.hh>
#include <iostream>

Language::Language(){
  allocateResources();

  searchLanguages();

  //tmp demo code
  requestEnable("eng");
  requestEnable("hin");
}

void Language::allocateResources(){
  localSetting = new Setting();
}

void Language::searchLanguages(){
  QString tessDataLocation;

  tessDataLocation = localSetting->getTessdataPath();
  tessDataLocation += "/tessdata";

  languageList.clear();

  QDirIterator tessDirIt(tessDataLocation);

  while(tessDirIt.hasNext()){
    tessDirIt.next();
    if ( (QFileInfo(tessDirIt.filePath()).isFile()) &&
      (QFileInfo(tessDirIt.filePath()).suffix() == "traineddata") ){

      //Apending detected languages!
      languageList.push_back(tessDirIt.fileName().replace(".traineddata", ""));
    }
  }
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