#ifndef IMAGINATE_C

#include "raylib.h"
#include <stdio.h>

#define RESOURCE_PATH "C:/Immortal Crusade/resources"
#define INTEL_RESOURCE_PATH "C:/Immortal Crusade/Intle_Resources"

#define IMAGINATE_C

Texture2D resizeImage(Texture2D originalImage, int newHeight) {
    float aspectRatio = (float)originalImage.width / originalImage.height;
    int newWidth = (int)(newHeight * aspectRatio);

    Image image = LoadImageFromTexture(originalImage);
    ImageResize(&image, newWidth, newHeight);

    Texture2D resizedTexture = LoadTextureFromImage(image);
    UnloadImage(image);

    return resizedTexture;
}

void fillImageArray(Texture2D *array, char *path, int count) {
    char filePath[512];
    int n = 0;
    
    // Load textures until we fail to find the next texture file
    while (n<count) {
        snprintf(filePath, sizeof(filePath), RESOURCE_PATH "/%s/%d.png", path, n + 1);
        Texture2D image = LoadTexture(filePath);
        if (image.id == 0) break;
        array[n] = image;
        n++;
    }
}

void fillImageArrayIntel(Texture2D *array, char *path, int count) {
    char filePath[512];
    int n = 0;
    
    // Load textures until we fail to find the next texture file
    while (n<count) {
        snprintf(filePath, sizeof(filePath), INTEL_RESOURCE_PATH "/%s/%d.png", path, n + 1);
        Texture2D image = LoadTexture(filePath);
        if (image.id == 0) break;
        array[n] = image;
        n++;
    }
}

void unloadImageArray(Texture2D *array, int count) {
    
    Texture2D image;
    for (int i = 0; i<count; i++) {
        image = array[i];
        if (image.id==0) break;
        UnloadTexture(image);
    }
}

void drawCharacter(Texture2D image, int x, int y) {
    DrawTexture(image, x-114, y-120, WHITE);
}

void animate(Texture2D *array, int count, int interval, int frameNo, int x, int y) {
    interval = (interval / count) * count;
    int framesPerImage = interval / count;
    int i = (frameNo % interval) / framesPerImage;
    Texture2D image = array[i];
    drawCharacter(image, x, y);
}

void drawTextBox(Rectangle box, char *text, int fontSize, Color boxColor, Color borderColor, Color textColor) {
    DrawRectangleRec(box, boxColor);
    
    DrawRectangleLinesEx(box, 2, borderColor); 
    int textWidth = MeasureText(text, fontSize);
    int textHeight = fontSize;

    Vector2 textPosition = {
        box.x + (box.width - textWidth) / 2,
        box.y + (box.height - textHeight) / 2
    };

    DrawText(text, textPosition.x, textPosition.y, fontSize, textColor);
}


#endif