#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>
#include "World.h"

World::World(): window(sf::VideoMode(xSize, ySize), "Hot Air"), ballon(xSize, ySize), fps("Resources/Font.ttf"), score(305, 178), maxScore(160, 130), paused(true) {
	music.setVolume(30);
	music.openFromFile("Resources/ms.ogg");
	music.setLoop(true);

	backgroundTexture.loadFromFile("Resources/background.png");
	background.setTexture(backgroundTexture);

	for(int i(maxScore.getScore()); i < getMaxScore(); i++)
		maxScore.addOne();

	std::srand(time(NULL));
}

World::~World() {
	while(birdRemove()) {}
}

void World::start() {
	music.play();

	sf::Clock birdSpawnChrono;
	sf::Clock birdMoveChrono;
	int birdSpawnTime = (std::rand()%3)+1;

	sf::Clock scoreChrono;

	while (window.isOpen()) {

		if(!paused) {
			//Spawning birds
			if(birdSpawnChrono.getElapsedTime().asSeconds() >= birdSpawnTime) {
				if(std::rand()%2) {
					birdSpawn(true);
					birdDirections.push_back(right);
				}
				else {
					birdSpawn(false);
					birdDirections.push_back(left);
				}
				birdSpawnTime = (std::rand()%3)+1;
				birdSpawnChrono.restart();
			}
			//Moving birds
			if(birdMoveChrono.getElapsedTime().asMilliseconds()	> 20) {
				for(int i(0); i < birds.size(); i++) {
					if(birdDirections[i] == left)
						birds[i]->move(-4);
					else
						birds[i]->move(4);
				}
				birdMoveChrono.restart();
			}
			birdRemove();

			//Score up
			if(scoreChrono.getElapsedTime().asSeconds() > 1) {
				scoreChrono.restart();
				score.addOne();
			}
		}

		//Check collisions
		for(int i(0); i < birds.size(); i++) {
			if(checkCollisions(birds[i]->getBounds(), ballon.getBounds())) {
				restart();
				paused = true;
			}
		}

		inGameUserInput();

		ballon.update();
		fps.update();

		window.clear();
		window.draw(background);
		window.draw(score);
		window.draw(maxScore);
		for(int i(0); i < birds.size(); i++)
			window.draw(*birds[i]);
		window.draw(ballon);
		window.draw(fps);
		window.display();
	}

	//Save maxScore
	std::ofstream scoreFile(".score.txt");
	if(maxScore.getScore() > getMaxScore())
		scoreFile << std::to_string(maxScore.getScore());

}

int World::getMaxScore() const {
	int maxS = 0;
	std::ifstream scoreFile(".score.txt");
	if(scoreFile.good()) {
		std::string maxScore;
		scoreFile >> maxScore;

		if(maxScore != "")
			maxS = std::stoi(maxScore);
	}

	return maxS;
}

void World::restart() {
	if(maxScore.getScore() < score.getScore()) {
		for(int i(maxScore.getScore()); i < score.getScore(); i++)
			maxScore.addOne();
	}

	score.reset();
	birds.clear();
	birdDirections.clear();
	ballon.resetPos();
}

void World::birdSpawn(bool left) {
	birds.push_back(std::move(new Bird(xSize, ySize/2 + 15, left)));
}

bool World::birdRemove() {
	bool removed = false;

	if(birds.size() > 0) {
		sf::FloatRect birdPos = birds[birds.size() -1]->getBounds();

		if(birdPos.left + birdPos.width < 0 or birdPos.left > xSize) {
			delete birds[birds.size() -1];
			birds.pop_back();
			removed = true;
		}
	}

	return removed;
}

bool World::checkCollisions(sf::FloatRect entity1, sf::FloatRect entity2) const {
	if(entity1.intersects(entity2))
		return true;

	return false;
}

void World::inGameUserInput() {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			//Saber si movimiento
			//Key pressed
			if(event.type == sf::Event::KeyPressed) {
				if(event.key.code == sf::Keyboard::Left)
					ballon.isXMoving(true);
				if(event.key.code == sf::Keyboard::Right)
					ballon.isXMoving(true);
				if(event.key.code == sf::Keyboard::Up)
					ballon.isYMoving(true);
				if(event.key.code == sf::Keyboard::Down)
					ballon.isYMoving(true);

				paused = false;
			}
			//Key released
			if(event.type == sf::Event::KeyReleased) {
				if(event.key.code == sf::Keyboard::Left)
					ballon.isXMoving(false);
				if(event.key.code == sf::Keyboard::Right)
					ballon.isXMoving(false);
				if(event.key.code == sf::Keyboard::Up)
					ballon.isYMoving(false);
				if(event.key.code == sf::Keyboard::Down)
					ballon.isYMoving(false);
			}
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			ballon.xAccelerate(false);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			ballon.xAccelerate(true);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			ballon.yAccelerate(false);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			ballon.yAccelerate(true);
}
