#include "Ballon.h"

int main() {
	const int xSize = 480;
	const int ySize = 350;

	sf::RenderWindow window(sf::VideoMode(xSize, ySize), "Hot Air");
	sf::Texture backgroundTexture;
	sf::Sprite background;
	backgroundTexture.loadFromFile("Imgs/background.png");
	background.setTexture(backgroundTexture);
	Ballon ballon(xSize, ySize);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			//Key pressed
			else if(event.type == sf::Event::KeyPressed) {
				if(event.key.code == sf::Keyboard::Left) {
					ballon.horiAcceleration(false);
					ballon.isMoving(true);	
				}
				else if(event.key.code == sf::Keyboard::Right) {
					ballon.horiAcceleration(true);
					ballon.isMoving(true);	
				}
			}
			//Key released
			else if(event.type == sf::Event::KeyReleased) {
				if(event.key.code == sf::Keyboard::Left) {
					ballon.isMoving(false);	
				}
				else if(event.key.code == sf::Keyboard::Right) {
					ballon.isMoving(false);	
				}
			}
		}

		ballon.update();

		window.clear();
		window.draw(background);
		window.draw(ballon);
		window.display();
	}

	return 0;
}
