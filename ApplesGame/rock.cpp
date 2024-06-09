#include "rock.h"
#include "game.h"

namespace ApplesGame
{
    void InitBlock(Rock& block, const Game& game)
    {
        block.sprite.setTexture(game.rockTexture);
        SetSpriteScale(block.sprite, BLOCK_SIZE, BLOCK_SIZE);
        SetSpriteRelativeOrigin(block.sprite, 0.5, 0.5);
    }

    void DrawBlock(Rock& block, sf::RenderWindow& window)
    {
        block.sprite.setPosition(block.position.x, block.position.y);
        window.draw(block.sprite);
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
