#pragma once
#include "constants.h"

namespace sf
{
    class Sprite;
}

namespace ApplesGame
{
    struct Vector2D
    {
        float x;
        float y;
    };

    typedef Vector2D Position2D;

    struct Rectangle
    {
        Position2D position;
        Vector2D size;
    };

    struct Circle
    {
        Position2D position;
        float radius;
    };

    Position2D GetRandomPositionOnScreen(float screenWidth, float screenHeight);

    bool IsRectangesCollied(
        Position2D rect1Position, Vector2D rect1Size,
        Position2D rect2Position, Vector2D rect2Size
    );

    bool IsCirclesCollied(
        Position2D rectPosition, float rectSize,
        Position2D CirclePosition, float CircleRadius
    );

    bool IsShapesCollide(const Rectangle& rect1, const Rectangle& rect2);
    bool IsShapesCollide(const Circle& cir, const Rectangle& rect);
    bool IsShapesCollide(const Circle& cir1, const Circle& cir2);

    void SetSpriteScale(sf::Sprite& sprite, float desiredWidth, float desiredHeight);
    void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY);
}
