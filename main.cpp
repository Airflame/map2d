#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include "include/Tile.h"
#include "include/Map.h"
#include "include/Player.h"
#define T_0 0.03

template<typename T> std::string tostr( T arg )
{
    std::stringstream ss;
    ss << arg;
    return ss.str();
}

bMap fromfile( std::string filename )
{
    bMap output;
    std::ifstream file(filename, std::ios::binary);
    if( file.good() )
    {
        char* buffer = new char[sizeof(int)];
        for( int r = 0; r < 32; r++ )
        {
            file.read(buffer, sizeof(int));
            binaryRow* br = (binaryRow*)buffer;
            bRow row(32,0);
            int n = 0;
            for( int i = 1; i <= sizeof(int); i++ )
            {
                for( int j = 1; j <= 8; j++ )
                {
                    row[i*8-j] = *br >> n & 1;
                    n++;
                }
            }
            output.push_back(row);
        }
        delete buffer;
    }
    else
    {
        output = bMap(32, bRow(32, 0) );
    }
    file.close();
    return output;
}


int main()
{
    //////////////////////WINDOW//////////////////////////////////////
    sf::Clock clock;
    float dt = 0;
    sf::RenderWindow window(sf::VideoMode(512, 512), "Map");
    window.setFramerateLimit(60);
    srand( time( NULL ) );
    //////////////////////////////////////////////////////////////////


    //////////////////////OBJECTS/////////////////////////////////////
    Tile* tiles[32][32];
    Player* player = new Player();
    Map* visitmap = new Map();
    for( int i = 0; i < 32; i++ )
    {
        for( int j = 0; j < 32; j++ )
        {
            tiles[i][j] = new Tile( i,j );
        }
    }
    bMap dummy(32, bRow(32, 0) );
    std::vector< std::vector<bMap> > maps(32, std::vector<bMap>(32, dummy));
    for( int i = 0; i < 32; i++ )
    {
        for( int j = 0; j < 32; j++ )
        {
            std::string filename = "";
            std::string sx = tostr(i);
            if( sx.length() == 1 )
                sx = "0" + sx;
            std::string sy = tostr(j);
            if( sy.length() == 1 )
                sy = "0" + sy;
            filename = "maps/" + sx + "-" + sy + ".map";
            maps[i][j] = fromfile(filename);
        }
    }
    float timer = T_0;
    bool openedmap = false;
    //////////////////////////////////////////////////////////////////


    while (window.isOpen())
    {
        ////////////DRAWING///////////////////////////////////////////////
        window.clear(sf::Color::Black);
        if( openedmap == false )
        {

            for( int i = 0; i < 32; i++ )
            {
                for( int j = 0; j < 32; j++ )
                {
                    if( maps[player->outerpos.y][player->outerpos.x][i][j] )
                        tiles[i][j]->setType(1);
                }
            }
            tiles[player->innerpos.y][player->innerpos.x]->setType(2);
            for( int i = 0; i < 32; i++ )
            {
                for( int j = 0; j < 32; j++ )
                {
                    window.draw(tiles[i][j]->entity);
                }
            }
        }
        else
        {
            for( int i = 0; i < 32; i++ )
            {
                for( int j = 0; j < 32; j++ )
                {
                    window.draw(visitmap->entity[i][j]);
                }
            }
        }
        //////////////////////////////////////////////////////////////////


        ////////////MAIN//LOOP////////////////////////////////////////////
        timer -= dt;
        //////////////////////////////////////////////////////////////////


        ////////////MOVEMENT//////////////////////////////////////////////
        if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) and timer < 0 )
        {
            if( player->innermove(0, -1) == false )
            {
                if( maps[player->outerpos.y][player->outerpos.x][player->innerpos.y][player->innerpos.x] == 1 )
                    player->innermove(0, 1);
                timer = T_0;
            }
            else
                visitmap->visit(player->outerpos.y, player->outerpos.x);
        }
        if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) and timer < 0 )
        {
            if( player->innermove(-1, 0) == false )
            {
                if( maps[player->outerpos.y][player->outerpos.x][player->innerpos.y][player->innerpos.x] == 1 )
                    player->innermove(1, 0);
                timer = T_0;
            }
            else
                visitmap->visit(player->outerpos.y, player->outerpos.x);
        }
        if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) and timer < 0 )
        {
            if( player->innermove(0, 1) == false )
            {
                if( maps[player->outerpos.y][player->outerpos.x][player->innerpos.y][player->innerpos.x] == 1 )
                    player->innermove(0, -1);
                timer = T_0;
            }
            else
                visitmap->visit(player->outerpos.y, player->outerpos.x);
        }
        if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) and timer < 0 )
        {
            if( player->innermove(1, 0) == false )
            {
                if( maps[player->outerpos.y][player->outerpos.x][player->innerpos.y][player->innerpos.x] == 1 )
                    player->innermove(-1, 0);
                timer = T_0;
            }
            else
                visitmap->visit(player->outerpos.y, player->outerpos.x);
        }
        //////////////////////////////////////////////////////////////////


        //////////EVENTS//////////////////////////////////////////////////
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if( sf::Keyboard::isKeyPressed(sf::Keyboard::M) )
                {
                    if( openedmap )
                        openedmap = false;
                    else
                        openedmap = true;
                }
            }
        }
        window.display();
        dt = clock.restart().asSeconds();
        for( int i = 0; i < 32; i++ )
        {
            for( int j = 0; j < 32; j++ )
            {
                tiles[i][j]->setType(0);
            }
        }
        //////////////////////////////////////////////////////////////////
    }

    return 0;
}
