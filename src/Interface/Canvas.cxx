#include <Interface/Canvas.hh>

Canvas::Canvas(QMainWindow *parent, ControlData *ctrlData) : QGraphicsView(parent){
  setParent(parent);
  localControl = ctrlData;
  allocateResources();
}

void Canvas::allocateResources(){
  displayController = new QGraphicsScene();
  scannedImg = NULL;
}

void Canvas::configureSettings(QWidget *parent){
  configureParent(parent);
  configureController();
}

void Canvas::configureParent(QWidget *parent){
  setParent(parent);
}

void Canvas::configureController(){
  setScene(displayController);
}

void Canvas::drawPage(QString pageToPrint){
  scannedImg = new QPixmap(pageToPrint);

  displayController->clear();
  displayController->addPixmap((*scannedImg));
}