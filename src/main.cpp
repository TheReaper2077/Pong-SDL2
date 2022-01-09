#include "Engine.h"
#include <stdlib.h>

Engine *engine = nullptr;

int main(int argc, char **argv) {
	engine = new Engine();
	engine->init();
	engine->gameloop();

	free(engine);
	engine = nullptr;
	return 0;
}