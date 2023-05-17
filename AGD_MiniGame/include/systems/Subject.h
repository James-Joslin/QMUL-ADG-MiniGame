#pragma once
#include "Observer.h"

class Subject
{
public:
	Subject() : head(nullptr) {}

	void addObserver(Observer* observer);
	void removeObserver(Observer*  observer);

	void notify(Entity& entity, EventType event);

private:
	//std::vector<Observer*> observers;

	Observer* head;
};