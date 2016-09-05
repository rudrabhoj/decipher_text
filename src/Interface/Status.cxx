#include <Interface/Status.hh>

Status::Status(QMainWindow *parent, ControlData *ctrlData) : QStatusBar(parent){
  localControl = ctrlData;
  setParent(parent);

  allocateResources();
  addGadgets();
  configureGui();
}

void Status::allocateResources(){
  permaMessage = new QLabel(this);
}

void Status::addGadgets(){
  addPermanentWidget(permaMessage);
}

void Status::configureGui(){
  permaMessage->setText( getFullAppName() );
}


//Foreign Dependents
QString Status::getFullAppName(){
  QString appName;
  QString appVer;

  appName = localControl->getSetting()->getAppName();
  appVer = localControl->getVersion();

  return appName + " " + appVer;
}
