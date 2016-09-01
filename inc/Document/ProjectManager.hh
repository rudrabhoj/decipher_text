#ifndef __DOCUMENT_PROJECTMANAGER_HH__
#define __DOCUMENT_PROJECTMANAGER_HH__

#include <Document/Page.hh>
#include <QList>
#include <QStringList>
#include <Control/EventManager.hh>

class ProjectManager{

public:
  ProjectManager(QString projDirName);
  void addPages(QStringList pages);
  void addPages(QString page);

  QString getProjectName();

  QList<Page> *emitPages();
  void setCurrentPage(int pgIndex);
  int getCurrentPage();

  void saveAs(QString saveName);

  //Foreign injections
  void injectEventManager(EventManager *eManager);

private:
  QString dirName;
  QString rootDir;
  QList<Page> pageList;
  int currentPage;
  QString projectName;
  bool saveState;

  void setCurrentPageDefault();
  void createEmptyProject();
  void copyProject(QString newRoot, QString newDir);
  void addSinglePage(QString page);
  void createProjectFile(QString pName, QString projContents);
  void verifyProjectRoot();
  void createImageDirs();

  void setSaveState(bool staat);

  bool removeDir(const QString &dirName);
  bool copyPath(QString sourceDir, QString destinationDir, bool overWriteDirectory);
  QString getWorkingDir();

  QString getSaveRootDir(QString saveName);
  QString getSaveContainer(QString saveName);
  QString getSaveFName(QString saveName);
  QStringList breakSaveString(QString saveName);
  void createSaveEnvironment(QString fName, QString containerDir, QString rootUrl);
  void createSaveContainer(QString containerDir, QString rootUrl);
  void createSaveImageEnvironment(QString containerDir, QString rootUrl);
  void copySaveImageEnvironment(QString containerDir, QString rootUrl);
  void createSaveImageDir(QString containerDir, QString rootUrl);
  void configureRoot(QString rootName, QString projDirName);
  void reConfigurePageRoot(QString rootUrl);

  QString dtpGetData();
  void dtpGenerateFile(QString fName);
  QString dtpGetPageSemantics();
  QString dtpGenerateSemantics(int index);
  QString dtpGetPageNames();


  //Foreign Dependencies
  EventManager *localEventManager;
  void publishPagesChanged();
};

#endif
