#include "FPS.h"
#include <string>

FPS::FPS(std::string pathFont)
{
    reloj.restart();
    numLaps = 0;

    fuente.loadFromFile(pathFont);
    txt.setFont(fuente);
    txt.setPosition(10, 10);
    txt.setColor(sf::Color::Red);
    txt.setCharacterSize(15);
}

void FPS::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    target.draw(txt, states);
}

void FPS::update()
{
    if(reloj.getElapsedTime() > sf::seconds(1))
    {
        std::string str = std::to_string(numLaps);
        str += " fps";
        txt.setString(str);
        numLaps = 0;
        reloj.restart();
    }

    numLaps++;
}
