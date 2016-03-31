#include "Score.h"
#include <string>

Score::Score() {
	for(int i(0); i < 10; i++) {
		std::string file = "Imgs/";
		file += std::to_string(i);
		file += ".png";

		numsTextures[i].loadFromFile(file);
		nums[i].setTexture(numsTextures[i]);
	}

	nums[0].setPosition(310,175);

	score = 0;
}

void Score::addOne() {
	score++;
}

void Score::reset() {
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

int Score::setFirstDigitsPos(int num, int xPos) {
	int yPos(178);
	int digits = getDigits(num);

	int a = 1;
	for(int b(1); b < digits; b++)
		a*= 10;

	nums[num/a].setPosition(xPos, yPos);

	return a;
}

void Score::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	int temp = score;
	int xPos(305);
	for(int i(0); i < getDigits(score); i++) {
		int a = const_cast<Score*>(this)->setFirstDigitsPos(temp, xPos);
		target.draw(nums[temp/a], states);

		temp %= a;
		xPos += 11;
	}
}
