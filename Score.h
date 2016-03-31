#ifndef SCORE_H
#define SCORE_H

#include <SFML/Graphics.hpp>
#include <array>

class Score: public sf::Drawable {
	private:
		std::array<sf::Texture, 10> numsTextures;
		std::array<sf::Sprite, 10> nums;
		int score;
		int getDigits(int num) const;
		int setFirstDigitsPos(int num, int xPos);

	public:
		Score();
		void addOne();
		void reset();

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
