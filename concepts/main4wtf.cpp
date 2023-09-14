#include <stdio.h>
#include <stdlib.h>

class base {
public:
    virtual void please() { printf("nuh uh\n"); };
};

class derived: public base {
    public:
    void please() override {
        printf(i);
    }
    char* i = "978";
};

int main(int argc, char** argv) {
    base* pain;

    derived* whha = new derived();

    // pain = whha;

    pain->please();
    // whha->please();

    // delete whha;
    // delete pain;
    return 0;

}