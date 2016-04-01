#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Bird.h"
#include "Ballon.h"
#include "FPS.h"
#include "Score.h"

class World {
	private:
		const int xSize = 480;
		const int ySize = 350;

		sf::RenderWindow window;
		sf::Texture backgroundTexture;
		sf::Sprite background;
		bool gameOn;

		Ballon ballon;
		std::vector<Bird*> birds;
		enum Direction {left, right};
		std::vector<Direction> birdDirections;

		FPS fps;
		Score score;

	private:
		void birdSpawn(bool left);
		bool birdRemove();
		void inGameUserInput();
		bool checkCollisions(sf::FloatRect entity1, sf::FloatRect entity2) const;
		void restart();

	public:
		World();
		~World();
		void start();
};

#endif
