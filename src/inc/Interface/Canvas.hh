#ifndef __INTERFACE_CANVAS_HH__
#define __INTERFACE_CANVAS_HH__

#include <Control/ControlData.hh>

#include <QMainWindow>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>

class Canvas : public QGraphicsView{
public:
  Canvas(QMainWindow *parent, ControlData *ctrlData);
  void configureSettings(QWidget *parent);
  void drawPage(QString pageToPrint);

private:
  ControlData *localControl;
  QGraphicsScene *displayController;
  QPixmap *scannedImg;

  void allocateResources();
  void configureParent(QWidget *parent);
  void configureController();
};

#endif
