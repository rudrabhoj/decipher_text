#include <Interface/MainWindow.hh>
#include <iostream>
#include <QStringList>
#include <QFileDialog>
#include <QStandardPaths>
#include <QFontDialog>
#include <Document/Page.hh>

MainWindow::MainWindow(QMainWindow *parent, ControlData *ctrlData) : QMainWindow(parent){
  localControl = ctrlData;

  setWindowTitle(configurAppName());
  resize(1280, 720);
  this->setWindowIcon( QIcon(getAppIconPath()) );

  centralWidget = new QWidget();
  this->setCentralWidget(centralWidget);

  allocateResources();

  configurePageList();

  configureCanvas();

  configureEditor();

  configureSplitters();

  loadLanguages();

  configureAction();

  configureMenu();

  configureSettingWindow();
  configureReplaceDialog();

  configureAboutWindow();

  configureRProcessDialog();

  configureConnections();

  configureToolbar();

  configureLayout();

  setSignalWrappers();

  show();
}

void MainWindow::allocateResources(){
  pageList = new PageNav(this, localControl);
  mainLayout = new QHBoxLayout();
  canvasObject = new Canvas(this, localControl);
  statusBar = new Status(this, localControl);
  editor = new TextEditor(this, localControl);
  mainSplitters = new QSplitter();
}

void MainWindow::configurePageList(){
  pageList->setParent(centralWidget);
}

void MainWindow::configureCanvas(){
  canvasObject->configureSettings(centralWidget);
}

void MainWindow::configureEditor(){
  editor->setParent(centralWidget);
  editor->editorFontSetting();
}

void MainWindow::configureSplitters(){
  QList<int> sizes = {60, 300, 300};

  mainSplitters->setOrientation(Qt::Horizontal);
  mainSplitters->setParent(centralWidget);

  mainSplitters->addWidget(pageList);
  mainSplitters->addWidget(canvasObject);
  mainSplitters->addWidget(editor);

  mainSplitters->setSizes(sizes);
}

void MainWindow::configureLayout(){
  mainLayout->addWidget(mainSplitters);
  centralWidget->setLayout(mainLayout);
  setStatusBar(statusBar);
}

void MainWindow::configureAction(){
  QString newProjectString = "&New Project";
  QString openProjectString = "&Open Existing Project";
  QString addImagesString = "&Add Images";
  QString saveProjectString = "&Save Project";
  QString saveAsProjectString = "&Save Project As";
  QString exitString = "&Exit";
  QString zoomInString = "&Zoom In";
  QString zoomOutString = "&Zoom Out";
  QString zoomNormalString = "&Zoom Normal";
  QString replaceTextString = "&Replace Text";
  QString fontSettingsString = "&Font Preferences";
  QString orcNowString = "&OCR Current Page";
  QString orcAllString = "&OCR All Pages";
  QString prefSettingsString = "&Settings";
  QString aboutString = "&About";
  QString documentationString = "&Documentation";

  QString iconPath = localControl->getSetting()->getIconDir();

  QPixmap newPix(iconPath + "/new.png");
  QPixmap openPix(iconPath + "/open.png");
  QPixmap savePix(iconPath + "/save.png");
  QPixmap zoomInPix(iconPath + "/zoom_in.png");
  QPixmap zoomOutPix(iconPath + "/zoom_out.png");
  QPixmap zoomNormalPix(iconPath + "/zoom_normal.png");
  QPixmap ocrNowPix(iconPath + "/ocr.png");
  QPixmap ocrAllPix(iconPath + "/ocrAll.png");
  QPixmap settingPix(iconPath + "/setting.png");

  newProject = new QAction(QIcon(newPix), newProjectString, this);
  newProject->setIconVisibleInMenu(false);

  openProject = new QAction(QIcon(openPix), openProjectString, this);
  openProject->setIconVisibleInMenu(false);

  addImages = new QAction(addImagesString, this);

  saveProject = new QAction(QIcon(savePix), saveProjectString, this);
  saveProject->setIconVisibleInMenu(false);

  saveAsProject = new QAction(saveAsProjectString, this);
  saveAsProject->setIconVisibleInMenu(false);

  exit = new QAction(exitString, this);
  exit->setIconVisibleInMenu(false);

  zoomIn = new QAction(QIcon(zoomInPix), zoomInString, this);
  zoomIn->setIconVisibleInMenu(false);

  zoomOut = new QAction(QIcon(zoomOutPix), zoomOutString, this);
  zoomOut->setIconVisibleInMenu(false);

  zoomNormal = new QAction(QIcon(zoomNormalPix), zoomNormalString, this);
  zoomNormal->setIconVisibleInMenu(false);

  replaceText = new QAction(replaceTextString, this);

  orcNow = new QAction(QIcon(ocrNowPix), orcNowString, this);
  orcNow->setIconVisibleInMenu(false);

  orcAll = new QAction(QIcon(ocrAllPix), orcAllString, this);
  orcAll->setIconVisibleInMenu(false);

  fontSettings = new QAction(fontSettingsString, this);
  fontSettings->setIconVisibleInMenu(false);

  prefSettings = new QAction(QIcon(settingPix), prefSettingsString, this);
  prefSettings->setIconVisibleInMenu(false);

  about = new QAction(aboutString, this);
  about->setIconVisibleInMenu(false);

  documentation = new QAction(documentationString, this);
  documentation->setIconVisibleInMenu(false);

  configureLanguageActions();
}

void MainWindow::configureLanguageActions(){
  int i, lim;
  QAction *lang;

  lim = allLanguages.length();

  for(i = 0; i < lim; i++){
    lang = new QAction(allLanguages[i], this);
    lang->setCheckable(true);
    if (allLanguages[i] == defaultOCRLanguage()) lang->setChecked(true);
    languageActions.push_back(lang);
  }
}

void MainWindow::configureSettingWindow(){
  settingWindow = new SettingDialog(this, localControl);
}

void MainWindow::configureReplaceDialog(){
  replaceDialog = new ReplaceDialog(this, localControl);
}

void MainWindow::configureAboutWindow(){
  aboutWindow = new About(this, localControl);
}

void MainWindow::configureRProcessDialog(){
  rProcessDialog = new RecognizeProcess(this, localControl);
}

void MainWindow::configureConnections(){
  configureMenuConnections();
  configureWidgetConnections();
}

void MainWindow::configureMenuConnections(){
  connect(newProject, &QAction::triggered, this, &MainWindow::handleNewProject);
  connect(openProject, &QAction::triggered, this, &MainWindow::handleOpenProject);
  connect(saveProject, &QAction::triggered, this, &MainWindow::handleSaveProject);
  connect(saveAsProject, &QAction::triggered, this, &MainWindow::handleSaveAsProject);
  connect(addImages, &QAction::triggered, this, &MainWindow::handleAddProject);
  connect(zoomIn, &QAction::triggered, this, [&](){canvasObject->zoomIn();});
  connect(zoomOut, &QAction::triggered, this, [&](){canvasObject->zoomOut();});
  connect(zoomNormal, &QAction::triggered, this, [&](){canvasObject->zoomNormal();});
  connect(replaceText, &QAction::triggered, this, &MainWindow::handleReplaceText);

  connect(fontSettings, &QAction::triggered, this, &MainWindow::setFontPreferences);

  connect(prefSettings, &QAction::triggered, this, [&](){settingWindow->displayDialog();});
  connect(about, &QAction::triggered, this, [&](){aboutWindow->displayDialog();});
  connect(orcNow, &QAction::triggered, this, [&](){handleRecognizeNow(false);});
  connect(orcAll, &QAction::triggered, this, [&](){handleRecognizeNow(true);});

  configureLanguageConnections();
}

void MainWindow::configureLanguageConnections(){
  int i, lim;
  lim = languageActions.length();

  for(i = 0; i < lim; i++){
    connect(languageActions[i], &QAction::changed, this, &MainWindow::handleLanguageChange);
  }
}

void MainWindow::configureWidgetConnections(){
  //Nothing to do for now
}



void MainWindow::handleRecognizeNow(bool ifAllPages){
  int i;
  i = pageList->currentRow();

  if (i > -1){
    rProcessDialog->recognizeNow(getFullPage(pageList->currentRow()), pageList->currentRow(), ifAllPages);
    loadOCRedText();
  }
}

void MainWindow::handleLanguageChange(){
  int i, lim;
  lim = languageActions.length();

  for(i = 0; i < lim; i++){

    if(languageActions[i]->isChecked()){
      sendEnableLangRequest(languageActions[i]->text());
    } else {
      sendDisableLangRequest(languageActions[i]->text());
    }
  }

  std::cout << localControl->getLanguage()->getLanguageArgument().toUtf8().data() << std::endl;
}

void MainWindow::handleReplaceText(){
  int i;
  i = pageList->currentRow();

  if (i > -1){
    replaceDialog->displayDialog(i);
  }
}

void MainWindow::handleOpenProject(){
  QStringList openNames;
  int lim;

  openNames = QFileDialog::getOpenFileNames(this, "Select a project file to open...", QDir::homePath(),
    "Decipher Text Project (*.dtp)");
  lim = openNames.length();

  if (lim > 0){
    localControl->getProjectManager()->openProject(openNames[0]);
  }
}

void MainWindow::handleSaveProject(){
  if(localControl->getProjectManager()->getSaveHistory()){
    localControl->getProjectManager()->justSave();
  } else {
    handleSaveAsProject();
  }

}

void MainWindow::handleNewProject(){
  localControl->getProjectManager()->newProject();
}

void MainWindow::handleSaveAsProject(){
  QString saveName;

  saveName = QFileDialog::getSaveFileName(this, "Save the project As...", QDir::homePath(),
    "Decipher Text Project (*.dtp)");

  localControl->getProjectManager()->saveAs(saveName);
}

void MainWindow::handleAddProject(){
  QStringList openNames;

  openNames = QFileDialog::getOpenFileNames(this, "Add image files to the project...", QDir::homePath(),
    "Images (*.png *.xpm *.jpg)");

  localControl->getProjectManager()->addPages(openNames);
}


void MainWindow::configureMenu(){
  QString fileString = "&File";
  QString toolsString = "&Tools";
  QString helpString = "&Help";

  file = this->menuBar()->addMenu(fileString);
  file->addAction(newProject);
  file->addAction(openProject);
  file->addAction(addImages);
  file->addAction(saveProject);
  file->addAction(saveAsProject);
  file->addAction(exit);

  tools = this->menuBar()->addMenu(toolsString);
  tools->addAction(orcNow);
  tools->addAction(orcAll);
  tools->addAction(replaceText);
  tools->addAction(fontSettings);
  tools->addAction(prefSettings);

  configureLanguageMenu();

  help = this->menuBar()->addMenu(helpString);
  help->addAction(about);
  help->addAction(documentation);
}

void MainWindow::configureLanguageMenu(){
  int i, lim;
  QString languageListString;

  lim = languageActions.length();
  languageListString = "&Languages";

  languageList = this->menuBar()->addMenu(languageListString);

  for(i = 0; i < lim; i++){
    languageList->addAction( languageActions[i] );
  }
}

void MainWindow::configureToolbar(){
  mainToolbar = addToolBar("Main Toolbar");
  mainToolbar->setIconSize(QSize(32, 32));

  mainToolbar->addAction(newProject);
  mainToolbar->addAction(openProject);
  mainToolbar->addAction(saveProject);

  mainToolbar->addSeparator();

  mainToolbar->addAction(zoomIn);
  mainToolbar->addAction(zoomOut);
  mainToolbar->addAction(zoomNormal);

  mainToolbar->addSeparator();

  mainToolbar->addAction(orcNow);
  mainToolbar->addAction(orcAll);
  mainToolbar->addAction(prefSettings);
}


void MainWindow::listItemChanged(){
  int i;
  i = pageList->currentRow();

  if (i >= 0){
    backupOldText();

    syncProjectManagerPageSelection(i);

    canvasObject->drawPage(getFullPage(i));
    loadOCRedText();
  } else {
    canvasObject->cleanPage();
    editor->clear();
  }
}

void MainWindow::handleCurrentReplaced(){
  loadOCRedText();
}

void MainWindow::updateWindowName(){
  setWindowTitle(configurAppName());
}



//Primary Dependence on Foreign Classes
QList<Page>* MainWindow::getPageLink(){
  return localControl->getProjectManager()->emitPages();
}

void MainWindow::backupOldText(){
  QList<Page>* localPages;
  int oldIndex;
  QString dummyDataX;

  localPages = getPageLink();

  oldIndex = pageList->getOldSelection();

  dummyDataX = editor->toPlainText();

  if(oldIndex > -1 && (*localPages)[oldIndex].getOcrStatus()){
    (*localPages)[oldIndex].resetDataX(dummyDataX);
  }

}

void MainWindow::syncProjectManagerPageSelection(int i){
  localControl->getProjectManager()->setCurrentPage(i);
}


void MainWindow::loadLanguages(){
  allLanguages = localControl->getLanguage()->getAll();
  enabledLanguages = localControl->getLanguage()->getEnabled();
}

void MainWindow::sendEnableLangRequest(QString lang){
  localControl->getLanguage()->requestEnable(lang);
}

void MainWindow::sendDisableLangRequest(QString lang){
  localControl->getLanguage()->disableLanguage(lang);
}

void MainWindow::loadOCRedText(){

  QList<Page>* localPages;
  int currentPage;

  localPages = getPageLink();
  currentPage = pageList->currentRow();

  if ( (*localPages)[currentPage].getOcrStatus() ){
    editor->syncText( (*localPages)[currentPage].getText() );
  }else {
    editor->syncText("");
  }
}

void MainWindow::setFontPreferences(){
  bool selectionStatus;
  QString family;
  double fntSize;

  QFont newFont = QFontDialog::getFont(&selectionStatus, editor->currentFont(), this);

  if(selectionStatus){
    family = newFont.family();
    fntSize = newFont.pointSize();

    localControl->getSetting()->setFontFamily(family); //foreign dep
    localControl->getSetting()->setFontSize(fntSize); //foreign dep

    localControl->getSetting()->editConfigFile("fontFamily", family);
    localControl->getSetting()->editConfigFile("fontSize", QString::number(fntSize));

    editor->setCurrentFont(newFont);
  } else {
    std::cout << "Nothing selected!" << std::endl;
  }
}

QString MainWindow::configurAppName(){
  return localControl->createName();
}

QString MainWindow::getAppIconPath(){
  return localControl->getSetting()->getIconDir() + "/app_icon.png";
}

//Secondary Dependence on Foreign Classes
void MainWindow::syncNavbar(){
  int lim, i;

  lim = getTotalPages();

  pageList->clear();

  for(i = 0; i < lim; i++){
    QListWidgetItem *tmpItem = new QListWidgetItem(QIcon(getThumbnailPage(i)), QString::number(i));
    pageList->addItem(tmpItem);
  }
}

QString MainWindow::getThumbnailPage(int index){
  QList<Page> *pageQList;
  pageQList = getPageLink();

  return (*pageQList)[index].getThumbLink();
}

int MainWindow::getTotalPages(){
  QList<Page> *pageQList;
  pageQList = getPageLink();

  return pageQList->length();
}

QString MainWindow::getFullPage(int index){
  QList<Page> *pageQList;
  pageQList = getPageLink();

  return (*pageQList)[index].getFullDisplayLink();
}

//Assists Foreigners
void MainWindow::setSignalWrappers(){
  pageUpdateWrapper = [&](){syncNavbar();};
  listNavUpdateWrapper = [&](){ listItemChanged(); };
  saveChanged = [&](){ updateWindowName(); };
  currentReplaced = [&](){ handleCurrentReplaced(); };

  localControl->getPubSub()->subscribe("pagesChanged", &pageUpdateWrapper);
  localControl->getPubSub()->subscribe("saveChanged", &saveChanged);
  localControl->getPubSub()->subscribe("pageNavSelChanged", &listNavUpdateWrapper);
  localControl->getPubSub()->subscribe("currentReplaced", &currentReplaced);
}


QString MainWindow::defaultOCRLanguage(){
  return "eng";
}
