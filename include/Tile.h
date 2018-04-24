#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>


class Tile
{
    public:
        sf::RectangleShape entity;
        int type, colour_offset;

        Tile( int, int );
        void setType( int );

    private:
        const int size = 16;
};

#endif // TILE_H
