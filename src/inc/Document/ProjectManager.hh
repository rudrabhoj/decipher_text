#ifndef __DOCUMENT_PROJECTMANAGER_H__
#define __DOCUMENT_PROJECTMANAGER_H__

#include <Document/Page.hh>
#include <QVector>

class ProjectManager{

public:
  void setName(QString name);
  QString getName();

private:
  QVector<Page> pageList;
};

#endif
