#pragma once
#include <list>

class Observer {
public:
	~Observer();
	virtual void Update() = 0;
protected:
	Observer();
};

class Observable
{
public:
	virtual ~Observable() {};
	virtual void attach(Observer*) = 0;
	virtual void detach(Observer*) = 0;
	virtual void notify() = 0;
protected:
	Observable() {};
private:
	std::list<Observer*> _observers;
};
