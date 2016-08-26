#ifndef __INTERFACE_CANVAS_HH__
#define __INTERFACE_CANVAS_HH__

#include <Control/ControlData.hh>
#include <Document/wordUnit.hh>

#include <functional>

#include <QMainWindow>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QtGlobal>
#include <QGraphicsLineItem>

class Canvas : public QGraphicsView{
public:
  Canvas(QMainWindow *parent, ControlData *ctrlData);
  void configureSettings(QWidget *parent);
  void drawPage(QString pageToPrint);
  void removeUnderline();
  void zoomIn();
  void zoomOut();
  void zoomNormal();

private:
  ControlData *localControl;
  QGraphicsScene *displayController;
  QPixmap *scannedImg;
  QGraphicsLineItem *underline;
  std::function<void()> implementDraw;

  double zoomTracker;
  double zoomInFactor;
  double zoomOutFactor;

  void allocateResources();
  void allocateUnderline();
  void configureUnderline();
  void configureParent(QWidget *parent);
  void configureController();
  void setZoomDefaults();
  void drawLine();

  //Foreign Dependents
  void setupConnections();
  wordUnit getCurrentWordUnit();

  int getLineX1();
  int getLineX2();
  int getLineY2();
};

#endif
