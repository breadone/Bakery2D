/*
    Level.hpp
    Bakery2D
    Created by breadone
*/

#pragma once
#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include <functional>
#include <citro2d.h>
#include "../Sprite/Sprite.hpp"

class Level {
public:
    C2D_SpriteSheet sheet;
    Level background;
    std::vector<Level> fgSprites;

    Level(void(*setup)(Level), void(*drawTop)(Level), void(*drawBottom)(Level));

    void load(const char* spritesheetFileName); 

    void setBG(Level spr);   

    std::function<void(Level)> setup;

    std::function<void(Level)> drawTop;

    std::function<void(Level)> drawBottom;

};
#endif  
