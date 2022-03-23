
#include <Particle.h>
#include <Random.h>

Particle::Particle(ParticleSystem* parent, ParticleData _particleData, Sprite graphics): SpriteObject(graphics, (int)LayerType::Overlay)
{
	parentParticleSystem = parent;
	particleData = _particleData;
	Initialize();
}

Particle::~Particle()
{
}

void Particle::Die()
{
	dead = true;

	Enable(false);

	if (parentParticleSystem == nullptr) // Mane ne daleliu sistema sukure?? :(
		delete this;
	else
		parentParticleSystem->ReportParticleDeath(this);
}

void Particle::Initialize()
{
	dead = false;
	scale = Vector2(particleData.startSize, particleData.startSize);
	initialLifetime = particleData.startLifetime;

	Enable(true);

	SetVelocity(Vector2::Random() * particleData.startSpeed);
	OnPositionChange();
}

void Particle::Revive(ParticleData newParticleData)
{
	particleData = newParticleData;
	Initialize();
}

void Particle::Tick()
{
	SpriteObject::Tick();

	double time = 1. / 60.;

	particleData.startLifetime -= time;

	if (abs(particleData.gravityMod - 0.001) > 0.001)
		SetVelocity(velocity - Vector2::down * (10. * time));

	if (particleData.velocityOverLifetime != Vector2::zero)
		SetVelocity(velocity + particleData.velocityOverLifetime * (time / initialLifetime));

	if (particleData.sizeOverLifetime != Vector2::zero)
	{
		scale += particleData.sizeOverLifetime * (time / initialLifetime);
		OnPositionChange();
	}


	if (particleData.startLifetime <= 0.)
	{
		Die();
		return;
	}
}



ParticleSystem::ParticleSystem(Sprite graphics, ParticleData _particleData, ParticleSystemData _particleSystemData)
{
	mySprite = graphics;
	particleData = _particleData;
	particleSystemData = _particleSystemData;

	savedEmissionBursts = _particleSystemData.emissionBursts;

	aliveTime = 0.;

	emissionPaused = false;
	lastPos = position;
}

ParticleSystem::~ParticleSystem()
{
	for (size_t i = 0; i < myParticles.size(); i++)
		delete myParticles[i];
}

void ParticleSystem::HandleBursts()
{
	if (particleSystemData.emissionBursts.size() == 0)
		return;

	for (size_t i = 0; i < particleSystemData.emissionBursts.size(); i++)
	{
		EmissionBursts* burst = &particleSystemData.emissionBursts[i];

		if (aliveTime < burst->timeDelay)
			continue;

		if (burst->interval > 0 &&
			burst->probability < 0.9999 && Random::RandZeroToOne() < burst->probability)
		{
			burst->timeDelay = aliveTime + burst->interval;
			continue;
		}

		for (size_t i = 0; i < burst->count; i++)
			SpawnParticle();

		if (burst->cycles <= 0)
		{
			particleSystemData.emissionBursts.erase(particleSystemData.emissionBursts.begin() + i);
			i--;
			continue;
		}
		else
		{
			burst->cycles--;
			burst->timeDelay = aliveTime + burst->interval;
		}
	}
}

void ParticleSystem::Tick()
{
	Transform::Tick();

	if (emissionPaused)
		return;

	HandleBursts();

	aliveTime += 1. / 60.;

	if (aliveTime >= particleSystemData.duration)
	{
		if (particleSystemData.looping)
		{
			if (particleSystemData.emissionBursts.size() == 0)
			{
				particleSystemData.emissionBursts = savedEmissionBursts;

				for (size_t i = 0; i < particleSystemData.emissionBursts.size(); i++)
					particleSystemData.emissionBursts[i].timeDelay += aliveTime;
			}

			//cycleTyme = 0.;
		}
		else
		{
			if(myAliveParticles.size() == 0 && particleSystemData.emissionBursts.size() == 0)
				delete this;

			return;
		}
	}

	if (particleSystemData.emissionRateOverDistance != 0)
	{
		double distance = (position - lastPos).Magnitude();

		int particlesToSpawnB = (int)(distance / particleSystemData.emissionRateOverDistance);

		if (particlesToSpawnB > 0)
			lastPos = position;

		for (int i = 0; i < particlesToSpawnB; i++)
			SpawnParticle();
	}

	if (particleSystemData.emissionRateOverTime == 0)
		return;

	double timeDiff = aliveTime - oldAliveTime;

	int particlesToSpawn = (int)(timeDiff / particleSystemData.emissionRateOverTime);

	if(particlesToSpawn > 0)
		oldAliveTime = aliveTime;

	for (int i = 0; i < particlesToSpawn; i++)
		SpawnParticle();
}

ParticleData ParticleSystem::GenerateParticleData()
{
	ParticleData newData = particleData;
	newData.startSpeed *= Random::RandZeroToOne();

	return newData;
}

void ParticleSystem::PauseEmission(bool var)
{
	emissionPaused = var;
}

void ParticleSystem::SpawnParticle()
{
	if (myDeadParticles.size() > 0)
	{
		Particle* oldPart = myDeadParticles[0];

		oldPart->SetPosition(position + Vector2::Random(RandomVectorGenerationType::Circle) * particleSystemData.emissionRadius);
		oldPart->Revive(GenerateParticleData());

		if (particleSystemData.particlesInheritVelocity)
			oldPart->SetVelocity(oldPart->GetVelocity() + velocity);

		myAliveParticles.push_back(oldPart);
		myDeadParticles.erase(myDeadParticles.begin());
		return;
	}

	Particle* part = new Particle(this, GenerateParticleData(), mySprite);

	part->SetPosition(position + Vector2::Random(RandomVectorGenerationType::Circle) * particleSystemData.emissionRadius);

	if (particleSystemData.particlesInheritVelocity)
		part->SetVelocity(part->GetVelocity() + velocity);

	myParticles.push_back(part);
	myAliveParticles.push_back(part);
}

void ParticleSystem::ReportParticleDeath(Particle* ptr)
{
	if (ptr == nullptr)
		return;

	for (size_t i = 0; i < myAliveParticles.size(); i++)
		if (myAliveParticles[i] == ptr)
		{
			myDeadParticles.push_back(ptr);
			myAliveParticles.erase(myAliveParticles.begin() + i);
			return;
		}
}