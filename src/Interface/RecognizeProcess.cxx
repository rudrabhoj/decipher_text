#include <Interface/RecognizeProcess.hh>
#include <iostream>

RecognizeProcess::RecognizeProcess(QWidget *parent, ControlData *ctrlData) : QDialog(parent){
  localControl = ctrlData;

  setModal(true);
  setWindowTitle("Recognizing...");
  resize(350, 100);

  allocateResources();

  configureLabels();
  configureProcessbars();
  configureLayout();
  configureConnections();
}

void RecognizeProcess::allocateResources(){
  centralLayout = new QVBoxLayout();
  description = new QLabel();
  progress = new QProgressBar();
}

void RecognizeProcess::configureProcessbars(){
  progress->setParent(this);

  progress->setMinimum(0);
  progress->setMaximum(0);
}

void RecognizeProcess::configureLabels(){
  description->setParent(this);
  description->setText("Recognizing Page, Please wait...");
}

void RecognizeProcess::configureLayout(){
  centralLayout->setSpacing(15);
  centralLayout->setAlignment(Qt::AlignVCenter);

  centralLayout->addWidget(description);
  centralLayout->addWidget(progress);

  setLayout(centralLayout);
}

void RecognizeProcess::displayDialog(){
  //tessRecog = new TesseractRecognize(localControl);

  show();
}

void RecognizeProcess::recognizeNow(QString pageLink, int pageIndex){
  displayDialog();

  implementOcr(pageLink, pageIndex);
}

void RecognizeProcess::closeDialog(){
  //delete tessRecog;
  unSetSave();
  accept();
}


//Primary Foreign Dependents

void RecognizeProcess::implementOcr(QString pageLink, int pageIndex){
  TesseractRecognize recognizeDaemon(localControl);
  recognizeDaemon.recognize(pageLink, pageIndex);
}

void RecognizeProcess::unSetSave(){
  localControl->getProjectManager()->setSaveState(false);
}

void RecognizeProcess::configureConnections(){
  onOcrProcessed = [&](){closeDialog();};

  localControl->getPubSub()->subscribe("ocrProcessed", &onOcrProcessed);
}
