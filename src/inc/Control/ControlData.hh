#ifndef __CONTROL_CONTROLDATA_H__
#define __CONTROL_CONTROLDATA_H__
#include <Control/Setting.hh>
#include <Control/Language.hh>
#include <Control/EventManager.hh>
#include <Document/ProjectManager.hh>

class ControlData{
private:
  Setting *preferences;
  Language *language;
  ProjectManager *myProject;

  void allocateResources();
  void deallocateResources();
  void configureProjectManager();
public:
  char **argv;
  int argc;
  EventManager *pubSub;

  ControlData(int inArgc, char *inArgv[]);
  ~ControlData();

  Setting *getSetting();
  EventManager *getPubSub();
  ProjectManager *getProjectManager();
};

#endif