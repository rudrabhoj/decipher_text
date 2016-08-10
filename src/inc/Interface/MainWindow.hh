#ifndef __INTERFACE_MAINWINDOW_HH__
#define __INTERFACE_MAINWINDOW_HH__
#include <QWidget>
#include <QListWidget>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTextEdit>
#include <QSplitter>
#include <QList>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QIcon>

#include <Interface/Canvas.hh>


#include <Control/ControlData.hh>

class MainWindow : public QMainWindow {
public:
  MainWindow(QMainWindow *parent, ControlData *ctrlData);

private:
  ControlData *localControl;

  QWidget *centralWidget;

  QHBoxLayout *mainLayout;
  QVBoxLayout *listLayout;

  QListWidget *pageList;

  Canvas *canvasObject;

  QSplitter *mainSplitters;

  QTextEdit *editor;

  QAction *newProject;
  QAction *openProject;
  QAction *addImages;
  QAction *saveProject;
  QAction *saveAsProject;
  QAction *exit;
  QAction *zoomIn;
  QAction *zoomOut;
  QAction *zoomNormal;
  QAction *orcNow;
  QAction *prefSettings;
  QAction *about;
  QAction *documentation;

  QMenu *file;
  QMenu *tools;
  QMenu *help;

  QToolBar *mainToolbar;

  void allocateResources();
  void configurePageList();
  void configureCanvas();
  void configureEditor();
  void configureSplitters();
  void configureLayout();
  void configureAction();
  void configureConnections();
  void configureMenuConnections();
  void configureWidgetConnections();
  void configureMenu();
  void configureToolbar();

  void handleOpenProject();
  void handleAddProject();

  void showLoadDialog();

  void testMessagePrint();


  //Foreign Dependenices
  std::function<void()> pageUpdateWrapper;
  
  void syncNavbar();
  void setSignalWrappers();

  QList<Page> *getPageLink();
  QString getThumbnailPage(int index);
  QString getFullPage(int index);
  int getTotalPages();
};

#endif
