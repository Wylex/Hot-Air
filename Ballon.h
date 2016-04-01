#ifndef BALLON_H
#define BALLON_H

#include <SFML/Graphics.hpp>

class Ballon: public sf::Drawable {
	private:
		const int xWindowSize;
		const int yWindowSize;
		const int accelerationStep = 3;

		sf::Texture ballonTexture;
		sf::Sprite ballon;
		sf::Texture ballonTextureReflec;
		sf::Sprite ballonReflec;

		int xAcceleration;
		int yAcceleration;
		bool xMovement = false;
		bool yMovement = false;

		sf::Clock updateClock;
		sf::Clock slowDownClock;

		sf::Clock xAccChrono;
		sf::Clock yAccChrono;

	public:
		Ballon(int xSize, int ySize);

		void xAccelerate(bool increase);
		void yAccelerate(bool increase);
		void isXMoving(bool mvm);
		void isYMoving(bool mvm);
		void resetPos();
		sf::FloatRect getBounds() const;

		void update();
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
