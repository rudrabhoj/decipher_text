#ifndef __INTERFACE_STATUS_HH__
#define __INTERFACE_STATUS_HH__

#include <QMainWindow>
#include <QWidget>
#include <QString>
#include <QStatusBar>
#include <QLabel>

#include <Control/ControlData.hh>

class Status : public QStatusBar{
public:
  Status(QMainWindow *parent, ControlData *ctrlData);

private:
  ControlData *localControl;
  QLabel *permaMessage;

  void allocateResources();
  void addGadgets();
  void configureGui();

  //Foreign Dependents
  QString getFullAppName();
};

#endif
