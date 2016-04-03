#include "Score.h"
#include <string>

Score::Score(int x, int y) {
	for(int i(0); i < 10; i++) {
		std::string file = "Resources/";
		file += std::to_string(i);
		file += ".png";

		numsTextures[i].loadFromFile(file);
		nums[i].setTexture(numsTextures[i]);
	}

	xPos = x;
	yPos = y;
	score = 0;
}

int Score::getDigits(int num) const {
	int digits = 0;
	int temp = num;
	do {
		digits++;
		temp/= 10;
	} while(temp >= 1);

	return digits;
}

int Score::setFirstDigitsPos(std::string num, int x) {
	char digit = num[0];
	int index = digit - '0';
	nums[index].setPosition(x, yPos);

	return index;
}

int Score::getScore() const {
	return score;
}

void Score::addOne() {
	score++;
}

void Score::reset() {
	score = 0;
}

void Score::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	std::string temp = std::to_string(score);
	int x(xPos);
	for(int i(0); i < getDigits(score); i++) {
		int a = const_cast<Score*>(this)->setFirstDigitsPos(temp, x);
		target.draw(nums[a], states);

		temp.erase(0,1);

		x+= 12;
	}
}
