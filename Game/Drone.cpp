#include "Drone.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "GameManager.h"
#include "EnemyProjectile.h"
#include <ColliderComponent.h>

Drone::Drone()
{
	startPosition = Vector2D(rand() % 780, 0);
	speed = 0.f;
	
	this->maxHp = 100.f;
	this->hp = this->maxHp;
}

Drone::~Drone()
{

}

void Drone::Init()
{
	__super::Init();

	AddComponent<TransformComponent>(startPosition.x, startPosition.y);
	AddComponent<SpriteComponent>("../Assets/graphics/droneA.bmp", false, false);
	AddComponent<ColliderComponent>(this, 64, 64);
	GetComponent<SpriteComponent>().CreateAnimation("DroneIdle", 0, 16, 200);
	GetComponent<SpriteComponent>().PlayAnimation("DroneIdle");

	SetName("Drone");
	SetTag(Tag::Enemy);

	speed = 0.3f;
	transformComponent = &GetComponent<TransformComponent>();
}

void Drone::Update()
{
	if (IsActive())
	{
		__super::Update();
		
		transformComponent->velocity.y = 1 * speed;
		transformComponent->position.x = startPosition.x + amplitude * std::sin(transformComponent->position.y);
		

		if (transformComponent->position.y > 850)
		{
			Destroy();
		}
	}
}

void Drone::Fire()
{

}

void Drone::BeginOverlap(Entity* otherEntity)
{
	if (otherEntity->GetTag() == Tag::Projectile)
	{
		GetComponent<SpriteComponent>().SetFlashing(true);
	}
}

void Drone::EndOverlap(Entity* otherEntity)
{
	if (otherEntity->GetTag() == Tag::Projectile)
	{
		GetComponent<SpriteComponent>().SetFlashing(false);
	}
}

void Drone::TakeDamage(float damage)
{
	this->hp -= damage;

	if (this->hp <= 0)
	{
		Destroyed(this);
	}
}
