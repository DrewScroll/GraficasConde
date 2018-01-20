#include <IDVWindow/IDVWin32Manager.h>

// SDL
#include <SDL/SDL.h>
// Windows
#include <windows.h>
#include <mmsystem.h>

void IDVWin32Manager::InitGlobalVars() {
	m_pApplication->InitVars();
}

void IDVWin32Manager::OnCreateApplication() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Video initialization failed: %s\n", SDL_GetError());
	}

	SDL_WM_SetCaption("IDV", 0);

	if (SDL_SetVideoMode(1280, 720, 32, SDL_HWSURFACE | SDL_RESIZABLE) == 0) {
		printf("Video mode set failed: %s\n", SDL_GetError());
	}

	m_pApplication->CreateAssets();
}

void IDVWin32Manager::OnDestroyApplication() {

}

void IDVWin32Manager::UpdateApplication() {
	while (m_bAlive) {
		ProcessInput();
		m_pApplication->OnUpdate();
	}
}

void IDVWin32Manager::ProcessInput() {
	SDL_Event       evento;
	while (SDL_PollEvent(&evento)) {
		switch (evento.type) {
		case SDL_KEYDOWN: {
			if (evento.key.keysym.sym == SDLK_q) {
				m_bAlive = false;
			}
			
		}break;

		case SDL_QUIT: {
			m_bAlive = false;
		}break;

		case SDL_KEYUP: {

		}break;

		case SDL_VIDEORESIZE: {
			printf("New dim %d x %d \n", evento.resize.w, evento.resize.h);
		}break;


		}
	}
}