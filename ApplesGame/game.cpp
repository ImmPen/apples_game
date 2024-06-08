#include "game.h"
#include <string>
#include "fonts.cpp"

namespace ApplesGame
{
    void RestartGame(Game& game)
    {
        InitPlayer(game.player, game);

        for (int i = 0; i < NUM_APPLES; i++)
        {
            InitApple(game.apples[i], game);
        }

        for (int i = 0; i < NUM_BLOCKS; i++)
        {
            InitBlock(game.blocks[i], game);
        }

        game.numEatenApples = 0;
        game.bGameOver = false;
        game.pauseTimer = 0;
    }

    void InitGame(Game& game)
    {
        game.playerTexture.loadFromFile(RESOURCES_PATH + "/Player.png");
        game.appleTexture.loadFromFile(RESOURCES_PATH + "/Apple.png");
        game.rockTexture.loadFromFile(RESOURCES_PATH + "/Rock.png");

        game.eatSoundBuffer.loadFromFile(RESOURCES_PATH + "/AppleEat.wav");
        game.deadSoundBuffer.loadFromFile(RESOURCES_PATH + "/Death.wav");
        game.sounds.eatingSound.setBuffer(game.eatSoundBuffer);
        game.sounds.dyingSound.setBuffer(game.deadSoundBuffer);

        game.font.loadFromFile(RESOURCES_PATH + "/arial.ttf");

        RestartGame(game);
    }

    void HandleInput(Game& game)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            game.player.direction = PlayerDirection::Right;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            game.player.direction = PlayerDirection::Up;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            game.player.direction = PlayerDirection::Down;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            game.player.direction = PlayerDirection::Left;
        }
    }

    void UpdateGame(Game& game, float timer)
    {
        if (!game.bGameOver)
        {
            HandleInput(game);
            RotatePlayer(game.player);
            MovePlayer(game.player, timer);
            
            //обработка столкновений с препятствиями
            for (int i = 0; i < NUM_BLOCKS; i++)
            {
                if (IsRectangesCollied(
                    game.player.position, Vector2D{ PLAYER_SIZE, PLAYER_SIZE },
                    game.blocks[i].position, Vector2D{ BLOCK_SIZE, BLOCK_SIZE }))
                {
                    game.bGameOver = true;
                    game.sounds.dyingSound.play();
                }
            }
            //обработка столкновений с яблоками
            for (int i = 0; i < NUM_APPLES; i++)
            {
                if (IsCirclesCollied(game.player.position, PLAYER_SIZE, game.apples[i].position, APPLE_SIZE))
                {
                    game.apples[i].position = GetRandomPositionOnScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
                    game.player.speed += ACCELERATION;
                    ++game.numEatenApples;
                    game.sounds.eatingSound.play();
                }
            }
            //обработка выхода за границы экрана
            if (game.player.position.y < 0 + PLAYER_SIZE / 2.f || game.player.position.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT ||
                game.player.position.x < 0 + PLAYER_SIZE / 2.f || game.player.position.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH)
            {
                game.bGameOver = true;
                game.sounds.dyingSound.play();
            }
        }
        else
        {
            if (game.pauseTimer >= NEW_GAME_DELAY)
                RestartGame(game);
            else
                game.pauseTimer += timer;
        }
    }

    void DrawGame(Game& game, sf::RenderWindow& window)
    {
        DrawPlayer(game.player, window);
        for (int i = 0; i < NUM_APPLES; i++)
        {
            DrawApple(game.apples[i], window);
        }
        for (int i = 0; i < NUM_BLOCKS; i++)
        {
            DrawBlock(game.blocks[i], window);
        }
        DrawFont(game.font, game.numEatenApples, game.bGameOver, window);
    }

    void DeinitGame()
    {
        return;
    }

}
