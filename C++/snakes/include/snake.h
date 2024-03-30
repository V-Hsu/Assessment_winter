#pragma once
#include<SFML/Graphics.hpp>
#include"food.h"
#define nodewidth 20

typedef struct
{
    int x;
    int y;
}node;

enum direction
{
    Up,
    Down,
    Left,
    Right
};

class snake
{
    friend class food;
private:
    sf::RenderWindow& window;
    direction ed; 
public:
    node snakes[100];
    int length;
    snake(sf::RenderWindow& window);
    void Draw();
    void Control();
    node Update();
    bool gameOver();
};
