// Core Libraries
#include <crtdbg.h>
#include <iostream>
#include <Windows.h>

#include "Game.h"
#include "Renderer.h"

#include "IMGUI/imgui.h"
#include "IMGUI_SDL/imgui_sdl.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char * args[])
{
	Uint32 frameStart, frameTime;
	UINT32 frames = 0;


	// show console
	AllocConsole();
	freopen("CON", "w", stdout);

	ImGui::CreateContext();
	ImGuiSDL::Initialize(Renderer::Instance()->getRenderer(), Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);

	TheGame::Instance()->init("SDLEngine 0.24", 100, 100, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT, false);

	while (TheGame::Instance()->isRunning())
	{
		frameStart = SDL_GetTicks();

		TheGame::Instance()->handleEvents();
		TheGame::Instance()->update();
		TheGame::Instance()->render();

		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime< DELAY_TIME)
		{
			SDL_Delay(int(DELAY_TIME - frameTime));
		}

		frames++;
		TheGame::Instance()->setFrames(frames);

	}

	TheGame::Instance()->clean();
	return 0;
}

