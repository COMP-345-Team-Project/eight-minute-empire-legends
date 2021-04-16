#pragma once
#include <list>
#include <string>

class Observer {
public:
	~Observer();
	virtual void Update(std::string context) = 0;
protected:
	Observer();
};

class Observable
{
public:
	Observable();
	~Observable();
	virtual void Attach(Observer* o);
	virtual void Detach(Observer* o);
	virtual void Notify(std::string context) = 0;	
private:
	std::list<Observer*> *_observers;
};
