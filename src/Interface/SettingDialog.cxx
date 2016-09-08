#include <Interface/SettingDialog.hh>
#include <iostream>

SettingDialog::SettingDialog(QWidget *parent, ControlData *ctrlData) : QDialog(parent){
  localControl = ctrlData;

  generalSetting();
  resourceAcquisition();
  setupButtons();
  setupLabels();
  setupEditors();
  configureLayout();
  configureConnections();
}

void SettingDialog::resourceAcquisition(){
  localSetting = localControl->getSetting();
}

void SettingDialog::generalSetting(){
  setModal(true);
  setWindowTitle("Settings");
  resize(840, 420);
}

void SettingDialog::setupButtons(){
  okayButton = new QPushButton(this);
  okayButton->setText("Okay");

  cancelButton = new QPushButton(this);
  cancelButton->setText("Cancel");
}

void SettingDialog::setupLabels(){
  tesseractPathLabel = new QLabel(this);
  tesseractPathLabel->setText("Tesseract Path:");
  tesseractPathLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

  tessdataPathLabel = new QLabel(this);
  tessdataPathLabel->setText("Tessdata Path:");
  tessdataPathLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

  appNameLabel = new QLabel(this);
  appNameLabel->setText("Application Name:");
  appNameLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

  interfaceLanguageLabel = new QLabel(this);
  interfaceLanguageLabel->setText("Interface Language:");
  interfaceLanguageLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

  emptyLabel = new QWidget(this);
  emptyLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void SettingDialog::setupEditors(){
  tesseractPathEditor = new QLineEdit(this);
  tesseractPathEditor->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

  tessdataPathEditor = new QLineEdit(this);
  tessdataPathEditor->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

  appNameEditor = new QLineEdit(this);
  appNameEditor->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

  interfaceLanguageEditor = new QLineEdit(this);
  interfaceLanguageEditor->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
}

void SettingDialog::configureLayout(){
  rowLayout = new QVBoxLayout();
  rowLayout->setSpacing(24);

  col1 = new QHBoxLayout();
  col1->setSpacing(1);

  col2 = new QHBoxLayout();
  col2->setSpacing(1);

  col3 = new QHBoxLayout();
  col3->setSpacing(1);

  col4 = new QHBoxLayout();
  col4->setSpacing(1);

  col5 = new QHBoxLayout();
  col5->setSpacing(1);

  col5_1 = new QHBoxLayout();
  col5_1->setSpacing(1);

  col1->addWidget(tesseractPathLabel);
  col1->addWidget(tesseractPathEditor);

  col2->addWidget(tessdataPathLabel);
  col2->addWidget(tessdataPathEditor);

  col3->addWidget(appNameLabel);
  col3->addWidget(appNameEditor);

  col4->addWidget(interfaceLanguageLabel);
  col4->addWidget(interfaceLanguageEditor);

  col5_1->addWidget(okayButton);
  col5_1->addWidget(cancelButton);

  col5->addWidget(emptyLabel);
  col5->addItem(col5_1);

  rowLayout->addLayout(col1);
  rowLayout->addLayout(col2);
  rowLayout->addLayout(col3);
  rowLayout->addLayout(col4);
  rowLayout->addLayout(col5);

  setLayout(rowLayout);
}

void SettingDialog::loadDefaultText(){
  QString tesseractPathDefault;
  QString tessdataPathDefault;
  QString appNameDefault;
  QString interfaceLanguageDefault;

  tesseractPathDefault = localSetting->getTesseractPath();
  tessdataPathDefault = localSetting->getTessdataPath();
  appNameDefault = localSetting->getAppName();
  interfaceLanguageDefault = localSetting->getInterfaceLanguage();

  tesseractPathEditor->setText(tesseractPathDefault);
  tessdataPathEditor->setText(tessdataPathDefault);
  appNameEditor->setText(appNameDefault);
  interfaceLanguageEditor->setText(interfaceLanguageDefault);
}

void SettingDialog::configureConnections(){
  connect(cancelButton, &QPushButton::clicked, this, &SettingDialog::reject);
  connect(okayButton, &QPushButton::clicked, this, &SettingDialog::commitChanges);
}

void SettingDialog::commitChanges(){
  QString tesseractPathDefault = tesseractPathEditor->text();
  QString tessdataPathDefault = tessdataPathEditor->text();
  QString appNameDefault = appNameEditor->text();
  QString interfaceLanguageDefault = interfaceLanguageEditor->text();

  localSetting->editConfigFile("tesseractPath", tesseractPathDefault);
  localSetting->editConfigFile("tessdataPath", tessdataPathDefault);
  localSetting->editConfigFile("appName", appNameDefault);
  localSetting->editConfigFile("interfaceLanguage", interfaceLanguageDefault);

  accept();
}


void SettingDialog::displayDialog(){
  loadDefaultText();
  show();
}
