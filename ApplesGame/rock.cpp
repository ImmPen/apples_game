#include "rock.h"
#include "game.h"

namespace ApplesGame
{
    void InitBlock(Rock& block, sf::Texture& blockTexture)
    {
        block.sprite.setTexture(blockTexture);
        SetSpriteScale(block.sprite, BLOCK_SIZE, BLOCK_SIZE);
        SetSpriteRelativeOrigin(block.sprite, 0.5, 0.5);
    }

    void DrawBlock(Rock& block, sf::RenderWindow& window)
    {
        block.sprite.setPosition(block.position.x, block.position.y);
        window.draw(block.sprite);
    }

    void ResetBlockPosition(Rock& block)
    {
        block.position.x = (float)(rand() % SCREEN_WIDTH);
        block.position.y = (float)(rand() % SCREEN_HEIGHT);
    }

    Rectangle GetCollider(const Rock& block)
    {
        Rectangle rect;
        rect.position = block.position;
        rect.size = { BLOCK_SIZE, BLOCK_SIZE };
        return rect;
    }

    void SetPosition(Rock& block, Position2D position)
    {
        block.position = position;
    }
}
