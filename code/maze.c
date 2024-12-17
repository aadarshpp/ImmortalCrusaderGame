#include "raylib.h"
#include <stdlib.h>
#include <string.h>

#include "imaginate.c"
#include "character_setup.c"
#include "scene_def.c"

#define MBOUNDS_ROWS 16
#define MBOUNDS_COLS 24
#define MAZE_RESOURCE_PATH "C:\\Immortal Crusade\\Maze_Resources"

#define MAX_BOMBS 3
#define MAX_PROPS 5

typedef struct {
    int x;
    int y;
    Texture2D image;
    Texture2D explosionFrames[6];
    bool exploded;
    int explosionFrame;
    int resetTimer;
} Bomb;

typedef struct {
    int x;
    int y;
    Texture2D image;
    char clue[1000];
} Prop;

typedef struct {
    int x;
    int y;
    Texture2D image;
    bool isLocked;
    char password[20];
} Barrier;

// Maze bounds
int Mazebounds[MBOUNDS_ROWS][MBOUNDS_COLS] = {
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0},
    {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0},
    {0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0},
    {0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1},
    {0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0},
    {0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0},
    {0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}
};

// initialize bombs
void initializeBombs(Bomb *bombs) {
    int cellWidth = GetMonitorWidth(0) / MBOUNDS_COLS;
    int cellHeight = GetMonitorHeight(0) / MBOUNDS_ROWS;
    
    bombs[0].x = 17 * cellWidth+28;
    bombs[0].y = 5 * cellHeight;
    bombs[0].image = LoadTexture(MAZE_RESOURCE_PATH "\\BG\\bomb1.png");
    fillImageArray(bombs[0].explosionFrames, "Tiny Swords (Update 010)/Effects/Explosion", 6);
    bombs[0].exploded = false;
    bombs[0].explosionFrame = 0;

    bombs[1].x = 12 * cellWidth;
    bombs[1].y = 8 * cellHeight;
    bombs[1].image = LoadTexture(MAZE_RESOURCE_PATH "\\BG\\bomb2.png");
    fillImageArray(bombs[1].explosionFrames, "Tiny Swords (Update 010)/Effects/Explosion", 6);
    bombs[1].exploded = false;
    bombs[1].explosionFrame = 0;
    
    bombs[2].x = 21 * cellWidth-20;
    bombs[2].y = 13 * cellHeight-25;
    bombs[2].image = LoadTexture(MAZE_RESOURCE_PATH "\\BG\\bomb3.png");
    fillImageArray(bombs[2].explosionFrames, "Tiny Swords (Update 010)/Effects/Explosion", 6);
    bombs[2].exploded = false;
    bombs[2].explosionFrame = 0;
}

int explosionCount = 0;
// draw and update bombs
void handleBombs(Bomb bombs[], int count, Character *character) {
    int cellWidth = GetMonitorWidth(0) / MBOUNDS_COLS;
    int cellHeight = GetMonitorHeight(0) / MBOUNDS_ROWS;

    int gridX = character->x / cellWidth;
    int gridY = character->y / cellHeight;

    for (int i = 0; i < count; i++) {
        int bombGridX = bombs[i].x / cellWidth;
        int bombGridY = bombs[i].y / cellHeight;
        if (!bombs[i].exploded && gridX == bombGridX && gridY == bombGridY) {
            bombs[i].exploded = true;
            explosionCount++;
            character->x = 215;
            character->y = 175;
            bombs[i].explosionFrame = 0;
            bombs[i].resetTimer = 180;
        }

        if (bombs[i].exploded) {
            if (bombs[i].explosionFrame < 36) {
                animate(bombs[i].explosionFrames, 6, 36, bombs[i].explosionFrame, bombs[i].x, bombs[i].y);
                bombs[i].explosionFrame++;
            } else if (bombs[i].resetTimer > 0) {
                bombs[i].resetTimer--;
                char countdownText[10];
                sprintf(countdownText, "%d", bombs[i].resetTimer / 60);
                DrawText(countdownText, bombs[i].x + 10, bombs[i].y - 20, 20, RED);
            } else {
                // Reset bomb
                bombs[i].exploded = false;
                bombs[i].explosionFrame = 0;
            }
        } else {
            DrawTexture(bombs[i].image, bombs[i].x, bombs[i].y, WHITE);
        }
    }
}

// initialize props
void initializeProps(Prop *props, int count) {
    int cellWidth = GetMonitorWidth(0) / MBOUNDS_COLS;
    int cellHeight = GetMonitorHeight(0) / MBOUNDS_ROWS;

    props[0].x = 8 * cellWidth;
    props[0].y = 3 * cellHeight;
    props[0].image = LoadTexture(MAZE_RESOURCE_PATH "\\BG\\prop1.png");
    strcpy(props[0].clue, "WELCOME! Search for clues that will lead you out of the maze.\nBeware of bombs.Your life will end after encountering 3 bombs.\n");

    props[1].x = 8 * cellWidth;
    props[1].y = 12 * cellHeight;
    props[1].image = LoadTexture(MAZE_RESOURCE_PATH "\\BG\\prop2.png");
    strcpy(props[1].clue, "The scroll reads: 'ezmerelda'");
    
    props[2].x = 18 * cellWidth;
    props[2].y = 2 * cellHeight;
    props[2].image = LoadTexture(MAZE_RESOURCE_PATH "\\BG\\prop3.png");
    strcpy(props[2].clue, "*nom nom*'");
    
    props[4].x = 4 * cellWidth;
    props[4].y = 10 * cellHeight;
    props[4].image = LoadTexture(MAZE_RESOURCE_PATH "\\BG\\prop4.png");
    strcpy(props[4].clue, "I am the friendly pumpkin :)");
}


void handleProps(Prop props[], int count, Character *character) {
    int cellWidth = GetMonitorWidth(0) / MBOUNDS_COLS;
    int cellHeight = GetMonitorHeight(0) / MBOUNDS_ROWS;

    int gridX = character->x / cellWidth;
    int gridY = character->y / cellHeight;

    for (int i = 0; i < count; i++) {
        int propGridX = props[i].x / cellWidth;
        int propGridY = props[i].y / cellHeight;
        // Draw the prop
        DrawTexture(props[i].image, props[i].x, props[i].y, WHITE);
        if (abs(gridX - propGridX) <= 0 && abs(gridY - propGridY) <= 0) {
            int bannerWidth = MeasureText(props[i].clue, 20) + 20;
            int numLines = 1;
            int lineHeight = 25;
            for (char *c = props[i].clue; *c != '\0'; c++) {
                if (*c == '\n') numLines++;
            }
            int bannerHeight = lineHeight * numLines + 20;
            int bannerX = props[i].x + 20;
            int bannerY = props[i].y - bannerHeight - 10;
            DrawRectangle(bannerX, bannerY, bannerWidth, bannerHeight, Fade(BLACK, 0.7));

            DrawText(props[i].clue, bannerX + 10, bannerY + 10, 20, YELLOW);
        }
    }
}

void handleCharacterMovement(Character *character, int *move, Moves *moves, int bounds[MBOUNDS_ROWS][MBOUNDS_COLS]) {
    int newX = character->x;
    int newY = character->y;

    if (moves->right) {
        newX += 4;
        character->currentWalk = WALK_RIGHT;
        character->currentStill = STILL_RIGHT;
    }
    if (moves->left) {
        newX -= 4;
        character->currentWalk = WALK_LEFT;
        character->currentStill = STILL_LEFT;
    }
    if (moves->up) {
        newY -= 4;
    }
    if (moves->down) {
        newY += 4;
    }

    int cellWidth = GetMonitorWidth(0) / MBOUNDS_COLS;
    int cellHeight = GetMonitorHeight(0) / MBOUNDS_ROWS;
    int gridX = (newX-39) / cellWidth;
    int gridX_left = newX / cellWidth;
    int gridY = newY / cellHeight;

    if (newX >= 30 && newY>=60 && gridX >= 0 && gridX < MBOUNDS_COLS && gridX_left >= 0 && gridX_left < MBOUNDS_COLS && gridY >= 0 && gridY < MBOUNDS_ROWS) {
        if ((bounds[gridY][gridX] == 0) && (bounds[gridY][gridX_left] == 0)) {
            character->x = newX;
            character->y = newY;
        }
    }

    char debugMsg[100];
    sprintf(debugMsg, "Pos: (%d, %d), Grid: (%d, %d), Cell: %d",
            character->x, character->y, gridX, gridY, bounds[gridY][gridX]);
    DrawText(debugMsg, 10, 10, 20, WHITE);

    *move = (moves->right ^ moves->left) || (moves->up ^ moves->down);
}

void sceneBuilder(Texture2D bgImage, Character *character, int frameNo, int *move, Bomb bombs[], int bombCount, Prop props[], int propCount) {
    DrawTexture(bgImage, 0, 0, WHITE);

    Moves movesClicked = {
        IsKeyDown(KEY_RIGHT),
        IsKeyDown(KEY_LEFT),
        IsKeyDown(KEY_UP),
        IsKeyDown(KEY_DOWN)
    };

    handleCharacterMovement(character, move, &movesClicked, Mazebounds);

    // Handle all bombs
    handleBombs(bombs, bombCount, character);
    handleProps(props, propCount, character);

    if (*move)
        animate(warrior.animationFramesArray[warrior.currentWalk], warrior.animationFramesLengths[warrior.currentWalk], 40, frameNo, character->x, character->y);
    else
        animate(warrior.animationFramesArray[warrior.currentStill], warrior.animationFramesLengths[warrior.currentStill], 40, frameNo, character->x, character->y);

    *move = 0;
}

void initializeBarrier(Barrier *barrier) {
    int cellWidth = GetMonitorWidth(0) / MBOUNDS_COLS;
    int cellHeight = GetMonitorHeight(0) / MBOUNDS_ROWS;

    barrier->x = 22 * cellWidth;
    barrier->y = 9 * cellHeight+2; 
    barrier->image = LoadTexture(MAZE_RESOURCE_PATH "\\BG\\barrier.png");
    barrier->isLocked = true;
    strcpy(barrier->password, "ezmerelda");
}

void handleBarrier(Barrier *barrier, Character *character, bool *passwordPrompt, char *inputPassword) {
    int cellWidth = GetMonitorWidth(0) / MBOUNDS_COLS;
    int cellHeight = GetMonitorHeight(0) / MBOUNDS_ROWS;

    int gridX = character->x / cellWidth;
    int gridY = character->y / cellHeight;

    int barrierGridX = barrier->x / cellWidth;
    int barrierGridY = barrier->y / cellHeight;

    if (barrier->isLocked && gridX == barrierGridX && gridY == barrierGridY) {
        *passwordPrompt = true;
        character->x = 1725;
    } 
    
    if (character->x<1722) *passwordPrompt = false;

    if (barrier->isLocked) {
        DrawTexture(barrier->image, barrier->x, barrier->y, WHITE);
    }

    if (*passwordPrompt) {
        DrawRectangle(1400, 500, 400, 100, Fade(BLACK, 0.7));
        DrawText("Enter Password:", 1420, 520, 20, WHITE);
        DrawRectangleLines(1410, 560, 380, 30, WHITE);
        DrawText(inputPassword, 1420, 565, 20, WHITE);

        if (IsKeyPressed(KEY_ENTER)) {
            if (strcmp(inputPassword, barrier->password) == 0) {
                barrier->isLocked = false;  // Unlock the barrier
                *passwordPrompt = false;   // Hide the prompt
                strcpy(inputPassword, ""); // Clear input
            } else {
                DrawText("Incorrect Password!", 1420, 500, 20, RED);
            }
        }
    }
}

typedef enum {
    NO_CHANGE_MAZE=0,
    BOMBED,
    OUT_OF_MAZE,
    PREV_SCENE_MAZE,
    EXIT_GAME_MAZE
} MazeGameState;

MazeGameState mazeMain() {
    
    Texture2D bgImage = resizeImage(LoadTexture(MAZE_RESOURCE_PATH "/BG/maze.png"), GetMonitorHeight(0));

    Bomb bombs[MAX_BOMBS];
    initializeBombs(bombs);
    
    Prop props[MAX_PROPS];
    initializeProps(props, MAX_PROPS);
    
    Barrier barrier;
    char inputPassword[20] = "";
    bool passwordPrompt = false;
    initializeBarrier(&barrier);


    int move = 0;
    int frameNo = 0;
    
    warrior.x = 215;
    warrior.y = 175;

    while (!WindowShouldClose()) {
        frameNo++;

        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        if (warrior.x<60) return PREV_SCENE_MAZE;
        if (warrior.x>1915) return OUT_OF_MAZE;
        
        sceneBuilder(bgImage, &warrior, frameNo, &move, bombs, MAX_BOMBS,props, MAX_PROPS);
        handleBarrier(&barrier, &warrior, &passwordPrompt, inputPassword);

        if (passwordPrompt) {
            int key = GetCharPressed();
            if ((key >= 32) && (key <= 125) && strlen(inputPassword) < 19) {
                int len = strlen(inputPassword);
                inputPassword[len] = (char)key;
                inputPassword[len + 1] = '\0';
            }

            if (IsKeyPressed(KEY_BACKSPACE) && strlen(inputPassword) > 0) {
                inputPassword[strlen(inputPassword) - 1] = '\0';
            }
        }

        // Game over
        if (explosionCount >= 3) {
            return BOMBED;
        }

        EndDrawing();
    }

    for (int i = 0; i < MAX_BOMBS; i++) {
        unloadImageArray(bombs[i].explosionFrames, 6);
        UnloadTexture(bombs[i].image);
    }
    
    for (int i = 0; i < MAX_PROPS; i++) {
    UnloadTexture(props[i].image);
    }
    
    UnloadTexture(barrier.image);

    UnloadTexture(bgImage);
    
    return EXIT_GAME_MAZE;

    return 0;
}

