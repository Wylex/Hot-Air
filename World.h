#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>

#include "Ballon.h"

class World {
	private:
		const int xSize;
		const int ySize;

		sf::RenderWindow window;

		sf::Texture backgroundTexture;
		sf::Sprite background;

		Ballon ballon;

	public:
		World();
		void start();
};

#endif
