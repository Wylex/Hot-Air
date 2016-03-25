#include "Ballon.h"
#include <iostream>

Ballon::Ballon(int x, int y): xSize(x), ySize(y) {
	ballonTexture.loadFromFile("Imgs/ballon.png");
	ballon.setTexture(ballonTexture);

	xAcceleration = 0;
	yAcceleration = 0;

	updateClock.restart();
	slowDownClock.restart();

	ballon.setPosition(xSize/2 - ballon.getLocalBounds().width/2, 100);
}

void Ballon::horiAcceleration(bool increase) {
	if(increase and xAcceleration < 30)
		if(xAcceleration == 0)
			xAcceleration = 8;
		else
			xAcceleration += 2;
	else if(xAcceleration > -30)
		if(xAcceleration == 0)
			xAcceleration = -8;
		else
			xAcceleration -= 2;
}

void Ballon::update() {
	//Mover globo
	if(updateClock.getElapsedTime().asMilliseconds() > 20) {
		updateClock.restart(); //Reiniciar tiempo

		sf::Vector2f position = ballon.getPosition();
		ballon.move(xAcceleration/10.0, yAcceleration/10.0);
		//Comprobar si no se ha salido de la imagen
		if(ballon.getGlobalBounds().left -5 < 0 or ballon.getGlobalBounds().left + ballon.getGlobalBounds().width + 5 > xSize) {
			ballon.setPosition(position);
			xAcceleration = 0;
		}
	}

	if(xAcceleration == 0 and yAcceleration == 0) //No iniciar cronómetro hasta que aumente la velocidad algo
		slowDownClock.restart();

	//Disminución progresiva de la aceleración
	if(slowDownClock.getElapsedTime().asMilliseconds() > 200 and !movement) {
		slowDownClock.restart();

		if(xAcceleration > 0)
			xAcceleration -= 2;
		else if(xAcceleration < 0)
			xAcceleration += 2;

		if(yAcceleration > 0)
			yAcceleration -= 2;
		else if(yAcceleration < 0)
			yAcceleration += 2;
	}

	std::cout << "xAcceleration = " << xAcceleration << std::endl;
}

void Ballon::isMoving(bool mvm) {
	movement = mvm;
}

void Ballon::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(ballon, states);
}
