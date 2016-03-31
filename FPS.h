#ifndef FPS_H
#define FPS_H

#include <SFML/Graphics.hpp>
#include <string>

class FPS: public sf::Drawable
{
    private:
        sf::Clock reloj;
        sf::Text txt;
        sf::Font fuente;
        int numLaps;


    public:
        FPS(std::string pathFont);
        virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
        void update();

};

#endif
