#ifndef __CONTROL_CONTROLDATA_HH__
#define __CONTROL_CONTROLDATA_HH__
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
  Language *getLanguage();

  QString createName();
  QString getVersion();
};

#endif
