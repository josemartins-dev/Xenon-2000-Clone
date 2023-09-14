#include <SDL.h>
#include "GameEngine.h"
#include "SDLWrapper.h"
#include "Window.h"
#include "Renderer.h"
#include "Texture.h"
#include <iostream>
#include <stdlib.h>
#include "Components.h"
#include "Input.h"
#include "../Game/GameManager.h"
#include "World.h"

Renderer* GameEngine::m_renderer = nullptr;
Manager GameEngine::manager;
SDL_Event GameEngine::event;

GameEngine::GameEngine()
{
	m_isRunning = false;
	m_isActive = false;
	m_engine = this;
	frameStart = 0.f;
	currentTime = 0.f;
	deltaTime = 0.f;
	frameTime = 0.f;
	frameRate = 60.f;
}

GameEngine::~GameEngine()
{
	Cleanup();
}

void GameEngine::Init(const char* windowTitle, int windowWidth, int windowHeight, bool isFullScreen)
{
	//Reset the text color to the default
	std::cout << "\033[0m";

	//Framerate variables
	frameStart = 0.f;
	currentTime = 0.f;
	frameTime = 0.f;
	deltaTime = 0.f;
	frameRate = 60.f;

	//Generate new random seed every time the engine is initialized
	srand(time(NULL));

	//Used to adjust if window should be full screen
	int flag = 0;

	InitializeSDL();
	InitializeWindow(windowTitle, windowWidth, windowHeight, isFullScreen);
	InitializeRenderer();

	m_isActive = true;

	World::GetInstance()->Init();
}

void GameEngine::Run()
{
	m_isRunning = true;

	//Engine Loop
	while (m_isRunning)
	{
		frameStart = currentTime;
		currentTime = SDL_GetTicks();
		deltaTime = (currentTime - frameStart) / 1000.0f;

		float timeStep = 1.0f / 60.f;

		frameTime += deltaTime;

		if (frameTime >= (1.0f / frameRate))
		{
			HandleEvents();
			Update();
			frameTime = 0.f;
		}

		World::GetInstance()->Update(timeStep);
 		Render();
		m_window->updateSurface();
	}

	Shutdown();
}

void GameEngine::Update()
{
	//Refresh and Update Entity Manager
	GameEngine::manager.Refresh();
	GameEngine::manager.Update();

	//Update Game Manager
	GameManager::GetInstance()->Update();
}

void GameEngine::HandleEvents()
{
	//Poll SDL Events
	SDL_PollEvent(&GameEngine::event);

	//Check events
	switch (GameEngine::event.type)
	{
	case SDL_QUIT:
		m_isRunning = false;
		break;
	}

	//Check for Input
	Input::GetInstance()->Listen();
}

void GameEngine::Render()
{
	SDL_SetRenderDrawColor(GameEngine::GetRenderer(), 0, 0, 0, 0);
	SDL_RenderClear(GameEngine::GetRenderer());
	GameEngine::manager.Draw();
	SDL_RenderPresent(GameEngine::GetRenderer());
}

void GameEngine::Shutdown()
{
	SDL_DestroyRenderer(GameEngine::GetRenderer());
	SDL_DestroyWindow(m_window->GetWindow());
	
	Cleanup();

	std::cout << "Engine Shutdown" << std::endl;

	SDL_Quit();
}

void GameEngine::InitializeSDL()
{
	m_sdl = new SDLWrapper(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);
}

void GameEngine::InitializeWindow(const char* windowTitle, int windowWidth, int windowHeight, bool isFullScreen)
{
	int flags = 0;

	if (isFullScreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	m_window = new Window(windowTitle, windowWidth, windowHeight, flags);
}

void GameEngine::InitializeRenderer()
{
	m_renderer = new Renderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void GameEngine::Cleanup()
{
	delete m_renderer;
	m_renderer = nullptr;

	delete m_window;
	m_window = nullptr;

	delete m_sdl;
	m_sdl = nullptr;
}

bool GameEngine::IsActive()
{
	return m_isActive;
}

GameEngine* GameEngine::GetEngine()
{
	return m_engine;
}

SDL_Renderer* GameEngine::GetRenderer()
{
	return m_renderer->GetRenderer();
}

