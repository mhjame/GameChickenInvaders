#include "Spaceship.h"

spaceship::spaceship(int posX, int posY)
{
    this->posX = posX;
    this->posY = posY;
}

spaceship::spaceship() {
    posX = 0;
    posY = 0;
};

spaceship::~spaceship() {};

void spaceship::move()
{
    posX += stepX;
    posY += stepY;

    //cout << stepX << "," << stepY << endl;
}

void spaceship::turnLeft()
{
    stepX =-5;
    stepY = 0;
}

void spaceship::turnRight()
{
    stepX = 5;
    stepY = 0;
}

void spaceship::turnUp()
{
    stepY = -5;
    stepX = 0;
}

void spaceship::turnDown()
{
    stepY = 5;
    stepX = 0;
}

bool spaceship::inside(int minX, int minY, int maxX, int maxY)
{
    if(posX >= minX && posY >= minY && (posX + sizW) <= maxX && (posY + sizH) <= maxY)
        return true;
    return false;
}
