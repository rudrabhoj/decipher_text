#include <Interface/About.hh>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

About::About(QWidget *parent, ControlData *ctrlData) : QDialog(parent){
  localControl = ctrlData;

  configureDialog();
  allocateResources();
  configureGui();
  configureConnections();
}

void About::configureDialog(){
  setWindowTitle("About");
  setModal(true);
  resize(840, 420);
}

void About::allocateResources(){
  rowLayout = new QVBoxLayout();
  textBox = new QTextEdit();
  doneOkay = new QPushButton();
}

void About::configureTextbox(){
  textBox->setParent(this);
  loadAboutText();
  textBox->setReadOnly(true);
}

void About::configureButtons(){
  doneOkay->setParent(this);
  doneOkay->setText("Okay");
}

void About::configureLayout(){
  rowLayout->addWidget(textBox);
  rowLayout->addWidget(doneOkay);
  setLayout(rowLayout);
}

void About::configureGui(){
  configureTextbox();
  configureButtons();
  configureLayout();
}

void About::displayDialog(){
  show();
}

void About::hideDialog(){
  hide();
}

void About::configureConnections(){
  connect(doneOkay, &QPushButton::clicked, this, &About::hideDialog);
}

void About::loadAboutText(){
  QString aboutInfo;

  aboutInfo = getAboutData();
  aboutInfo = solveVariables(aboutInfo);
  textBox->setText(aboutInfo);
}

QString About::solveVariables(QString rawInput){
  rawInput = rawInput.replace("VERSION_NO", getVersion());

  return rawInput;
}

QString About::getAboutData(){
  QString url, lineData;
  QFile aboutTarget;

  url = getAboutUrl();
  aboutTarget.setFileName(url);

  if(!aboutTarget.open(QIODevice::ReadOnly)){
    QMessageBox::information(0, "error", aboutTarget.errorString());
  }

  QTextStream inputStream(&aboutTarget);

  while(!inputStream.atEnd()) lineData += inputStream.readLine() + "\n";

  aboutTarget.close();

  return lineData;
}

// Foreign dependents:
QString About::getAboutUrl(){
  return localControl->getSetting()->getAboutUrl();
}

QString About::getVersion(){
  return localControl->getVersion();
}
