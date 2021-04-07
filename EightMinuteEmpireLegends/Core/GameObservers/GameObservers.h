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
	virtual void Attach(Observer*) = 0;
	virtual void Detach(Observer*) = 0;
	virtual void Notify() = 0;
protected:
	Observable() {};
private:
	std::list<Observer*> *_observers;
};
