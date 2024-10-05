#include "game.h"
#include "fonts.h"
#include <iostream>
#include "GameStatePlaying.h"
#include "GameStateGameOver.h"
#include "GameStatePause.h"
#include "GameStateMainMenu.h"

namespace ApplesGame
{
    void InitGame(Game& game)
    {
        game.gameStateChangeType = GameStateChangeType::None;
        game.pendingGameStateType = GameStateType::None;
        game.pendingGameStateIsExclusivelyVisible = false;
        game.recordsTable = GetNewRecordTable();
        SwitchGameState(game, GameStateType::MainMenu);
        /*game.playerTexture.loadFromFile(RESOURCES_PATH + "/Player.png");
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

        StartChoosingState(game);*/
    }

    void HandleWindowEvents(Game& game, sf::RenderWindow& window)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (game.gameStateStack.size() > 0)
            {
                HandleWindowEventGameState(game, game.gameStateStack.back(), event);
            }
        }
    }

    bool UpdateGame(Game& game, float timer)
    {
        switch (game.gameStateChangeType) // убираем стейты в случае свитч'а или поп'а
        {
        case GameStateChangeType::Pop:
            if (game.gameStateStack.size() > 0)
            {
                ShutdownGameState(game, game.gameStateStack.back());
                game.gameStateStack.pop_back();
            }
            break;
        case GameStateChangeType::Switch:
            while (game.gameStateStack.size() > 0)
            {
                ShutdownGameState(game, game.gameStateStack.back());
                game.gameStateStack.pop_back();
            }
            break;
        default:
            break;
        }
        if (game.pendingGameStateType != GameStateType::None) // добавляем стейт, в случае пуш'а или свитч'а
        {
            game.gameStateStack.push_back({ game.pendingGameStateType, nullptr, game.pendingGameStateIsExclusivelyVisible });
            InitGameState(game, game.gameStateStack.back());
        }
        game.pendingGameStateType = GameStateType::None;
        game.pendingGameStateIsExclusivelyVisible = false;
        game.gameStateChangeType = GameStateChangeType::None;

        if (game.gameStateStack.size() > 0)
        {
            UpdateGameState(game, game.gameStateStack.back(), timer);
            return true;
        }
        return false;
    }

    void DrawGame(Game& game, sf::RenderWindow& window)
    {
        if (game.gameStateStack.size() > 0)
        {
            std::vector<GameState*> visibleGameStates;
            for (auto it = game.gameStateStack.rbegin(); it != game.gameStateStack.rend(); ++it)
            {
                visibleGameStates.push_back(&(*it));
                if (it->isExclusivelyVisible)
                {
                    break;
                }
            }

            for (auto it = visibleGameStates.rbegin(); it != visibleGameStates.rend(); ++it)
            {
                DrawGameState(game, **it, window);
            }
        }
    }

    void ShutownGame(Game& game)
    {
        while (game.gameStateStack.size() > 0)
        {
            ShutdownGameState(game, game.gameStateStack.back());
            game.gameStateStack.pop_back();
        }
        game.gameStateChangeType = GameStateChangeType::None;
        game.pendingGameStateType = GameStateType::None;
        game.pendingGameStateIsExclusivelyVisible = false;
    }

    void PushGameState(Game& game, GameStateType stateType, bool isExclusivelyVisible)
    {
        game.pendingGameStateType = stateType;
        game.pendingGameStateIsExclusivelyVisible = false;
        game.gameStateChangeType = GameStateChangeType::Push;
    }

    void PopGameState(Game& game)
    {
        game.pendingGameStateType = GameStateType::None;
        game.pendingGameStateIsExclusivelyVisible = false;
        game.gameStateChangeType = GameStateChangeType::Pop;
    }

    void SwitchGameState(Game& game, GameStateType stateType)
    {
        game.pendingGameStateType = stateType;
        game.pendingGameStateIsExclusivelyVisible = false;
        game.gameStateChangeType = GameStateChangeType::Switch;
    }

    void InitGameState(Game& game, GameState& state)
    {
        switch (state.type)
        {
        case GameStateType::MainMenu:
        {
            state.data = new GameStateMainMenuData();
            InitGameStateMainMenu(*(GameStateMainMenuData*)state.data, game);
            break;
        }
        case GameStateType::Playing:
        {
            state.data = new GameStatePlayingData();
            InitGameStatePlaying(*(GameStatePlayingData*)state.data, game);
            break;
        }
        case GameStateType::GameOver:
        {
            state.data = new GameStateGameOverData();
            InitGameStateGameOver(*(GameStateGameOverData*)state.data, game);
            break;
        }
        case GameStateType::Pause:
        {
            state.data = new GameStatePauseData();
            InitGameStateExitDialog(*(GameStatePauseData*)state.data, game);
            break;
        }
        default:
            break;
        }
    }

    void ShutdownGameState(Game& game, GameState& state)
    {
        switch (state.type)
        {
        case GameStateType::MainMenu:
        {
            ShutdownGameStateMainMenu(*(GameStateMainMenuData*)state.data, game);
            delete (GameStateMainMenuData*)state.data;
            break;
        }
        case GameStateType::Playing:
        {
            ShutdownGameStatePlaying(*(GameStatePlayingData*)state.data, game);
            delete (GameStatePlayingData*)state.data;
            break;
        }
        case GameStateType::GameOver:
        {
            ShutdownGameStateGameOver(*(GameStateGameOverData*)state.data, game);
            delete (GameStateGameOverData*)state.data;
            break;
        }
        case GameStateType::Pause:
        {
            ShutdownGameStateExitDialog(*(GameStatePauseData*)state.data, game);
            delete (GameStatePauseData*)state.data;
            break;
        }
        default:
            break;
        }

        state.data = nullptr;
    }

    void HandleWindowEventGameState(Game& game, GameState& state, sf::Event& event)
    {
        switch (state.type)
        {
        case GameStateType::MainMenu:
        {
            HandleGameStateMainMenuWindowEvent(*(GameStateMainMenuData*)state.data, game, event);
            break;
        }
        case GameStateType::Playing:
        {
            HandleGameStatePlayingWindowEvent(*(GameStatePlayingData*)state.data, game, event);
            break;
        }
        case GameStateType::GameOver:
        {
            HandleGameStateGameOverWindowEvent(*(GameStateGameOverData*)state.data, game, event);
            break;
        }
        case GameStateType::Pause:
        {
            HandleGameStateExitDialogWindowEvent(*(GameStatePauseData*)state.data, game, event);
            break;
        }
        default:
            break;
        }
    }

    void UpdateGameState(Game& game, GameState& state, float timeDelta)
    {
        switch (state.type)
        {
        case GameStateType::MainMenu:
        {
            UpdateGameStateMainMenu(*(GameStateMainMenuData*)state.data, game, timeDelta);
            break;
        }
        case GameStateType::Playing:
        {
            UpdateGameStatePlaying(*(GameStatePlayingData*)state.data, game, timeDelta);
            break;
        }
        case GameStateType::GameOver:
        {
            UpdateGameStateGameOver(*(GameStateGameOverData*)state.data, game, timeDelta);
            break;
        }
        case GameStateType::Pause:
        {
            UpdateGameStateExitDialog(*(GameStatePauseData*)state.data, game, timeDelta);
            break;
        }
        default:
            break;
        }
    }

    void DrawGameState(Game& game, GameState& state, sf::RenderWindow& window)
    {
        switch (state.type)
        {
        case GameStateType::MainMenu:
        {
            DrawGameStateMainMenu(*(GameStateMainMenuData*)state.data, game, window);
            break;
        }
        case GameStateType::Playing:
        {
            DrawGameStatePlaying(*(GameStatePlayingData*)state.data, game, window);
            break;
        }
        case GameStateType::GameOver:
        {
            DrawGameStateGameOver(*(GameStateGameOverData*)state.data, game, window);
            break;
        }
        case GameStateType::Pause:
        {
            DrawGameStateExitDialog(*(GameStatePauseData*)state.data, game, window);
            break;
        }
        default:
            break;
        }
    }
    /*void StartChoosingState(Game& game)
    {
        SwitchGameState(game, GameState::MainMenu);
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
        case GameState::MainMenu:
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
    */
}
