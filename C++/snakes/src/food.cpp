#include "food.h"
food::food(sf::RenderWindow &window) : window(window)
{
    foodx = 0;
    foody = 0;
}

void food::creatfood(snake &s)
{
    while (1)
    {
        foodx = rand() % (1600 / nodewidth);
        foody = rand() % (1200 / nodewidth);
        int i;
        for (i = 0; i < s.length; i++)
        {
            if (s.snakes[i].x == foodx && s.snakes[i].y == foody)
                break;
        }
        if (i < s.length)
            continue;
        else
            break;
    }
}

void food::Draw()
{
    int left = foodx * nodewidth;
    int top = foody * nodewidth;
    sf::RectangleShape foods(sf::Vector2f(20, 20));
    foods.setFillColor(sf::Color::Red);
    foods.setPosition(sf::Vector2f(left, top));
    window.draw(foods);
    window.display();
}