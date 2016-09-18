#ifndef __INTERFACE_MAINWINDOW_HH__
#define __INTERFACE_MAINWINDOW_HH__
#include <QWidget>
#include <QListWidget>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <Interface/TextEditor.hh>
#include <QSplitter>
#include <QList>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QIcon>

#include <QVector>
#include <QString>

#include <Interface/Canvas.hh>
#include <Interface/Status.hh>
#include <Interface/PageNav.hh>
#include <Interface/SettingDialog.hh>
#include <Interface/About.hh>
#include <Interface/RecognizeProcess.hh>
#include <Interface/ReplaceDialog.hh>


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

  PageNav *pageList;

  Canvas *canvasObject;
  Status *statusBar;

  QSplitter *mainSplitters;

  TextEditor *editor;

  SettingDialog *settingWindow;
  ReplaceDialog *replaceDialog;
  About *aboutWindow;
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
  QAction *orcAll;
  QAction *fontSettings;
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
  void configureReplaceDialog();
  void configureAboutWindow();
  void configureRProcessDialog();
  void configureMenuConnections();
  void configureWidgetConnections();
  void configureMenu();
  void configureToolbar();

  QString defaultOCRLanguage();
  void handleRecognizeNow(bool ifAllPages);
  void handleLanguageChange();

  void handleOpenProject();
  void handleSaveAsProject();
  void handleSaveProject();
  void handleNewProject();
  void handleAddProject();

  void showLoadDialog();

  void listItemChanged();
  void updateWindowName();


  //Foreign Dependenices
  std::function<void()> pageUpdateWrapper;
  std::function<void()> listNavUpdateWrapper;
  std::function<void()> saveChanged;
  void loadOCRedText();
  QString configurAppName();

  void syncNavbar();
  void backupOldText();
  void setSignalWrappers();
  void sendEnableLangRequest(QString lang);
  void sendDisableLangRequest(QString lang);
  QString getAppIconPath();

  void loadLanguages();
  void syncProjectManagerPageSelection(int i);

  QList<Page> *getPageLink();
  QString getThumbnailPage(int index);
  QString getFullPage(int index);
  int getTotalPages();

  void setFontPreferences();
};

#endif
