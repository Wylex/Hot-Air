#include "Ballon.h"
#include <iostream>

Ballon::Ballon(int x, int y): xSize(x), ySize(y) {
	ballonTexture.loadFromFile("Imgs/ballon.png");
	ballon.setTexture(ballonTexture);
	ballonTextureReflec.loadFromFile("Imgs/ballon_reflec.png");
	ballonReflec.setTexture(ballonTextureReflec);

	xAcceleration = 0;
	yAcceleration = 0;

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

void Ballon::vertAcceleration(bool increase) {
	if(increase and yAcceleration < 30)
		if(yAcceleration == 0)
			yAcceleration = 8;
		else
			yAcceleration += 2;
	else if(yAcceleration > -30)
		if(yAcceleration == 0)
			yAcceleration = -8;
		else
			yAcceleration -= 2;
}

void Ballon::update() {
	//Mover globo
	if(updateClock.getElapsedTime().asMilliseconds() > 40) {
		updateClock.restart(); //Reiniciar tiempo

		sf::Vector2f position = ballon.getPosition();
		ballon.move(xAcceleration/10.0, yAcceleration/10.0);
		//Comprobar si no se ha salido de la imagen
		if(ballon.getGlobalBounds().left -5 < 0 or ballon.getGlobalBounds().left + ballon.getGlobalBounds().width + 5 > xSize) {
			ballon.setPosition(position);
			xAcceleration = 0;
		}
		if(ballon.getGlobalBounds().top -5 < 0 or ballon.getGlobalBounds().top + ballon.getGlobalBounds().height + 5 > (ySize/2) + 40) {
			ballon.setPosition(position);
			yAcceleration = 0;
		}
	}

	if(xAcceleration == 0 and yAcceleration == 0) //No iniciar cronómetro hasta que aumente la velocidad algo
		slowDownClock.restart();

	//Disminución progresiva de la aceleración
	if(slowDownClock.getElapsedTime().asMilliseconds() > 120) {
		if(!xMovement) {
			slowDownClock.restart();

			if(xAcceleration > 0)
				xAcceleration -= 2;
			else if(xAcceleration < 0)
				xAcceleration += 2;
		}
		if(!yMovement) {
			slowDownClock.restart();

			if(yAcceleration > 0)
				yAcceleration -= 2;
			else if(yAcceleration < 0)
				yAcceleration += 2;
		}
	}


	ballonReflec.setPosition(ballon.getPosition().x, ((ySize/2) + 40) + ((ySize/2) + 40) - (ballon.getGlobalBounds().top + ballon.getLocalBounds().height));
}

void Ballon::isMoving(bool mvm, bool x) {
	if(x)
		xMovement = mvm;
	else
		yMovement = mvm;
}

void Ballon::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(ballon, states);
	target.draw(ballonReflec, states);
}
