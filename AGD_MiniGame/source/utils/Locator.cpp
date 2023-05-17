#include "../../include/utils/Locator.h"
#include "../../include/utils/AudioManager.h"

ServiceLocator::ServiceLocator()
{
   
}

ServiceLocator::~ServiceLocator()
{

}

std::shared_ptr<AudioManager> ServiceLocator::getAudioManager() {
    static std::shared_ptr<AudioManager> audioManagerService;
    audioManagerService = std::make_shared<AudioManager>();
    return audioManagerService;
}

//Service Locator is good, but I wouldn't have a getServices() function in the logic component. 
//Services should be accessed through a static function - your getAudioManager() - in the Locator class (i.e. calling it as Locator::getAudioManager()->playSound()).