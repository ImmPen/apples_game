#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "apple.h"
#include "player.h"
#include "rock.h"
#include "sounds.h"


namespace ApplesGame
{
	struct Game;

	struct GameStatePlayingData
	{
		// Resources
		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Texture blockTexture;
		sf::Font font;
		sf::SoundBuffer eatSoundBuffer;
		sf::SoundBuffer deadSoundBuffer;

		// Game data
		Player player;
		std::vector<Apple> apples;
		AppleGrid applesGrid;
		int numEatenApples = 0;
		std::vector<Rock> blocks;
		Sound sounds;

		// UI data
		sf::Text scoreText;
		sf::Text inputHintText;
	};

	void InitGameStatePlaying(GameStatePlayingData& data, Game& game);
	void ShutdownGameStatePlaying(GameStatePlayingData& data, Game& game);
	void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Game& game, const sf::Event& event);
	void UpdateGameStatePlaying(GameStatePlayingData& data, Game& game, float timeDelta);
	void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window);
}
