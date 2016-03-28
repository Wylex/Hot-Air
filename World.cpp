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
	sf::Clock birdSpawnChrono;
	sf::Clock birdMove;

	std::srand(time(NULL));

	while (window.isOpen()) {

		if(birdSpawnChrono.getElapsedTime().asSeconds() > 2)
			birdSpawn();


		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
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

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				ballon.horiAcceleration(false);
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				ballon.horiAcceleration(true);
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				ballon.vertAcceleration(false);
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				ballon.vertAcceleration(true);

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

		ballon.update();

		window.clear();
		window.draw(background);
		window.draw(ballon);
		for(int i(0); i < birds.size(); i++)
			window.draw(*birds[i]);
		window.display();
	}

}

void World::birdSpawn() {
	birds.push_back(std::move(new Bird(xSize, ySize/2 + 40, true)));
}

bool World::birdRemove() {
	bool removed = false;

	if(birds.size() > 0) {
		sf::FloatRect birdPos = birds[birds.size() -1]->getBounds();

		if(birdPos.left + birdPos.width < 0 or birdPos.left + birdPos.width > 350) {
			delete birds[birds.size() -1];
			birds.pop_back();
			removed = true;
		}
	}

	return removed;
}
