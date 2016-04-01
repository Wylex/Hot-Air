#include "Ballon.h"
#include <cmath>

Ballon::Ballon(int x, int y): xWindowSize(x), yWindowSize(y) {
	ballonTexture.loadFromFile("Resources/ballon.png");
	ballon.setTexture(ballonTexture);
	ballonTextureReflec.loadFromFile("Resources/ballon_reflec.png");
	ballonReflec.setTexture(ballonTextureReflec);

	xAcceleration = 0;
	yAcceleration = 0;

	ballon.setPosition(xWindowSize/2 - ballon.getLocalBounds().width/2, 100);
}

void Ballon::xAccelerate(bool increase) {
	if(xAccChrono.getElapsedTime().asMilliseconds() > 45) {
		if(increase and xAcceleration < 50)
			if(xAcceleration == 0)
				xAcceleration = accelerationStep*3;
			else
				xAcceleration += accelerationStep;
		else if(xAcceleration > -50)
			if(xAcceleration == 0)
				xAcceleration = -accelerationStep*3;
			else
				xAcceleration -= accelerationStep;
		xAccChrono.restart();
	}
}

void Ballon::yAccelerate(bool increase) {
	if(yAccChrono.getElapsedTime().asMilliseconds() > 45) {
		if(increase and yAcceleration < 50)
			if(yAcceleration == 0)
				yAcceleration = accelerationStep*3;
			else
				yAcceleration += accelerationStep;
		else if(yAcceleration > -50)
			if(yAcceleration == 0)
				yAcceleration = -accelerationStep*3;
			else
				yAcceleration -= accelerationStep;
		yAccChrono.restart();
	}
}

void Ballon::update() {
	//Mover globo
	if(updateClock.getElapsedTime().asMilliseconds() > 40) {
		updateClock.restart(); //Reiniciar tiempo

		int xAcc, yAcc;
		if(xAcceleration > 0)
			xAcc = accelerationStep;
		else
			xAcc = -accelerationStep;
		if(yAcceleration > 0)
			yAcc = accelerationStep;
		else
			yAcc = -accelerationStep;

		for(int i(0); i < std::abs(xAcceleration)/accelerationStep; i++) {
			ballon.move(xAcc/10.0, 0);
			//Comprobar si no se ha salido de la imagen
			if(ballon.getGlobalBounds().left -5 < 0 or ballon.getGlobalBounds().left + ballon.getGlobalBounds().width + 5 > xWindowSize) {
				ballon.move(-xAcc/10.0, 0);
				xAcceleration = 0;
			}
		}
		for(int i(0); i < std::abs(yAcceleration)/accelerationStep; i++) {
			ballon.move(0, yAcc/10.0);
			if(ballon.getGlobalBounds().top -5 < 0 or ballon.getGlobalBounds().top + ballon.getGlobalBounds().height + 5 > (yWindowSize/2) + 40) {
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
				xAcceleration -= accelerationStep;
			else if(xAcceleration < 0)
				xAcceleration += accelerationStep;
		}
		if(!yMovement) {
			slowDownClock.restart();

			if(yAcceleration > 0)
				yAcceleration -= accelerationStep;
			else if(yAcceleration < 0)
				yAcceleration += accelerationStep;
		}
	}

	//Reflejo del globo
	ballonReflec.setPosition(ballon.getPosition().x, ((yWindowSize/2) + 40) + ((yWindowSize/2) + 40) - (ballon.getGlobalBounds().top + ballon.getLocalBounds().height));
	sf::Color ballonRefColor = ballonReflec.getColor();
	ballonRefColor.a = 210 - (ballonReflec.getGlobalBounds().top - ((yWindowSize/2) + 40));
	ballonReflec.setColor(ballonRefColor);
}

void Ballon::isXMoving(bool mvm) {
		xMovement = mvm;
}

void Ballon::isYMoving(bool mvm) {
		yMovement = mvm;
}

void Ballon::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(ballon, states);
	target.draw(ballonReflec, states);
}

void Ballon::resetPos() {
	ballon.setPosition(xWindowSize/2 - ballon.getLocalBounds().width/2, 100);
	xAcceleration = 0;
	yAcceleration = 0;
}

sf::FloatRect Ballon::getBounds() const {
	return ballon.getGlobalBounds();
}
