#ifndef SCENE_SETUP_C

#include <stdlib.h>
#include <time.h>

#include "scene_enum.c"
#include "scene_def.c"
#include "character_setup.c"

#define SCENE_SETUP_C

#define RESOURCE_PATH "C:/Immortal Crusade/resources"

int* getPixelCoordinates(int bx, int by, int rows, int cols) {
    static int pixelCoordinates[2];
    pixelCoordinates[0] = bx * GetMonitorWidth(0) / cols;
    pixelCoordinates[1] = by * GetMonitorHeight(0) / rows;
    return pixelCoordinates;
}

int* getBoxCoordinates(int px, int py, int rows, int cols, Direction facing) {
    static int boxCoordinates[2];
    float offset = (facing==LEFT) ? 39 : 0;
    boxCoordinates[0] = (px-offset) * cols / GetMonitorWidth(0);
    boxCoordinates[1] = py * rows/GetMonitorHeight(0);
    return boxCoordinates;
}

void exitScene(Parameters* parameters, SceneName exitTo, int nx, int ny) {
    
    drawTextBox((Rectangle){50, GetMonitorHeight(0)-75, GetMonitorWidth(0)-50*2, 75}, "Press ENTER", 30, WHITE, BLACK, BLACK);
    //Rectangle box(lx,ty, w, h), const char *text, int fontSize, Color boxColor, Color borderColor, Color textColor
    
    if (IsKeyPressed(KEY_ENTER)) {
        parameters->character->sceneName = exitTo;
        parameters->character->x = nx;
        parameters->character->y = ny;
    }
}


Texture2D phoenixFeather;
Texture2D rulesImage;
Texture2D deadQueenImage; 
Texture2D ressurectionQueenImage;
Texture2D finImage;

void setUpItemImages() {
    phoenixFeather = resizeImage(LoadTexture(RESOURCE_PATH "/UI/phoenixFeather.png"), 50);
    rulesImage = resizeImage(LoadTexture(RESOURCE_PATH "/BG/rules.png"), GetMonitorHeight(0));
    deadQueenImage = resizeImage(LoadTexture(RESOURCE_PATH "/BG/deadqueen.png"), GetMonitorHeight(0)); 
    ressurectionQueenImage = resizeImage(LoadTexture(RESOURCE_PATH "/BG/ressurection.png"), GetMonitorHeight(0));
    finImage = resizeImage(LoadTexture(RESOURCE_PATH "/BG/fin.png"), GetMonitorHeight(0));
}

void unloadItemImages() {
    UnloadTexture(phoenixFeather);
    UnloadTexture(rulesImage);
    UnloadTexture(deadQueenImage);
    UnloadTexture(ressurectionQueenImage);
    UnloadTexture(finImage);
}

Texture2D BgImages[20];
void setUpBgImages() {
    BgImages[START] = resizeImage(LoadTexture(RESOURCE_PATH "/BG/start.png"), GetMonitorHeight(0)); 
    BgImages[CI1] = resizeImage(LoadTexture(RESOURCE_PATH "/BG/cr1.png"), GetMonitorHeight(0));
    BgImages[CI2] = resizeImage(LoadTexture(RESOURCE_PATH "/BG/CI2n.png"), GetMonitorHeight(0));
    BgImages[JN1] = resizeImage(LoadTexture(RESOURCE_PATH "/BG/JN1.png"), GetMonitorHeight(0));
    BgImages[CD1] = resizeImage(LoadTexture(RESOURCE_PATH "/BG/cd1.png"), GetMonitorHeight(0));
    BgImages[CD2] = resizeImage(LoadTexture(RESOURCE_PATH "/BG/cd2.png"), GetMonitorHeight(0));
    BgImages[JN2] = resizeImage(LoadTexture(RESOURCE_PATH "/BG/JN2.png"), GetMonitorHeight(0));
    BgImages[ENEMY_BASE] = resizeImage(LoadTexture(RESOURCE_PATH "/BG/enemybase.png"), GetMonitorHeight(0));
    BgImages[CASTLE] = resizeImage(LoadTexture(RESOURCE_PATH "/BG/castle.png"), GetMonitorHeight(0));
    BgImages[QUEEN_ROOM] = resizeImage(LoadTexture(RESOURCE_PATH "/BG/queenroom.png"), GetMonitorHeight(0));
}

void unloadBgImages() {
    unloadImageArray(BgImages, 20);
}

Texture2D MAIN_MENU_BG_IMAGES[3];

void setUpMainMenu() {
    MAIN_MENU_BG_IMAGES[START_GAME] = resizeImage(LoadTexture(RESOURCE_PATH "/BG/mainmenu_start.png"), GetMonitorHeight(0));
    MAIN_MENU_BG_IMAGES[SHOW_RULES] = resizeImage(LoadTexture(RESOURCE_PATH "/BG/mainmenu_rules.png"), GetMonitorHeight(0));
    MAIN_MENU_BG_IMAGES[QUIT_GAME] = resizeImage(LoadTexture(RESOURCE_PATH "/BG/mainmenu_quit.png"), GetMonitorHeight(0));
}

Scene StartScene;

void noAction(Parameters* parameters) {}
void moveBack(Parameters* parameters) { parameters->character->x = parameters->original_x; parameters->character->y = parameters->original_y; }

void exitToCI1Bottom (Parameters* parameters) { exitScene(parameters, CI1, 820, 950);  }
void exitToCD1Right  (Parameters* parameters) { exitScene(parameters, CD1, 1800, 650); }
void exitToCD2Top    (Parameters* parameters) { exitScene(parameters, CD2, 960, 270);  }
void exitToJN2Left   (Parameters* parameters) { exitScene(parameters, JN2, 230, 600);  }

void setUpStartScene() {
    StartScene.name = START;
    
    StartScene.boundsRows = 20;
    StartScene.boundsCols = 24;
    
    static int startBounds[20][24] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,4,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
    
    StartScene.bounds = (int*) startBounds;
    
    StartScene.functionPointersLength = 6;
    static SceneFuncPointer startFunctionPointers[6] = {&noAction, &moveBack, &exitToCI1Bottom, &exitToCD1Right, &exitToCD2Top, &exitToJN2Left};
    StartScene.functionPointers = startFunctionPointers;
    
    static SceneName startExitToScenes[4] = {CI1, CD1, CD2, JN2};
    StartScene.exitToScenes = startExitToScenes;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------

typedef struct {
    char* trueClue;
    char* falseClues[3];
} ClueIsland;

Scene CI1Scene;
ClueIsland clue_island_one;

void noMovementAndResetClues(Parameters* parameters) {
    if (parameters->character->isMoving) {
        srand(time(NULL));
        *(parameters->callShowClue) = 0;
        *(parameters->isTrueClue) = 0;
        *(parameters->falseClueIndex) = rand()%3;
    }
}

void falseClue(Parameters* parameters) {
    moveBack(parameters);
    *(parameters->callShowClue) = 1;
}
void trueClue(Parameters* parameters) {
    moveBack(parameters);
    *(parameters->callShowClue) = 1;
    *(parameters->isTrueClue) = 1;
}

void exitToStartTop        (Parameters* parameters) { exitScene(parameters, START, 940, 260); }
void exitToJN1BottomMiddle (Parameters* parameters) { exitScene(parameters, JN1, 1050, 960);  }
void exitToCI2Right        (Parameters* parameters) { exitScene(parameters, CI2, 1680, 600);  }


void setUpCI1Scene() {
    CI1Scene.name = CI1;
    
    CI1Scene.boundsRows = 10;
    CI1Scene.boundsCols = 20;
    
    static int CI1Bounds[10][20] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,0,0,0,2,1,2,0,0,0,0,0,0,6,0,1},
        {1,0,0,6,6,0,0,0,0,2,0,0,0,0,6,6,0,0,0,1},
        {1,0,0,6,6,0,0,0,0,0,0,0,0,0,6,6,0,0,0,1},
        {1,1,0,0,0,0,0,0,6,6,6,0,0,0,0,0,0,0,7,1},
        {1,1,4,0,0,0,0,0,6,6,6,0,0,0,0,0,0,0,7,1},
        {1,0,6,6,0,0,0,0,0,0,0,0,0,6,6,6,6,0,0,1},
        {1,0,6,6,6,6,0,0,0,1,0,0,0,6,6,6,6,0,0,1},
        {1,0,0,0,6,6,6,0,3,1,3,0,0,0,0,0,0,0,6,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
    
    CI1Scene.bounds = (int*) CI1Bounds;
    
    CI1Scene.functionPointersLength = 8;
    static SceneFuncPointer CI1FunctionPointers[8] = {&noMovementAndResetClues, &moveBack, &exitToJN1BottomMiddle, &exitToStartTop, &exitToCI2Right, NULL, &falseClue, &trueClue};
    CI1Scene.functionPointers = CI1FunctionPointers;
    
    static SceneName CI1ExitToScenes[4] = {JN1, START, CI2, -1};
    CI1Scene.exitToScenes = CI1ExitToScenes;
    
    clue_island_one.trueClue = ("Your sacrifice is downright inverted");
    clue_island_one.falseClues[0] = ("The monster holds the key to victory");
    clue_island_one.falseClues[1] = ("Four though they may be, dull should their edge be");
    clue_island_one.falseClues[2] = ("The pumpkins may contain a secret tool");
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------

Scene CI2Scene;
ClueIsland clue_island_two;

void exitToJN1BottomLeft (Parameters* parameters) { exitScene(parameters, JN1, 430, 960); }
void exitToCD1Top        (Parameters* parameters) { exitScene(parameters, CD1, 930, 270); }
void exitToCI1Left       (Parameters* parameters) { exitScene(parameters, CI1, 260, 600); }

void setUpCI2Scene() {
    CI2Scene.name = CI2;
    
    CI2Scene.boundsRows = 10;
    CI2Scene.boundsCols = 20;
    
    static int CI2Bounds[10][20] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,0,0,0,0,2,1,2,0,0,0,0,0,0,0,1},
        {1,0,0,6,6,6,6,0,0,0,2,0,0,0,0,0,0,0,0,1},
        {1,6,6,0,0,0,0,0,0,0,0,0,0,6,6,0,0,0,0,1},
        {1,6,6,0,0,0,0,0,0,0,0,0,0,6,6,0,0,1,1,1},
        {1,0,0,7,7,7,7,0,0,0,0,0,0,0,0,0,0,5,1,1},
        {1,0,0,7,7,7,7,0,0,0,0,6,6,6,6,0,0,0,5,1},
        {1,0,0,7,7,7,7,0,0,0,1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,3,1,3,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
    
    CI2Scene.bounds = (int*) CI2Bounds;
    
    CI2Scene.functionPointersLength = 8;
    static SceneFuncPointer CI2FunctionPointers[8] = {&noAction, &moveBack, &exitToJN1BottomLeft, &exitToCD1Top, NULL, &exitToCI1Left, &falseClue, &trueClue};
    CI2Scene.functionPointers = CI2FunctionPointers;
    
    static SceneName CI2ExitToScenes[4] = {JN1, CD1, -1, CI1};
    CI2Scene.exitToScenes = CI2ExitToScenes;
    
    clue_island_two.trueClue = ("Your victory is your world inverted");
    clue_island_two.falseClues[0] = ("When in doubt, go up and about");
    clue_island_two.falseClues[1] = ("A frog-like goblin, a princess-like thee");
    clue_island_two.falseClues[2] = ("Grey is go, green is no");
}


// --------------------------------------------------------------------------------------------------------------------------------------------------------

Scene JN1Scene;

void exitToCI2Top (Parameters* parameters) { exitScene(parameters, CI2, 1030, 230); }
void exitToCI1Top (Parameters* parameters) { exitScene(parameters, CI1, 930, 230);  }
void exitToJN2Top (Parameters* parameters) { exitScene(parameters, JN2, 930, 270);  }

void setUpJN1Scene() {
    JN1Scene.name = JN1;
    
    JN1Scene.boundsRows = 10;
    JN1Scene.boundsCols = 20;
    
    static int JN1Bounds[10][20] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
        {1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,1},
        {1,0,2,1,2,0,0,0,3,1,3,0,0,0,0,0,4,1,4,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
    
    JN1Scene.bounds = (int*) JN1Bounds;
    
    JN1Scene.functionPointersLength = 5;
    static SceneFuncPointer JN1FunctionPointers[5] = {&noAction, &moveBack, &exitToCI2Top, &exitToCI1Top, &exitToJN2Top};
    JN1Scene.functionPointers = JN1FunctionPointers;
    
    static SceneName JN1ExitToScenes[4] = {CI2, CI1, JN2, -1};
    JN1Scene.exitToScenes = JN1ExitToScenes;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------

Scene JN2Scene;

void exitToJN1BottomRight (Parameters* parameters) { exitScene(parameters, JN1, 1590, 960);         }
void exitToStartRight     (Parameters* parameters) { exitScene(parameters, START, 1620, 520);       }

void exitToEnemyBaseTop   (Parameters* parameters) {  
    if (!(warrior.intelSolved)) {
            drawTextBox((Rectangle){50, GetMonitorHeight(0)-75, GetMonitorWidth(0)-50*2, 75}, "Press ENTER", 30, WHITE, BLACK, BLACK);
            
            if (IsKeyPressed(KEY_ENTER)) {
                warrior.prevSceneName = warrior.sceneName;
                warrior.sceneName = INTEL;
            }
    } else {
        exitScene(parameters, ENEMY_BASE, 1030, 240); 
    }
}

void setUpJN2Scene() {
    JN2Scene.name = JN2;
    
    JN2Scene.boundsRows = 10;
    JN2Scene.boundsCols = 20;
    
    static int JN2Bounds[10][20] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,0,0,0,0,0,0,2,1,2,0,0,0,0,0,0,0,1,1},
        {1,1,0,0,0,1,0,0,0,2,0,0,0,1,0,0,0,0,1,1},
        {1,4,0,0,0,1,0,0,1,1,1,0,0,1,0,0,0,0,0,1},
        {1,1,4,0,0,1,0,0,1,1,1,0,0,1,0,0,0,0,0,1},
        {1,1,4,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1},
        {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,3,1,3,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
    
    JN2Scene.bounds = (int*) JN2Bounds;
    
    JN2Scene.functionPointersLength = 5;
    static SceneFuncPointer JN2FunctionPointers[5] = {&noAction, &moveBack, &exitToJN1BottomRight, &exitToEnemyBaseTop, &exitToStartRight};
    JN2Scene.functionPointers = JN2FunctionPointers;
    
    static SceneName JN2ExitToScenes[4] = {JN1, ENEMY_BASE, START, -1};
    JN2Scene.exitToScenes = JN2ExitToScenes;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------

Scene CD1Scene;

void exitToCI2Bottom     ( Parameters* parameters) { exitScene(parameters, CI2, 940, 920);         }
void exitToStartFromLeft ( Parameters* parameters) { exitScene(parameters, START, 320, 520);  }

void setUpCD1Scene() {
    CD1Scene.name = CD1;
    
    CD1Scene.boundsRows = 10;
    CD1Scene.boundsCols = 20;
    
    static int CD1Bounds[10][20] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,2,1,2,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,0,1,0,1,1,0,0,0,0,0,1,1,0,0,0,1},
        {1,0,0,0,0,0,0,1,1,0,0,0,1,0,0,0,0,3,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,3,1,1},
        {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,3,1},
        {1,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1},
        {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

    
    CD1Scene.bounds = (int*) CD1Bounds;
    
    CD1Scene.functionPointersLength = 4;
    static SceneFuncPointer CD1FunctionPointers[4] = {&noAction, &moveBack, &exitToCI2Bottom, &exitToStartFromLeft};
    CD1Scene.functionPointers = CD1FunctionPointers;
    
    static SceneName CD1ExitToScenes[4] = {CI2, START, -1, -1};
    CD1Scene.exitToScenes = CD1ExitToScenes;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------

Scene CD2Scene;

void exitToStartBottom   ( Parameters* parameters) { exitScene(parameters, START, 940, 625);         }
void exitToEnemyBaseLeft ( Parameters* parameters) { 
    if (!(warrior.intelSolved)) {
        drawTextBox((Rectangle){50, GetMonitorHeight(0)-75, GetMonitorWidth(0)-50*2, 75}, "Press ENTER-", 30, WHITE, BLACK, BLACK);
        
        if (IsKeyPressed(KEY_ENTER)) {
            // drawTextBox((Rectangle){50, GetMonitorHeight(0)-500, GetMonitorWidth(0)-50*2, 75}, "Presseddd ENTER", 30, WHITE, BLACK, BLACK);
            warrior.prevSceneName = warrior.sceneName;
            warrior.sceneName = INTEL;
        }
    } else {
        exitScene(parameters, ENEMY_BASE, 300, 620);  
    }
}

void setUpCD2Scene() {
    CD2Scene.name = CD2;
    
    CD2Scene.boundsRows = 10;
    CD2Scene.boundsCols = 20;
    
    static int CD2Bounds[10][20] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,1,0,0,0,0,2,1,2,0,0,0,0,0,0,0,0,1},
        {1,0,0,1,0,1,0,0,0,2,0,0,0,0,1,0,0,0,0,1},
        {1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
        {1,0,1,1,0,0,0,1,0,0,1,0,0,0,0,0,0,3,1,1},
        {1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,3,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,3,1},
        {1,0,1,0,0,1,1,0,0,0,0,0,1,0,0,0,0,1,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

    
    CD2Scene.bounds = (int*) CD2Bounds;
    
    CD2Scene.functionPointersLength = 4;
    static SceneFuncPointer CD2FunctionPointers[4] = {&noAction, &moveBack, &exitToStartBottom, &exitToEnemyBaseLeft};
    CD2Scene.functionPointers = CD2FunctionPointers;
    
    static SceneName CD2ExitToScenes[4] = {START, ENEMY_BASE, -1, -1};
    CD2Scene.exitToScenes = CD2ExitToScenes;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------

Scene ENEMY_BASEScene;

void exitToJN2FromTop       ( Parameters* parameters) { exitScene(parameters, JN2, 860, 960 );     }
void exitToCD2FromLeft      ( Parameters* parameters) { exitScene(parameters, CD2, 1790, 650 );    }
void exitToCastleFromBottom ( Parameters* parameters) { 
    if (!(warrior.mazeSolved)) {
        drawTextBox((Rectangle){50, GetMonitorHeight(0)-75, GetMonitorWidth(0)-50*2, 75}, "Press ENTER", 30, WHITE, BLACK, BLACK);
        
        if (IsKeyPressed(KEY_ENTER)) {
            warrior.prevSceneName = warrior.sceneName;
            warrior.sceneName = MAZE;
        }
    } else {
        exitScene(parameters, CASTLE, 1030, 240 ); 
    }
    
}

void setUpENEMY_BASE() {
    ENEMY_BASEScene.name = ENEMY_BASE;
    
    ENEMY_BASEScene.boundsRows = 10;
    ENEMY_BASEScene.boundsCols = 20;
    
        static int ENEMY_BASESceneBounds[10][20] = {
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,0,0,0,0,2,1,2,0,0,0,1,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,1,0,1},
            {1,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
            {1,3,1,0,1,1,0,0,0,0,1,0,0,0,1,1,0,0,0,1},
            {1,1,3,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1},
            {1,3,0,0,0,1,0,1,1,0,0,0,0,0,0,0,1,1,0,1},
            {1,0,1,0,0,1,0,0,0,0,4,0,0,0,0,0,1,1,0,1},
            {1,0,0,0,0,0,0,0,0,4,1,4,0,1,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        };

    
    ENEMY_BASEScene.bounds = (int*) ENEMY_BASESceneBounds;
    
    ENEMY_BASEScene.functionPointersLength = 5;
    static SceneFuncPointer ENEMY_BASESceneFunctionPointers[5] = {&noAction, &moveBack, &exitToJN2FromTop, &exitToCD2FromLeft, &exitToCastleFromBottom};
    ENEMY_BASEScene.functionPointers = ENEMY_BASESceneFunctionPointers;
    
    static SceneName ENEMY_BASESceneExitToScenes[4] = {START, ENEMY_BASE, -1, -1};
    ENEMY_BASEScene.exitToScenes = ENEMY_BASESceneExitToScenes;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------

Scene CASTLEScene;

void exitToEnemyBaseBottom ( Parameters* parameters) { exitScene(parameters, ENEMY_BASE, 980, 620 ); }
void exitToQueenRoomBottom ( Parameters* parameters) { exitScene(parameters, QUEEN_ROOM, 980, 1000 ); }

void setUpCASTLE() {
    CASTLEScene.name = CASTLE;
    
    CASTLEScene.boundsRows = 10;
    CASTLEScene.boundsCols = 20;
    
        static int CASTLESceneBounds[10][20] = {
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,0,0,0,1,2,1,2,0,0,0,0,0,0,0,0},
            {1,0,0,0,0,0,0,0,0,0,2,0,0,0,1,1,1,0,1,1},
            {1,0,0,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,1,1},
            {1,1,0,0,1,1,0,1,1,1,1,1,1,1,0,0,0,0,0,0},
            {1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,1,1,1,0,0},
            {1,0,0,0,1,1,0,0,0,0,3,0,0,0,0,1,1,1,0,0},
            {1,0,1,0,1,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0},
            {1,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        };

    
    CASTLEScene.bounds = (int*) CASTLESceneBounds;
    
    CASTLEScene.functionPointersLength = 4;
    static SceneFuncPointer CASTLESceneFunctionPointers[4] = {&noAction, &moveBack, &exitToEnemyBaseBottom, &exitToQueenRoomBottom};
    CASTLEScene.functionPointers = CASTLESceneFunctionPointers;
    
    static SceneName CASTLESceneExitToScenes[4] = {ENEMY_BASE, QUEEN_ROOM, -1, -1};
    CASTLEScene.exitToScenes = CASTLESceneExitToScenes;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------

Scene QueenRoomScene;

void exitToCastleMiddle ( Parameters* parameters) { exitScene(parameters, CASTLE, 1000, 650 ); }
void goToEndScene(Parameters* parameters) { (parameters->character->sceneName) = END; }

void setUpQueenRoom() {
    QueenRoomScene.name = QUEEN_ROOM;
    
    
    QueenRoomScene.boundsRows = 19;
    QueenRoomScene.boundsCols = 32;
    
    static int QueenRoomBounds[19][32] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,0,1,1,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,1,0,1,1,1,1,1,1},
        {1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1},
        {1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1},
        {1,1,0,1,0,1,0,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,3,3,0,0,0,1,1,0,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,0,2,2,2,2,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
    
    QueenRoomScene.bounds = (int*) QueenRoomBounds;
    
    QueenRoomScene.functionPointersLength = 4;
    static SceneFuncPointer QueenRoomSceneFunctionPointers[4] = {&noAction, &moveBack, &exitToCastleMiddle, &goToEndScene};
    QueenRoomScene.functionPointers = QueenRoomSceneFunctionPointers;
    
    static SceneName QueenRoomSceneExitToScenes[4] = {CASTLE, -1, -1, -1};
    QueenRoomScene.exitToScenes = QueenRoomSceneExitToScenes;
}

#endif
