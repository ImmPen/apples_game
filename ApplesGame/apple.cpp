#include "apple.h"
#include "game.h"
#include <assert.h>

namespace ApplesGame
{
    void InitApple(Apple& apple, sf::Texture& appleTexture)
    {
        apple.sprite.setTexture(appleTexture);
        apple.isEaten = false;
        SetSpriteScale(apple.sprite, APPLE_SIZE, APPLE_SIZE);
        SetSpriteRelativeOrigin(apple.sprite, 0.5, 0.5);
    }

    void DrawApple(Apple& apple, sf::RenderWindow& window)
    {
        apple.sprite.setPosition(apple.position.x, apple.position.y);
        if (!apple.isEaten)
        {
            window.draw(apple.sprite);
        }
        
    }

    Circle GetCollider(const Apple& apple)
    {
        Circle cir;
        cir.position = apple.position;
        cir.radius = APPLE_SIZE;
        return cir;
    }

    void SetPosition(Apple& apple, Position2D position)
    {
        apple.position = position;
    }

    void ResetAppleState(Apple& apple)
    {
        apple.position.x = (float)(rand() % SCREEN_WIDTH);
        apple.position.y = (float)(rand() % SCREEN_HEIGHT);
        apple.isEaten = false;
    }

    void MarkAppleAsEaten(Apple& apple)
    {
        apple.isEaten = true;
    }

    void ClearAppleGrid(AppleGrid& grid)
    {
        grid.appleCells.clear();
        grid.cells.clear();
    }

    void AddAppleToGrid(Apple& apple, AppleGrid& grid)
    {
        RemoveAppleFromGrid(apple, grid);
        Vector2Df appleCornerTL = apple.position + Vector2Df{ -APPLE_SIZE / 2, -APPLE_SIZE / 2 };
        Vector2Df appleCornerBR = apple.position + Vector2Df{ APPLE_SIZE / 2, APPLE_SIZE / 2 };

        const float cellSizeX = (float)SCREEN_WIDTH / APPLES_GRID_CELLS_H;
        const float cellSizeY = (float)SCREEN_WIDTH / APPLES_GRID_CELLS_V;
        int minCellX = std::max((int)(appleCornerTL.x / cellSizeX), 0);
        int maxCellX = std::min((int)(appleCornerBR.x / cellSizeX), (int)APPLES_GRID_CELLS_H - 1);
        int minCellY = std::max((int)(appleCornerTL.y / cellSizeY), 0);
        int maxCellY = std::min((int)(appleCornerBR.y / cellSizeY), (int)APPLES_GRID_CELLS_V - 1);

        for (int cellX = minCellX; cellX <= maxCellX; ++cellX)
        {
            for (int cellY = minCellY; cellY <= maxCellY; ++cellY)
            {
                grid.cells[{cellX, cellY}].insert(&apple);
                grid.appleCells.insert({ &apple, {cellX, cellY} });
            }
        }

    }

    void RemoveAppleFromGrid(Apple& apple, AppleGrid& grid)
    {
        auto range = grid.appleCells.equal_range(&apple);
        for (auto it = range.first; it != range.second; it++)
        {
            grid.cells[it->second].erase(&apple);
        }
        grid.appleCells.erase(range.first, range.second);
    }

    bool FindPlayerCollisionWithApples(const Vector2Df& playerPosition, const AppleGrid& grid, AppleSet& result)
    {
        Vector2Df playerCornerTL = playerPosition + Vector2Df{ -PLAYER_SIZE / 2, -PLAYER_SIZE / 2 };
        Vector2Df playerCornerBR = playerPosition + Vector2Df{ PLAYER_SIZE / 2, PLAYER_SIZE / 2 };

        const float cellSizeX = (float)SCREEN_WIDTH / APPLES_GRID_CELLS_H;
        const float cellSizeY = (float)SCREEN_WIDTH / APPLES_GRID_CELLS_V;
        int minCellX = std::max((int)(playerCornerTL.x / cellSizeX), 0);
        int maxCellX = std::min((int)(playerCornerBR.x / cellSizeX), (int)APPLES_GRID_CELLS_H - 1);
        int minCellY = std::max((int)(playerCornerTL.y / cellSizeY), 0);
        int maxCellY = std::min((int)(playerCornerBR.y / cellSizeY), (int)APPLES_GRID_CELLS_V - 1);

        for (int cellX = minCellX; cellX <= maxCellX; ++cellX)
        {
            for (int cellY = minCellY; cellY <= maxCellY; ++cellY)
            {
                const auto it = grid.cells.find({ cellX, cellY });
                if (it == grid.cells.cend())
                {
                    continue;
                }

                for (Apple* apple : it->second)
                {
                    Vector2Df distance = playerPosition - apple->position;
                    if (GetVectorLenght(distance) < (PLAYER_SIZE + APPLE_SIZE) / 2)
                    {   
                        result.insert(apple);
                    }
                }
            }
        }

        return result.size() > 0;
    }
}
