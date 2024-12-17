#ifndef CHARACTER_DEF_C

#include "raylib.h"
#include "scene_enum.c"
#include "imaginate.c"

#define CHARACTER_DEF_C

// Enum to define character types
typedef enum {
    WARRIOR = 0,
    GOBLIN
} CharacterType;

// Enum for directions
typedef enum {
    LEFT = 0,
    RIGHT
} Direction;

// Enum for animation states
typedef enum {
    WALK_LEFT = 0,
    WALK_RIGHT,
    STILL_LEFT,
    STILL_RIGHT,
    ATTACK
} Animation;

// Character structure definition
typedef struct {
    CharacterType type;
    SceneName sceneName, prevSceneName;
    int intelSolved, mazeSolved;
    int isMoving;
    int x, y;
    Direction facing;
    Animation currentWalk, currentStill;
    Texture2D** animationFramesArray;
    int* animationFramesLengths;
} Character;

// Function to unload character textures
void unloadCharacterTextures(Character* character) {
    // Unload animation frames for walk and still states
    for (int i = WALK_LEFT; i <= STILL_RIGHT; i++) {
        unloadImageArray(character->animationFramesArray[i], character->animationFramesLengths[i]);
    }
    // Unload attack animation for goblins
    if (character->type == GOBLIN) {
        unloadImageArray(character->animationFramesArray[ATTACK], character->animationFramesLengths[ATTACK]);
    }
}

#endif
