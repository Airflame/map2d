#include "Player.h"

Player::Player()
{
    outerpos = sf::Vector2i(15,15);
    innerpos = sf::Vector2i(15,15);
}

bool Player::innermove( int argx, int argy )
{
    bool outerchange = false;
    innerpos.x += argx;
    innerpos.y += argy;
    if( innerpos.x > 31 )
    {
        outerpos.x++;
        innerpos.x = 0;
        outerchange = true;
    }
    if( innerpos.x < 0 )
    {
        outerpos.x--;
        innerpos.x = 31;
        outerchange = true;
    }
    if( innerpos.y > 31 )
    {
        outerpos.y++;
        innerpos.y = 0;
        outerchange = true;
    }
    if( innerpos.y < 0 )
    {
        outerpos.y--;
        innerpos.y = 31;
        outerchange = true;
    }
    return outerchange;
}
