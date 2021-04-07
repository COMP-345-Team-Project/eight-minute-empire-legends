#pragma once
#include "GameObservers.h"

Observer::Observer() {
};
Observer::~Observer() {
};

Observable::Observable() {
	_observers = new std::list<Observer*>;
};

Observable::~Observable() {
	delete _observers;
};

void Observable::Attach(Observer* o) {
	_observers->push_back(o);
};

void Observable::Detach(Observer* o) {
	_observers->remove(o);
};

void Observable::Notify() {
	std::list<Observer*>::iterator i = _observers->begin();
	for (; i != _observers->end(); ++i) {
		(*i)->Update();
	}
};