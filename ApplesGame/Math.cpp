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

    bool IsRectangesCollied(Position2D rect1Position, Vector2Df rect1Size, Position2D rect2Position, Vector2Df rect2Size)
    {
        float dx = (float)fabs(rect1Position.x - rect2Position.x);
        float dy = (float)fabs(rect1Position.y - rect2Position.y);
        return 
            (dx <= (rect1Size.x + rect2Size.x) / 2.f &&
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

    bool IsPointInRect(Vector2Df point, Vector2Df rectTL, Vector2Df rectBR)
    {
        if (point.x < rectTL.x || point.x > rectBR.x)
        {
            return false;
        }
        if (point.y < rectTL.y || point.y > rectBR.y)
        {
            return false;
        }
        return true;
    }

    Vector2Df operator+(const Vector2Df& lhs, const Vector2Df& rhs)
    {
        Vector2Df result;
        result.x = lhs.x + rhs.x;
        result.y = lhs.y + rhs.y;
        return result;
    }

    Vector2Df operator-(const Vector2Df& lhs, const Vector2Df& rhs)
    {
        Vector2Df result;
        result.x = lhs.x - rhs.x;
        result.y = lhs.y - rhs.y;
        return result;
    }

    float GetVectorLenght(Vector2Df& vec)
    {
        return sqrtf(vec.x * vec.x + vec.y * vec.y);
    }

    bool operator==(const Vector2Di& lhs, const Vector2Di& rhs)
    {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }

    bool IsShapesCollide(const Rectangle& rect1, const Rectangle& rect2)
    {
        return IsRectangesCollied(
            rect1.position, rect1.size,
            rect2.position, rect2.size);
    }

    bool IsShapesCollide(const Circle& cir1, const Circle& cir2)
    {
        return IsCirclesCollied(
            cir1.position, cir1.radius,
            cir2.position, cir2.radius);
    }

    bool IsShapesCollide(const Circle& cir, const Rectangle& rect)
    {
        return IsRectangesCollied(
            cir.position, { cir.radius, cir.radius },
            rect.position, rect.size);
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

    std::string GetRandomName()
    {
        std::string result = "";
        int name_length = 3;
        for (int i = 0; i < name_length; i++)
        {
            char sym = rand() % 26 + 65;
            result += sym;
        }
        return result;
    }

    sf::Vector2f GetItemOrigin(const sf::Sprite& sprite, const Vector2Df& relativePosition)
    {
        const sf::Vector2u textureSize = sprite.getTexture()->getSize();
        return { relativePosition.x * textureSize.x, relativePosition.y * textureSize.y };
    }

    sf::Vector2f GetItemOrigin(const sf::Text& text, const sf::Vector2f& relativePosition)
    {
        sf::FloatRect textSize = text.getLocalBounds();
        return {
            (textSize.left + textSize.width) * relativePosition.x,
            (textSize.top + textSize.height) * relativePosition.y,
        };
    }

    sf::Vector2f OurVectorToSf(const Vector2Df& v)
    {
        return sf::Vector2f(v.x, v.y);
    }

    sf::Vector2f GetSpriteScale(const sf::Sprite& sprite, const Vector2Df& desiredSize)
    {
        const sf::Vector2u textureSize = sprite.getTexture()->getSize();
        const sf::Vector2f spriteScale = { desiredSize.x / textureSize.x, desiredSize.y / textureSize.y };
        return spriteScale;
    }

    void DrawItemsList(sf::RenderWindow& window, const std::vector<sf::Text*>& items, float spacing, Orientation orientation, Alignment alignment, const sf::Vector2f& position, const sf::Vector2f& origin)
    {
        sf::FloatRect totalRect;
        // Calculate total height/width of all texts
        for (auto it = items.begin(); it != items.end(); ++it)
        {
            sf::FloatRect itemRect = (*it)->getGlobalBounds();

            if (orientation == Orientation::Horizontal)
            {
                totalRect.width += itemRect.width + (it != items.end() - 1 ? spacing : 0.f);
                totalRect.height = std::max(totalRect.height, itemRect.height);
            }
            else
            {
                totalRect.width = std::max(totalRect.width, itemRect.width);
                totalRect.height += itemRect.height + (it != items.end() - 1 ? spacing : 0.f);
            }
        }

        totalRect.left = position.x - origin.x * totalRect.width;
        totalRect.top = position.y - origin.y * totalRect.height;
        sf::Vector2f currentPos = { totalRect.left, totalRect.top };

        for (auto it = items.begin(); it != items.end(); ++it)
        {
            sf::FloatRect itemRect = (*it)->getGlobalBounds();
            sf::Vector2f itemOrigin;

            if (orientation == Orientation::Horizontal)
            {
                itemOrigin.y = alignment == Alignment::Min ? 0.f : alignment == Alignment::Middle ? 0.5f : 1.f;
                itemOrigin.x = 0.f;
                currentPos.y = totalRect.top + itemOrigin.y * totalRect.height;
            }
            else
            {
                itemOrigin.y = 0.f;
                itemOrigin.x = alignment == Alignment::Min ? 0.f : alignment == Alignment::Middle ? 0.5f : 1.f;
                currentPos.x = totalRect.left + itemOrigin.x * totalRect.width;
            }

            (*it)->setOrigin(GetItemOrigin(**it, itemOrigin));
            (*it)->setPosition(currentPos);
            window.draw(**it);

            if (orientation == Orientation::Horizontal)
            {
                currentPos.x += itemRect.width + spacing;
            }
            else
            {
                currentPos.y += itemRect.height + spacing;
            }
        }
    }
}
