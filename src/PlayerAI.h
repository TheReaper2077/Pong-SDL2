#pragma once

#include "Engine.h"
#include <stdlib.h>

class PlayerAI: public Object {
public:
	PlayerAI() {
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
	bool up, down;
};