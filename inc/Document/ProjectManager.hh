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
  void createProjectFile(QString projContents);
  void verifyProjectRoot();
  void createImageDirs();

  void setSaveState(bool staat);

  bool removeDir(const QString &dirName);
  QString getWorkingDir();


  //Foreign Dependencies
  EventManager *localEventManager;
  void publishPagesChanged();
};

#endif
