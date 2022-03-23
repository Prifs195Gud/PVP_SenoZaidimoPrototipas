#pragma once

#include <vector>
#include <Vectors.h>
#include <Tick.h>
#include <SpriteObject.h>

using namespace std;

struct EmissionBursts // Duomenu konteineris daleliu "sprogimams"
{
	double timeDelay = 0.;
	int count = 1;
	int cycles = 0;
	double interval = 0.;
	double probability = 1.;
};

struct ParticleData // Duomenu konteineris skirtas saugoti daleles duomenis
{
	double startLifetime = 1.;
	double startSpeed = 1.;
	double startSize = 1.;

	double gravityMod = 0.;

	Vector2 velocityOverLifetime;
	Vector2 sizeOverLifetime;
};

struct ParticleSystemData // Daleliu sistemos duomenys
{
	double duration = 1.;

	bool looping = false;
	bool prewarm = false;

	bool particlesInheritVelocity = false;

	double startDelay = 0.;

	double emissionRateOverTime = 0.1;
	double emissionRateOverDistance = 0.;
	vector<EmissionBursts> emissionBursts;

	double emissionRadius = 1.;
};

class ParticleSystem; // Daleliu sistemos klases prototipas, nes pjaunasi su Particle klase, nes tenais yra pointer ParticleSystem

class Particle : public SpriteObject // Paprasciausia dalele, tai nuotraukyte, kuri skraido ir poto mirsta, ir dingsta (arba pasako daleliu sitemai, kad mire)
{
public:
	Particle(ParticleSystem* parent, ParticleData _particleData, Sprite graphics);
	~Particle();

	void Tick() override;
	void Revive(ParticleData newParticleData);

private:
	ParticleSystem* parentParticleSystem;
	ParticleData particleData;

	double initialLifetime;
	bool dead;

	void Die();
	void Initialize();
};

class ParticleSystem : public Transform // Daleliu sistemos klase, skirta gaminti daleles. Tikro gyvenimo pvz. butu pats fontanas koks
{
public:
	ParticleSystem(Sprite graphics, ParticleData _particleData, ParticleSystemData _particleSystemData);
	~ParticleSystem();

	void Tick() override;
	void ReportParticleDeath(Particle* ptr);

private:
	Sprite mySprite;

	vector<Particle*> myParticles;
	vector<Particle*> myAliveParticles;
	vector<Particle*> myDeadParticles;

	vector<EmissionBursts> savedEmissionBursts;

	ParticleData particleData;
	ParticleSystemData particleSystemData;

	double aliveTime, oldAliveTime;
	Vector2 lastPos;

	bool emissionPaused;

	void PauseEmission(bool var);
	void SpawnParticle();
	void HandleBursts();
	ParticleData GenerateParticleData();
};

