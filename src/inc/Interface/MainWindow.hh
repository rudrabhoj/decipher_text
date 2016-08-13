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

#include <QVector>
#include <QString>

#include <Interface/Canvas.hh>
#include <Interface/SettingDialog.hh>
#include <Interface/RecognizeProcess.hh>


#include <Control/ControlData.hh>

class MainWindow : public QMainWindow {
public:
  MainWindow(QMainWindow *parent, ControlData *ctrlData);

private:
  ControlData *localControl;

  QVector<QString> allLanguages;
  QVector<QString> enabledLanguages;
  QVector<QAction*> languageActions;

  QWidget *centralWidget;

  QHBoxLayout *mainLayout;
  QVBoxLayout *listLayout;

  QListWidget *pageList;

  Canvas *canvasObject;

  QSplitter *mainSplitters;

  QTextEdit *editor;

  SettingDialog *settingWindow;
  RecognizeProcess *rProcessDialog;

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
  QMenu *languageList;
  QMenu *help;

  QToolBar *mainToolbar;

  void allocateResources();
  void configurePageList();
  void configureCanvas();
  void configureEditor();
  void configureSplitters();
  void configureLayout();
  void configureAction();
  void configureLanguageActions();
  void configureLanguageMenu();
  void configureConnections();
  void configureLanguageConnections();
  void configureSettingWindow();
  void configureRProcessDialog();
  void configureMenuConnections();
  void configureWidgetConnections();
  void configureMenu();
  void configureToolbar();

  void handleRecognizeNow();
  void handleLanguageChange();

  void handleOpenProject();
  void handleAddProject();

  void showLoadDialog();

  void testMessagePrint();


  //Foreign Dependenices
  std::function<void()> pageUpdateWrapper;
  void loadOCRedText();
  
  void syncNavbar();
  void setSignalWrappers();
  void sendEnableLangRequest(QString lang);
  void sendDisableLangRequest(QString lang);

  void loadLanguages();

  QList<Page> *getPageLink();
  QString getThumbnailPage(int index);
  QString getFullPage(int index);
  int getTotalPages();
};

#endif
