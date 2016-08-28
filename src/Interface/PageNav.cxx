#include <Interface/PageNav.hh>

PageNav::PageNav(QMainWindow *parent, ControlData *ctrlData) : QListWidget(parent){
  localControl = ctrlData;
  setParent(parent);

  configure();
}

void PageNav::configure(){
  setViewMode(QListView::IconMode);
  setIconSize(QSize(104, 148));

  setOldSelection(-1);
  setNewSelection(-1);

  configureConnections();
}

int PageNav::getNewSelection(){
  return newSelection;
}

int PageNav::getOldSelection(){
  return oldSelection;
}


void PageNav::setOldSelection(int index){
  oldSelection = index;
}

void PageNav::setNewSelection(int index){
  newSelection = index;
}

void PageNav::configureConnections(){
  connect(this, &QListWidget::currentItemChanged, this, &PageNav::listItemChanged);
}

void PageNav::listItemChanged(){
  if (getNewSelection() > -1){
    setOldSelection( getNewSelection() );
    setNewSelection( currentRow() );
  } else {
    setNewSelection( currentRow() );
  }
}
