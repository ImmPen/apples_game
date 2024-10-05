#include "player.h"
#include "GameSettings.h"
#include "game.h"
#include "apple.h"


namespace ApplesGame
{
    void InitPlayer(Player& player, sf::Texture& playerTexture)
    {
        player.sprite.setRotation(0.f);
        player.sprite.setTexture(playerTexture);
        SetSpriteScale(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
        SetSpriteRelativeOrigin(player.sprite, 0.5, 0.5);
    }
    
    void DrawPlayer(Player& player, sf::RenderWindow& window)
    {
        player.sprite.setPosition(OurVectorToSf(player.position));

        const sf::Vector2f spriteScale = (GetSpriteScale(player.sprite, { PLAYER_SIZE, PLAYER_SIZE }));

        switch (player.direction)
        {
        case PlayerDirection::Up:
        {
            player.sprite.setScale(spriteScale.x, spriteScale.y);
            player.sprite.setRotation(-90.f);
            break;
        }
        case PlayerDirection::Right:
        {
            player.sprite.setScale(spriteScale.x, spriteScale.y);
            player.sprite.setRotation(0.f);
            break;
        }
        case PlayerDirection::Down:
        {
            player.sprite.setScale(spriteScale.x, spriteScale.y);
            player.sprite.setRotation(90.f);
            break;
        }
        case PlayerDirection::Left:
        {
            player.sprite.setScale(-spriteScale.x, spriteScale.y);
            player.sprite.setRotation(0.f);
            break;
        }
        }

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

    bool PlayerEatsApple(Player& player, Apple& apple, AppleGrid& grid, int gameMode)
    {
        if (!apple.isEaten)
        {
            RemoveAppleFromGrid(apple, grid);
            if (gameMode & 1)
            {
                SetMovementSpeed(player, GetMovementSpeed(player) + ACCELERATION);
            }
            if ((gameMode >> 1) & 1)
            {
                SetPosition(apple, GetRandomPositionOnScreen(SCREEN_WIDTH, SCREEN_HEIGHT));
                AddAppleToGrid(apple, grid);
            }
            else
            {
                apple.isEaten = true;
            }
            return true;
        }
        return false;
    }

    bool HasPlayerCollisionWithScreenBorder(const Player& player)
    {
        return !IsPointInRect(player.position, { 0.f, 0.f }, { (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT });
    }
    
}
