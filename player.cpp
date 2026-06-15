#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "player.h"

player::~player()
{
	al_destroy_bitmap(image);
}
player::player(int HEIGHT)
{
	image = al_create_bitmap(64, 64);
	if (!image) {
		exit(1);
	}

	al_set_target_bitmap(image);
	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_draw_filled_rectangle(0, 25, 64, 39, al_map_rgb(75, 75, 75));
	al_draw_filled_rectangle(25, 0, 39, 64, al_map_rgb(50, 50, 50));
	al_draw_circle(32, 32, 8, al_map_rgb(0, 0, 0), 5);

	al_draw_line(0, 32, 64, 32, al_map_rgb(255, 100, 255), 2);
	al_draw_line(32, 0, 32, 64, al_map_rgb(255, 100, 255), 2);
	al_draw_circle(32, 32, 16, al_map_rgb(200, 200, 200), 5);

	// Draw a directional indicator on the RIGHT side (the shooting side)
	// A yellow arrow pointing right - this side will be flipped by al_draw_bitmap flags
	al_draw_filled_triangle(48, 28, 60, 32, 48, 36, al_map_rgb(255, 255, 0));

	x = 20;
	y = HEIGHT / 2;

	speed = 7;
	boundx = al_get_bitmap_width(image);
	boundy = al_get_bitmap_height(image);
	lastDir = DIR_RIGHT;
}

void player::DrawPlayer()
{
	int flags = 0;

	// Flip bitmap based on last movement direction
	// The yellow arrow is on the RIGHT side of the original bitmap.
	// When going LEFT, flip horizontally so the arrow is on the left.
	// When going UP, flip vertically so the arrow is on top.
	// When going DOWN, flip vertically so the arrow is on bottom - but DOWN means
	// we want the indicator at the bottom, so we use ALLEGRO_FLIP_VERTICAL.
	switch (lastDir)
	{
	case DIR_RIGHT:
		flags = 0;                                          // arrow on right
		break;
	case DIR_LEFT:
		flags = ALLEGRO_FLIP_HORIZONTAL;                    // arrow on left
		break;
	case DIR_UP:
		flags = ALLEGRO_FLIP_VERTICAL;                      // arrow on top (flip vertically)
		break;
	case DIR_DOWN:
		flags = 0;                                          // arrow on bottom needs both flips
		// The arrow is on the right by default; we need it on the bottom.
		// Rotating is not allowed per instructions (use flags), so we'll combine flips:
		// ALLEGRO_FLIP_VERTICAL moves it from right->the bitmap is flipped, arrow would go left
		// Instead use ALLEGRO_FLIP_HORIZONTAL | ALLEGRO_FLIP_VERTICAL for the down direction
		flags = ALLEGRO_FLIP_HORIZONTAL | ALLEGRO_FLIP_VERTICAL;
		break;
	}

	al_draw_bitmap(image, x, y, flags);
}

void player::MoveUp()
{
	y -= speed;
	if (y < 0)
		y = 0;
	lastDir = DIR_UP;
}
void player::MoveDown(int HEIGHT)
{
	y += speed;
	if (y > HEIGHT - boundy)
		y = HEIGHT - boundy;
	lastDir = DIR_DOWN;
}
void player::MoveLeft()
{
	x -= speed;
	if (x < 0)
		x = 0;
	lastDir = DIR_LEFT;
}
void player::MoveRight(int WIDTH)
{
	x += speed;
	if (x > WIDTH - boundx)
		x = WIDTH - boundx;
	lastDir = DIR_RIGHT;
}
