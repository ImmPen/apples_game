#pragma once
#include "Math.h"
#include "player.h"
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
    struct Apple
    {
        Position2D position;
        sf::Sprite sprite;
        bool eaten = false;
        struct AppleGridCell* gridCells[4] = {};
        int numGridIntersects = 0;
    };

    struct AppleGridCell
    {
        Apple* apples[MAX_APPLES_IN_CELL] = {};
        int numApplesInGrid = 0;
    };

    struct AppleGrid
    {
        AppleGridCell cells[APPLES_GRID_CELLS_H][APPLES_GRID_CELLS_V];
    };

    struct Game;
    void InitApple(Apple& apple, const Game& game);
    void DrawApple(Apple& apple, sf::RenderWindow& window);
    Circle GetCollider(const Apple& apple);
    void SetPosition(Apple& apple, Position2D position);

    void ClearAppleGrid(AppleGrid& grid);
    void AddAppleToGrid(Apple& apple, AppleGrid& grid);
    void RemoveAppleFromGrid(Apple& apple, AppleGrid& grid);
    std::vector<Apple*> PlayerMayCollideApple(Player& player, std::vector<Apple>, AppleGrid& grid);
}
