#include "Bird.h"
#include <ctime>
#include <cstdlib>

Bird::Bird(int xSize, int ySize, bool left) {

	std::srand(time(NULL));

	int yPosition = std::rand()%int(ySize - bird.getGlobalBounds().height);

	if(left) {
		birdText.loadFromFile("Resources/bird2B.png");
		bird.setPosition(0 - bird.getGlobalBounds().width, yPosition);
	}
	else {
		birdText.loadFromFile("Resources/bird1B.png");
		bird.setPosition(xSize, yPosition);
	}

	bird.setTexture(birdText);
}

void Bird::move(int speed) {
	bird.move(speed, 0);
}

sf::FloatRect Bird::getBounds() const {
	return bird.getGlobalBounds();
}

void Bird::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(bird, states);
}
