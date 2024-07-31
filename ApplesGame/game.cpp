#include "game.h"
#include "fonts.h"
#include <iostream>

namespace ApplesGame
{
    void PushGameState(Game& game, GameState state)
    {
        game.gameStateStack.push_back(state);
    }
    void PopGameState(Game& game)
    {
        game.gameStateStack.pop_back();
    }
    void SwitchGameState(Game& game, GameState state)
    {
        if (game.gameStateStack.size() > 0)
        {
            game.gameStateStack.pop_back();
        }
        game.gameStateStack.push_back(state);
    }
    GameState GetGameState(const Game& game)
    {
        return game.gameStateStack.back();
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

        int numApples = rand() % (MAX_NUM_APPLES - MIN_NUM_APPLES) + MIN_NUM_APPLES;
        game.apples.resize(numApples);
        for (auto& apple : game.apples)
        {
            InitApple(apple, game);
        }
        game.blocks.resize(NUM_BLOCKS);
        for (auto& block : game.blocks)
        {
            InitBlock(block, game);
        }
        game.gameMode = 0;
        game.recordsTable = GetNewRecordTable();

        StartChoosingState(game);
    }

    void StartChoosingState(Game& game)
    {
        SwitchGameState(game, GameState::Choosing);
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

        for (auto& apple : game.apples)
        {
            apple.eaten = false;
            SetPosition(apple, GetRandomPositionOnScreen(SCREEN_WIDTH, SCREEN_HEIGHT));
            AddAppleToGrid(apple, game.grid);            
        }

        for (auto& block : game.blocks)
        {
            SetPosition(block, GetRandomPositionOnScreen(SCREEN_WIDTH, SCREEN_HEIGHT));
        }

        game.numEatenApples = 0;
        SwitchGameState(game, GameState::Playing);
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
        
        //обработка столкновений с яблоками
        std::vector<Apple*> applesMayCollidePlayer = PlayerMayCollideApple(game.player, game.apples, game.grid);
        for (auto& element : applesMayCollidePlayer)
        {
            if (IsShapesCollide(GetCollider(game.player), GetCollider(*element)))
            {
                if (PlayerEatsApple(game.player, *element, game.grid, game.gameMode))
                {
                    ++game.numEatenApples;
                    game.sounds.eatingSound.play();
                }
                if (!((game.gameMode >> 1) & 1) && game.numEatenApples == game.apples.size())
                {
                    StartGameOverState(game);
                }
            }
        }
        //обработка столкновений с препятствиями
        for (auto& block : game.blocks)
        {
            if (IsShapesCollide(GetCollider(game.player), GetCollider(block)))
            {
                StartGameOverState(game);
            }
        }
        //обработка выхода за границы экрана
        if (!IsShapesCollide(GetCollider(game.player), game.backgroungRect))
        {
            StartGameOverState(game);
        }
    }

    void StartGameOverState(Game& game)
    {
        AddEntryToTable(game.recordsTable, { "YOU", game.numEatenApples });
        SwitchGameState(game, GameState::GameOver);
        game.sounds.dyingSound.play();
        game.pauseTimer = 0.f;
        ClearAppleGrid(game.grid);
    }

    void UpdateGameOverState(Game& game, float timer)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            StartPlayingState(game);
    }

    void StartPauseState(Game& game)
    {
        PushGameState(game, GameState::Pause);
    }

    void UpdatePauseState(Game& game, float timer)
    {
        game.pauseTimer += timer;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            PopGameState(game);
        }
    }

    void UpdateGame(Game& game, float timer)
    {
        GameState currentGameState = GetGameState(game);
        switch (currentGameState)
        {
        case GameState::None:
            break;
        case GameState::Choosing:
            UpdateChoosingState(game);
            break;
        case GameState::Playing:
            UpdatePlayingState(game, timer);
            break;
        case GameState::GameOver:
            UpdateGameOverState(game, timer);
            break;
        case GameState::Pause:
            UpdatePauseState(game, timer);
            break;
        default:
            break;
        }
    }

    void DrawGame(Game& game, sf::RenderWindow& window)
    {
        DrawPlayer(game.player, window);
        for (auto& apple : game.apples)
        {
            DrawApple(apple, window);
        }
        for (auto& block : game.blocks)
        {
            DrawBlock(block, window);
        }
        DrawFont(window, game);
    }

    void DeinitGame(Game& game)
    {
        ClearAppleGrid(game.grid);
    }

    void HandleWindowEvents(Game& game, sf::RenderWindow& window)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                GameState state = GetGameState(game);
                if (state != GameState::Playing)
                {
                    window.close();
                }
                else
                {
                    StartPauseState(game);
                }
            }
        }

    }

}
