#ifndef SCORE_H
#define SCORE_H

#include <SFML/Graphics.hpp>
#include <array>
#include <fstream>
#include <string>

class Score: public sf::Drawable {
	private:
		std::array<sf::Texture, 10> numsTextures;
		std::array<sf::Sprite, 10> nums;
		int xPos, yPos;
		int score;
		int getDigits(int num) const;
		int setFirstDigitsPos(int num, int xPos);

	public:
		Score(int x, int y);
		void addOne();
		void reset();
		int getScore() const;
		void saveScore(std::string filePath) const;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
