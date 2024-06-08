#include "player.h"
#include "constants.h"
#include "game.h"

namespace ApplesGame
{
    void InitPlayer(Player& player, const Game& game)
    {
        player.position = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f };
        player.speed = INITIAL_SPEED;
        player.direction = PlayerDirection::Right;
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
            player.position.x += timer * player.speed;
            break;
        case PlayerDirection::Up:
            player.position.y -= timer * player.speed;
            break;
        case PlayerDirection::Down:
            player.position.y += timer * player.speed;
            break;
        case PlayerDirection::Left:
            player.position.x -= timer * player.speed;
            break;
        }
    }
}
