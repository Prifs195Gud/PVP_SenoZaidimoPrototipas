#pragma once

#include <vector>
#include <Vectors.h>
#include <Tick.h>
#include <SpriteObject.h>

using namespace std;

struct EmissionBursts
{
	double timeDelay = 0.;
	int count = 1;
	int cycles = 1;
	double interval = 0.;
	double probability = 1.;
};

struct ParticleData
{
	double startLifetime = 1.;
	double startSpeed = 1.;
	double startSize = 1.;

	double gravityMod = 0.;

	bool paused = false;
	bool visible = false;

	Vector2 velocityOverLifetime;
	Vector2 sizeOverLifetime;
};

struct ParticleSystemData
{
	double duration = 1.;

	bool looping = false;
	bool prewarm = false;

	double startDelay = 0.;

	double emissionRateOverTime = 0.1;
	double emissionRateOverDistance = 0.;
	vector<EmissionBursts> emissionBursts;

	double emissionRadius = 1.;
};

class Particle : public SpriteObject
{
public:
	Particle(ParticleData _particleData, Sprite graphics);
	~Particle();

	void Tick() override;
	void Revive(ParticleData newParticleData);

private:
	ParticleData particleData;

	bool dead;

	void Die();
	void Initialize();
};

class ParticleSystem : public Transform
{
public:
	ParticleSystem(Sprite graphics, ParticleData _particleData, ParticleSystemData _particleSystemData);
	~ParticleSystem();

	void Tick() override;

private:
	Sprite mySprite;

	vector<Particle*> myParticles;
	vector<Particle*> myAliveParticles;
	vector<Particle*> myDeadParticles;

	ParticleData particleData;
	ParticleSystemData particleSystemData;

	double aliveTime, oldAliveTime;

	void SpawnParticle();
	ParticleData GenerateParticleData();
};

