#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>

class Player
{
    public:
        sf::Vector2i outerpos;
        sf::Vector2i innerpos;

        Player();
        bool innermove( int, int );
};

#endif // PLAYER_H
