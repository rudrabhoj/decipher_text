#include <Interface/Canvas.hh>
#include <Document/Page.hh>


#include <QPen>
#include <QColor>
#include <QList>
#include <iostream>

Canvas::Canvas(QMainWindow *parent, ControlData *ctrlData) : QGraphicsView(parent){
  setParent(parent);
  localControl = ctrlData;
  allocateResources();
  setZoomDefaults();
  setupConnections();
}

void Canvas::allocateResources(){
  displayController = new QGraphicsScene();
  scannedImg = NULL;
  underline = NULL;
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

  removeHighlights();
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


void Canvas::drawLine(){
  removeHighlights();

  configureUnderline();
}

void Canvas::removeUnderline(){
  if (underline != NULL && underline->scene() != 0){
    displayController->removeItem(underline);
  }
}

void Canvas::removeHighlights(){
  removeUnderline();
}

void Canvas::zoomNormal(){
  std::cout << "Unimplemented for now" << std::endl;
}


void Canvas::allocateUnderline(){
  removeHighlights(); //Remove previous exisetence of underline
  underline = new QGraphicsLineItem();
}


void Canvas::configureUnderline(){
  QPen turtle;
  int x1, x2, y2;

  turtle.setColor(QColor(Qt::darkGreen));
  turtle.setWidth(4);

  allocateUnderline();

  underline->setPen(turtle);

  x1 = getLineX1();
  x2 = getLineX2();
  y2 = getLineY2();

  underline->setLine(x1, y2, x2, y2);
  displayController->addItem(underline);

}

//Foreign Dependents
void Canvas::setupConnections(){
  implementDraw = [&](){ drawLine(); };

  localControl->getPubSub()->subscribe("drawLines", &implementDraw);
}

wordUnit Canvas::getCurrentWordUnit(){
  int pgNo;
  QList<Page> *pageBank;
  Page *localPage;

  pgNo = localControl->getProjectManager()->getCurrentPage();
  pageBank = localControl->getProjectManager()->emitPages();
  localPage = &((*pageBank)[pgNo]);

  return localPage->currentWord;
}

int Canvas::getLineX1(){
  wordUnit localWordUnit;

  localWordUnit = getCurrentWordUnit();

  return localWordUnit.x1;
}

int Canvas::getLineX2(){
  wordUnit localWordUnit;

  localWordUnit = getCurrentWordUnit();

  return localWordUnit.x2;
}

int Canvas::getLineY2(){
  wordUnit localWordUnit;

  localWordUnit = getCurrentWordUnit();

  return localWordUnit.y2;
}
