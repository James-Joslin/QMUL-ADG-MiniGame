#include "../../include/systems/Locator.h"


static SoundEffects* service;

SoundEffects* Locator::getBuffer()
{
	return service;
}

void Locator::provide(SoundEffects* serv)
{
	service = serv;
}