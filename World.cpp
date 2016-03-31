#include <ctime>
#include <cstdlib>
#include "World.h"

World::World(): window(sf::VideoMode(xSize, ySize), "Hot Air"), ballon(xSize, ySize), fps("Imgs/Font.ttf") {
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
	int birdSpawnTime = (std::rand()%3)+2;
	std::vector<Direction> birdDirections;

	sf::Clock scoreChrono;

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
			birdSpawnTime = (std::rand()%3)+1;
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

		//Score up
		if(scoreChrono.getElapsedTime().asSeconds() > 1) {
			scoreChrono.restart();
			score.addOne();
		}

		inGameUserInput();

		ballon.update();
		fps.update();

		window.clear();
		window.draw(background);
		window.draw(score);
		for(int i(0); i < birds.size(); i++)
			window.draw(*birds[i]);
		window.draw(ballon);
		window.draw(fps);
		window.display();
	}

}

void World::birdSpawn(bool left) {
	birds.push_back(std::move(new Bird(xSize, ySize/2 + 15, left)));
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

void World::inGameUserInput() {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			//Saber si movimiento
			//Key pressed
			if(event.type == sf::Event::KeyPressed) {
				if(event.key.code == sf::Keyboard::Left)
					ballon.isXMoving(true);
				if(event.key.code == sf::Keyboard::Right)
					ballon.isXMoving(true);
				if(event.key.code == sf::Keyboard::Up)
					ballon.isYMoving(true);
				if(event.key.code == sf::Keyboard::Down)
					ballon.isYMoving(true);
			}
			//Key released
			if(event.type == sf::Event::KeyReleased) {
				if(event.key.code == sf::Keyboard::Left)
					ballon.isXMoving(false);
				if(event.key.code == sf::Keyboard::Right)
					ballon.isXMoving(false);
				if(event.key.code == sf::Keyboard::Up)
					ballon.isYMoving(false);
				if(event.key.code == sf::Keyboard::Down)
					ballon.isYMoving(false);
			}
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			ballon.xAccelerate(false);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			ballon.xAccelerate(true);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			ballon.yAccelerate(false);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			ballon.yAccelerate(true);

}
