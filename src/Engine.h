#pragma once

#include "SDL2/SDL_events.h"
#include "SDL2/SDL_keycode.h"
#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_video.h"
#include "Game.h"
#include "assert.h"
#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>	
#include <chrono>
#include <math.h>
#include <ratio>
#include <stdlib.h>

#define WIDTH 800
#define HEIGHT 600
#define TITLE "TITLE"

#define BACKGROUND_COLOR SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
#define PADDLE_COLOR SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
#define BALL_COLOR SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
#define RAD (180/PI)

const int UPS = 60;

class Engine {
public:
	Engine() {}
	~Engine();
	
	void init();
	void gameloop();
	void eventHandler();
	void update();
	void render();
	void reset();
	void render(Object obj);

private:
	SDL_Window *window = nullptr;
	SDL_Renderer *renderer = nullptr;
	SDL_Event *event = nullptr;
	SDL_Rect rect;

	double dt;
	bool isRunning;
};