/* Butterfly class. */
#pragma once

class Butterfly {
	public:
		Butterfly();
		~Butterfly();
		void setX(int posX);
		int getX();
		void setY(int posY);
		int getY();
		void setDx(int movX);
		int getDx();
		void setDy(int movY);
		int getDy();
	private:
		int x, y; /* Screen position */
		int dx, dy; /* Movement vector */
};
