#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "imaginate.c"
#include "character_setup.c"

#ifndef INTEL_RESOURCE_PATH
#define INTEL_RESOURCE_PATH "C:/immortal_crusader/Intle_Resources"
#endif

typedef enum{
    no=0,
    yes,
    in
}State;
int screenWidth,screenHeight, count=0, intleState[4]={0,0,0,0};
bool trigger, gameOver;

Rectangle chainPos = {0, 0, 5,200};
Rectangle playpos = {10,0,10,20};
Rectangle tower={1790,540,10,10};
Vector2 intlepos={965,152};

Texture2D chainsaw[8];//stores all images of chainsaw
Texture2D intlebox[3];//stores images of the diff states of input(green grey yellow)
Texture2D nums[10];//stores img of all 10 digits to display as needed
int input[4], pass[4]; // first for storing user input, second for storing correct answer.
//Using arr of pointers for the first one because it will return null initially instead of a garbage val

void setPass(){
    int p=rand()%(9999-1000)+1000;//generating 4 digit random number
    int pt=3;
    while(p!=0){
        pass[pt]=p%10;
        p/=10;
        pt--;
    }
}
bool win(){//check if you've won
    for(int i=0;i<4;i++){
        if(intleState[i]!=yes)
            return false;
    }
    return true;
}
void drawNums(){
    int x=intlepos.x;
    for(int i=0;i<count;i++){
        DrawTexture(nums[input[i]],x+190*i,intlepos.y,WHITE);
    }
}

void drawBox(){
    int x=intlepos.x, type=no;
    for(int i=0;i<4;i++){
        type=intleState[i];
        DrawTexture(intlebox[type],x+190*i,intlepos.y,WHITE);
    }
    drawNums();
}

void drawChain(int f){
    chainPos.x += 0.8f;
    int y=535;
    for(int i=0;i<2;i++){
        DrawTexture(chainsaw[f],chainPos.x,y,WHITE);
        y+=37;
    }
}

void getGuess(){
    
    drawBox();
    int key = GetCharPressed();// Check if a key is pressed
    while (key > 0) {// Only add printable characters and limit input length
        if (key >= 48 && key <= 57 && count < 4) {//48 is key for num 0, 57 for num 9
            input[count++] = key-48;
        }
        key = GetCharPressed(); // Check next character
    }
}

void checkGuess(){
 
    for(int i=0;i<4;i++){
        if(input[i]==pass[i]){//in correct pos
            intleState[i]=yes;
            continue;
        }
        for(int j=0;j<4;j++){
            if(j!=i && input[i]==pass[j])// number is present at diff pos
                intleState[i]=in;
        }
    }
    drawBox();
}

typedef enum {
    NO_CHANGE_INTEL = 0,
    SAWED,
    SOLVED,
    PREV_SCENE_INTEL,
    EXIT_GAME_INTEL
} IntelGameState;


IntelGameState intelMain()
{   
    for(int i=0; i<4; i++) intleState[i]=0;
    count=0;
    chainPos.x=0;
    playpos.x=80;

    screenWidth = (int)GetScreenWidth();
    screenHeight = (int)GetScreenHeight();
    playpos.y=585;
    trigger = false;
    
    setPass();
    
    Texture bg=LoadTexture(INTEL_RESOURCE_PATH "/IntleBG.png");
    
    char filePath[300];
    fillImageArrayIntel(chainsaw,"MySaw", 8);
    for (int i = 0; i <10; i++) {
        snprintf(filePath, sizeof(filePath), INTEL_RESOURCE_PATH "/Nums/%d.png", i);
        nums[i] = LoadTexture(filePath);
    }
    
    intlebox[no]=LoadTexture(INTEL_RESOURCE_PATH "/Intle/no.png");
    intlebox[yes]=LoadTexture(INTEL_RESOURCE_PATH "/Intle/yes.png");
    intlebox[in]=LoadTexture(INTEL_RESOURCE_PATH "/Intle/in.png");
    
    Texture rules=LoadTexture(INTEL_RESOURCE_PATH "/rules.png");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    // Main game loop
    int cframe=0;//indicates which of the 7 frames of spinning chain is to be displayed. Each loop, the frame changes
    unsigned int frameNo = 0;
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if (playpos.x<=40) {
            return PREV_SCENE_INTEL;
        }
        
        if (chainPos.x+38 >= playpos.x) {
            gameOver = true;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
            
            if (gameOver) {
                return SAWED;
            }
            
            bool keyRight = IsKeyDown(KEY_RIGHT);
            bool keyLeft = IsKeyDown(KEY_LEFT);
            
            int prevX = playpos.x;
            
            if (keyRight && !keyLeft) { playpos.x += 4; warrior.currentWalk=WALK_RIGHT; warrior.currentStill= STILL_RIGHT;}
            else if (keyLeft && !keyRight)  { playpos.x -= 4; warrior.currentWalk=WALK_LEFT; warrior.currentStill= STILL_LEFT;}
            
            if (playpos.x>=1700) {
                playpos.x = 1700;//don't update x past 1700
                trigger = true;
            }
            // Handle backspace
            if (IsKeyPressed(KEY_BACKSPACE) && count > 0) {
                count--;
                for(int i=0;i<4;i++){
                    intleState[i]=no;//make it all grey again
                }
            }
            
            if (playpos.x<=40) {
                return PREV_SCENE_INTEL;
            }
            
            DrawTexture(bg,0,0,WHITE);
            DrawTexture(rules, 70,70,WHITE);
            
            if (prevX!=playpos.x) {
                animate(warrior.animationFramesArray[warrior.currentWalk], warrior.animationFramesLengths[warrior.currentWalk], 40, frameNo, playpos.x, playpos.y);
            } else {
                animate(warrior.animationFramesArray[warrior.currentStill], warrior.animationFramesLengths[warrior.currentStill], 40, frameNo, playpos.x, playpos.y);
            }
            
            
            if(trigger){
                drawChain(cframe);
                count<4?getGuess():checkGuess();
            }
            
            if(win()){
                return SOLVED;
            }
            
        EndDrawing();
        
        frameNo++;
        cframe = (cframe+1)%8;
    }
    
    return EXIT_GAME_INTEL;

    return 0;
}
