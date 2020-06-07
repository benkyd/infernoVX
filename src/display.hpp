#ifndef INFERNOVX_DISPLAY_H_
#define INFERNOVX_DISPLAY_H_

#include <string>

#include <logger.h>

#if _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <glad/glad.h>
#include <KHR/khrplatform.h>

#include <glm/glm.hpp>

class Camera;

class Display
{
public:

	Display( int w, int h, std::string title );

	// returns true if the display was resized
	bool Input( SDL_Event* e, Camera* camera );

	glm::vec2 GetDisplaySizePx();

	void PrepareFrame();
	void NextFrame();

	bool IsWindowOpen = false;
	bool IsMouseActive = true;

private:

	Logger mLogger;

	SDL_Window* mWindow = nullptr;
	SDL_GLContext mGlContext = nullptr;

	int mW, mH;

};

#endif
