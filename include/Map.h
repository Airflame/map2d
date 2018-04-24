#ifndef MAP_H
#define MAP_H
#include <vector>
#include <SFML/Graphics.hpp>

typedef std::vector< std::vector<bool> > bMap;
typedef std::vector<bool> bRow;
typedef int binaryRow;

class Map
{
    public:
        sf::RectangleShape entity[32][32];
        bMap visited;
        sf::Vector2i current;

        Map();
        void visit( int, int );
};

#endif // MAP_H
