#include <Document/ProjectManager.hh>
#include <Document/wordUnit.hh>
#include <QDir>
#include <QVector>
#include <QTextStream>
#include <QStandardPaths>
#include <QFileInfo>
#include <iostream>

ProjectManager::ProjectManager(QString projDirName){
  QString designatedRoot;

  designatedRoot = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation)[0] +
                                                              "/decipher_text Projects";

  configureRoot(designatedRoot, projDirName);

  verifyProjectRoot();

  createEmptyProject();

  setSaveState(false);

  setCurrentPageDefault();

  /*
  QStringList myPages;
  myPages.push_back("/home/rudrabhoj/Desktop/20012.jpg");

  addPages(myPages);
  */
}

void ProjectManager::configureRoot(QString rootName, QString projDirName){
  rootDir = rootName;
  dirName = projDirName;
  projectName = projDirName;
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
  createProjectFile("/project.dtp", "");

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

void ProjectManager::createProjectFile(QString pName, QString projContents){
  QString targetName;
  QFile pFile;

  targetName = getWorkingDir() + pName;

  pFile.setFileName(targetName);

  if (pFile.open(QIODevice::WriteOnly)){
    QTextStream out(&pFile);

    out << projContents;

    pFile.close();
  }
}


bool ProjectManager::copyPath(QString sourceDir, QString destinationDir, bool overWriteDirectory){

    QDir originDirectory(sourceDir);

    if (! originDirectory.exists())
    {
        return false;
    }

    QDir destinationDirectory(destinationDir);

    if(destinationDirectory.exists() && !overWriteDirectory)
    {
        return false;
    }
    else if(destinationDirectory.exists() && overWriteDirectory)
    {
        destinationDirectory.removeRecursively();
    }

    originDirectory.mkpath(destinationDir);

    foreach (QString directoryName, originDirectory.entryList(QDir::Dirs | \
                                                              QDir::NoDotAndDotDot))
    {
        QString destinationPath = destinationDir + "/" + directoryName;
        originDirectory.mkpath(destinationPath);
        copyPath(sourceDir + "/" + directoryName, destinationPath, overWriteDirectory);
    }

    foreach (QString fileName, originDirectory.entryList(QDir::Files))
    {
        QFile::copy(sourceDir + "/" + fileName, destinationDir + "/" + fileName);
    }

    /*! Possible race-condition mitigation? */
    QDir finalDestination(destinationDir);
    finalDestination.refresh();

    if(finalDestination.exists())
    {
        return true;
    }

    return false;
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

QStringList ProjectManager::breakSaveString(QString saveName){
  QString token;
  QStringList linkData;

  token = "/";

  #ifdef _WIN32
    token = "\\";
  #endif

  linkData = saveName.split(token);

  return  linkData;
}

QString ProjectManager::getSaveFName(QString saveName){
  QString fName;
  int lim;
  QStringList linkData;

  linkData = breakSaveString(saveName);
  lim = linkData.length();

  fName = linkData[lim - 1];

  if(fName.right(4) != ".dtp") fName += ".dtp";

  return fName;
}

QString ProjectManager::getSaveContainer(QString saveName){
  QString fName, containerDir;

  fName = getSaveFName(saveName);

  if(fName.right(4) != ".dtp"){
    containerDir = fName;
    fName += ".dtp";
  } else{
    containerDir = fName.left(fName.length() - 4 );
  }

  return containerDir;
}

QString ProjectManager::getSaveRootDir(QString saveName){
  int i, lim;
  QString rootUrl;
  QStringList linkData;

  linkData = breakSaveString(saveName);
  lim = linkData.length();

  for(i = 0; i < lim - 1; i++) rootUrl += linkData[i] + "/";

  rootUrl = rootUrl.left(rootUrl.length() - 1);

  return rootUrl;
}

void ProjectManager::saveAs(QString saveName){
  QString fName, containerDir, rootUrl;

  if (saveName.trimmed() != ""){
    fName = getSaveFName(saveName);
    containerDir = getSaveContainer(saveName);
    rootUrl = getSaveRootDir(saveName);

    createSaveEnvironment(fName, containerDir, rootUrl);
  }
}

void ProjectManager::createSaveContainer(QString containerDir, QString rootUrl){
  QString targetContainer;
  QDir targetContainerDir;

  targetContainer = rootUrl + "/" + containerDir;
  targetContainerDir.setPath(targetContainer);

  if (targetContainerDir.exists()) removeDir(targetContainer);

  targetContainerDir.mkdir(targetContainer);
}

void ProjectManager::createSaveImageDir(QString containerDir, QString rootUrl){
  QString imgRoot;
  QDir dummyDir;

  imgRoot = rootUrl + "/" + containerDir + "/images";

  dummyDir.mkdir(imgRoot);
}

void ProjectManager::copySaveImageEnvironment(QString containerDir, QString rootUrl){
  QString projectWorkingDir, imageRootDir, newImgRoot;
  QDir dummyDir;

  projectWorkingDir = getWorkingDir();
  imageRootDir = projectWorkingDir + "/images";
  newImgRoot = rootUrl + "/" + containerDir + "/images";

  copyPath(imageRootDir + "/full", newImgRoot + "/full", true);
  copyPath(imageRootDir + "/refined", newImgRoot + "/refined", true);
  copyPath(imageRootDir + "/thumbnail", newImgRoot + "/thumbnail", true);
}

void ProjectManager::createSaveImageEnvironment(QString containerDir, QString rootUrl){
  createSaveImageDir(containerDir, rootUrl);
  copySaveImageEnvironment(containerDir, rootUrl);
}

void ProjectManager::reConfigurePageRoot(QString rootUrl){
  int i, lim;

  lim = pageList.length();

  for(i = 0; i < lim; i++){
    pageList[i].updateRoot(rootUrl);
  }

}

void ProjectManager::createSaveEnvironment(QString fName, QString containerDir, QString rootUrl){
  createSaveContainer(containerDir, rootUrl);
  createSaveImageEnvironment(containerDir, rootUrl);
  configureRoot(rootUrl, containerDir);
  reConfigurePageRoot(rootUrl + "/" + containerDir);
  dtpGenerateFile(fName);

  std::cout << "File: " << fName.toUtf8().data() << std::endl;
  std::cout << "Container: " << containerDir.toUtf8().data() << std::endl;
  std::cout << "Root URL: " << rootUrl.toUtf8().data() << std::endl;
}

void ProjectManager::dtpGenerateFile(QString fName){
  QString pgNames, pgSemantics, pgData, sendData;

  sendData = dtpGetPageNames();
  sendData += "\n\n";
  sendData += dtpGetPageSemantics();
  sendData += "\n\n";
  sendData += dtpGetData();

  createProjectFile("/" + fName, sendData);
}

QString ProjectManager::dtpGetPageNames(){
  QString sendList;
  QString dummy;
  int i, lim;

  lim = pageList.length();
  for (i = 0; i < lim; i++){
    dummy = "ADDPAGE " + pageList[i].getFName();
    sendList += dummy + "\n";
  }

  return sendList;
}

QString ProjectManager::dtpGetPageSemantics(){
  QString sendList;
  QString dummy;
  int i, lim;

  sendList = "";

  lim = pageList.length();
  for (i = 0; i < lim; i++){

    if(pageList[i].getOcrStatus()){
      dummy = "SEMANTICS " + QString::number(i) + " " + dtpGenerateSemantics(i);
      sendList += dummy + "\n";
    }
  }
  return sendList;
}

QString ProjectManager::dtpGenerateSemantics(int index){
  QString sendList, dummy, myData, lineBool;
  int i, lim;
  QVector<wordUnit> myContents;

  sendList = "";

  myContents = pageList[index].getAllWords();
  lim = myContents.length();

  for(i = 0; i < lim; i++){
    if(myContents[i].newLine){
      myData = "///n///";
      lineBool = " true";
    } else {
      myData = myContents[i].data;
      lineBool = " false";
    }

    dummy = myData + " " + QString::number(myContents[i].x1) + " " + QString::number(myContents[i].y1);
    dummy += " " + QString::number(myContents[i].x2) + " " + QString::number(myContents[i].y2);
    dummy += " " + QString::number(myContents[i].lineNo) + " " + QString::number(myContents[i].wordNo);
    dummy += lineBool;
    sendList += dummy + "__@n@__";
  }

  sendList = sendList.left(sendList.length() - 7); //removing trailing __@n@__

  return sendList;
}

QString ProjectManager::dtpGetData(){
  QString sendList;
  QString dummy;
  int i, lim;

  sendList = "";

  lim = pageList.length();
  for (i = 0; i < lim; i++){

    if(pageList[i].getOcrStatus()){
      dummy = "DATA " + QString::number(i) + " " + pageList[i].getText().replace("\n","///n///" );
      sendList += dummy + "\n";
    }
  }
  return sendList;
}


//Foreign dependencies:
void ProjectManager::injectEventManager(EventManager *eManager){
  localEventManager = eManager;
}

void ProjectManager::publishPagesChanged(){
  localEventManager->publish("pagesChanged");
}
