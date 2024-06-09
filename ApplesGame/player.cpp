#include "player.h"
#include "constants.h"
#include "game.h"

namespace ApplesGame
{
    void InitPlayer(Player& player, const Game& game)
    {
        player.sprite.setRotation(0.f);
        player.sprite.setTexture(game.playerTexture);
        SetSpriteScale(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
        SetSpriteRelativeOrigin(player.sprite, 0.5, 0.5);
    }
    
    void DrawPlayer(Player& player, sf::RenderWindow& window)
    {
        player.sprite.setPosition(player.position.x, player.position.y);
        window.draw(player.sprite);
    }

    void RotatePlayer(Player& player)
    {
        switch (player.direction)
        {
        case PlayerDirection::Right:
            player.sprite.setRotation(0);
            SetSpriteScale(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
            break;
        case PlayerDirection::Up:
            player.sprite.setRotation(-90);
            SetSpriteScale(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
            break;
        case PlayerDirection::Down:
            player.sprite.setRotation(90);
            SetSpriteScale(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
            break;
        case PlayerDirection::Left:
            player.sprite.setRotation(0);
            SetSpriteScale(player.sprite, -PLAYER_SIZE, PLAYER_SIZE);
            break;
        }
    }

    void MovePlayer(Player& player, float timer)
    {
        switch (player.direction)
        {
        case PlayerDirection::Right:
            SetPlayerPosition(player, { GetPosition(player).x + timer * GetMovementSpeed(player), GetPosition(player).y });
            break;
        case PlayerDirection::Up:
            SetPlayerPosition(player, { GetPosition(player).x, GetPosition(player).y - timer * GetMovementSpeed(player) });
            break;
        case PlayerDirection::Down:
            SetPlayerPosition(player, { GetPosition(player).x, GetPosition(player).y + timer * GetMovementSpeed(player) });
            break;
        case PlayerDirection::Left:
            SetPlayerPosition(player, { GetPosition(player).x - timer * GetMovementSpeed(player), GetPosition(player).y });
            break;
        }
    }

    Circle GetCollider(const Player& player)
    {
        Circle pl;
        pl.position = player.position;
        pl.radius = PLAYER_SIZE;
        return pl;
    }

    float GetMovementSpeed(const Player& player)
    {
        return player.speed;
    }

    void SetMovementSpeed(Player& player, float speed)
    {
        player.speed = speed;
    }

    void SetPlayerDirection(Player& player, PlayerDirection direction)
    {
        player.direction = direction;
    }

    void SetPlayerPosition(Player& player, Position2D position)
    {
        player.position = position;
    }

    Position2D GetPosition(const Player& player)
    {
        return player.position;
    }


}
