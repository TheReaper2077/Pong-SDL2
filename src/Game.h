#pragma once

#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"
#include <iostream>
#include <cmath>
#include <math.h>

class Vec2 {
public:
	float x, y, magnitude, theta;
	
	Vec2(float x, float y): x(x), y(y) {}
	Vec2(int x, int y): x(x), y(y) {}
	Vec2(double x, double y): x(x), y(y) {}
	Vec2(): x(0), y(0) {}

	void clear() {x = y = 0;}
	
	void operator=(const Vec2 v) {
		x = v.x;
		y = v.y;

		magnitude = getMagnitude();
	}

	void operator+=(const Vec2 v) {
		x += v.x;
		y += v.y;
	}

	void operator-=(const Vec2 v) {
		x -= v.x;
		y -= v.y;
	}

	void operator*=(const int i) {
		x *= i;
		y *= i;
	}

	void setAlpha(const float alpha) {
		x = magnitude*cos(alpha);
		y = magnitude*sin(alpha);
	}

	Vec2 operator+(const Vec2 v) const {
		return Vec2(v.x + x, v.y + y);
	}

	Vec2 operator*(const double d) const {
		return Vec2(d * x, d * y);
	}

	Vec2 operator-(const Vec2 v) const {
		return Vec2(v.x - x, v.y - y);
	}

	float getMagnitude() {
		this->magnitude = std::sqrt(powf(x, 2) + powf(y, 2));
		return magnitude;
	}

private:
	void setMagnitude() {
		// this->magnitude = std::sqrt(powf(x, 2) + powf(y, 2));
	}
};

class Vec2I {
public:
	int x, y;
	
	Vec2I(int x, int y): x(x), y(y) {}
	Vec2I(): x(0), y(0) {}
};


struct Transform {
	Vec2 position;
	Vec2I scale;
};

struct Rigidbody {
	Vec2 velocity;
};

class Object {
public:
	Transform transform;
	Rigidbody rigidbody;

	Object() {}
	virtual void update(double dt) = 0;
	virtual void render(SDL_Renderer *renderer) = 0;

	SDL_Rect *getRenderRect() {
		rect = {static_cast<int>(transform.position.x), static_cast<int>(transform.position.y), transform.scale.x, transform.scale.y};
		return &rect;
	}

	SDL_Rect *getCollisionRect() {
		rect = {static_cast<int>(transform.position.x + rigidbody.velocity.x), static_cast<int>(transform.position.y + rigidbody.velocity.y), transform.scale.x, transform.scale.y};
		return &rect;
	}

protected:
	SDL_Rect rect;
};

