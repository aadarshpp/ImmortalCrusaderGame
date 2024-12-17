#ifndef SCENE_ENUM

#define SCENE_ENUM

// Enum for scene types
typedef enum {
    MAINMENU=0,
    RULES,
    
    START,
    CI1,
    CI2,
    JN1,
    JN2,
    CD1,
    CD2,
    ENEMY_BASE,
    CASTLE,
    QUEEN_ROOM,
    
    INTEL,
    MAZE,
    
    DEATH,
    GAMEOVER,
    STARTING_POINT_DEATH_END,
    END,
    
    X
} SceneName;

// Enum for main menu options
typedef enum {
    START_GAME,
    SHOW_RULES,
    QUIT_GAME
} MainMenuOptions;

#endif