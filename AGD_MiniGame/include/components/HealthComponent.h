#pragma once

class HealthComponent
{
public:
	HealthComponent(int _currentHealth, int _maxHealth) : currentHealth{ _currentHealth }, maxHealth{ _maxHealth } {}

	int getHealth() { return currentHealth; }

	void changeHealth(int change)
	{
		currentHealth += change;
		if (currentHealth > maxHealth) currentHealth = maxHealth;
		if (currentHealth < 0) currentHealth = 0;
	}

protected:

	int currentHealth;
	int maxHealth;
};
