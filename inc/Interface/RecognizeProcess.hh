#ifndef __INTERFACE_RECOGNIZEPROCESS_HH__
#define __INTERFACE_RECOGNIZEPROCESS_HH__
#include <functional>

#include <QDialog>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QList>
#include <QProgressBar>
#include <Control/TesseractRecognize.hh>

#include <Control/ControlData.hh>
#include <Document/Page.hh>

class RecognizeProcess : public QDialog {
public:
  RecognizeProcess(QWidget *parent, ControlData *ctrlData);
  void recognizeNow(QString pageLink, int pageIndex, bool recAllPages);

private:
  QVBoxLayout *centralLayout;
  QLabel *mainText;
  QProgressBar *progress;
  QList<QProgressBar*> subBars;

  ControlData *localControl;

  std::function<void()> onOcrProcessed;

  void allocateResources();
  void configureLabels();
  void configureProcessbars();
  void configureLayout();
  void displayDialog();
  void closeDialog();
  int getTotalCores();
  void reconfigureProcessbars(bool manyPages);

  //Foreigners
  TesseractRecognize *tessRecog;
  void unSetSave();
  void implementOcr(QString pageLink, int pageIndex, bool recAllPages);
  void configureConnections();
  int getPagesLen();
  void updateProcessStatus(int staat); //Foreigners call him
};

#endif
