#ifndef __CONTROL_CONTROLDATA_H__
#define __CONTROL_CONTROLDATA_H__
#include <Control/Setting.hh>
#include <Control/Language.hh>
#include <Control/EventManager.hh>

class ControlData{
private:
  Setting *preferences;
  Language *language;

  void allocateResources();
  void deallocateResources();
public:
  char **argv;
  int argc;
  EventManager *pubSub;

  ControlData(int inArgc, char *inArgv[]);
  ~ControlData();

  Setting *getSetting();
};

#endif