#include <SFML/Graphics.hpp>
#include "constants.h"
#include "fonts.h"


namespace ApplesGame
{
    void DrawFont(sf::Font font, int score, int currentGameState, int gameMode, sf::RenderWindow& window)
    {
        if (currentGameState & (1 << 1))
        {
            sf::Text chooseText;
            sf::Text chosenGameModeText;

            chooseText.setFont(font);
            chooseText.setString("\t\t\t\tChoose your game mode. Press Space to start\n" 
                "\t\tUse Up Arrow for Endless mode, Down Arrow fo Finite Mode\n" 
                "Use Left Arrow for Acceleration mode, Right Arrow fo non - acceleration Mode");
            chooseText.setCharacterSize(24);
            chooseText.setOrigin(24 * 15, 24 * 1.5);
            chooseText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

            chosenGameModeText.setFont(font);
            chosenGameModeText.setString(std::string("Your Game Mode: ") + //тут нужно приведение типа, т.к. конкатенация раюотает только со стрингом, а "такая строка" имеет тип массива символов 
                ((gameMode & (1 << 1)) ? "Endless " : "Finfite ") +
                (gameMode & 1 ? "With Acceleration" : "Without Acceleration"));
            chosenGameModeText.setCharacterSize(24);
            chosenGameModeText.setOrigin(24 * 10, 24 * 0.5);
            chosenGameModeText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 24 * 3);

            window.draw(chooseText);
            window.draw(chosenGameModeText);
        }
        else if (currentGameState & 1)
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
        }
        else
        {
            sf::Text gameOverText;
            sf::Text scoreText;
            gameOverText.setFont(font);
            gameOverText.setString("Game Over!");
            gameOverText.setCharacterSize(60);
            gameOverText.setOrigin(60 * 2, 60 / 2);
            gameOverText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
            scoreText.setFont(font);
            scoreText.setString("Your score: " + std::to_string(score));
            scoreText.setCharacterSize(24);
            scoreText.setOrigin(24 * 2, 24 / 2);
            scoreText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 60);
            window.draw(gameOverText);
            window.draw(scoreText);
        }

    }
}