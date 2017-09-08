#include "src/World/World.h"

int main(int argc, char *argv[]) {
    unsigned int screenWidth = 1700;
    unsigned int screenHeight = 750;

    World world(screenWidth, screenHeight);

    world.width = 6000;
    world.height = 1000;
    world.start();
}