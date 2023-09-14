#include "Level.hpp"

Level::Level(void(*setup)(Level), void(*drawTop)(Level), void(*drawBottom)(Level)) {
    this->setup = *setup;
    this->drawTop = *drawTop;
    this->drawBottom = *drawBottom;
}

void Level::load(const char* spritesheetFileName) {
    // load spritesheet
    this->sheet = C2D_SpriteSheetLoad(spritesheetFileName);
    if (!this->sheet) { svcBreak(USERBREAK_PANIC); }

    // load sprites
    size_t numImages = C2D_SpriteSheetCount(this->sheet);

	for (size_t i = 0; i < numImages; i++) {
		Sprite* thisSprite = &fgSprites[i];
		float x = 400 / 2;
		float y = 240 / 2;

		C2D_SpriteFromSheet(&thisSprite->spr, this->sheet, i);
		C2D_SpriteSetCenter(&thisSprite->spr, 0.5f, 0.5f);
        thisSprite->setPosition(x, y);
	}

    *(this.setup)();
}

void Level::setBG(Sprite spr) {
    this->background = spr;
}