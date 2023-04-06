#include "../../include/systems/Observer.h"
#include "../../include/core/Game.h"
#include "../../include/entities/Player.h"


void AchievementManager::init(std::shared_ptr<Entity> entity)
{
	std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(entity);
	player->getPotionCollected().addObserver(this);
	player->getShoutTriggered().addObserver(this);
}


bool AchievementManager::onNotify(const Entity& entitiy, EventType event)
{
	switch (event)
	{
	case EventType::COLLECT_POTION:
	{
		potionCounter++;
		return (potionCounter >= potionGoal && !potionObtained) ? unlockAchievement(AchievementType::COLLECTED_ALL_POTIONS), potionObtained = true, true : false;
		break;
	}
	case EventType::SHOUT:
	{
		shoutCounter++;
		return (shoutCounter >= shoutGoal && !shoutObtained) ? unlockAchievement(AchievementType::SHOUT_5_TIMES), shoutObtained = true, true : false;
		break;
	}
	default:
		return false;
	}
}

void AchievementManager::unlockAchievement(AchievementType achievement)
{
	switch (achievement)
	{
	case AchievementType::COLLECTED_ALL_POTIONS:
	{
		std::cout << "Achievement Unlocked: Collected All Potions" << std::endl;
		break;
	}
	case AchievementType::SHOUT_5_TIMES:
	{
		std::cout << "Achievement Unlocked: Shouted 5 Times" << std::endl;
		break;
	}
	}
}


	
