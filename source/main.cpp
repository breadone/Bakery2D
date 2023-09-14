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
    void (*setup)(Level*);
    void (*update)(Level*);
    bool hasBeenSetup = false;

    Level(char* spritesheetPath, void(*setup)(Level*), void(*update)(Level*)) {
        this->setup = setup;
        this->update = update;

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

        // SPRITE 0 MUST BE THE BG

    }

    void setRenderTargets(C3D_RenderTarget* top, C3D_RenderTarget* bottom) {
        this->top = top;
        this->bottom = bottom;
    }

    // sets up the level if it hasnt been, then updates the frame
    void run() {
        if (!hasBeenSetup) {
            this->setup(this);
            this->hasBeenSetup = true;
        }
        this->update(this);
    }
};

void setupIntroLevel(Level* level) {

}
void updateIntroLevel(Level* level) {

}
Level *introLevel = new Level("romfs:/gfx/introLevel/sprites.t3x", &setupIntroLevel, &updateIntroLevel);

int main(int argc, char** argv) {
    romfsInit();
    gfxInitDefault();
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();

    C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    C3D_RenderTarget* bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);

    Level *level;

    level = introLevel;
    level->setRenderTargets(top, bottom);

    while (aptMainLoop()) {
        level->run();
    }

    return 0;
}