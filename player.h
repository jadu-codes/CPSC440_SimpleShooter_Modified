#ifndef PLAYERH
#define PLAYERH
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>

// Direction the player last moved (for flipping bitmap and firing direction)
enum Direction { DIR_RIGHT, DIR_LEFT, DIR_UP, DIR_DOWN };

class player
{
public:
	player(int HEIGHT);
	~player();
	void DrawPlayer();
	void MoveUp();
	void MoveDown(int HEIGHT);
	void MoveLeft();
	void MoveRight(int WIDTH);
	int getBoundX() { return boundx; }
	int getBoundY() { return boundy; }
	int getX() { return x; }
	int getY() { return y; }
	void SetX(int nx) { x = nx; }
	void SetY(int ny) { y = ny; }
	Direction getDirection() { return lastDir; }
private:
	int x;
	int y;
	int speed;
	int boundx;
	int boundy;
	Direction lastDir;
	ALLEGRO_BITMAP* image;
};
#endif
