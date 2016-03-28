#include "World.h"

World::World(): window(sf::VideoMode(xSize, ySize), "Hot Air"), ballon(xSize, ySize) {
	backgroundTexture.loadFromFile("Imgs/background.png");
	background.setTexture(backgroundTexture);

}

void World::start() {
	while (window.isOpen()) {
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
		window.display();
	}

}
