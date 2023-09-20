#include "GameManager.h"
#include "Vector2D.h"
#include "EntityComponentSystem.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include <iostream>
#include "Projectile.h"
#include "Loner.h"
#include "Rusher.h"
#include "Level.h"
#include "Debris.h"
#include "Drone.h"
#include "CompanionPickup.h"
#include "WeaponPickup.h"
#include "ShieldPickup.h"
#include "BigAsteroid.h"
#include "MetalAsteroid.h"
#include "PlayerLifeUI.h"
#include <LogOutput.h>
#include "Player.h"
#include "World.h"

GameManager* GameManager::m_instance = nullptr;

GameManager::~GameManager()
{
	delete m_instance;
}

void GameManager::Init()
{
	CreateLevel();
	LoadUI();
}

void GameManager::Update()
{
	SpawnDebris();
	SpawnEnemies();
	SpawnPickups();
}

void GameManager::CreateLevel()
{	
	if (&world)
	{
		world.CreateEntity<Level>();

		player = world.CreateEntity<Player>();
	}
}

void GameManager::SpawnEnemies()
{
	lonerSpawnTimer += 0.5f;
	rusherSpawnTimer += +0.5f;
	asteroidSpawnTimer += 0.5f;

	if (lonerSpawnTimer >= lonerSpawnTimerMax)
	{
		enemiesToSpawn = rand() % 2 + 1;

		for (int i = 0; i < enemiesToSpawn; ++i)
		{
			world.CreateEntity<Loner>();
		}

		lonerSpawnTimer = 0.f;
	}

	if (rusherSpawnTimer >= rusherSpawnTimerMax)
	{
		enemiesToSpawn = rand() % 5 + 3;

		for (int i = 0; i < enemiesToSpawn; ++i)
		{
			world.CreateEntity<Rusher>();
		}

		rusherSpawnTimer = 0.f;
	}

	if (asteroidSpawnTimer >= asteroidSpawnTimerMax)
	{
		 int asteroidsToSpawn = rand() % 1 + 2;

		for (int i = 0; i < asteroidsToSpawn; ++i)
		{
			world.CreateEntity<BigAsteroid>();
			world.CreateEntity<MetalAsteroid>();
		}

		asteroidSpawnTimer = 0.f;
	}
}

void GameManager::SpawnDebris()
{
	debrisSpawnTimer += 0.5f;

	if (debrisSpawnTimer >= debrisSpawnTimerMax)
	{
		world.CreateEntity<Debris>(true);
		debrisSpawnTimerMax = 150 + (rand() % (200 - 150) + 1);
		debrisSpawnTimer = 0.f;
	}
}

void GameManager::SpawnPickups()
{
	pickupSpawnTimer += 0.5f;

	if (pickupSpawnTimer >= pickupSpawnTimerMax)
	{
		pickupsToSpawn = 1;

		for (int i = 0; i < pickupsToSpawn; ++i)
		{
			world.CreateEntity<WeaponPickup>();
			world.CreateEntity<ShieldPickup>();
		}

		pickupSpawnTimer = 0.f;
	}
}

void GameManager::LoadUI()
{
	for (int i = 0; i < 3; ++i)
	{
		playerLives.push_back(world.CreateEntity<PlayerLifeUI>(Vector2D(20 + (i * 60), 700)));
	}

	DebugLog(LogMessage::WARNING, "Loaded Player Life UI");
}

void GameManager::EraseLife()
{
	if (playerLives.size() > 0)
	{
		playerLives.back()->Destroy();
		playerLives.pop_back();
	}
}

