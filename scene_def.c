#ifndef SCENE_DEF

#include "scene_enum.c"
#include "character_def.c"

#define SCENE_DEF

// Struct for moves made (keys pressed) by the player
typedef struct {
    int right;
    int left;
    int up;
    int down;
    int entryRequested;
} Moves;

// Structure for scene parameters
typedef struct {
    Character* character;
    int* callShowClue;
    int* isTrueClue;
    int* falseClueIndex;
    int original_x;
    int original_y;
} Parameters;

// Function pointer type for scene functions
typedef void (*SceneFuncPointer)(Parameters*);

// Structure for scene details
typedef struct {
    SceneName name;
    
    int boundsRows, boundsCols;
    int* bounds;
    
    int functionPointersLength;
    SceneFuncPointer* functionPointers;
    
    SceneName* exitToScenes;
} Scene;

#endif
