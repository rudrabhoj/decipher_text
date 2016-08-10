#include <Interface/Canvas.hh>
#include <iostream>

Canvas::Canvas(QMainWindow *parent, ControlData *ctrlData) : QGraphicsView(parent){
  setParent(parent);
  localControl = ctrlData;
  allocateResources();
  setZoomDefaults();
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

void Canvas::setZoomDefaults(){
  zoomTracker = 1.0;
  zoomInFactor = zoomTracker;
  zoomOutFactor = zoomTracker;
}

void Canvas::zoomIn(){
  zoomInFactor += 0.05;
  zoomTracker += 0.05;

  zoomOutFactor = 1.0;

  scale(zoomInFactor, zoomInFactor);
}

void Canvas::zoomOut(){
  zoomOutFactor -= 0.05;
  zoomTracker -= 0.05;
  zoomInFactor = 1.0;

  scale(zoomOutFactor, zoomOutFactor);
}

void Canvas::zoomNormal(){
  std::cout << "Unimplemented for now" << std::endl;
}