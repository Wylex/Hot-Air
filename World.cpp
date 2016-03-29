#include <ctime>
#include <cstdlib>
#include "World.h"

World::World(): window(sf::VideoMode(xSize, ySize), "Hot Air"), ballon(xSize, ySize) {
	backgroundTexture.loadFromFile("Imgs/background.png");
	background.setTexture(backgroundTexture);

}

World::~World() {
	while(birdRemove()) {}
}

void World::start() {
	std::srand(time(NULL));

	sf::Clock birdSpawnChrono;
	sf::Clock birdMoveChrono;
	int birdSpawnTime = (std::rand()%4)+3;
	std::vector<Direction> birdDirections;

	while (window.isOpen()) {

		//Spawning birds
		if(birdSpawnChrono.getElapsedTime().asSeconds() > birdSpawnTime) {
			if(std::rand()%2) {
				birdSpawn(true);
				birdDirections.push_back(right);
			}
			else {
				birdSpawn(false);
				birdDirections.push_back(left);
			}
			birdSpawnTime = (std::rand()%5)+1;
			birdSpawnChrono.restart();
		}
		//Moving birds
		if(birdMoveChrono.getElapsedTime().asMilliseconds()	> 20) {
			for(int i(0); i < birds.size(); i++) {
				if(birdDirections[i] == left)
					birds[i]->move(-3);
				else
					birds[i]->move(3);
			}
			birdMoveChrono.restart();
		}
		birdRemove();

		userInput();

		ballon.update();

		window.clear();
		window.draw(background);
		for(int i(0); i < birds.size(); i++)
			window.draw(*birds[i]);
		window.draw(ballon);
		window.display();
	}

}

void World::birdSpawn(bool left) {
	birds.push_back(std::move(new Bird(xSize, ySize/2 + 40, left)));
}

bool World::birdRemove() {
	bool removed = false;

	if(birds.size() > 0) {
		sf::FloatRect birdPos = birds[birds.size() -1]->getBounds();

		if(birdPos.left + birdPos.width < 0 or birdPos.left > xSize) {
			delete birds[birds.size() -1];
			birds.pop_back();
			removed = true;
		}
	}

	return removed;
}

void World::userInput() {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			//Saber si movimiento
			//Key pressed
			if(event.type == sf::Event::KeyPressed) {
				if(event.key.code == sf::Keyboard::Left)
					ballon.isMoving(true, true);
				if(event.key.code == sf::Keyboard::Right)
					ballon.isMoving(true, true);
				if(event.key.code == sf::Keyboard::Up)
					ballon.isMoving(true, false);
				if(event.key.code == sf::Keyboard::Down)
					ballon.isMoving(true, false);
			}
			//Key released
			if(event.type == sf::Event::KeyReleased) {
				if(event.key.code == sf::Keyboard::Left)
					ballon.isMoving(false, true);
				if(event.key.code == sf::Keyboard::Right)
					ballon.isMoving(false, true);
				if(event.key.code == sf::Keyboard::Up)
					ballon.isMoving(false, false);
				if(event.key.code == sf::Keyboard::Down)
					ballon.isMoving(false, false);
			}
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			ballon.horiAcceleration(false);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			ballon.horiAcceleration(true);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			ballon.vertAcceleration(false);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			ballon.vertAcceleration(true);

}
