#pragma once
#include "player.h"
#include "apple.h"
#include "rock.h"
#include "sounds.h"
#include "records.h"
#include <SFML/Audio.hpp>

namespace ApplesGame 
{
    struct Game
    {
        Player player;

        Apple* apples;
        int numApples;

        Rock blocks[NUM_BLOCKS];

        Sound sounds;

        int numEatenApples = 0;
        int currentGameState;
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

    void InitGame(Game& game);

    void StartChoosingState(Game& game);
    void UpdateChoosingState(Game& game);

    void StartPlayingState(Game& game);
    void UpdatePlayingState(Game& game, float timer);

    void StartGameOverState(Game& game);
    void UpdateGameOverState(Game& game, float timer);

    void UpdateGame(Game& game, float timer);

    void DrawGame(Game& game, sf::RenderWindow& window);

    void DeinitGame(Game& game);
}
