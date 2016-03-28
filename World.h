#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Bird.h"
#include "Ballon.h"

class World {
	private:
		const int xSize = 480;
		const int ySize = 350;

		sf::RenderWindow window;
		sf::Texture backgroundTexture;
		sf::Sprite background;

		Ballon ballon;
		std::vector<Bird*> birds;

	private:
		void birdSpawn();
		bool birdRemove();

	public:
		World();
		~World();
		void start();
};

#endif
