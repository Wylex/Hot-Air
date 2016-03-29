#include "Bird.h"
#include <ctime>
#include <cstdlib>

Bird::Bird(int xSize, int ySize, bool left) {
	birdText.loadFromFile("Imgs/bird1.png");
	bird.setTexture(birdText);

	std::srand(time(NULL));

	int yPosition = std::rand()%int(ySize - bird.getGlobalBounds().height);

	if(left)
		bird.setPosition(0 - bird.getGlobalBounds().width, yPosition);
	else
		bird.setPosition(xSize, yPosition);
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
