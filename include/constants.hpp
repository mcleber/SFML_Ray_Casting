/**
 * @file   constants.hpp
 *
 * @brief  Formulas, constants and variables executed at compile time.
*/

#pragma once

#include <cstddef>

constexpr float CELL_SIZE {48.0f};

constexpr float PI {3.141592653589793f};

constexpr float TURN_SPEED {120.0f};

constexpr float MOVE_SPEED {2.5f};

constexpr size_t MAX_RAYCASTING_STEPS {16};

constexpr size_t MAX_RAYCASTING_DEPTH {64};

constexpr float PLAYER_FOV {60.0f};

constexpr float PLAYER_TURN_SPEED {100.0f};

 constexpr float PLAYER_SIZE {0.1f};

constexpr float SCREEN_W {1024.0f};

constexpr float SCREEN_H {768.0f};

constexpr float CAMERA_Z {0.5f * SCREEN_H};

constexpr size_t NUM_RAYS {600}; // Large numbers (e.g. 1200) create smooth walls.

constexpr float COLUMN_WIDTH {SCREEN_W / (float)NUM_RAYS};
