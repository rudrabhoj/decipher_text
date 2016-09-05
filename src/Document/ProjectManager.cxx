#include <Document/ProjectManager.hh>
#include <Document/wordUnit.hh>
#include <QDir>
#include <QVector>
#include <QTextStream>
#include <QStandardPaths>
#include <QCoreApplication>
#include <QFileInfo>
#include <iostream>

ProjectManager::ProjectManager(QString projDirName){
  loadEmptyDefault(projDirName);
}

void ProjectManager::loadEmptyDefault(QString projDirName){
  QString designatedRoot;

  designatedRoot = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation)[0] +
                                                              "/decipher_text Projects";

  configureRoot(designatedRoot, projDirName);

  verifyProjectRoot();

  createEmptyProject();

  //Should use direct set to avoid calling event manager too soon.
  saveState = false;
  saveHistory = false;

  setCurrentPageDefault();
  setSaveFileName("Untitled Project");
  setSavedUrl(getWorkingDir() + "/" + "Untitled Project.dtp");
}

void ProjectManager::configureRoot(QString rootName, QString projDirName){
  rootDir = rootName;
  dirName = projDirName;
  projectName = projDirName;
}

void ProjectManager::setSaveState(bool staat){
  if(!getSaveHistory() && staat == true) setSaveHistory(true);
  saveState = staat;

  publishSave();
}

bool ProjectManager::getSaveState(){
  return saveState;
}

void ProjectManager::setSaveHistory(bool staat){
  saveHistory = staat;
}

void ProjectManager::setSavedUrl(QString urlData){
  savedUrl = urlData;
}

QString ProjectManager::getSavedUrl(){
  return savedUrl;
}

bool ProjectManager::getSaveHistory(){
  return saveHistory;
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
  QString ofName, imagesRoot, imagesFull, imagesRefined, imagesThumb, commandExe;
  int futurePageIndex;

  ofName = oldFileInfo.fileName();

  imagesRoot = getWorkingDir() + "/images";
  imagesFull = imagesRoot + "/full";
  imagesRefined = imagesRoot + "/refined";
  imagesThumb = imagesRoot + "/thumbnail";

  QFile::copy(page, imagesFull + "/" + ofName);

  commandExe = getImageMagickCommand() + " ";
  commandExe += "\"" + imagesFull + "/" + ofName + "\"";
  commandExe += " -thumbnail 104x148! ";
  commandExe += "\"" + imagesThumb + "/" + ofName + "\"";

  system(commandExe.toUtf8().data());

  futurePageIndex = pageList.length();

  commitPage(ofName, futurePageIndex);
}

void ProjectManager::commitPage(QString ofName, int index){
  Page dummyPage(getWorkingDir(), index);
  dummyPage.setFileName(ofName);

  pageList.push_back(dummyPage);
  setSaveState(false);
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
  createProjectFile(getWorkingDir() + "/Untitled Project.dtp", "");

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

void ProjectManager::createProjectFile(QString targetName, QString projContents){
  QFile pFile;


  pFile.setFileName(targetName);

  if (pFile.open(QIODevice::WriteOnly)){
    QTextStream out(&pFile);

    out << projContents;

    pFile.close();
  }
}

void ProjectManager::setSaveFileName(QString svName){
  saveFileName = svName;
}

QString ProjectManager::getSaveFileName(){
  return saveFileName;
}

bool ProjectManager::sanitizationNeeded(QString testUrl){
  QStringList brokenUrl;
  QString fileSelf, fileContainer;
  int lim;

  brokenUrl = testUrl.split("/");
  lim = brokenUrl.length();
  fileSelf = brokenUrl[lim - 1];
  fileContainer = brokenUrl[lim - 2];
  if(fileSelf.indexOf(fileContainer) > -1){
    return true;
  } else {
    return false;
  }
}

QString ProjectManager::getImageMagickCommand(){
  QFileInfo location1;
  QFileInfo location2;
  QString binDir, path;

  binDir = QCoreApplication::applicationDirPath();
  return "convert";

  #ifdef _WIN32
  location1.setFile(binDir + "\\imagemagick\\convert.exe");
  location2.setFile(binDir + "\\imagemagick\\convert.exe"); //For now single location on windows
  #else
  location1.setFile("/usr/bin/convert");
  location2.setFile("/usr/local/bin/convert");
  #endif

  if(location1.exists() && location1.isFile()){
    path = location1.absoluteFilePath();
  } else if(location2.exists() && location2.isFile()) {
    path = location1.absoluteFilePath();
  } else {
    path = "";
  }

  return path;
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

QString ProjectManager::trimCommand(QString lineData, QString command, QString modifier){
  int trimLen, lim;
  QString sendData;

  trimLen = command.length() + modifier.length() + 1;
  lim = lineData.length();
  sendData = lineData.right(lim - trimLen);
  sendData = sendData.trimmed();

  return sendData;
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

  //#ifdef _WIN32
    //token = "\\";
  //#endif

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

void ProjectManager::newProject(){
  dtpDeleteAllPages();
  setSaveState(false);
  setSaveHistory(false);
  setSaveFileName("Untitled Project");
  setSavedUrl(getWorkingDir() + "/" + "Untitled Project.dtp");

  std::cout << "Publishing thing starts now" << std::endl;
  std::cout << "Pub 1" << std::endl;
  publishPagesChanged();
  std::cout << "Pub 2" << std::endl;
  publishSave();
  std::cout << "Pub 3" << std::endl;
}

QString ProjectManager::getSaveRootDir(QString saveName){
  int i, lim;
  QString rootUrl;
  QStringList linkData;

  linkData = breakSaveString(saveName);
  lim = linkData.length();

  for(i = 0; i < lim - 1; i++){
    rootUrl += linkData[i] + "/";
  }

  rootUrl = rootUrl.left(rootUrl.length() - 1);

  return rootUrl;
}

void ProjectManager::justSave(){
  saveAs(getSavedUrl());
}

void ProjectManager::saveAs(QString saveName){
  QString fName, containerDir, rootUrl;

  if (saveName.trimmed() != ""){
    if(sanitizationNeeded(saveName)) saveName = open2SaveUrlConvert(saveName);
    fName = getSaveFName(saveName);
    containerDir = getSaveContainer(saveName);
    rootUrl = getSaveRootDir(saveName);

  createSaveEnvironment(fName, containerDir, rootUrl);

    setSaveState(true);
  }
}

QString ProjectManager::open2SaveUrlConvert(QString openName){
  QStringList myList;
  QString sendData;
  int lim, i;

  myList = openName.split("/");
  lim = myList.length();

  for(i = 0; i < (lim - 1); i++){
    sendData += myList[i];
    if (i < lim - 2) sendData += "/";
  }

  sendData += ".dtp";

  return sendData;
}

void ProjectManager::openProject(QString openName){
  QString targetFile, targetRoot, targetContainer, originalOpenUrl;
  originalOpenUrl = openName;

  if (openName.trimmed() != "" && openName != getSavedUrl()){
    if(sanitizationNeeded(openName)) openName = open2SaveUrlConvert(openName);


    targetFile = getSaveFName(openName);
    targetContainer = getSaveContainer(openName);
    targetRoot = getSaveRootDir(openName);

    //configureRoot(targetRoot, targetContainer);
    dtpDeleteAllPages();
    publishPagesChanged();
    removeDir( getWorkingDir() );
    copyPath(targetRoot + "/" + targetContainer, getWorkingDir(), true);

    loadInterpretDtp(targetRoot, targetContainer, targetFile);
    setSaveState(true);
    setSaveFileName(targetContainer);
    setSavedUrl(originalOpenUrl);
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
  //configureRoot(rootUrl, containerDir);
  //reConfigurePageRoot(rootUrl + "/" + containerDir);
  dtpGenerateFile(rootUrl + "/" + containerDir + "/" + fName);
  setSaveFileName(containerDir);
  setSavedUrl(rootUrl + "/" + containerDir + "/" + fName);

  std::cout << "File: " << fName.toUtf8().data() << std::endl;
  std::cout << "Container: " << containerDir.toUtf8().data() << std::endl;
  std::cout << "Root URL: " << rootUrl.toUtf8().data() << std::endl;
}

void ProjectManager::dtpGenerateFile(QString fURL){
  QString pgNames, pgSemantics, pgData, sendData;

  sendData = dtpGetPageNames();
  sendData += "\n\n";
  sendData += dtpGetPageSemantics();
  sendData += "\n\n";
  sendData += dtpGetData();

  createProjectFile(fURL, sendData);
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

void ProjectManager::dtpDeleteAllPages(){
  if(pageList.length() > 0){
    pageList.clear();
  }
}

void ProjectManager::loadInterpretDtp(QString targetRoot, QString targetContainer, QString targetFile){
  QString targetUrl, lineData;
  QFile inputFile;

  targetUrl = targetRoot + "/" + targetContainer + "/" + targetFile;
  inputFile.setFileName(targetUrl);
  if(inputFile.open(QIODevice::ReadOnly)){
    QTextStream localInput(&inputFile);
    while(!localInput.atEnd()){
      lineData = localInput.readLine();
      interpretDtp(lineData);
    }
    inputFile.close();
  }
}

void ProjectManager::interpretDtp(QString lineData){
  QStringList brokenLine;
  QString command;
  int modifier;

  brokenLine = lineData.split(" ");
  command = brokenLine[0];

  if (command == "ADDPAGE"){
    lineData = trimCommand(lineData, command, "");
    interpretDtpAddPage(lineData);
  } else if(command == "SEMANTICS"){
    modifier = brokenLine[1].toInt();
    lineData = trimCommand(lineData, command, brokenLine[1]);
    interpretDtpSemantics(modifier, lineData);
  } else if(command == "DATA"){
    modifier = brokenLine[1].toInt();
    lineData = trimCommand(lineData, command, brokenLine[1]);
    interpretDtpData(modifier, lineData);
  }
}

void ProjectManager::interpretDtpAddPage(QString lineData){
  int index;

  index = pageList.length();

  commitPage(lineData, index);

  publishPagesChanged();
}

void ProjectManager::interpretDtpSemantics(int modifier, QString lineData){
  QStringList masterList, localList;
  int lim, i;
  QVector<wordUnit> localPageList;

  masterList = lineData.split("__@n@__");
  lim = masterList.length();

  for (i = 0; i < lim; i++){
    localList = masterList[i].split(" ");
    localPageList.push_back( getSemantics(localList) );
  }
  pageList[modifier].importOcr(localPageList);
}

wordUnit ProjectManager::getSemantics(QStringList sem){
  wordUnit dummyUnit;
  bool isNewPage;

  if(sem[7] == "true"){
    isNewPage = true;
  } else {
    isNewPage = false;
  }

  dummyUnit.data = sem[0].replace("///n///", "\n");
  dummyUnit.x1 = sem[1].toInt();
  dummyUnit.y1 = sem[2].toInt();
  dummyUnit.x2 = sem[3].toInt();
  dummyUnit.y2 = sem[4].toInt();
  dummyUnit.lineNo = sem[5].toInt();
  dummyUnit.wordNo = sem[6].toInt();
  dummyUnit.newLine = isNewPage;

  return dummyUnit;
}

void ProjectManager::interpretDtpData(int modifier, QString lineData){
  lineData = lineData.replace("///n///", "\n");
  pageList[modifier].resetDataX(lineData);
}


//Foreign dependencies:
void ProjectManager::injectEventManager(EventManager *eManager){
  localEventManager = eManager;
}

void ProjectManager::publishPagesChanged(){
  localEventManager->publish("pagesChanged");
}

void ProjectManager::publishSave(){
  localEventManager->publish("saveChanged");
}
