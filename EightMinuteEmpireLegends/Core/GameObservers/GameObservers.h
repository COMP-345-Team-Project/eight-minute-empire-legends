#pragma once
#include <list>
#include <string>

class Observer {
public:
	~Observer();
	virtual void update() = 0;
protected:
	Observer();	
};

class Observable
{
public:
	Observable();
	~Observable(); //Inline destructor
	virtual void attach(Observer*);
	virtual void detach(Observer*);
	virtual void notify() = 0;
protected:
	std::list<Observer*> *_observers;
};

