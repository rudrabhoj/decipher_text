#ifndef __INTERFACE_PAGENAV_HH__
#define __INTERFACE_PAGENAV_HH__

#include <Control/ControlData.hh>

#include <QListWidget>
#include <QMainWindow>

class PageNav : public QListWidget{
public:
  PageNav(QMainWindow *parent, ControlData *ctrlData);
  int getOldSelection();
  int getNewSelection();
  //void allocateResources();
private:
  ControlData *localControl;
  int oldSelection;
  int newSelection;

  void configure();
  void configureConnections();

  void setOldSelection(int index);
  void setNewSelection(int index);

  void listItemChanged();

};
#endif
