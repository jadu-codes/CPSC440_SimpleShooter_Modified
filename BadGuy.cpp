#include "BadGuy.h"
BadGuy::~BadGuy()
{
	al_destroy_bitmap(image);
}
BadGuy::BadGuy()
{
	image = al_create_bitmap(64, 64);
	if (!image) {
		exit(1);
	}

	al_set_target_bitmap(image);
	al_clear_to_color(al_map_rgb(0, 0, 0));

	x = 0;
	y = 0;

	al_draw_filled_rectangle(25, 10, 39, 54, al_map_rgb(100, 100, 120));
	al_draw_filled_ellipse(32, 32, 32, 16, al_map_rgb(255, 0, 255));
	al_draw_filled_circle(32, 32, 4, al_map_rgb(255, 255, 255));
	al_draw_filled_circle(16, 32, 4, al_map_rgb(120, 255, 255));
	al_draw_filled_circle(48, 32, 4, al_map_rgb(255, 255, 120));
	boundx = al_get_bitmap_width(image) * .75;
	boundy = al_get_bitmap_height(image) * .75;
	live = false;

}
void BadGuy::DrawBadGuy()
{
	if (live)
	{
		al_draw_bitmap(image, x, y, 0);
	}
}

// Helper: check if two bad guys overlap
static bool BadGuysOverlap(int ax, int ay, int abx, int aby,
	int bx, int by, int bbx, int bby)
{
	// Use bounding-box overlap
	return !(ax + abx < bx - bbx ||
		ax - abx > bx + bbx ||
		ay + aby < by - bby ||
		ay - aby > by + bby);
}

void BadGuy::StartBadGuy(int WIDTH, int HEIGHT, BadGuy others[], int numOthers, int myIndex)
{
	if (!live)
	{
		if (rand() % 500 == 0)
		{
			int tries = 0;
			bool placed = false;

			while (!placed && tries < 100)
			{
				int newX, newY;
				do {
					newX = rand() % (WIDTH - boundx);
				} while (newX < 100);
				do {
					newY = rand() % (HEIGHT - boundy);
				} while (newY < 100);

				// Check that no other live bad guy occupies the same spot
				bool overlap = false;
				for (int i = 0; i < numOthers; i++)
				{
					if (i == myIndex) continue;          // skip self
					if (!others[i].getLive()) continue;  // skip dead ones
					if (BadGuysOverlap(newX, newY, boundx, boundy,
						others[i].getX(), others[i].getY(),
						others[i].getBoundX(), others[i].getBoundY()))
					{
						overlap = true;
						break;
					}
				}

				if (!overlap)
				{
					x = newX;
					y = newY;
					live = true;
					placed = true;
				}
				tries++;
			}
		}
	}
}
