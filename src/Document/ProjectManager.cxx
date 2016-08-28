#include <Document/ProjectManager.hh>
#include <QDir>
#include <QTextStream>
#include <QStandardPaths>
#include <QFileInfo>
#include <iostream>

ProjectManager::ProjectManager(QString projDirName){
  rootDir = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation)[0] + 
                                                              "/decipher_text Projects";
  dirName = projDirName;

  projectName = projDirName;

  verifyProjectRoot();

  createEmptyProject();

  setSaveState(true);
  
  setCurrentPageDefault();

  /*
  QStringList myPages;
  myPages.push_back("/home/rudrabhoj/Desktop/20012.jpg");

  addPages(myPages);
  */
}

void ProjectManager::setSaveState(bool staat){
  saveState = staat;
}

void ProjectManager::verifyProjectRoot(){
  QDir rootVerify;
  rootVerify.setPath(this->rootDir);

  if (!rootVerify.exists()){
    rootVerify.mkdir(this->rootDir);
  }
}

QList<Page>* ProjectManager::emitPages(){
  return &pageList;
}

void ProjectManager::setCurrentPage(int pgIndex){
  currentPage = pgIndex;
}

int ProjectManager::getCurrentPage(){
  return currentPage;
}

void ProjectManager::setCurrentPageDefault(){
  setCurrentPage(-1);
}

void ProjectManager::addPages(QStringList pages){
  int i, lim;
  lim = pages.length();

  for(i = 0; i < lim; i++){
    addSinglePage(pages[i]);
  }

  publishPagesChanged();
}

void ProjectManager::addPages(QString page){
  addSinglePage(page);
  publishPagesChanged();
}

void ProjectManager::addSinglePage(QString page){
  QFileInfo oldFileInfo(page);
  QString ofName, imagesRoot, imagesFull, imagesRefined, imagesThumb;
  QString commandExe;
  int futurePageIndex;

  ofName = oldFileInfo.fileName();

  imagesRoot = getWorkingDir() + "/images";
  imagesFull = imagesRoot + "/full";
  imagesRefined = imagesRoot + "/refined";
  imagesThumb = imagesRoot + "/thumbnail";

  QFile::copy(page, imagesFull + "/" + ofName);

  commandExe = "convert ";
  commandExe += "\"" + imagesFull + "/" + ofName + "\"";
  commandExe += " -thumbnail 104x148\\! ";
  commandExe += "\"" + imagesThumb + "/" + ofName + "\"";

  system(commandExe.toUtf8().data());

  futurePageIndex = pageList.length();

  Page dummyPage(getWorkingDir(), futurePageIndex);
  dummyPage.setFileName(ofName);

  pageList.push_back(dummyPage);
}

void ProjectManager::createEmptyProject(){
  QString targetName, root, dirName;
  QDir targetDir;

  targetName = getWorkingDir();
  targetDir.setPath(targetName);

  //Remove old contents if exists
  if (targetDir.exists()){
    removeDir(targetName);
  }

  targetDir.mkdir(targetName);
  createProjectFile("");

  createImageDirs();
}

void ProjectManager::createImageDirs(){
  QString projectWorkingDir, imageRootDir;
  QDir dummyDir;

  projectWorkingDir = getWorkingDir();
  imageRootDir = projectWorkingDir + "/images";

  dummyDir.mkdir(imageRootDir);
  dummyDir.mkdir(imageRootDir + "/full");
  dummyDir.mkdir(imageRootDir + "/refined");
  dummyDir.mkdir(imageRootDir + "/thumbnail");
}

void ProjectManager::createProjectFile(QString projContents){
  QString targetName;
  QFile pFile;

  targetName = getWorkingDir() + "/project.dtp";

  pFile.setFileName(targetName);

  if (pFile.open(QIODevice::WriteOnly)){
    QTextStream out(&pFile);

    out << projContents;

    pFile.close();
  }
}


bool ProjectManager::removeDir(const QString &dirName){
  bool result = true;
  QDir dir(dirName);

  if (dir.exists(dirName)) {
    Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden 
    | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {

      if (info.isDir()) {
        result = removeDir(info.absoluteFilePath());
      }
      else {
        result = QFile::remove(info.absoluteFilePath());
      }
      if (!result) {
        return result;
      }
    }
    result = dir.rmdir(dirName);
  }

  return result;
}


QString ProjectManager::getWorkingDir(){
  return rootDir + "/" + this->dirName;
}



QString ProjectManager::getProjectName(){
  return projectName;
}



//Foreign dependencies:
void ProjectManager::injectEventManager(EventManager *eManager){
  localEventManager = eManager;
}

void ProjectManager::publishPagesChanged(){
  localEventManager->publish("pagesChanged");
}
