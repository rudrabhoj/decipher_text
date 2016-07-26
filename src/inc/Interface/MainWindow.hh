#ifndef __INTERFACE_MAINWINDOW_H__
#define __INTERFACE_MAINWINDOW_H__
#include <QWidget>
#include <QListWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTextEdit>
#include <QSplitter>

class MainWindow : public QWidget {
public:
  MainWindow(QWidget *parent = 0);
private:
  QHBoxLayout *mainLayout;
  QVBoxLayout *listLayout;

  QListWidget *pageList;

  QGraphicsScene *canvas;
  QGraphicsView *canvasDisplay;

  QSplitter *mainSplitters;

  QTextEdit *editor;

  void allocateResources();
  void configurePageList();
  void configureCanvas();
  void configureEditor();
  void configureSplitters();
  void configureLayout();
};

#endif