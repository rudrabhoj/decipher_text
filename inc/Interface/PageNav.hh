#ifndef __INTERFACE_PAGENAV_HH__
#define __INTERFACE_PAGENAV_HH__

#include <Control/ControlData.hh>

#include <QListWidget>
#include <QMainWindow>

class PageNav : public QListWidget{
public:
  PageNav(QMainWindow *parent, ControlData *ctrlData);
  int presentSelection();
  int pastSelection();
  //void allocateResources();
private:
  ControlData *localControl;
  int oldSelection;

  void configure();
  void setPastSelection(int index);
};
#endif
