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
  void setSaveState(bool staat);
  bool getSaveHistory();
  bool getSaveState();

  void saveAs(QString saveName);
  void openProject(QString openName);

  //Foreign injections
  void injectEventManager(EventManager *eManager);

private:
  QString dirName;
  QString rootDir;
  QList<Page> pageList;
  int currentPage;
  QString projectName;
  bool saveState;
  bool saveHistory;

  void setCurrentPageDefault();
  void createEmptyProject();
  void loadEmptyDefault(QString projDirName);
  void copyProject(QString newRoot, QString newDir);
  void addSinglePage(QString page);
  void commitPage(QString ofName, int index);
  void createProjectFile(QString pName, QString projContents);
  void verifyProjectRoot();
  void createImageDirs();

  void setSaveHistory(bool staat);

  bool removeDir(const QString &dirName);
  QString trimCommand(QString lineData, QString command, QString modifier);
  bool copyPath(QString sourceDir, QString destinationDir, bool overWriteDirectory);
  QString getImageMagickCommand();
  QString getWorkingDir();

  QString getSaveRootDir(QString saveName);
  bool sanitizationNeeded(QString testUrl);
  QString open2SaveUrlConvert(QString openName);
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
  void dtpDeleteAllPages();
  void loadInterpretDtp(QString targetRoot, QString targetContainer, QString targetFile);
  void interpretDtp(QString lineData);
  void interpretDtpAddPage(QString lineData);
  void interpretDtpSemantics(int modifier, QString lineData);
  wordUnit getSemantics(QStringList sem);
  void interpretDtpData(int modifier, QString lineData);


  //Foreign Dependencies
  EventManager *localEventManager;
  void publishPagesChanged();
  void publishSave();
};

#endif
