#ifndef BALLON_H
#define BALLON_H

#include <SFML/Graphics.hpp>

class Ballon: public sf::Drawable {
	private:
		const int xSize;
		const int ySize;

		sf::Texture ballonTexture;
		sf::Sprite ballon;
		int xAcceleration;
		int yAcceleration;
		bool xMovement = false;
		bool yMovement = false;
		sf::Clock updateClock;
		sf::Clock slowDownClock;

	public:
		Ballon(int xSize, int ySize);

		void horiAcceleration(bool increase);
		void vertAcceleration(bool increase);

		void update();
		void isMoving(bool mvm, bool x);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
