#pragma once
#include "GameSettings.h"
#include <SFML/Graphics.hpp>

namespace sf
{
    class Sprite;
}

namespace ApplesGame
{
    struct Vector2Df
    {
        float x;
        float y;
    };
    struct Vector2Di
    {
        int x;
        int y;
    };
    typedef Vector2Df Position2D;

    struct Rectangle
    {
        Position2D position;
        Vector2Df size;
    };

    struct Circle
    {
        Position2D position;
        float radius;
    };

    Position2D GetRandomPositionOnScreen(float screenWidth, float screenHeight);

    bool IsRectangesCollied(
        Position2D rect1Position, Vector2Df rect1Size,
        Position2D rect2Position, Vector2Df rect2Size
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

    std::string GetRandomName();

    // Helper method for organizing text items
	enum class Orientation
	{
		Horizontal,
		Vertical
	};

	enum class Alignment
	{
		Min, // Left or Top
		Middle,
		Max // Right or Bottom
	};

    sf::Vector2f OurVectorToSf(const Vector2Df& v);
    sf::Vector2f GetSpriteScale(const sf::Sprite& sprite, const Vector2Df& desiredSize);
    sf::Vector2f GetItemOrigin(const sf::Sprite& sprite, const Vector2Df& relativePosition);
	sf::Vector2f GetItemOrigin(const sf::Text& text, const sf::Vector2f& relativePosition);

    void DrawItemsList(sf::RenderWindow& window, const std::vector<sf::Text*>& items, float spacing, Orientation orientation, Alignment alignment, const sf::Vector2f& position, const sf::Vector2f& origin);

    bool IsPointInRect(Vector2Df point, Vector2Df rectTL, Vector2Df rectBR);

    Vector2Df operator+(const Vector2Df& lhs, const Vector2Df& rhs);
    Vector2Df operator-(const Vector2Df& lhs, const Vector2Df& rhs);
    float GetVectorLenght(Vector2Df& vec);
    bool operator==(const Vector2Di& lhs, const Vector2Di& rhs);
}

template<>
struct std::hash<ApplesGame::Vector2Di>
{
    std::size_t operator()(const ApplesGame::Vector2Di& v) const noexcept
    {
        return std::hash<int>()(v.x) ^ (std::hash<int>()(v.y) << 1);
    }
};