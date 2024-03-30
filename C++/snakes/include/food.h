#pragma once
#include"snake.h"
class snake;
class food
{
    friend class snake;
public:
    int foodx;
    int foody;
    sf::RenderWindow& window;
    food(sf::RenderWindow& window);
    void creatfood(snake& s);
    void Draw();
};
