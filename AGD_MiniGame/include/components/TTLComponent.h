#pragma once



class TTLComponent
{
public:

	TTLComponent(int _ttl) : ttl{ _ttl } {}

	int getTTL() { return ttl; }

	void update()
	{
		if (ttl > 0)
		{
			ttl--;
		}
	}

private:

	int ttl;

};