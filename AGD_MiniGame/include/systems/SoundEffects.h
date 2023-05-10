#pragma once
#include <SFML/Audio.hpp>

class SoundEffects
{
public:
	SoundEffects() {}
	~SoundEffects() {}

	void playAudio()
	{
		getSound(getBuffer("CollectItemAudio.wav")).play();
	}
	void stopAudio() {};

	sf::SoundBuffer getBuffer(std::string file) 
	{
		sf::SoundBuffer buffer;
		buffer.loadFromFile(file); 
		return buffer;
	}

	sf::Sound getSound(sf::SoundBuffer buffer)
	{
		sf::Sound sound;
		sound.setBuffer(buffer);
		return sound;
	}

private:


};