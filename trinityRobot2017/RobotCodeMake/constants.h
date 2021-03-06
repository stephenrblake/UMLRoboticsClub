// constants for NavVal

#pragma once

static const float CLEAR_THRESHOLD = 0.25;
static const int RESOLUTION = 1;

constexpr static const int ARENALENGTH_CM = 244;
constexpr static const int CELLSIZE_CM = 1;
constexpr static const int ROBOT_DIAMETER_CM = 31;

//big enough to hold entire maze no matter where we start
static const int GRID_SIZE_CM  = 5 * ARENALENGTH_CM;
static const int GRID_SIZE_CELLS = GRID_SIZE_CM / RESOLUTION;

// Constant cell types, used as parameters to updateValue().
enum cellType { 
    UNKNOWN = -1,
    CLEAR,
    WALL,
    FLAME,
    CANDLE,
    EXTINGUISHED,
    SAFE_ZONE,
    RED_SIDE_CRADLE,
    BLUE_SIDE_CRADLE,
    GREEN_SIDE_CRADLE,
    DOOR,
    EXPLORED_DOOR,
    HALLWAY,
    START_ZONE
};

