#include "Map.h"

Map::Map()
{
    for( int i = 0; i < 32; i++ )
    {
        for( int j = 0; j < 32; j++ )
        {
            entity[i][j].setSize(sf::Vector2f(16,16));
            entity[i][j].setPosition(sf::Vector2f(j*16,i*16));
            entity[i][j].setOutlineColor(sf::Color::Black);
            entity[i][j].setOutlineThickness(1);
            entity[i][j].setFillColor(sf::Color(44, 62, 80));
        }
    }
    for( int i = 0; i < 32; i++ )
    {
        bRow row;
        for( int j = 0; j < 32; j++ )
        {
            row.push_back(0);
        }
        visited.push_back(row);
        row.clear();
    }
    visited[15][15] = 1;
}

void Map::visit( int posy, int posx )
{
    visited[posy][posx] = true;
    for( int i = 0; i < 32; i++ )
    {
        for( int j = 0; j < 32; j++ )
        {
            if( visited[i][j] == true )
                entity[i][j].setFillColor(sf::Color(149, 165, 166));
            else
                entity[i][j].setFillColor(sf::Color(44, 62, 80));
        }
    }
    entity[posy][posx].setFillColor(sf::Color(236, 240, 241));
}
