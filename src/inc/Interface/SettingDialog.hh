#ifndef __INTERFACE_SETTINGDIALOG_HH__
#define __INTERFACE_SETTINGDIALOG_HH__

#include <QDialog>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include <Control/ControlData.hh>
#include <Control/Setting.hh>

class SettingDialog : public QDialog {
public:
  SettingDialog(QWidget *parent, ControlData *ctrlData);
  void displayDialog();

private:
  Setting *localSetting;
  ControlData *localControl;

  QVBoxLayout *rowLayout;
  QHBoxLayout *col1;
  QHBoxLayout *col2;
  QHBoxLayout *col3;
  QHBoxLayout *col4;
  QHBoxLayout *col5;
  QHBoxLayout *col5_1;

  QPushButton *okayButton;
  QPushButton *cancelButton;

  QLabel *tesseractPathLabel;
  QLabel *tessdataPathLabel;
  QLabel *appNameLabel;
  QLabel *interfaceLanguageLabel;
  QWidget* emptyLabel;

  QLineEdit *tesseractPathEditor;
  QLineEdit *tessdataPathEditor;
  QLineEdit *appNameEditor;
  QLineEdit *interfaceLanguageEditor;


  void resourceAcquisition();
  void generalSetting();
  void setupButtons();
  void setupLabels();
  void setupEditors();
  void configureLayout();
  void loadDefaultText();
  void configureConnections();
  void commitChanges();
};

#endif