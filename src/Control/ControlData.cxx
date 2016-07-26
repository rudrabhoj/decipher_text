#include <Control/ControlData.hh>
#include <Control/Setting.hh>

ControlData::ControlData(){
  allocateResources();
}

void ControlData::allocateResources(){
  preferences = new Setting();
}

Setting* ControlData::getSetting(){
  return preferences;
}
