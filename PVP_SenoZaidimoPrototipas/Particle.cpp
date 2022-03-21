
#include <Particle.h>

Particle::Particle(ParticleData _particleData, Sprite graphics): SpriteObject(graphics, (int)LayerType::Overlay)
{
	particleData = _particleData;
	Initialize();
}

Particle::~Particle()
{
}

void Particle::Die()
{
	particleData.visible = false;
	dead = true;

	Enable(false);
}

void Particle::Initialize()
{
	particleData.visible = true;
	dead = false;
	Enable(true);
	SetVelocity(Vector2::Random() * particleData.startSpeed);
}

void Particle::Revive(ParticleData newParticleData)
{
	particleData = newParticleData;
	Initialize();
}

void Particle::Tick()
{
	SpriteObject::Tick();

	particleData.startLifetime -= 1. / 60.;

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

	aliveTime = 0.;
}

ParticleSystem::~ParticleSystem()
{
	for (size_t i = 0; i < myParticles.size(); i++)
		delete myParticles[i];
}

void ParticleSystem::Tick()
{
	Transform::Tick();

	aliveTime += 1. / 60.;

	if (aliveTime >= particleSystemData.duration)
	{
		if (particleSystemData.looping)
		{
			//cycleTyme = 0.;
		}
		else
		{
			delete this;
			return;
		}
	}

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
	newData.startSpeed = ((double)rand() / (double)RAND_MAX) * newData.startSpeed;

	return newData;
}

void ParticleSystem::SpawnParticle()
{
	if (myDeadParticles.size() > 0)
	{
		Particle* oldPart = myDeadParticles[0];

		oldPart->SetPosition(position + Vector2::Random(RandomVectorGenerationType::Circle) * particleSystemData.emissionRadius);
		oldPart->Revive(GenerateParticleData());

		myAliveParticles.push_back(oldPart);
		myDeadParticles.erase(myDeadParticles.begin());
		return;
	}

	Particle* part = new Particle(GenerateParticleData(), mySprite);

	part->SetPosition(position + Vector2::Random(RandomVectorGenerationType::Circle) * particleSystemData.emissionRadius);

	myParticles.push_back(part);
	myAliveParticles.push_back(part);
}