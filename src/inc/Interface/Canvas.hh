#ifndef __INTERFACE_CANVAS_H__
#define __INTERFACE_CANVAS_H__

#include <QGraphicsScene>

class Canvas : public QGraphicsView{
public:
  Canvas(QMainWindow *parent, ControlData *ctrlData);
  configureSettings(QWidget *parent);

private:
  QGraphicsView *displayController;

  void allocateResources();
  void configureParent();
  void configureController();
}

#endif
