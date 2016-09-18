#include <Control/ControlData.hh>

ControlData::ControlData(int inArgc, char *inArgv[]){
  argc = inArgc;
  argv = inArgv;
  allocateResources();
  configureProjectManager();
}

ControlData::~ControlData(){
  deallocateResources();
}

void ControlData::allocateResources(){
  pubSub = new EventManager();
  preferences = new Setting();
  language = new Language();
  myProject = new ProjectManager("Untitled Project");
}

void ControlData::configureProjectManager(){
  myProject->injectEventManager(pubSub);
}

void ControlData::deallocateResources(){
  delete preferences;
  delete language;
  delete pubSub;
  delete myProject;
}

Setting* ControlData::getSetting(){
  return preferences;
}

EventManager* ControlData::getPubSub(){
  return pubSub;
}

ProjectManager* ControlData::getProjectManager(){
  return myProject;
}

Language* ControlData::getLanguage(){
  return language;
}

QString ControlData::createName(){
  QString myName;

  myName = myProject->getSaveFileName();
  if (!myProject->getSaveState()) myName += "*";
  myName += " - ";
  myName += preferences->getAppName();
  myName += " " + getVersion();

  return myName;
}

QString ControlData::getVersion(){
  return "0.9.0-alpha";
}
