#include <Interface/MainWindow.hh>

#include <QWidget>
#include <QListWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTextEdit>
#include <QSplitter>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent){
  setWindowTitle("Decipher Text");
  resize(1280, 720);

  allocateResources();

  configurePageList();

  configureCanvas();

  configureEditor();

  configureSplitters();

  configureLayout();

  show();
}

void MainWindow::allocateResources(){
  pageList = new QListWidget();
  mainLayout = new QHBoxLayout();
  canvas = new QGraphicsScene();
  canvasDisplay = new QGraphicsView();
  editor = new QTextEdit();
  mainSplitters = new QSplitter();
}

void MainWindow::configurePageList(){
  pageList->setParent(this);
}

void MainWindow::configureCanvas(){
  canvas->setParent(this);
  canvas->addText("Hello, World");
  canvasDisplay->setParent(this);
  canvasDisplay->setScene(canvas);
}

void MainWindow::configureEditor(){
  editor->setParent(this);
}

void MainWindow::configureSplitters(){
  mainSplitters->setOrientation(Qt::Horizontal);
  mainSplitters->setParent(this);

  mainSplitters->addWidget(pageList);
  mainSplitters->addWidget(canvasDisplay);
  mainSplitters->addWidget(editor);
}

void MainWindow::configureLayout(){
  mainLayout->addWidget(mainSplitters);
  setLayout(mainLayout);
}