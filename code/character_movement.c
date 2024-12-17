#ifndef CHARACTER_MOVEMENT_C
#include "character_setup.c"
#define CHARACTER_MOVEMENT_C

void handleMovement(Character *character, Moves* moves) {
    
    int step = (character->type==WARRIOR) ? 4 : 10;
    
    if (moves->right) {
        character->x += step;
        if (!moves->left) {
            character->facing = RIGHT;
            character->currentWalk = WALK_RIGHT;
            character->currentStill = STILL_RIGHT;
            character->isMoving = 1;
        }
    }
    if (moves->left) {
        character->x -= step;
        if (!moves->right) {
            character->facing = LEFT;
            character->currentWalk = WALK_LEFT;  
            character->currentStill = STILL_LEFT;
            character->isMoving = 1;
        }
    }
    
    if (moves->up) {
        character->y -= step;
        if(!moves->down) {
            character->isMoving = 1;
        }
    }
    if (moves->down) {
        character->y += step;
        if(!moves->up) {
            character->isMoving = 1;
        }
    }
}

void chaseWarrior(Scene* scene, int frameNo, int isAvailable[10]) {

    int step = 10;
    
    // Check if the goblin is close enough to trigger DEATH scene
    if (abs(warrior.x - goblin.x) <= step && abs(warrior.y - goblin.y) <= step) {
        //(*ressurections)--;
        warrior.sceneName = DEATH;
        return;
    }

    int x, y;
   
    // Calculate the target position (x, y) based on warrior's position
    if (warrior.x > goblin.x + step) 
        x = goblin.x + step;
    else if (warrior.x < goblin.x - step) 
        x = goblin.x - step;
    else 
        x = goblin.x;

    if (warrior.y > goblin.y + step) 
        y = goblin.y + step;
    else if (warrior.y < goblin.y - step) 
        y = goblin.y - step;
    else 
        y = goblin.y;
    
   
    goblin.x = x;
    goblin.y = y;
    animate(goblin.animationFramesArray[goblin.currentWalk], 6, 36, frameNo, goblin.x, goblin.y);
}


void checkForGoblinInOtherIsland(int bx, int by, Scene* scene) {
    int directions[9][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}, {0, -1}, {-1, 0}, {-1, -1}, {1, -1}, {-1, 1}};
    int checkingBoxCoordinates[2];
    for (int i=0; i<9; i++) {
        checkingBoxCoordinates[0] = bx + directions[i][0];
        checkingBoxCoordinates[1] = by + directions[i][1];
        if (
                checkingBoxCoordinates[0]<0 || checkingBoxCoordinates[0]>=scene->boundsCols || 
                checkingBoxCoordinates[1]<0 || checkingBoxCoordinates[1]>=scene->boundsRows
            )   continue; // out of bounds
            
        int checkingBoxNumber = scene->bounds[checkingBoxCoordinates[0] + checkingBoxCoordinates[1] * scene->boundsCols];
        
        if (checkingBoxNumber<2 || checkingBoxNumber>5) continue; // not an exit
        
        SceneName exitTo = scene->exitToScenes[checkingBoxNumber-2];
        
        if (exitTo==-1) continue; // not a scene
        
        if (goblin.sceneName==exitTo) {
            goblin.sceneName = warrior.sceneName;
            goblin.x = checkingBoxCoordinates[0] * GetMonitorWidth(0) / scene->boundsCols;
            goblin.y = checkingBoxCoordinates[1] * GetMonitorHeight(0) / scene->boundsRows;
        }
        
        break;
    }
}

#endif