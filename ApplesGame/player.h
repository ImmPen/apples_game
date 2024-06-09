#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "constants.h"

namespace ApplesGame
{
    enum class PlayerDirection
    {
        Right = 0,
        Up,
        Left,
        Down
    };

    struct Player
    {
        Position2D position;
        float speed = INITIAL_SPEED;
        PlayerDirection direction;
        sf::Sprite sprite;
    };

    struct Game;

    void InitPlayer(Player& player, const Game& game);

    void DrawPlayer(Player& player, sf::RenderWindow& window);

    void RotatePlayer(Player& player);

    void MovePlayer(Player& player, float timer);

    Circle GetCollider(const Player& player);

    float GetMovementSpeed(const Player& player);

    void SetMovementSpeed(Player& player, float speed);

    void SetPlayerDirection(Player& player, PlayerDirection direction);

    void SetPlayerPosition(Player& player, Position2D position);

    Position2D GetPosition(const Player& player);

}
