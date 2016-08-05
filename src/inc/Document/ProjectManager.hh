5#ifndef __DOCUMENT_PROJECTMANAGER_H__
#define __DOCUMENT_PROJECTMANAGER_H__

#include <Document/Page.hh>
#include <QVector>

class ProjectManager{

public:
  ProjectManager(QString projectRootDir);

  void setName(QString name);
  void setSaveState(bool staat);
  void setprojectFileUrl(QString url);

  QString getName();
  bool getSaveState();

  void addPage(QString imageName);
  void saveProject();
  void openProject(QString projectFileLink);

private:
  QString name;
  QVector<Page> pageList;
  bool saveState;
  QString projectRoot;
  QString projectFileUrl;

  void moveProjectUrl(QString newUrl);
};

#endif
