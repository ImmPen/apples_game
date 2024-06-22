#include "game.h"
#include "fonts.h"
#include <iostream>

namespace ApplesGame
{
    

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

        // �������� �����, �.�. � ����������� ������������ ������ �����������
        game.backgroungRect.position = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f };
        //�������� ������� ������, ����� �������� � ������� ������������ �����, ����� ����� �������� ���� ������, � �� ��������� ������� �� ����
        game.backgroungRect.size = { SCREEN_WIDTH - PLAYER_SIZE * 2, SCREEN_HEIGHT - PLAYER_SIZE * 2 };

        InitPlayer(game.player, game);

        game.numApples = rand() % (MAX_NUM_APPLES - MIN_NUM_APPLES) + MIN_NUM_APPLES;
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

        game.recordsTable = GetNewRecordTable();

        StartChoosingState(game);
    }

    void StartChoosingState(Game& game)
    {
        game.currentGameState = 1 << 1;
    }

    void UpdateChoosingState(Game& game)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))       // Finite Mode
        {
            game.gameMode = (game.gameMode & (0 << 1)) | (game.gameMode & 1);   
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))     //Endless mode
        {
            game.gameMode = game.gameMode | (1 << 1);   
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))      // Without acceleration
        {
            game.gameMode = (game.gameMode & 0) | (game.gameMode & (1 << 1));         
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))     // With Acceleration
        {
            game.gameMode = game.gameMode | 1;         
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            StartPlayingState(game);
        }
    }

    void StartPlayingState(Game& game)
    {
        SetPlayerPosition(game.player, { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 });
        SetPlayerDirection(game.player, PlayerDirection::Right);
        SetMovementSpeed(game.player, INITIAL_SPEED);

        for (int i = 0; i < game.numApples; i++)
        {
            game.apples[i].eaten = false;
            SetPosition(game.apples[i], GetRandomPositionOnScreen(SCREEN_WIDTH, SCREEN_HEIGHT));
            AddAppleToGrid(game.apples[i], game.grid);            
        }

        for (int i = 0; i < NUM_BLOCKS; i++)
        {
            SetPosition(game.blocks[i], GetRandomPositionOnScreen(SCREEN_WIDTH, SCREEN_HEIGHT));
        }

        game.numEatenApples = 0;
        game.currentGameState = 1;
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
        
        //��������� ������������ � �������������
        for (int i = 0; i < NUM_BLOCKS; i++)
        {
            if (IsShapesCollide(GetCollider(game.player), GetCollider(game.blocks[i])))
            {
                StartGameOverState(game);
            }
        }
        //��������� ������������ � ��������
        int numApplesMayCollidePlayer = 0;
        Apple** applesMayCollidePlayer;
        applesMayCollidePlayer = PlayerMayCollideApple(game.player, game.apples, game.grid, numApplesMayCollidePlayer);
        for (int i = 0; i < numApplesMayCollidePlayer; i++)
        {
            if (IsShapesCollide(GetCollider(game.player), GetCollider(*applesMayCollidePlayer[i])))
            {
                if (PlayerEatsApple(game.player, *applesMayCollidePlayer[i], game.grid, game.gameMode))
                {
                    ++game.numEatenApples;
                    game.sounds.eatingSound.play();
                }
                if (!((game.gameMode >> 1) & 1) && game.numEatenApples == game.numApples)
                {
                    StartGameOverState(game);
                }
            }
        }
        //��������� ������ �� ������� ������
        if (!IsShapesCollide(GetCollider(game.player), game.backgroungRect))
        {
            StartGameOverState(game);
        }
    }

    void StartGameOverState(Game& game)
    {
        addEntryToTable(game.recordsTable, { "YOU", game.numEatenApples });
        game.currentGameState = 0;
        game.sounds.dyingSound.play();
        game.pauseTimer = 0.f;
        ClearAppleGrid(game.grid);
    }

    void UpdateGameOverState(Game& game, float timer)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            StartPlayingState(game);
    }

    void UpdateGame(Game& game, float timer)
    {
        if (game.currentGameState & (1 << 1))
        {
            UpdateChoosingState(game);
        }
        else if (game.currentGameState & 1)
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
        DrawFont(window, game);
    }

    void DeinitGame(Game& game)
    {
        ClearAppleGrid(game.grid);
    }

}
