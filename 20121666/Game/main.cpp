#include "Game.h"

void main() {
	Game *Games = new Game;

	Games->Init();

	while (true) {
		Games->Update();
	}
}