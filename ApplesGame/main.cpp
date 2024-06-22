#include <SFML/Graphics.hpp>
#include <string>
#include "Math.h"
#include "game.h"

int main()
{
    using namespace ApplesGame;
    int seed = (int)time(nullptr);
    srand(seed);
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples Game");
    
    Game game;
    InitGame(game);

    sf::Clock clock;
    clock.restart();

    while (window.isOpen())
    {
        sf::sleep(sf::milliseconds(15));
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }
        
        float timer = clock.getElapsedTime().asSeconds();
        clock.restart();

        UpdateGame(game, timer);

        window.clear();
        DrawGame(game, window);
        window.display();
    }

    DeinitGame(game);

	return 0;
}