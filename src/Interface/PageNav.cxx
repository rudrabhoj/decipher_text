#include <Interface/PageNav.hh>

PageNav::PageNav(QMainWindow *parent, ControlData *ctrlData) : QListWidget(parent){
  localControl = ctrlData;
  setParent(parent);

  configure();
}

void PageNav::configure(){
  setViewMode(QListView::IconMode);
  setIconSize(QSize(104, 148));
  setPastSelection(-1);
}

int PageNav::presentSelection(){
  return currentRow();
}

int PageNav::pastSelection(){
  return oldSelection;
}


void PageNav::setPastSelection(int index){
  oldSelection = index;
}
