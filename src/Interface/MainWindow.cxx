#include <Interface/MainWindow.hh>
#include <iostream>

MainWindow::MainWindow(QMainWindow *parent, ControlData *ctrlData) : QMainWindow(parent){
  localControl = ctrlData;

  setWindowTitle("Decipher Text");
  resize(1280, 720);

  centralWidget = new QWidget();
  this->setCentralWidget(centralWidget);

  allocateResources();

  configurePageList();

  configureCanvas();

  configureEditor();

  configureSplitters();

  configureAction();

  configureMenu();

  configureToolbar();

  configureLayout();

  show();
}

void MainWindow::allocateResources(){
  pageList = new QListWidget();
  mainLayout = new QHBoxLayout();
  canvas = new QGraphicsScene();
  canvasDisplay = new QGraphicsView();
  editor = new QTextEdit();
  mainSplitters = new QSplitter();
}

void MainWindow::configurePageList(){
  pageList->setParent(centralWidget);
}

void MainWindow::configureCanvas(){
  canvas->setParent(centralWidget);
  canvas->addText("Our Glorious scans would be here soon.");
  canvasDisplay->setParent(centralWidget);
  canvasDisplay->setScene(canvas);
}

void MainWindow::configureEditor(){
  editor->setParent(centralWidget);
}

void MainWindow::configureSplitters(){
  QList<int> sizes = {15, 605, 605};

  mainSplitters->setOrientation(Qt::Horizontal);
  mainSplitters->setParent(centralWidget);

  mainSplitters->addWidget(pageList);
  mainSplitters->addWidget(canvasDisplay);
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
}

void MainWindow::configureMenu(){
  QString fileString = "&File";
  QString toolsString = "&Tools";
  QString helpString = "&Help";

  file = this->menuBar()->addMenu(fileString);
  file->addAction(newProject);
  file->addAction(openProject);
  file->addAction(saveProject);
  file->addAction(saveAsProject);
  file->addAction(exit);

  tools = this->menuBar()->addMenu(toolsString);
  tools->addAction(orcNow);
  tools->addAction(prefSettings);

  help = this->menuBar()->addMenu(helpString);
  help->addAction(about);
  help->addAction(documentation);
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

