#ifndef __CONTROL_CONTROLDATA_H__
#define __CONTROL_CONTROLDATA_H__
#include <Control/Setting.hh>

class ControlData{
private:
  Setting *preferences;

  void allocateResources();
  void deallocateResources();
public:
  char **argv;
  int argc;

  ControlData(int inArgc, char *inArgv[]);
  ~ControlData();

  Setting *getSetting();
};

#endif