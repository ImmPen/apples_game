#include <SFML/Graphics.hpp>
#include "constants.h"


namespace ApplesGame
{
    void DrawFont(sf::Font font, int score, bool bGameOver, sf::RenderWindow& window)
    {
        sf::Text scoreText;
        sf::Text helpText;
        scoreText.setFont(font);
        scoreText.setString("Score: " + std::to_string(score));
        scoreText.setCharacterSize(24);

        helpText.setFont(font);
        helpText.setString("Use arrows to switch movement direction");
        helpText.setCharacterSize(24);
        helpText.setPosition(0, 25);

        window.draw(scoreText);
        window.draw(helpText);

        if (bGameOver)
        {
            sf::Text gameOverText;
            gameOverText.setFont(font);
            gameOverText.setString("Game Over!");
            gameOverText.setCharacterSize(60);
            gameOverText.setOrigin(60 * 2, 60 / 2);
            gameOverText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
            window.draw(gameOverText);
        }
    }
}