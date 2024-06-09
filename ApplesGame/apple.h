#pragma once
#include "Math.h"
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
    struct Apple
    {
        Position2D position;
        sf::Sprite sprite;
    };

    struct Game;
    void InitApple(Apple& apple, const Game& game);
    void DrawApple(Apple& apple, sf::RenderWindow& window);
    Circle GetCollider(const Apple& apple);
    void SetPosition(Apple& apple, Position2D position);
}
