#include <iostream>
#include <stdio.h>

class Level {
protected:
    const char* spritesheet;
    char* rt;
    Level* derived;
    bool hasBeenSetup = false;
    int sprites[10];

public:
    virtual void setup() = 0;
    virtual void update() = 0;

    template <typename T>
    Level(T* derived, const char* spritesheetPath) : derived(derived), spritesheet(spritesheetPath) {
        for (int i = 0; i < 10; i++) {
            sprites[i] = 10 - i;
        }
    }

    void setRT(char* rt) {
        this->rt = rt;
    }

    void run() {
        if (!hasBeenSetup) {
            derived->setup();
            this->hasBeenSetup = true;
        }
        derived->update();
    }
};

class MainLevel: public Level {
public:
    int score = 0;

    MainLevel(): Level(this, "romfs:/gfx/sprites.t3x") {}

    void setup() {
        printf("welcome to gaming\n");
    }

    void update() {
        score++;
        printf("%d\n", score);
    }
};

class WinScreen: public Level {
public:
    WinScreen(): Level(this, "romfs:/gfx/sprites.t3x") {}

    void setup() {}

    void update() {
        printf("you win! you reached score 10\n");
    }
};

int main() {
    Level* level;

    MainLevel* mn = new MainLevel();
    WinScreen* wn = new WinScreen();

    level = mn;

    // std::cout << "HELLO???" << std::endl;
    printf("please\n");

    for (int i = 0; i < 20; i++) {
        level->update();

        if (mn->score == 10) {
            level = wn;
            level->update();
            return 0;
        } 
    }

    return 0;
}