// this file (and the makefile) exists purely to test compilation, it has no real use

#include <citro2d.h>
#include <stdlib.h>
#include <vector>

#include "../source/Sprite/Sprite.hpp"
// #include "Level/Level.hpp"

#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240
#define MAX_SPRITES   768

class Level {
public:
    Sprite sprites[MAX_SPRITES];
    C2D_SpriteSheet spritesheet;
    C3D_RenderTarget* top;
    C3D_RenderTarget* bottom;
    Level* level;
    bool hasBeenSetup = false;

    virtual void setup() = 0;
    virtual void update() = 0;

    template <typename T>
    Level(T* levelName, char* spritesheetPath) : level(levelName) {
        this->spritesheet = C2D_SpriteSheetLoad(spritesheetPath);
        size_t numImages = C2D_SpriteSheetCount(spritesheet);

        for (size_t i = 0; i < numImages; i++) {
            Sprite* thisSprite = &sprites[i];
            float x = SCREEN_WIDTH / 2;
            float y = SCREEN_HEIGHT / 2;

            C2D_SpriteFromSheet(&thisSprite->spr, spritesheet, i);
            C2D_SpriteSetCenter(&thisSprite->spr, 0.5f, 0.5f);
            thisSprite->setPosition(x, y);
        }
    }

    void setRenderTargets(C3D_RenderTarget* top, C3D_RenderTarget* bottom) {
        this->top = top;
        this->bottom = bottom;
    }

    // sets up the level if it hasnt been, then updates the frame
    void run() {
        if (!hasBeenSetup) {
            level->setup(this);
            this->hasBeenSetup = true;
        }
        level->update(this);
    }
};

struct MainLevel: public Level {
    C2D_SpriteSheet spritesheet;
    int score = 0;

    MainLevel(): Level(this, "romfs:/gfx/sprites.t3x") {}

    void setup() {
        printf("welcome to gaming\n");
    }

    void update() {
        score++;
    }
}

// Level *level;

// void changeLevel(Level* newLevel) {
//     level = newLevel;
// }

int main(int argc, char** argv) {
    romfsInit();
    gfxInitDefault();
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();

    C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    C3D_RenderTarget* bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);

    

    level = MainLevel();
    level->setRenderTargets(top, bottom);

    while (aptMainLoop()) {
        level->run();
    }

    return 0;
}