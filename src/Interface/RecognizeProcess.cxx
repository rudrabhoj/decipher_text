#include <Interface/RecognizeProcess.hh>
#include <thread>
#include <functional>
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
  mainText = new QLabel();
  progress = new QProgressBar();
}

void RecognizeProcess::configureProcessbars(){
  progress->setParent(this);

  progress->setMinimum(0);
  progress->setMaximum(0);
}


void RecognizeProcess::reconfigureProcessbars(bool manyPages){
  int pagesToRecognize;
  QString recText;

  pagesToRecognize = getPagesLen();

  if(manyPages){
    progress->setMinimum(1);
    progress->setMaximum(pagesToRecognize);
    progress->setValue(1);

    recText = "Recognizing 1/" + QString::number(pagesToRecognize);
    progress->setFormat(recText +  " %p% ");
  }
}

void RecognizeProcess::configureLabels(){
  mainText->setParent(this);
  mainText->setText("Overall Process:");
}

void RecognizeProcess::configureLayout(){
  centralLayout->setSpacing(15);
  centralLayout->setAlignment(Qt::AlignVCenter);

  centralLayout->addWidget(mainText);
  centralLayout->addWidget(progress);

  setLayout(centralLayout);
}

void RecognizeProcess::displayDialog(){
  //tessRecog = new TesseractRecognize(localControl);

  show();
}

void RecognizeProcess::recognizeNow(QString pageLink, int pageIndex, bool recAllPages){
  displayDialog();
  reconfigureProcessbars(recAllPages);

  implementOcr(pageLink, pageIndex, recAllPages);
}

void RecognizeProcess::closeDialog(){
  //delete tessRecog;
  unSetSave();
  accept();
}

int RecognizeProcess::getTotalCores(){
  return std::thread::hardware_concurrency();
}


//Primary Foreign Dependents

void RecognizeProcess::implementOcr(QString pageLink, int pageIndex, bool recAllPages){
  std::function<void(int)> processConnector;
  processConnector = [&](int staat){updateProcessStatus(staat);};

  TesseractRecognize recognizeDaemon(localControl);
  recognizeDaemon.setUpdateConnector(&processConnector);
  recognizeDaemon.recognize(pageLink, pageIndex, recAllPages);
}

void RecognizeProcess::unSetSave(){
  localControl->getProjectManager()->setSaveState(false);
}

int RecognizeProcess::getPagesLen(){
  return localControl->getProjectManager()->emitPages()->length();
}

void RecognizeProcess::configureConnections(){
  onOcrProcessed = [&](){closeDialog();};

  localControl->getPubSub()->subscribe("ocrProcessed", &onOcrProcessed);
}

      //Foreigners call him, so kinda same ;)
void RecognizeProcess::updateProcessStatus(int staat){
  QString recText;
  int pagesToRecognize;

  pagesToRecognize = getPagesLen();

  progress->setValue(staat);

  recText = "Recognizing ";
  recText += QString::number(staat - (getTotalCores() - 1) );
  recText += "-";
  recText += QString::number(staat);
  recText += "/";
  recText += QString::number(pagesToRecognize);

  progress->setFormat(recText +  " %p% ");
}
