#pragma once
#include "Math.h"
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
    struct Rock
    {
        Position2D position;
        sf::Sprite sprite;
    };

    struct Game;
    void InitBlock(Rock& block, const Game& game);
    void DrawBlock(Rock& block, sf::RenderWindow& window);
    Rectangle GetCollider(const Rock& block);
    void SetPosition(Rock& block, Position2D position);
}
