#include <cstdlib>
#include "Math.h"
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
    Position2D GetRandomPositionOnScreen(float screenWidth, float screenHeight)
    {
        Position2D result;
        result.x = rand() / ((float)(RAND_MAX)) * screenWidth;
        result.y = rand() / ((float)(RAND_MAX)) * screenHeight;
        return result;
    }

    bool IsRectangesCollied(Position2D rect1Position, Vector2D rect1Size, Position2D rect2Position, Vector2D rect2Size)
    {
        float dx = (float)fabs(rect1Position.x - rect2Position.x);
        float dy = (float)fabs(rect1Position.y - rect2Position.y);
        return (dx <= (rect1Size.x + rect2Size.x) / 2.f &&
            dy <= (rect1Size.y + rect2Size.y) / 2.f);
    }

    bool IsCirclesCollied(Position2D rectPosition, float rectSize, Position2D CirclePosition, float CircleRadius)
    {
        float squareDistance =
            (rectPosition.x - CirclePosition.x) * (rectPosition.x - CirclePosition.x) +
            (rectPosition.y - CirclePosition.y) * (rectPosition.y - CirclePosition.y);
        float squareRadius = (CircleRadius + rectSize) * (CircleRadius + rectSize) / 4;
        return squareDistance <= squareRadius;
    }
    void SetSpriteScale(sf::Sprite& sprite, float desiredWidth, float desiredHeight)
    {
        sf::FloatRect spriteRect = sprite.getLocalBounds();
        sf::Vector2f scale = { desiredWidth / spriteRect.width, desiredHeight / spriteRect.height };
        sprite.setScale(scale);

    }
    void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY)
    {
        sf::FloatRect spriteRect = sprite.getLocalBounds();
        sprite.setOrigin(spriteRect.width * originX, spriteRect.height * originY);
    }
}
