#include <SFML/Graphics.hpp>
#include "constants.h"
#include "fonts.h"
#include "game.h"

namespace ApplesGame
{
    void DrawChoosingScreen(sf::RenderWindow& window, sf::Font font, int gameMode)
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

    void DrawPlayingScreen(sf::RenderWindow& window, sf::Font font, int score)
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

    void DrawLoseScreen(sf::RenderWindow& window, sf::Font font, int score, const RecordsTable& table)
    {
        sf::Text gameOverText;
        sf::Text scoreText;
        sf::Text recordsTableText;
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
        recordsTableText.setFont(font);
        
        for (int i = 0; i < NUM_NAMES_IN_TABLE; i++)
        {
            std::string records = table.entry[i].name + "\t" + std::to_string(table.entry[i].score) + "\n";
            recordsTableText.setString(records);
            recordsTableText.setCharacterSize(24);
            recordsTableText.setFillColor(sf::Color::White);
            if (table.entry[i].name == "YOU")
            {
                recordsTableText.setFillColor(sf::Color::Red);
            }
            recordsTableText.setPosition(0, 24 * i);
            window.draw(recordsTableText);
        }
        
        window.draw(gameOverText);
        window.draw(scoreText);
    }

    void DrawPauseScreen(sf::RenderWindow& window, sf::Font font)
    {
        sf::Text pauseText;
        pauseText.setFont(font);
        pauseText.setString(
            "\tPress Esc to exit\n"
            "Press Space to continue");
        pauseText.setCharacterSize(24);
        pauseText.setOrigin(24 * 5, 24 * 1.5);
        pauseText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
        window.draw(pauseText);
    }

    void DrawFont(sf::RenderWindow& window, const Game& game)
    {
        GameState state = GetGameState(game);
        switch (state)
        {
        case GameState::Choosing:
            DrawChoosingScreen(window, game.font, game.gameMode);
            break;
        case GameState::Playing:
            DrawPlayingScreen(window, game.font, game.numEatenApples);
            break;
        case GameState::GameOver:
            DrawLoseScreen(window, game.font, game.numEatenApples, game.recordsTable);
            break;
        case GameState::Pause:
            DrawPauseScreen(window, game.font);
            break;
        default:
            break;
        }
    }
}