#pragma once
#include <string>

class SDL_Renderer;
union SDL_Event;
class Manager;
class SDLWrapper;
class Window;
class Renderer;

class GameEngine
{
public:
	GameEngine();
	~GameEngine();

	void Init(const char* windowTitle, int windowWidth, int windowHeight, bool isFullScreen);

	void Run();

	void Update();

	void HandleEvents();

	void Render();

	void Shutdown();

	bool IsActive();
	class GameEngine* GetEngine();

	inline float GetDeltaTime() { return deltaTime; }

	static SDL_Renderer* GetRenderer();
	static SDL_Event event;
	static Manager manager;

private:	
	void InitializeSDL();
	void InitializeWindow(const char* windowTitle, int windowWidth, int windowHeight, bool isFullScreen);
	void InitializeRenderer();
	void Cleanup();

	SDLWrapper* m_sdl = nullptr;
	Window* m_window = nullptr;
	static Renderer* m_renderer;

	bool m_isRunning;
	bool m_isActive;

	GameEngine* m_engine;
	
	float frameStart;
	int currentTime;
	float frameTime;
	float deltaTime;
	float frameRate;
};
