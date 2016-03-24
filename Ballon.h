#ifndef BALLON_H
#define BALLON_H

#include <SFML/Graphics.hpp>

class Ballon: public sf::Drawable {
	private:
		sf::Texture ballonTexture;
		sf::Sprite ballon;
		sf::Vector2f position;

	public:
		Ballon(int xSize, int ySize);
		void horiAcceleration(bool increase);
		void vertAcceleration(bool increase);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
