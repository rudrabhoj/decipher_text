#include <Interface/MainWindow.hh>
#include <iostream>
#include <QStringList>
#include <QFileDialog>
#include <QStandardPaths>
#include <Document/Page.hh>

MainWindow::MainWindow(QMainWindow *parent, ControlData *ctrlData) : QMainWindow(parent){
  localControl = ctrlData;

  setWindowTitle(localControl->getSetting()->getAppName());
  resize(1280, 720);

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

  configureRProcessDialog();

  configureConnections();

  configureToolbar();

  configureLayout();

  setSignalWrappers();

  show();
}

void MainWindow::allocateResources(){
  pageList = new QListWidget();
  mainLayout = new QHBoxLayout();
  canvasObject = new Canvas(0, localControl);
  editor = new QTextEdit();
  mainSplitters = new QSplitter();
}

void MainWindow::configurePageList(){
  pageList->setParent(centralWidget);
  pageList->setViewMode(QListView::IconMode);
  pageList->setIconSize(QSize(104, 148));
}

void MainWindow::configureCanvas(){
  canvasObject->configureSettings(centralWidget);
}

void MainWindow::configureEditor(){
  editor->setParent(centralWidget);
  editorFontSetting();
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
  QString orcNowString = "&OCR";
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
  QPixmap settingPix(iconPath + "/setting.png");

  newProject = new QAction(QIcon(newPix), newProjectString);
  newProject->setIconVisibleInMenu(false);

  openProject = new QAction(QIcon(openPix), openProjectString);
  openProject->setIconVisibleInMenu(false);

  addImages = new QAction(addImagesString);

  saveProject = new QAction(QIcon(savePix), saveProjectString);
  saveProject->setIconVisibleInMenu(false);

  saveAsProject = new QAction(saveAsProjectString);
  saveAsProject->setIconVisibleInMenu(false);

  exit = new QAction(exitString);
  exit->setIconVisibleInMenu(false);

  zoomIn = new QAction(QIcon(zoomInPix), zoomInString);
  zoomIn->setIconVisibleInMenu(false);

  zoomOut = new QAction(QIcon(zoomOutPix), zoomOutString);
  zoomOut->setIconVisibleInMenu(false);

  zoomNormal = new QAction(QIcon(zoomNormalPix), zoomNormalString);
  zoomNormal->setIconVisibleInMenu(false);

  orcNow = new QAction(QIcon(ocrNowPix), orcNowString);
  orcNow->setIconVisibleInMenu(false);

  prefSettings = new QAction(QIcon(settingPix), prefSettingsString);
  prefSettings->setIconVisibleInMenu(false);

  about = new QAction(aboutString);
  about->setIconVisibleInMenu(false);

  documentation = new QAction(documentationString);
  documentation->setIconVisibleInMenu(false);

  configureLanguageActions();
}

void MainWindow::configureLanguageActions(){
  int i, lim;
  QAction *lang;

  lim = allLanguages.length();

  for(i = 0; i < lim; i++){
    lang = new QAction(allLanguages[i]);
    lang->setCheckable(true);
    if (allLanguages[i] == defaultOCRLanguage()) lang->setChecked(true);
    languageActions.push_back(lang);
  }
}

void MainWindow::configureSettingWindow(){
  settingWindow = new SettingDialog(this, localControl);
}

void MainWindow::configureRProcessDialog(){
  rProcessDialog = new RecognizeProcess(this, localControl);
}

void MainWindow::configureConnections(){
  configureMenuConnections();
  configureWidgetConnections();  
}

void MainWindow::configureMenuConnections(){
  connect(openProject, &QAction::triggered, this, &MainWindow::handleOpenProject);
  connect(addImages, &QAction::triggered, this, &MainWindow::handleAddProject);
  connect(zoomIn, &QAction::triggered, this, [&](){canvasObject->zoomIn();});
  connect(zoomOut, &QAction::triggered, this, [&](){canvasObject->zoomOut();});
  connect(zoomNormal, &QAction::triggered, this, [&](){canvasObject->zoomNormal();});

  connect(prefSettings, &QAction::triggered, this, [&](){settingWindow->displayDialog();});
  connect(orcNow, &QAction::triggered, this, &MainWindow::handleRecognizeNow);

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
  connect(pageList, &QListWidget::currentItemChanged, this, &MainWindow::testMessagePrint);
}

void MainWindow::editorFontSetting(){
  if (getConfigFontFamily() != "NaN"){
    editor->setFontFamily(getConfigFontFamily());
  }

  editor->setFontPointSize(getConfigFontSize());
}

 

void MainWindow::handleRecognizeNow(){
  int i;
  i = pageList->currentRow();

  if (i > -1){
    rProcessDialog->recognizeNow(getFullPage(pageList->currentRow()), pageList->currentRow());
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

void MainWindow::handleOpenProject(){
  QStringList openNames;
  int i, lim;

  openNames = QFileDialog::getOpenFileNames(this, "Select a project file to open...", QDir::homePath(),
    "Decipher Text Project (*.dtp)");
  lim = openNames.length();

  for (i = 0; i < lim; i++){
    std::cout << openNames[i].toUtf8().data() << std::endl;
  }
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
  mainToolbar->addAction(prefSettings);
}


void MainWindow::testMessagePrint(){
  int i;
  i = pageList->currentRow();

  if (i >= 0){
    canvasObject->drawPage(getFullPage(i));
    loadOCRedText();
  }
}



//Primary Dependence on Foreign Classes
QList<Page>* MainWindow::getPageLink(){
  return localControl->getProjectManager()->emitPages();
}

QString MainWindow::getConfigFontFamily(){
  return localControl->getSetting()->getFontFamily();
}

double MainWindow::getConfigFontSize(){
  return localControl->getSetting()->getFontSize();
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
    editor->clear();
    editorFontSetting();
    editor->setText((*localPages)[currentPage].getText());
  }else {
    editorFontSetting();
    editor->clear();
  }
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

  localControl->getPubSub()->subscribe("pagesChanged", &pageUpdateWrapper);
}

QString MainWindow::defaultOCRLanguage(){
  return "eng";
}