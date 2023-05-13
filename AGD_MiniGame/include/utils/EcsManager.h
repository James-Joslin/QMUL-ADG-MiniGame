#pragma once
#include "ArchetypeManager.h"
#include "../../include/entities/Entity.h"

class Game;

class EcsManager
{
public:
	EcsManager();
	~EcsManager();

	std::shared_ptr<ArchetypeManager> getArchetypeManager() { return archetypeManager; }
	std::vector<std::shared_ptr<System>> getLogicSystems() { return logicSystems; }
	void populateECS(Game& game);
	void updateECS(float elapsedTime, Game& game, SystemType _systemType);
	void updateBigArray();
	void updateArchetypes();

private:
	std::shared_ptr<ArchetypeManager> archetypeManager;
	
	std::vector<std::shared_ptr<System>> logicSystems;
	std::vector<std::shared_ptr<System>> graphicsSystems;
	std::vector<std::shared_ptr<System>> systems;

	std::vector<std::shared_ptr<System>>::iterator systemIt;
	std::vector<std::shared_ptr<Entity>>::iterator entityIt;
};

