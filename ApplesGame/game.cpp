#include "game.h"
#include "fonts.h"
#include <iostream>

namespace ApplesGame
{
    void StartPlayingState(Game& game)
    {
        SetPlayerPosition(game.player, { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 });
        SetPlayerDirection(game.player, PlayerDirection::Right);
        SetMovementSpeed(game.player, INITIAL_SPEED);

        for (int i = 0; i < game.numApples; i++)
        {
            SetPosition(game.apples[i], GetRandomPositionOnScreen(SCREEN_WIDTH, SCREEN_HEIGHT));
        }

        for (int i = 0; i < NUM_BLOCKS; i++)
        {
            SetPosition(game.blocks[i], GetRandomPositionOnScreen(SCREEN_WIDTH, SCREEN_HEIGHT));
        }

        game.numEatenApples = 0;
        game.bGameOver = false;
        game.pauseTimer = 0;
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

    void UpdatePlayingState(Game& game, float timer)
    {
        HandleInput(game);
        RotatePlayer(game.player);
        MovePlayer(game.player, timer);
        
        //обработка столкновений с препятствиями
        for (int i = 0; i < NUM_BLOCKS; i++)
        {
            if (IsShapesCollide(GetCollider(game.player), GetCollider(game.blocks[i])))
            {
                StartGameOverState(game);
            }
        }
        //обработка столкновений с яблоками
        for (int i = 0; i < game.numApples; i++)
        {
            if (IsShapesCollide(GetCollider(game.player), GetCollider(game.apples[i])))
            {
                SetPosition(game.apples[i], GetRandomPositionOnScreen(SCREEN_WIDTH, SCREEN_HEIGHT));
                SetMovementSpeed(game.player, GetMovementSpeed(game.player) + ACCELERATION);
                ++game.numEatenApples;
                game.sounds.eatingSound.play();
            }
        }
        //обработка выхода за границы экрана
        if (!IsShapesCollide(GetCollider(game.player), game.backgroungRect))
        {
            Circle collider = GetCollider(game.player);
            game.backgroungRect;
            bool fl = IsShapesCollide(collider, game.backgroungRect);
            StartGameOverState(game);
        }
    }

    void StartGameOverState(Game& game)
    {
        game.bGameOver = true;
        game.sounds.dyingSound.play();
        game.pauseTimer = 0.f;
    }

    void UpdateGameOverState(Game& game, float timer)
    {
        if (game.pauseTimer >= NEW_GAME_DELAY)
            StartPlayingState(game);
        else
            game.pauseTimer += timer;
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

        // передаем центр, т.к. в вычислениях используется центры коллайдеров
        game.backgroungRect.position = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f }; 
        //вычитаем размеры игрока, чтобы коллизия с игроком прекращалась тогда, когда игрок касается края экрана, а не полностью выходит за него
        game.backgroungRect.size = { SCREEN_WIDTH - PLAYER_SIZE * 2, SCREEN_HEIGHT - PLAYER_SIZE * 2 }; 

        InitPlayer(game.player, game);

        game.numApples = rand() % NUM_APPLES;
        game.apples = new Apple[game.numApples];
        for (int i = 0; i < game.numApples; i++)
        {
            InitApple(game.apples[i], game);
        }
        for (int i = 0; i < NUM_BLOCKS; i++)
        {
            InitBlock(game.blocks[i], game);
        }
        game.gameMode = 0;
        //ChooseGameMode(game);
        StartPlayingState(game);
    }

    void UpdateGame(Game& game, float timer)
    {
        if (!game.bGameOver)
        {
            UpdatePlayingState(game, timer);
        }
        else
        {
            UpdateGameOverState(game, timer);
        }
    }

    void DrawGame(Game& game, sf::RenderWindow& window)
    {
        DrawPlayer(game.player, window);
        for (int i = 0; i < game.numApples; i++)
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
