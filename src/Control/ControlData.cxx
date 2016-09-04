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
  preferences = new Setting();
  language = new Language();
  pubSub = new EventManager();
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

  myName = myProject->getProjectName();
  if (!myProject->getSaveState()) myName += "*";
  myName += " - ";
  myName += preferences->getAppName();
  myName += " 0.5-alpha";

  return myName;
}
