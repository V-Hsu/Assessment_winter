#include "snake.h"
#include "food.h"
#include<time.h>
int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(1600, 1200), "test");
    window.clear(sf::Color::White);
    snake s(window);
    food f(window);
    f.creatfood(s);
    while (window.isOpen())
    {
        sf::Event event;
        window.clear(sf::Color::White);
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        f.Draw();
        s.Draw();
        sf::sleep(sf::seconds(0.08));
        s.Control();
        node lastTail=s.Update();
        if(s.snakes[0].x==f.foodx&&s.snakes[0].y==f.foody)
        {
            if(s.length<100)
            {
                s.snakes[s.length]=lastTail;
                s.length++;
            }
            f.creatfood(s);
        }
        if(s.gameOver()==true)
        {
            window.close();
        }
    }

    return 0;
}