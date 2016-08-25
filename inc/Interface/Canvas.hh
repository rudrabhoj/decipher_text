#ifndef __INTERFACE_CANVAS_HH__
#define __INTERFACE_CANVAS_HH__

#include <Control/ControlData.hh>

#include <QMainWindow>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QtGlobal>

class Canvas : public QGraphicsView{
public:
  Canvas(QMainWindow *parent, ControlData *ctrlData);
  void configureSettings(QWidget *parent);
  void drawPage(QString pageToPrint);
  void zoomIn();
  void zoomOut();
  void zoomNormal();

private:
  ControlData *localControl;
  QGraphicsScene *displayController;
  QPixmap *scannedImg;

  double zoomTracker;
  double zoomInFactor;
  double zoomOutFactor;

  void allocateResources();
  void configureParent(QWidget *parent);
  void configureController();
  void setZoomDefaults();
};

#endif
