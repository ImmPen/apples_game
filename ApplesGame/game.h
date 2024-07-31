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
    enum class GameState
    {
        None = 0,
        Choosing,
        Playing,
        GameOver,
        Pause
    };
    struct Game
    {
        Player player;

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

        AppleGrid grid;
    };
    
    void PushGameState(Game& game, GameState state);
    void PopGameState(Game& game);
    void SwitchGameState(Game& game, GameState state);
    GameState GetGameState(const Game& game);

    void InitGame(Game& game);

    void StartChoosingState(Game& game);
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

    void HandleWindowEvents(Game& game, sf::RenderWindow& window);
}
