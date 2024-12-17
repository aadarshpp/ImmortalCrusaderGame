#ifndef CHARACTER_SETUP_C

#include <stdlib.h>
#include "character_def.c"

#define CHARACTER_SETUP_C

// Warrior Setup
Character warrior;

void setUpWarrior(int x, int y, SceneName sceneName) {
    warrior.type = WARRIOR;
    
    warrior.intelSolved = 0;
    warrior.isMoving = 0;
    warrior.sceneName = sceneName;
    
    warrior.x = x; 
    warrior.y = y;
    
    // Setup the direction the character is facing and looking
    warrior.facing = LEFT;

    // Setup the animation arrays
    warrior.animationFramesArray = (Texture2D**)malloc(4 * sizeof(Texture2D*)); // 4 animations
    warrior.animationFramesLengths = (int*)malloc(4 * sizeof(int));
    
    // Walk Right
    warrior.animationFramesArray[WALK_RIGHT] = (Texture2D*)malloc(6 * sizeof(Texture2D));
    fillImageArray(warrior.animationFramesArray[WALK_RIGHT], "/Warrior_purple/Walk/Right", 6);
    warrior.animationFramesLengths[WALK_RIGHT] = 6;
    
    // Walk Left
    warrior.animationFramesArray[WALK_LEFT] = (Texture2D*)malloc(6 * sizeof(Texture2D));
    fillImageArray(warrior.animationFramesArray[WALK_LEFT], "/Warrior_purple/Walk/Left", 6);
    warrior.animationFramesLengths[WALK_LEFT] = 6;
    
    // Still Right
    warrior.animationFramesArray[STILL_RIGHT] = (Texture2D*)malloc(7 * sizeof(Texture2D));
    fillImageArray(warrior.animationFramesArray[STILL_RIGHT], "/Warrior_purple/Still/Right", 7);
    warrior.animationFramesLengths[STILL_RIGHT] = 7;
    
    // Still Left
    warrior.animationFramesArray[STILL_LEFT] = (Texture2D*)malloc(7 * sizeof(Texture2D));
    fillImageArray(warrior.animationFramesArray[STILL_LEFT], "/Warrior_purple/Still/Left", 7);
    warrior.animationFramesLengths[STILL_LEFT] = 7;

    // Set current animations
    warrior.currentWalk = WALK_LEFT;
    warrior.currentStill = STILL_LEFT;
}

void freeWarrior() {
    if (warrior.animationFramesArray != NULL) {
        // Free each sub-array within animationFramesArray
        for (int i = 0; i < 4; i++) {
            if (warrior.animationFramesArray[i] != NULL) {
                free(warrior.animationFramesArray[i]);
                warrior.animationFramesArray[i] = NULL;
            }
        }
        // Free the main array
        free(warrior.animationFramesArray);
        warrior.animationFramesArray = NULL;
    }

    // Free the animation lengths array
    if (warrior.animationFramesLengths != NULL) {
        free(warrior.animationFramesLengths);
        warrior.animationFramesLengths = NULL;
    }
}


// Goblin Setup
Character goblin;

void setUpGoblin(int x, int y, SceneName sceneName){
    goblin.type = GOBLIN;
    
    goblin.sceneName = sceneName;
    goblin.isMoving = 0;
    
    goblin.x = x; 
    goblin.y = y;

    // Setup the direction the character is facing and looking
    goblin.facing = LEFT;
    
    // Setup the animation arrays
    goblin.animationFramesArray = (Texture2D**)malloc(5 * sizeof(Texture2D*)); // 5 animations
    goblin.animationFramesLengths = (int*)malloc(5 * sizeof(int));

    // Walk Right
    goblin.animationFramesArray[WALK_RIGHT] = (Texture2D*)malloc(6 * sizeof(Texture2D));
    fillImageArray(goblin.animationFramesArray[WALK_RIGHT], "/Goblin_red/Walk/Right", 6);
    goblin.animationFramesLengths[WALK_RIGHT] = 6;

    // Walk Left
    goblin.animationFramesArray[WALK_LEFT] = (Texture2D*)malloc(6 * sizeof(Texture2D));
    fillImageArray(goblin.animationFramesArray[WALK_LEFT], "/Goblin_red/Walk/Left", 6);
    goblin.animationFramesLengths[WALK_LEFT] = 6;

    // Still Right
    goblin.animationFramesArray[STILL_RIGHT] = (Texture2D*)malloc(7 * sizeof(Texture2D));
    fillImageArray(goblin.animationFramesArray[STILL_RIGHT], "/Goblin_red/Still/Right", 7);
    goblin.animationFramesLengths[STILL_RIGHT] = 7;

    // Still Left
    goblin.animationFramesArray[STILL_LEFT] = (Texture2D*)malloc(7 * sizeof(Texture2D));
    fillImageArray(goblin.animationFramesArray[STILL_LEFT], "/Goblin_red/Still/Left", 7);
    goblin.animationFramesLengths[STILL_LEFT] = 7;
    
    // Attack
    goblin.animationFramesArray[ATTACK] = (Texture2D*)malloc(18 * sizeof(Texture2D));
    fillImageArray(goblin.animationFramesArray[ATTACK], "/Goblin_red/Attack/All", 18);
    goblin.animationFramesLengths[ATTACK] = 18;

    // Set current animations
    goblin.currentWalk = WALK_LEFT;
    goblin.currentStill = STILL_LEFT;
}

void freeGoblin() {
    if (goblin.animationFramesArray != NULL) {
        // Free each sub-array within animationFramesArray
        for (int i = 0; i < 5; i++) {
            if (goblin.animationFramesArray[i] != NULL) {
                free(goblin.animationFramesArray[i]);
                goblin.animationFramesArray[i] = NULL;
            }
        }
        // Free the main array
        free(goblin.animationFramesArray);
        goblin.animationFramesArray = NULL;
    }

    // Free the animation lengths array
    if (goblin.animationFramesLengths != NULL) {
        free(goblin.animationFramesLengths);
        goblin.animationFramesLengths = NULL;
    }
}


#endif
