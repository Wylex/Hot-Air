#include "Ballon.h"
#include <cmath>
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
	if(increase and xAcceleration < 50)
		if(xAcceleration == 0)
			xAcceleration = 9;
		else
			xAcceleration += 3;
	else if(xAcceleration > -50)
		if(xAcceleration == 0)
			xAcceleration = -9;
		else
			xAcceleration -= 3;
}

void Ballon::vertAcceleration(bool increase) {
	if(increase and yAcceleration < 50)
		if(yAcceleration == 0)
			yAcceleration = 9;
		else
			yAcceleration += 3;
	else if(yAcceleration > -50)
		if(yAcceleration == 0)
			yAcceleration = -9;
		else
			yAcceleration -= 3;
}

void Ballon::update() {
	//Mover globo
	if(updateClock.getElapsedTime().asMilliseconds() > 40) {
		updateClock.restart(); //Reiniciar tiempo

		int xAcc, yAcc;
		if(xAcceleration > 0)
			xAcc = 3;
		else
			xAcc = -3;
		if(yAcceleration > 0)
			yAcc = 3;
		else
			yAcc = -3;

		for(int i(0); i < std::abs(xAcceleration)/3; i++) {
			ballon.move(xAcc/10.0, 0);
			//Comprobar si no se ha salido de la imagen
			if(ballon.getGlobalBounds().left -5 < 0 or ballon.getGlobalBounds().left + ballon.getGlobalBounds().width + 5 > xSize) {
				ballon.move(-xAcc/10.0, 0);
				xAcceleration = 0;
			}
		}
		for(int i(0); i < std::abs(yAcceleration)/3; i++) {
			ballon.move(0, yAcc/10.0);
			if(ballon.getGlobalBounds().top -5 < 0 or ballon.getGlobalBounds().top + ballon.getGlobalBounds().height + 5 > (ySize/2) + 40) {
				ballon.move(0, -yAcc/10.0);
				yAcceleration = 0;
			}
		}
	}

	if(xAcceleration == 0 and yAcceleration == 0) //No iniciar cronómetro hasta que aumente la velocidad algo
		slowDownClock.restart();

	//Disminución progresiva de la aceleración
	if(slowDownClock.getElapsedTime().asMilliseconds() > 120) {
		if(!xMovement) {
			slowDownClock.restart();

			if(xAcceleration > 0)
				xAcceleration -= 3;
			else if(xAcceleration < 0)
				xAcceleration += 3;
		}
		if(!yMovement) {
			slowDownClock.restart();

			if(yAcceleration > 0)
				yAcceleration -= 3;
			else if(yAcceleration < 0)
				yAcceleration += 3;
		}
	}

	std::cout << xAcceleration << std::endl;

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
