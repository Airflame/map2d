#include "../include/Tile.h"

Tile::Tile( int yt, int xt )
{
    entity.setSize(sf::Vector2f(size,size));
    entity.setPosition(sf::Vector2f(xt*size,yt*size));
    entity.setFillColor(sf::Color(41, 128, 185));
    type = 0;
    colour_offset = (rand()%6-3);
}

void Tile::setType( int arg )
{
    type = arg;
    switch( arg )
    {
    case 0: //background
        entity.setFillColor(sf::Color(41 + colour_offset, 128 + colour_offset, 185 + colour_offset));
        break;
    case 1: //body
        entity.setFillColor(sf::Color(241 + colour_offset, 196 + colour_offset, 15 + colour_offset));
        break;
    case 2:
        entity.setFillColor(sf::Color(236 + colour_offset, 240 + colour_offset, 241 + colour_offset));
        break;
    }
}
