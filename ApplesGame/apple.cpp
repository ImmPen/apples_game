#include "apple.h"
#include "game.h"

namespace ApplesGame
{
    void InitApple(Apple& apple, const Game& game)
    {
        apple.position = GetRandomPositionOnScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
        apple.sprite.setTexture(game.appleTexture);
        SetSpriteScale(apple.sprite, APPLE_SIZE, APPLE_SIZE);
        SetSpriteRelativeOrigin(apple.sprite, 0.5, 0.5);
    }

    void DrawApple(Apple& apple, sf::RenderWindow& window)
    {
        apple.sprite.setPosition(apple.position.x, apple.position.y);
        window.draw(apple.sprite);
    }
}
