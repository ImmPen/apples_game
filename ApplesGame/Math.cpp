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

    bool IsCirclesCollied(Position2D cir1Position, float cir1Radius, Position2D cir2Position, float cir2Radius)
    {
        float squareDistance =
            (cir1Position.x - cir2Position.x) * (cir1Position.x - cir2Position.x) +
            (cir1Position.y - cir2Position.y) * (cir1Position.y - cir2Position.y);
        float squareRadius = (cir2Radius + cir1Radius) * (cir2Radius + cir1Radius) / 4;
        return squareDistance <= squareRadius;
    }

    bool IsShapesCollide(Rectangle& rect1, Rectangle& rect2)
    {
        return IsRectangesCollied(
            rect1.position, rect1.size,
            rect2.position, rect2.size);
    }

    bool IsShapesCollide(Circle& cir1, Circle& cir2)
    {
        return IsCirclesCollied(
            cir1.position, cir1.radius,
            cir2.position, cir2.radius);
    }

    bool IsShapesCollide(Circle& cir, Rectangle& rect)
    {
        float dx = std::min(
            fabs(rect.position.x - cir.position.x),
            fabs(rect.position.x + rect.size.x - cir.position.x));
        float dy = std::min(
            fabs(rect.position.y - cir.position.x),
            fabs(rect.position.y + rect.size.y - cir.position.y));
        return (dx * dx + dy * dy) < (cir.radius * cir.radius);
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
