#include <Control/ControlData.hh>
#include <Control/Setting.hh>
#include <iostream>

ControlData::ControlData(int inArgc, char *inArgv[]){
  argc = inArgc;
  argv = inArgv;
  allocateResources();
}

ControlData::~ControlData(){
  deallocateResources();
}

void ControlData::allocateResources(){
  preferences = new Setting(this);
}

void ControlData::deallocateResources(){
  delete preferences;
}

Setting* ControlData::getSetting(){
  return preferences;
}
