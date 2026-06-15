#ifndef WEAPONH
#define WEAPONH
#include "BadGuy.h"
#include "player.h"
class weapon
{
public:
	weapon();
	~weapon();
	void Drawweapon();
	void Fireweapon(player& Player);
	void Updateweapon(int WIDTH, int HEIGHT);
	void Collideweapon(BadGuy BadGuys[], int cSize);
private:
	int x;
	int y;
	int boundx;
	int boundy;
	bool live;
	int speed;
	float angle;
	Direction dir;   // direction weapon is travelling
	ALLEGRO_BITMAP* image;
};
#endif
