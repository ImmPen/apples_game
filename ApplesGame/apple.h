#pragma once
#include "Math.h"
#include "player.h"
#include <SFML/Graphics.hpp>
#include <unordered_set>
#include <unordered_map>

namespace ApplesGame
{
    struct Apple
    {
        Position2D position;
        sf::Sprite sprite;
        bool isEaten = false;
    };

    void ResetAppleState(Apple& apple);
    void MarkAppleAsEaten(Apple& apple);

    using AppleSet = std::unordered_set<Apple*>;

    struct AppleGrid
    {
        std::unordered_map<Vector2Di, AppleSet> cells;
        std::unordered_multimap<Apple*, Vector2Di> appleCells;
    };

    struct Game;
    void InitApple(Apple& apple, sf::Texture& appleTexture);
    void DrawApple(Apple& apple, sf::RenderWindow& window);
    Circle GetCollider(const Apple& apple);
    void SetPosition(Apple& apple, Position2D position);

    void ClearAppleGrid(AppleGrid& grid);
    void AddAppleToGrid(Apple& apple, AppleGrid& grid);
    void RemoveAppleFromGrid(Apple& apple, AppleGrid& grid);
    std::vector<Apple*> PlayerMayCollideApple(Player& player, std::vector<Apple>, AppleGrid& grid);
    bool FindPlayerCollisionWithApples(const Vector2Df& playerPosition, const AppleGrid& grid, AppleSet& result);
}
