#include "Ballon.h"
#include <cmath>

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
	if(xAccChrono.getElapsedTime().asMilliseconds() > 40) {
		if(increase and xAcceleration < 50)
			if(xAcceleration == 0)
				xAcceleration = 6;
			else
				xAcceleration += 2;
		else if(xAcceleration > -50)
			if(xAcceleration == 0)
				xAcceleration = -6;
			else
				xAcceleration -= 2;
		xAccChrono.restart();
	}
}

void Ballon::vertAcceleration(bool increase) {
	if(yAccChrono.getElapsedTime().asMilliseconds() > 40) {
		if(increase and yAcceleration < 50)
			if(yAcceleration == 0)
				yAcceleration = 6;
			else
				yAcceleration += 2;
		else if(yAcceleration > -50)
			if(yAcceleration == 0)
				yAcceleration = -6;
			else
				yAcceleration -= 2;
		yAccChrono.restart();
	}
}

void Ballon::update() {
	//Mover globo
	if(updateClock.getElapsedTime().asMilliseconds() > 40) {
		updateClock.restart(); //Reiniciar tiempo

		int xAcc, yAcc;
		if(xAcceleration > 0)
			xAcc = 2;
		else
			xAcc = -2;
		if(yAcceleration > 0)
			yAcc = 2;
		else
			yAcc = -2;

		for(int i(0); i < std::abs(xAcceleration)/2; i++) {
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

	//Reflejo del globo
	ballonReflec.setPosition(ballon.getPosition().x, ((ySize/2) + 40) + ((ySize/2) + 40) - (ballon.getGlobalBounds().top + ballon.getLocalBounds().height));
	sf::Color ballonRefColor = ballonReflec.getColor();
	ballonRefColor.a = 210 - (ballonReflec.getGlobalBounds().top - ((ySize/2) + 40));
	ballonReflec.setColor(ballonRefColor);
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
