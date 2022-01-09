#include "Engine.h"
#include "Player.h"
#include "Ball.h"
#include "PlayerAI.h"
#include <stdlib.h>

Ball ball;
Player player;
PlayerAI playerAI;

int gridsize = 25;

Engine::~Engine() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Engine::init() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	assert(window && renderer);
	event = new SDL_Event();
	isRunning = true;

	player.transform.scale = playerAI.transform.scale = Vec2I(gridsize*1, gridsize*5);

	player.transform.position = Vec2(WIDTH - player.transform.scale.x, HEIGHT/2);
	playerAI.transform.position = Vec2(0, HEIGHT/2);

	ball.reset();
	ball.transform.scale = Vec2I(gridsize, gridsize);
}

void Engine::gameloop() {
	while (isRunning) {
		const auto& t_start = std::chrono::high_resolution_clock::now();
		
		eventHandler();

		BACKGROUND_COLOR;
		SDL_RenderClear(renderer);

		update();
		render();

		SDL_RenderPresent(renderer);

		const auto& t_end = std::chrono::high_resolution_clock::now();
		dt = std::chrono::duration<double, std::ratio<1, UPS>>(t_end - t_start).count();
	}
}

void Engine::eventHandler() {
	while (SDL_PollEvent(event)) {
		if (event->type == SDL_QUIT) {
			isRunning = false;
		}
		if (event->type == SDL_KEYDOWN) {
			switch (event->key.keysym.sym) {
			case SDLK_w:
				player.up = true;
				break;
			case SDLK_s:
				player.down = true;
				break;
			}
		}
		if (event->type == SDL_KEYUP) {
			switch (event->key.keysym.sym) {
			case SDLK_w:
				player.up = false;
				break;
			case SDLK_s:
				player.down = false;
				break;
			}
		}
	}
}

void Engine::update() {
	if (ball.transform.position.y <= playerAI.transform.position.y) {
		playerAI.up = true;
	} else if (ball.transform.position.y >= playerAI.transform.position.y + playerAI.transform.scale.y) {
		playerAI.down = true;
	} else {
		playerAI.up = playerAI.down = false;
	}

	player.update(dt);
	playerAI.update(dt);
	ball.update(dt);

	ball.collision(playerAI);
	ball.collision(player);
}

void Engine::render() {
	PADDLE_COLOR;
	player.render(renderer);
	playerAI.render(renderer);
	ball.render(renderer);
}