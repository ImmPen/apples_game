#include "apple.h"
#include "game.h"

namespace ApplesGame
{
    void InitApple(Apple& apple, const Game& game)
    {
        apple.sprite.setTexture(game.appleTexture);
        SetSpriteScale(apple.sprite, APPLE_SIZE, APPLE_SIZE);
        SetSpriteRelativeOrigin(apple.sprite, 0.5, 0.5);
    }

    void DrawApple(Apple& apple, sf::RenderWindow& window)
    {
        apple.sprite.setPosition(apple.position.x, apple.position.y);
        window.draw(apple.sprite);
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
}
