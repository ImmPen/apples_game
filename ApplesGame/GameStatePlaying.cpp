#include "GameStatePlaying.h"
#include "Game.h"
#include <assert.h>

namespace ApplesGame
{
	void InitGameStatePlaying(GameStatePlayingData& data, Game& game)
	{
		// Init game resources (terminate if error)
		assert(data.playerTexture.loadFromFile(RESOURCES_PATH + "Player.png"));
		assert(data.appleTexture.loadFromFile(RESOURCES_PATH + "Apple.png"));
		assert(data.blockTexture.loadFromFile(RESOURCES_PATH + "Rock.png"));
		assert(data.font.loadFromFile(RESOURCES_PATH + "arial.ttf"));
		assert(data.eatSoundBuffer.loadFromFile(RESOURCES_PATH + "AppleEat.wav"));
		assert(data.deadSoundBuffer.loadFromFile(RESOURCES_PATH + "Death.wav"));

		// Init player
		InitPlayer(data.player, data.playerTexture);

		// Init apples
		data.apples.clear();
		ClearAppleGrid(data.applesGrid);
		int numApples = MIN_NUM_APPLES + rand() % (MAX_NUM_APPLES + 1 - MIN_NUM_APPLES);
		data.apples.resize(numApples);
		for (Apple& apple : data.apples)
		{
			InitApple(apple, data.appleTexture);
			ResetAppleState(apple);
			AddAppleToGrid(apple, data.applesGrid);
		}
		//Init rocks
		data.blocks.resize(NUM_BLOCKS);
		for (Rock& block : data.blocks)
		{
			InitBlock(block, data.blockTexture);
			ResetBlockPosition(block);
		}

		data.sounds.eatingSound.setBuffer(data.eatSoundBuffer);
		data.sounds.dyingSound.setBuffer(data.deadSoundBuffer);

		data.numEatenApples = 0;

		data.scoreText.setFont(data.font);
		data.scoreText.setCharacterSize(24);
		data.scoreText.setFillColor(sf::Color::Yellow);

		data.inputHintText.setFont(data.font);
		data.inputHintText.setCharacterSize(24);
		data.inputHintText.setFillColor(sf::Color::White);
		data.inputHintText.setString("Use arrow keys to move, ESC to exit");
		data.inputHintText.setOrigin(GetItemOrigin(data.inputHintText, { 1.f, 0.f }));
	}

	void ShutdownGameStatePlaying(GameStatePlayingData& data, Game& game)
	{
		// We dont need to free resources here, because they will be freed automatically
	}

	void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Game& game, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				PushGameState(game, GameStateType::Pause, false);
			}
		}
	}

	void UpdateGameStatePlaying(GameStatePlayingData& data, Game& game, float timeDelta)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			data.player.direction = PlayerDirection::Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			data.player.direction = PlayerDirection::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			data.player.direction = PlayerDirection::Down;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			data.player.direction = PlayerDirection::Left;
		}

		// Update player
		RotatePlayer(data.player);
		MovePlayer(data.player, timeDelta);

		AppleSet collidingApples;

		if (FindPlayerCollisionWithApples(data.player.position, data.applesGrid, collidingApples))
		{
			for (Apple* apple : collidingApples)
			{
				if ((std::uint8_t)game.options & (std::uint8_t)GameOptions::ENDLESS_MODE)
				{
					ResetAppleState(*apple);
					AddAppleToGrid(*apple, data.applesGrid);
				}
				else
				{
					MarkAppleAsEaten(*apple);
					RemoveAppleFromGrid(*apple, data.applesGrid);
				}
				// Increase eaten apples counter
				data.numEatenApples++;
				data.sounds.eatingSound.play();
				// Increase player speed
				if ((std::uint8_t)game.options & (std::uint8_t)GameOptions::ACCELERATION_MODE)
				{
					data.player.speed += ACCELERATION;
				}
			}
			
		}

		bool isGameFinished = false;

		for (auto& block : data.blocks)
		{
			if (IsShapesCollide(GetCollider(data.player), GetCollider(block)))
			{
				isGameFinished = true;
			}
		}

		isGameFinished = isGameFinished || (data.numEatenApples == data.apples.size())
			&& !((std::uint8_t)game.options & (std::uint8_t)GameOptions::ENDLESS_MODE);
		// Check collision with screen border
		if (isGameFinished || HasPlayerCollisionWithScreenBorder(data.player))
		{
			AddEntryToTable(game.recordsTable, { "YOU", data.numEatenApples });
			data.sounds.dyingSound.play();
			PushGameState(game, GameStateType::GameOver, false);
		}
	}

	void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window)
	{
		// Draw player
		DrawPlayer(data.player, window);
		// Draw apples
		for (Apple& apple : data.apples)
		{
			DrawApple(apple, window);
		}
		//Draw rocks
		for (Rock& block : data.blocks)
		{
			DrawBlock(block, window);
		}

		data.scoreText.setPosition(10.f, 10.f);
		window.draw(data.scoreText);

		sf::Vector2f viewSize = window.getView().getSize();
		data.inputHintText.setPosition(viewSize.x - 10.f, 10.f);
		window.draw(data.inputHintText);
	}
}
