#ifndef __CONTROL_CONTROLDATA_H__
#define __CONTROL_CONTROLDATA_H__
#include <Control/Setting.hh>

class ControlData{
private:
	Setting *preferences;

  void allocateResources();
public:
  ControlData();
  Setting *getSetting();
};

#endif