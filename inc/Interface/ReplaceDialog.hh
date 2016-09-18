#ifndef __INTERFACE_REPLACEDIALOG_HH__
#define __INTERFACE_REPLACEDIALOG_HH__

#include <QDialog>
#include <Control/ControlData.hh>

namespace Ui {
class ReplaceDialog;
}

class ReplaceDialog : public QDialog
{
  Q_OBJECT

public:
  explicit ReplaceDialog(QWidget *parent, ControlData *ctrData);
  ~ReplaceDialog();

private:
  ControlData *localControl;
  Ui::ReplaceDialog *ui;
};

#endif // __INTERFACE_REPLACEDIALOG_HH__
