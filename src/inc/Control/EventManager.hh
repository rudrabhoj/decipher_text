// A Simple Pub-Sub Event Manager
// Thread unsafe. Do not subscribe/unsubscribe in multi-threaded processes.

#ifndef __CONTROL_EVENTMANAGER_H__
#define __CONTROL_EVENTMANAGER_H__

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