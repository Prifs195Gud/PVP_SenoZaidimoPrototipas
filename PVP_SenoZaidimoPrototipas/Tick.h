#pragma once

#include <vector>

using namespace std;

// Tas kas turi buti kas kiekviena frame atnaujinamas, tesiog overridinkite Tick()
class Tickable
{
public:
	Tickable();
	~Tickable();

	virtual void Tick();

	static vector<Tickable*>* GetAllTicks();
private:
	static vector<Tickable*> allTicks;
};