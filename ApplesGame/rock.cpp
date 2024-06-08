#include "rock.h"
#include "game.h"

namespace ApplesGame
{
    void InitBlock(Rock& block, const Game& game)
    {
        block.position = GetRandomPositionOnScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
        block.sprite.setTexture(game.rockTexture);
        SetSpriteScale(block.sprite, BLOCK_SIZE, BLOCK_SIZE);
        SetSpriteRelativeOrigin(block.sprite, 0.5, 0.5);
    }

    void DrawBlock(Rock& block, sf::RenderWindow& window)
    {
        block.sprite.setPosition(block.position.x, block.position.y);
        window.draw(block.sprite);
    }
}
