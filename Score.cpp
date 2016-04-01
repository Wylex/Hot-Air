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

int Score::setFirstDigitsPos(int num, int x) {
	int digits = getDigits(num);

	int a = 1;
	for(int b(1); b < digits; b++)
		a*= 10;

	nums[num/a].setPosition(x, yPos);

	return a;
}

int Score::getScore() const {
	return score;
}

void Score::saveScore(std::string filePath) const {
	std::ofstream file(filePath);
	file << score;
}

void Score::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	int temp = score;
	int x(xPos);
	for(int i(0); i < getDigits(score); i++) {
		int a = const_cast<Score*>(this)->setFirstDigitsPos(temp, x);
		target.draw(nums[temp/a], states);

		temp %= a;
		x+= 12;
	}
}
