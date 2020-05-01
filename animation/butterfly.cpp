/* Butterfly class. */

#include "butterfly.hpp"

Butterfly::Butterfly(){}
Butterfly::~Butterfly(){}
void Butterfly::setX(int posX){ x = posX; }
int Butterfly::getX(){ return x; }
void Butterfly::setY(int posY){ y = posY; }
int Butterfly::getY(){ return y; }
void Butterfly::setDx(int movX){ dx = movX; }
int Butterfly::getDx(){ return dx; }
void Butterfly::setDy(int movY){ dy = movY; }
int Butterfly::getDy(){ return dy; }
