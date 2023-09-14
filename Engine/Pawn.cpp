#include "Pawn.h"
#include "GameEngine.h"
#include <iostream>
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "Vector2D.h"
#include "../Game/GameManager.h"
#include "Explosion.h"

Pawn::Pawn()
{
	maxHp = 0.f;
	hp = maxHp;
}

Pawn::~Pawn()
{

}

void Pawn::Init()
{
	__super::Init();
}

void Pawn::Update()
{
	__super::Update();
}

void Pawn::Destroyed(Entity* entity)
{
	GameManager::GetManager()->CreateEntity<Explosion>(entity->GetComponent<TransformComponent>().position);
	entity->Destroy();
}
