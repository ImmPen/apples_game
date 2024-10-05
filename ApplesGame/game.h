#pragma once
#include <vector>
#include "player.h"
#include "apple.h"
#include "rock.h"
#include "sounds.h"
#include "records.h"
#include <SFML/Audio.hpp>

namespace ApplesGame 
{
    enum class GameStateType
    {
        None = 0,
        MainMenu,
        Playing,
        GameOver,
        Pause
    };

    enum class GameOptions : std::uint8_t
    {
        FINITE_MODE = 0x01,
        ENDLESS_MODE = 0x02,
        ACCELERATION_MODE = 0x04,
        NO_ACCELERATION_MODE = 0x08,
        DEFAULT_MODE = ENDLESS_MODE | ACCELERATION_MODE,
        Empty = 0
    };

    struct GameState
    {
        GameStateType type = GameStateType::None;
        void* data = nullptr;
        bool isExclusivelyVisible = false;
    };

    enum class GameStateChangeType
    {
        None,
        Push,
        Pop,
        Switch
    };

    struct Game
    {
        std::vector<GameState> gameStateStack;
        GameStateChangeType gameStateChangeType = GameStateChangeType::None;
        GameStateType pendingGameStateType = GameStateType::None;
        bool pendingGameStateIsExclusivelyVisible = false;

        GameOptions options = GameOptions::DEFAULT_MODE;
        RecordsTable recordsTable;

        /*Player player;

        std::vector<Apple> apples;

        std::vector<Rock> blocks;

        Sound sounds;

        int numEatenApples = 0;
        //int currentGameState;
        std::vector<GameState> gameStateStack = {};
        float pauseTimer = 0;
        int gameMode;

        sf::Texture playerTexture;
        sf::Texture appleTexture;
        sf::Texture rockTexture;

        sf::SoundBuffer eatSoundBuffer;
        sf::SoundBuffer deadSoundBuffer;

        sf::Font font;

        Rectangle backgroungRect;

        RecordsTable recordsTable;

        AppleGrid grid;*/
    };
    
    void InitGame(Game& game);
    void HandleWindowEvents(Game& game, sf::RenderWindow& window);
    bool UpdateGame(Game& game, float timer);
    void DrawGame(Game& game, sf::RenderWindow& window);
    void ShutownGame(Game& game);

    void PushGameState(Game& game, GameStateType stateType, bool isExclusivelyVisible);
    void PopGameState(Game& game);
    void SwitchGameState(Game& game, GameStateType stateType);

    void InitGameState(Game& game, GameState& state);
    void ShutdownGameState(Game& game, GameState& state);
    void HandleWindowEventGameState(Game& game, GameState& state, sf::Event& event);
    void UpdateGameState(Game& game, GameState& state, float timeDelta);
    void DrawGameState(Game& game, GameState& state, sf::RenderWindow& window);

    /*void StartChoosingState(Game& game);
    void UpdateChoosingState(Game& game);

    void StartPlayingState(Game& game);
    void UpdatePlayingState(Game& game, float timer);

    void StartGameOverState(Game& game);
    void UpdateGameOverState(Game& game, float timer);

    void StartPauseState(Game& game);
    void UpdatePauseState(Game& game, float timer);

    void UpdateGame(Game& game, float timer);

    void DrawGame(Game& game, sf::RenderWindow& window);

    void DeinitGame(Game& game);

    void HandleWindowEvents(Game& game, sf::RenderWindow& window);*/
}
