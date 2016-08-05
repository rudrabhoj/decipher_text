#include <Control/ControlData.hh>

ControlData::ControlData(int inArgc, char *inArgv[]){
  argc = inArgc;
  argv = inArgv;
  allocateResources();
}

ControlData::~ControlData(){
  deallocateResources();
}

void ControlData::allocateResources(){
  preferences = new Setting();
  language = new Language();
  pubSub = new EventManager();
}

void ControlData::deallocateResources(){
  delete preferences;
  delete language;
  delete pubSub;
}

Setting* ControlData::getSetting(){
  return preferences;
}
