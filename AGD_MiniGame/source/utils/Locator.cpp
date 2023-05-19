#include "../../include/utils/Locator.h"
#include "../../include/utils/AudioManager.h"
#include <iostream>

ServiceLocator::ServiceLocator()
{
   
}

ServiceLocator::~ServiceLocator()
{

}

std::shared_ptr<AudioManager> ServiceLocator::audioManagerService = nullptr;
std::shared_ptr<AudioManager> ServiceLocator::getAudioManager() 
{
    if (!audioManagerService) 
    {
        audioManagerService = std::make_shared<AudioManager>();
    }
    return audioManagerService;
}