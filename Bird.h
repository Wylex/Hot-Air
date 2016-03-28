#ifndef BIRD_H
#define BIRD_H

#include <SFML/Graphics.hpp>

class Bird: public sf::Drawable {
	private:
		sf::Texture birdText;
		sf::Sprite bird;

	public:
		Bird(int xSize, int ySize, bool left);
		void move(int speed);
		sf::FloatRect getBounds() const;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
