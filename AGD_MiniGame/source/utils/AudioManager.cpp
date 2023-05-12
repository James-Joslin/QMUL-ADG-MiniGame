#include "../../include/utils/AudioManager.h"
#include <iostream>

void AudioManager::playSound(const std::string& soundID) {
    if (!buffer.loadFromFile(soundID)) {
        return; 
    }
    //std::cout << "Sound duration: " << buffer.getDuration().asSeconds() << std::endl;
    sound.setBuffer(buffer);
    sound.play();
}

void AudioManager::stopSound() {
    sound.stop();
}
