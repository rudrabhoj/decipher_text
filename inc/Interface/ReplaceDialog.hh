#ifndef __INTERFACE_REPLACEDIALOG_HH__
#define __INTERFACE_REPLACEDIALOG_HH__

#include <QDialog>
#include <QList>

#include <Control/ControlData.hh>
#include <Document/Page.hh>

namespace Ui {
class ReplaceDialog;
}

class ReplaceDialog : public QDialog
{
  Q_OBJECT

public:
  explicit ReplaceDialog(QWidget *parent, ControlData *ctrData);
  void displayDialog(int inCurrentItem);
  ~ReplaceDialog();

private:
  ControlData *localControl;
  Ui::ReplaceDialog *ui;
  int currentItem;

  void connectButtons();
  void replaceCurrent();
  void replaceAll();
  int getTotalPages();

  //Foreign Dependents
  QList<Page> *getPages();
  void replaceAt(int pos, QString original, QString replacement);
  void publishCurrentReplaced();
};

#endif // __INTERFACE_REPLACEDIALOG_HH__
