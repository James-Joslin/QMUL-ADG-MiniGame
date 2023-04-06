#include "../../include/systems/Subject.h"
#include <vector>


void Subject::notify(const Entity& entity, EventType event)
{
	for (Observer* o : observers)
	{
		o->onNotify(entity, event);
	}
}

void Subject::addObserver(Observer* observer)
{ 
	observers.push_back(observer);
}