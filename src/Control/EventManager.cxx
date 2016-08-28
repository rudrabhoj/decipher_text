#include <Control/EventManager.hh>
#include <iostream>

EventManager::EventManager(){

}

bool EventManager::eventExists(QString message){
  int i, lim;
  lim = eventList.length();

  for (i = 0; i < lim; i++){
    if(eventList[i].message == message) return true;
  }

  return false;
}

void EventManager::createEmptyEvent(QString message){
  exeData dat;

  dat.message = message;

  eventList.push_back(dat);
}

int EventManager::findMessageId(QString message){
  int i, lim;
  lim = eventList.length();

  //Create new event if such event do not exist
  if (!eventExists(message)){
    createEmptyEvent(message);
    return lim; // which now equals (eventList.length() - 1);
  } else{
    for (i = 0; i < lim; i++){
      if (eventList[i].message == message) return i;
    }
  }

  //You should never ever return this
  return -1;
}

void EventManager::addFoo(QString message, exeFunction *foo){
  int id;

  id = findMessageId(message);
  eventList[id].fooList.push_back(foo);
}

void EventManager::removeFoo(QString message, exeFunction *foo){
  int messageId, lim, i;

  messageId = findMessageId(message);
  lim = eventList[messageId].fooList.length();

  for (i = 0; i < lim; i++){
    if (eventList[messageId].fooList[i] == foo){
      eventList[messageId].fooList.removeAt(i);
      //break; //Would uncomment it if I believed humans aren't stupid enough to add same sub unlimitd times
    }
  }
}


void EventManager::subscribe(QString message, exeFunction *foo){
  if(!eventExists(message)) createEmptyEvent(message);

  addFoo(message, foo);
}

void EventManager::unsubscribe(QString message, exeFunction *foo){
  if(eventExists(message)){
    removeFoo(message, foo);
  }
}

void EventManager::publish(QString message){
  int i, lim, messageId;
  exeFunction *localFoo;

  messageId = findMessageId(message);

  lim = eventList[messageId].fooList.length();

  for(i = 0; i < lim; i++){
    localFoo = eventList[messageId].fooList[i];
    (*localFoo)();
  }
}
