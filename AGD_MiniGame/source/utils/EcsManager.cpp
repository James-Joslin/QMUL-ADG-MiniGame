#include "../../include/utils/EcsManager.h"
#include "../../include/systems/Systems.h"
#include "../../include/core/Game.h"

EcsManager::EcsManager()
{
	archetypeManager = nullptr;
}

EcsManager::~EcsManager()
{
}

void EcsManager::populateECS(Game& game)
{
	auto ttl = std::make_shared<TTLSystem>();
	auto input = std::make_shared<InputSystem>();
	auto movement = std::make_shared<MovementSystem>();
	auto gameplay = std::make_shared<GameplaySystem>();
	auto collider = std::make_shared<ColliderSystem>();
	auto graphics = std::make_shared<GraphicsSystem>();
	auto debug = std::make_shared<PrintDebugSystem>();

	switch (game.getEcsMethod())
	{
	case bigArray:
		logicSystems.push_back(ttl);
		logicSystems.push_back(input);
		logicSystems.push_back(movement);
		logicSystems.push_back(gameplay);
		logicSystems.push_back(collider);

		graphicsSystems.push_back(graphics);
		if (game.getDrawDebug())
		{
			graphicsSystems.push_back(debug);
		}
		break;

	case archetypes:
		archetypeManager = std::make_shared<ArchetypeManager>();

		logicSystems.push_back(collider);
		archetypeManager->addArchetypeSystems(ArchetypeID::StaticEntity, logicSystems, graphics);

		logicSystems.clear();
		logicSystems.push_back(input);
		logicSystems.push_back(movement);
		logicSystems.push_back(gameplay);
		logicSystems.push_back(collider);
		archetypeManager->addArchetypeSystems(ArchetypeID::DwarfPlayer, logicSystems, graphics);

		logicSystems.clear();
		logicSystems.push_back(ttl);
		logicSystems.push_back(movement);
		archetypeManager->addArchetypeSystems(ArchetypeID::Fireball, logicSystems, graphics);

		if (game.getDrawDebug())
		{
			archetypeManager->addDebug(ArchetypeID::DwarfPlayer, debug);
			archetypeManager->addDebug(ArchetypeID::StaticEntity, debug);
		}
		break;

	default:
		break;
	}
}

void EcsManager::updateECS(float elapsedTime, Game& game, SystemType _systemType)
{
	auto entities = game.getEntities();
	
	switch (game.getEcsMethod())
	{
	case bigArray:
		switch (_systemType)
		{
		case SystemType::Logic:
			systems = logicSystems;
			break;
		case SystemType::Graphics:
			systems = graphicsSystems;
			break;
		default:
			break;
		}
		systemIt = systems.begin();
		while (systemIt != systems.end())
		{
			entityIt = entities.begin();
			while (entityIt != entities.end())
			{
				if (!(*entityIt)->isDeleted())
				{
					if ((*systemIt)->validate((*entityIt).get()))
					{
						(*systemIt)->update((*entityIt).get(), &game, elapsedTime);
					}
				}
				entityIt++;
			}
			systemIt++;
		}
		break;

	case archetypes:
		entityIt = entities.begin();
		while (entityIt != entities.end())
		{
			if (!(*entityIt)->isDeleted())
			{
				auto archetypeSystems = archetypeManager->getSystems((*entityIt)->getArchetypeID(), _systemType); // return appropriate systems vector
				systemIt = archetypeSystems.begin();
				while (systemIt != archetypeSystems.end())
				{
					(*systemIt)->update((*entityIt).get(), &game, elapsedTime);
					systemIt++;
				}
			}
			entityIt++;
		}
		break;

	default:
		break;
	}
}
