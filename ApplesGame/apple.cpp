#include "apple.h"
#include "game.h"

namespace ApplesGame
{
    void InitApple(Apple& apple, const Game& game)
    {
        apple.sprite.setTexture(game.appleTexture);
        apple.eaten = false;
        SetSpriteScale(apple.sprite, APPLE_SIZE, APPLE_SIZE);
        SetSpriteRelativeOrigin(apple.sprite, 0.5, 0.5);
    }

    void DrawApple(Apple& apple, sf::RenderWindow& window)
    {
        apple.sprite.setPosition(apple.position.x, apple.position.y);
        if (!apple.eaten)
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

    void ClearAppleGrid(AppleGrid& grid)
    {
        for (int i = 0; i < APPLES_GRID_CELLS_H; i++)
        {
            for (int j = 0; j < APPLES_GRID_CELLS_V; j++)
            {
                for (int k = 0; k < grid.cells[i][j].numApplesInGrid; k++)
                {
                    if (grid.cells[i][j].apples[k])
                    {
                        for (int c = 0; c < grid.cells[i][j].apples[k]->numGridIntersects; c++)
                        {
                            grid.cells[i][j].apples[k]->gridCells[c] = nullptr;
                        }
                        grid.cells[i][j].apples[k]->numGridIntersects = 0;
                    }
                    grid.cells[i][j].numApplesInGrid = 0;
                    grid.cells[i][j].apples[k] = nullptr;
                }
            }
        }
    }

    void AddAppleToGrid(Apple& apple, AppleGrid& grid)
    {
        try 
        {
            Vector2D top_left = { apple.position.x - APPLE_SIZE / 2, apple.position.y - APPLE_SIZE / 2 };
            Vector2D gridCellTopLeft =
            { std::max((int)top_left.x / GRID_CELL_WITDH, 0),
            std::max((int)top_left.y / GRID_CELL_HEIGHT, 0) };
            Vector2D gridCellBotRight =
            { std::min((int)(top_left.x + APPLE_SIZE) / GRID_CELL_WITDH, APPLES_GRID_CELLS_H - 1),
            std::min((int)(top_left.y + APPLE_SIZE) / GRID_CELL_HEIGHT, APPLES_GRID_CELLS_V - 1) };
            for (int i = gridCellTopLeft.x; i <= gridCellBotRight.x; i++)
            {
                for (int j = gridCellTopLeft.y; j <= gridCellBotRight.y; j++)
                {
                    grid.cells[i][j].apples[grid.cells[i][j].numApplesInGrid++] = &apple;
                    apple.gridCells[apple.numGridIntersects++] = &grid.cells[i][j];
                }
            }
        }
        catch(std::runtime_error err)
        {
            throw(err.what());
            SetPosition(apple, GetRandomPositionOnScreen(SCREEN_WIDTH, SCREEN_HEIGHT));
            AddAppleToGrid(apple, grid);
        }
    }

    void RemoveAppleFromGrid(Apple& apple, AppleGrid& grid)
    {
        for (int i = 0; i < apple.numGridIntersects; i++)
        {
            auto cell = apple.gridCells[i];
            for (int i = 0; i < cell->numApplesInGrid; i++)
            {
                if (cell->apples[i] == &apple)
                {
                    cell->apples[i] = cell->apples[cell->numApplesInGrid - 1];
                    cell->apples[cell->numApplesInGrid - 1] = nullptr;
                    cell->numApplesInGrid--;
                }
            }
            apple.gridCells[i] = nullptr;
        }
        apple.numGridIntersects = 0;
    }

    Apple** PlayerMayCollideApple(Player& player, Apple* apple, AppleGrid& grid, int& numApples)
    {
        Apple* result[(4 * MAX_APPLES_IN_CELL)];
        Vector2D top_left = { player.position.x - PLAYER_SIZE / 2, player.position.y - PLAYER_SIZE / 2 };
        Vector2D gridCellTopLeft =
        { std::max((int)top_left.x / GRID_CELL_WITDH, 0),
        std::max((int)top_left.y / GRID_CELL_HEIGHT, 0) };
        Vector2D gridCellBotRight =
        { std::min((int)(top_left.x + APPLE_SIZE) / GRID_CELL_WITDH, APPLES_GRID_CELLS_H - 1),
        std::min((int)(top_left.y + APPLE_SIZE) / GRID_CELL_HEIGHT, APPLES_GRID_CELLS_V - 1) };
        for (int i = gridCellTopLeft.x; i <= gridCellBotRight.x; i++)
        {
            for (int j = gridCellTopLeft.y; j <= gridCellBotRight.y; j++)
            {
                AppleGridCell cell = grid.cells[i][j];
                for (int c = 0; c < cell.numApplesInGrid; c++)
                {
                    result[numApples++] = cell.apples[c];
                }
            }
        }
        return result;
    }
}
