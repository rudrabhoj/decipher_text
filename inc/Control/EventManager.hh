// A Simple Pub-Sub Event Manager
// Thread unsafe. Do not subscribe/unsubscribe in multi-threaded processes.

#ifndef __CONTROL_EVENTMANAGER_HH__
#define __CONTROL_EVENTMANAGER_HH__

#include <functional>
#include <QString>
#include <QList>

class EventManager{
private:
  typedef std::function<void()> exeFunction;
  typedef QList<exeFunction*> fooArray;

  struct exeData{
    QString message;
    fooArray fooList;
  };

  typedef struct exeData exeData;

  QList<exeData> eventList;

  bool eventExists(QString message);
  void createEmptyEvent(QString message);
  void addFoo(QString message, exeFunction *foo);
  void removeFoo(QString message, exeFunction *foo);

  int findMessageId(QString message);

public:
  EventManager();
  void publish(QString message);
  void subscribe(QString message, exeFunction *foo);
  void unsubscribe(QString message, exeFunction *foo);

};

#endif

/*

List of Messages:
1. pagesChanged       : When there is change in number and/or order of pages. Or content.
                        It should be clear changes are made always in Document.ProjectManager, not GUI!
                        GUI just sync itself.
2. ocrProcessed       : When a new page is OCRed.
3. drawLines          : When cursor is on a valid OCRed text. Draw lines by on corresponding image on the Canvas.
4. pageNavSelChanged  : When navbox's currently selected page has changed.
*/
