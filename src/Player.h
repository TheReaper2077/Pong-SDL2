#pragma once

#include "Game.h"
#include "SDL2/SDL_render.h"
#include "Engine.h"

class Player: public Object {
public:
	Player() {
		up = down = false;
	}

	void update(double dt) {
		if (up) {this->rigidbody.velocity.y = -speed;}
		if (down) {this->rigidbody.velocity.y = speed;}
		if ((transform.position.y > 0 && up) || (transform.position.y + transform.scale.y < HEIGHT && down)) {this->transform.position += this->rigidbody.velocity*dt;}
	}

	void render(SDL_Renderer *renderer) {
		SDL_RenderFillRect(renderer, getRenderRect());
	}

	int speed = 5;
	bool up = false, down = false;
};