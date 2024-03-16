#include "Level.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"

Level::Level()
{
	scrollingSpeed = 0.1f;
}

Level::~Level()
{
	transformComponent = nullptr;
	spriteComponent = nullptr;
}

void Level::Init()
{
	__super::Init();

	SetName("Level");

	if (transformComponent == nullptr)
	{
		AddComponent<TransformComponent>(0, -198);
		transformComponent = &GetComponent<TransformComponent>();
	}

	if (spriteComponent == nullptr)
	{
		AddComponent<SpriteComponent>("../Assets/graphics/galaxy2.bmp", false, false);
		spriteComponent = &GetComponent<SpriteComponent>();
	}
}

void Level::Update()
{
	__super::Update();

	spriteComponent->ChangeSrcRect(1000, 1000);
	spriteComponent->ChangeDstRect(1500, 1200);
}
