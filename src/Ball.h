#pragma once

#include "Engine.h"
#include "SDL2/SDL_render.h"
#include "src/Game.h"
#include "src/Player.h"


class Ball: public Object {
public:
	void update(double dt) {
		if (this->transform.position.y + this->transform.scale.y >= HEIGHT) {
			this->rigidbody.velocity.y *= -1;
		} else if (this->transform.position.y <= 0) {
			this->rigidbody.velocity.y *= -1;
		}

		if (this->transform.position.x + this->transform.scale.x >= WIDTH) {
			reset();
		} else if (this->transform.position.x <= 0) {
			reset();
		}

		this->transform.position += this->rigidbody.velocity*dt;
	}

	template<typename T>
	void collision(T &racket) {
		if (SDL_HasIntersection(this->getRenderRect(), racket.getRenderRect())) {
			Vec2 R, A = racket.rigidbody.velocity, B = this->rigidbody.velocity;
			
			float theta = std::atan((B.y + A.y)/(B.x + A.x));
			float A_Mag = std::sqrt(powf(A.x, 2) + powf(A.y, 2));
			float B_Mag = std::sqrt(powf(B.x, 2) + powf(B.y, 2));
			float alpha = std::atan((A.y)/(A.x + B_Mag));

			R.x = speed*cos(alpha);
			R.y = speed*sin(alpha);
			this->rigidbody.velocity = R;
			
			this->rigidbody.velocity.x *= (this->transform.position.x - racket.transform.position.x < 0) ? -1: 1;
		}
		
		racket.rigidbody.velocity.clear();
	}

	void render(SDL_Renderer *renderer) {
		SDL_RenderFillRect(renderer, getRenderRect());
	}

	void reset() {
		this->transform.position = Vec2(WIDTH/2, HEIGHT/2);
		int theta = (rand() % 2) ? 1: -1;
		this->rigidbody.velocity = Vec2(speed*theta, 0);
	}

	int speed = 15;
};