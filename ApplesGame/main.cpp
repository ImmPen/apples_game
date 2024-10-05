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
    
    Game* game = new Game();
    InitGame(*game);

    sf::Clock clock;
    clock.restart();

    while (window.isOpen())
    {
        sf::sleep(sf::milliseconds(15));
        HandleWindowEvents(*game, window);
        
        float timer = clock.getElapsedTime().asSeconds();
        clock.restart();

        if (UpdateGame(*game, timer))
        {
            window.clear();
            DrawGame(*game, window);
            window.display();
        }
        else
        {
            window.close();
        }
    }
    ShutownGame(*game);
	return 0;
}