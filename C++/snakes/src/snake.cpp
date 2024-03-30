#include "snake.h"

snake::snake(sf::RenderWindow &window) : window(window)
{
    snakes[0] = {5, 7};
    snakes[1] = {4, 7};
    snakes[2] = {3, 7};
    snakes[3] = {2, 7};
    snakes[4] = {1, 7};
    length = 5;
    ed = Right;
}

void snake::Draw()
{
    int left, top;
    for (int i = 0; i < length; i++)
    {
        left = snakes[i].x * nodewidth;
        top = snakes[i].y * nodewidth;
        sf::RectangleShape nodes(sf::Vector2f(20, 20));
        nodes.setFillColor(sf::Color::Blue);
        nodes.setPosition(sf::Vector2f(left, top));
        window.draw(nodes);
        window.display();
    }
}

node snake::Update()
{
    node tail = snakes[length - 1];
    for (int i = length - 1; i > 0; i--)
    {
        snakes[i] = snakes[i - 1];
    }
    node newnode = snakes[0];
    switch (ed)
    {
    case Up:
        newnode.y--;
        break;
    case Down:
        newnode.y++;
        break;
    case Left:
        newnode.x--;
        break;
    case Right:
        newnode.x++;
        break;
    }
    snakes[0] = newnode;
    return tail;
}

void snake::Control()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && ed != Down)
        ed = Up;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && ed != Up)
        ed = Down;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && ed != Right)
        ed = Left;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && ed != Left)
        ed = Right;
}

bool snake::gameOver()
{
    if (snakes[0].x < 0 || snakes[0].x > 1600 / nodewidth)
        return true;
    if (snakes[0].y < 0 || snakes[0].y > 1200 / nodewidth)
        return true;
    for (int i = 1; i < length; i++)
    {
        if (snakes[0].x == snakes[i].x && snakes[0].y == snakes[i].y)
            return true;
    }
    return false;
}