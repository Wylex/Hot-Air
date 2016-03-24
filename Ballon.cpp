#include "Ballon.h"

Ballon::Ballon(int xSize, int ySize) {
	ballonTexture.loadFromFile("Imgs/ballon.png");
	ballon.setTexture(ballonTexture);

	position.x = xSize/2 - ballon.getLocalBounds().width/2;
	position.y = 100;
	ballon.setPosition(position.x, position.y);
}


void Ballon::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(ballon, states);
}
