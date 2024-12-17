#ifndef SCENE_BUILDER_C

#include "raylib.h"
#include "scene_setup.c"
#include "character_setup.c"
#include "character_movement.c"

#include <stdio.h>

#define SCENE_BUILDER_C

void showClue(int showTrueClue, char* trueClue, char** falseClues, int falseClueIndex) {
    
    char* clue;
    if (showTrueClue) {
        clue = trueClue;
    } else {
        clue = falseClues[falseClueIndex];
    }
    
    drawTextBox((Rectangle){50, GetMonitorHeight(0)-75, GetMonitorWidth(0)-50*2, 75}, clue, 30, WHITE, BLACK, BLACK);
    //Rectangle box, const char *text, int fontSize, Color boxColor, Color borderColor, Color textColor
}

void buildScene(Scene* scene, Character* warriorPointer, int frameNo, int ressurections) {
    DrawTexture(BgImages[scene->name] , 0, 0, WHITE);
    for (int i=0; i<ressurections; i++) DrawTexture(phoenixFeather, 60 + phoenixFeather.width*i, 10, WHITE);
    
    static int callShowClue = 0;
    static int falseClueIndex = 0;
    static int isTrueClue = 0;
    
    int original_x = warriorPointer->x;
    int original_y = warriorPointer->y;
    
    Moves movesClicked = {IsKeyDown(KEY_RIGHT), IsKeyDown(KEY_LEFT), IsKeyDown(KEY_UP), IsKeyDown(KEY_DOWN), IsKeyPressed(KEY_ENTER)};
    handleMovement(warriorPointer, &movesClicked);
    
    int* boxCoordinates = getBoxCoordinates(warriorPointer->x, warriorPointer->y, scene->boundsRows, scene->boundsCols, warriorPointer->facing);
    int box = scene->bounds[boxCoordinates[0] + boxCoordinates[1]*scene->boundsCols];
    
    if (box==0) {
        boxCoordinates = getBoxCoordinates(warriorPointer->x, warriorPointer->y, scene->boundsRows, scene->boundsCols, !warriorPointer->facing);
        box = scene->bounds[boxCoordinates[0] + boxCoordinates[1]*scene->boundsCols];
    }
    
    char msg[100];
    sprintf(msg, "%d %d\n%d %d\n%d\n", (warriorPointer->x), (warriorPointer->y), boxCoordinates[0], boxCoordinates[1], box);
    DrawText(msg, 10, 10, 40, WHITE);
    
    Parameters parameters = {warriorPointer, &callShowClue, &isTrueClue, &falseClueIndex, original_x, original_y};
    if (callShowClue && (warriorPointer->sceneName==CI1 || warriorPointer->sceneName==CI2)) {
        ClueIsland clueIsland = (warriorPointer->sceneName==CI1) ? clue_island_one : clue_island_two;
        showClue(isTrueClue, clueIsland.trueClue, clueIsland.falseClues, falseClueIndex);
    }
    
    if (box>=0 && box<scene->functionPointersLength && scene->functionPointers[box]!=NULL)
        scene->functionPointers[box](&parameters);
    
    if (warriorPointer->isMoving)
        animate(warriorPointer->animationFramesArray[warriorPointer->currentWalk], 6, 36, frameNo, warriorPointer->x, warriorPointer->y);
    else
        animate(warriorPointer->animationFramesArray[warriorPointer->currentStill], 7, 21, frameNo, warriorPointer->x, warriorPointer->y);
    
    warriorPointer->isMoving = 0;
    
    int isAvilableForMovement[10] = {1, 0, 1, 1, 1, 1, 0, 0, 0, 0};
    
    if (goblin.sceneName==warriorPointer->sceneName) {
        chaseWarrior(scene, frameNo, isAvilableForMovement);
    } else {
        checkForGoblinInOtherIsland(boxCoordinates[0], boxCoordinates[1], scene);
    }

}

#endif