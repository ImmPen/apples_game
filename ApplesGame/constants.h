#pragma once
#include <string>

namespace ApplesGame
{
	const std::string RESOURCES_PATH = "./Resources";
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
	const float INITIAL_SPEED = 100.f;
	const float PLAYER_SIZE = 20.f;
	const float ACCELERATION = 20.f;
	const int MAX_NUM_APPLES = 100;
	const int MIN_NUM_APPLES = 20;
	const float APPLE_SIZE = 20.f;
	const float NEW_GAME_DELAY = 5;
	const int NUM_BLOCKS = 5;
	const float BLOCK_SIZE = 40.f;
	const int NUM_NAMES_IN_TABLE = 10;
	const int MAX_APPLES_IN_CELL = 10;
	const int GRID_CELL_WITDH = 100;
	const int GRID_CELL_HEIGHT = 100;
	const int APPLES_GRID_CELLS_H = SCREEN_WIDTH / GRID_CELL_WITDH;
	const int APPLES_GRID_CELLS_V = SCREEN_HEIGHT / GRID_CELL_HEIGHT;
}
