#pragma once
#include "Observer.h"

class Subject
{
public:
	void addObserver(Observer* observer);
	void removeObserver(std::shared_ptr<Observer> observer);

	void notify(const Entity& entity, EventType event);

	std::vector<Observer*> getObserversVector() { return observers; }

private:
	std::vector<Observer*> observers;
};