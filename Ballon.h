#ifndef BALLON_H
#define BALLON_H

#include <SFML/Graphics.hpp>

class Ballon: public sf::Drawable {
	private:
		sf::Texture ballonTexture;
		sf::Sprite ballon;
		int xAcceleration;
		int yAcceleration;
		bool movement = false;
		sf::Clock updateClock;
		sf::Clock slowDownClock;

		const int xSize;
		const int ySize;

	public:
		Ballon(int xSize, int ySize);
		void update();
		void horiAcceleration(bool increase);
		void vertAcceleration(bool increase);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void isMoving(bool mvm);
};

#endif
