#pragma once
#include "player.h"
#include "apple.h"
#include "rock.h"
#include "sounds.h"
#include <SFML/Audio.hpp>

namespace ApplesGame 
{
    struct Game
    {
        Player player;

        Apple apples[NUM_APPLES];

        Rock blocks[NUM_BLOCKS];

        Sound sounds;

        int numEatenApples = 0;
        bool bGameOver = false;
        float pauseTimer = 0;

        sf::Texture playerTexture;
        sf::Texture appleTexture;
        sf::Texture rockTexture;

        sf::SoundBuffer eatSoundBuffer;
        sf::SoundBuffer deadSoundBuffer;

        sf::Font font;
    };

    void RestartGame(Game& game);

    void InitGame(Game& game);

    void UpdateGame(Game& game, float timer);

    void DrawGame(Game& game, sf::RenderWindow& window);

    void DeinitGame();
}
