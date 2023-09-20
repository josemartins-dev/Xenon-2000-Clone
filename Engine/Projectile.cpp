#include "Projectile.h"
#include "Vector2D.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include <iostream>
#include "../Game/GameManager.h"
#include "Explosion.h"
#include "World.h"

Projectile::Projectile()
{
	projectileDamage = 0.f;
}

Projectile::Projectile(Vector2D position, float projRange, float projSpeed)
{
	projectileDamage = 0.f;
}

Projectile::~Projectile()
{
	
}

void Projectile::Init()
{
	__super::Init();
}

void Projectile::Update()
{
	__super::Update();
}

void Projectile::Destroyed(Entity* entity)
{
	World& world = GameEngine::GetEngine()->GetWorld();
	if (&world)
	{
		world.CreateEntity<Explosion>(entity->GetComponent<TransformComponent>().position);
	}
	entity->Destroy();
}
