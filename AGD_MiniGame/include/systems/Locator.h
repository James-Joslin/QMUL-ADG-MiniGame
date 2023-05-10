#pragma once
#include "SoundEffects.h"

class Locator
{
public:
	Locator() {}
	~Locator() {}

	static SoundEffects* getBuffer();
	static void provide(SoundEffects* serv);

private:

	
};
