#include "GameStatePause.h"
#include "Game.h"
#include <assert.h>

namespace ApplesGame
{
	void InitGameStateExitDialog(GameStatePauseData& data, Game& game)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "arial.ttf"));

		data.menu.rootItem.hintText.setString("Are you sure you want to stop this game?");
		data.menu.rootItem.hintText.setFont(data.font);
		data.menu.rootItem.hintText.setCharacterSize(24);
		data.menu.rootItem.hintText.setFillColor(sf::Color::Red);
		data.menu.rootItem.childrenOrientation = Orientation::Horizontal;
		data.menu.rootItem.childrenAlignment = Alignment::Middle;
		data.menu.rootItem.childrenSpacing = 20.f;
		data.menu.rootItem.children.push_back(&data.yesItem);
		data.menu.rootItem.children.push_back(&data.noItem);

		data.yesItem.text.setString("Yes");
		data.yesItem.text.setFont(data.font);
		data.yesItem.text.setCharacterSize(24);

		data.noItem.text.setString("No");
		data.noItem.text.setFont(data.font);
		data.noItem.text.setCharacterSize(24);

		InitMenuItem(data.menu.rootItem);
		SelectMenuItem(data.menu, &data.yesItem);

		data.background.setFillColor(sf::Color(0, 0, 0, 128)); // Semi-transparent black
	}

	void ShutdownGameStateExitDialog(GameStatePauseData& data, Game& game)
	{
		// We dont need to free resources here, because they will be freed automatically
	}

	void HandleGameStateExitDialogWindowEvent(GameStatePauseData& data, Game& game, const sf::Event& event)
	{

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				PopGameState(game);
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				if (data.menu.selectedItem == &data.yesItem)
				{
					SwitchGameState(game, GameStateType::MainMenu);
				}
				else if (data.menu.selectedItem == &data.noItem)
				{
					PopGameState(game);
				}
			}
		}

		Orientation orientation = data.menu.selectedItem->parent->childrenOrientation;
		if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Up ||
			orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Left)
		{
			SelectPreviousMenuItem(data.menu);
		}
		else if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Down ||
			orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Right)
		{
			SelectNextMenuItem(data.menu);
		}
	}

	void UpdateGameStateExitDialog(GameStatePauseData& data, Game& game, float timeDelta)
	{

	}

	void DrawGameStateExitDialog(GameStatePauseData& data, Game& game, sf::RenderWindow& window)
	{
		sf::Vector2f windowSize = (sf::Vector2f)window.getSize();

		data.background.setSize(windowSize);
		window.draw(data.background);

		sf::Text* hintText = &GetCurrentMenuContext(data.menu)->hintText;
		hintText->setOrigin(GetItemOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(windowSize.x / 2.f, 150.f);
		window.draw(*hintText);

		DrawMenu(data.menu, window, windowSize / 2.f, { 0.5f, 0.f });
	}

}
