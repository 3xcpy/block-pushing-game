#include<stdio.h>
#include<stdint.h>

#include<raylib.h>

struct {
	uint32_t* walls;
	uint32_t* boxes;
	uint32_t* markers;
	uint32_t levelWidth, levelHeight;
	
	//player
	uint32_t px, py;
} state;

void set_wall(int x, int y, uint32_t val)
{
	state.walls[x + (y * state.levelHeight)] = val;
}

void set_box(int x, int y, uint32_t val)
{
	state.boxes[x + (y * state.levelHeight)] = val;
}

uint32_t pack_color(uint8_t r, uint8_t g, uint8_t b, uint32_t a)
{
	return (a << 24) + (b << 16) + (g << 8) + r;
}

void unpack_color(const uint32_t color, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) {
	*r = (color >> 0) & 255;
	*g = (color >> 8) & 255;
	*b = (color >> 16) & 255;
	*a = (color >> 24) & 255;
}

void draw_level(int offsetx, int offsety, int tilesizex, int tilesizey)
{
	//loop over every tile
	for (uint32_t x = 0; x < state.levelWidth; x++)
	{
		for (uint32_t y = 0; y < state.levelHeight; y++)
		{
			//Walls
			if (state.walls[x + (y * state.levelWidth)] != 0)
			{
				DrawRectangle(offsetx + (x * tilesizex), offsety + (y * tilesizey), tilesizex, tilesizey, BLACK);
			}
		}
	}
}

void update_level()
{
	//loop over every tile
	for (int32_t x = 0; x < state.levelWidth; x++)
	{
		for (int32_t y = 0; y < state.levelHeight; y++)
		{
			
		}
	}
}

void init()
{
	uint32_t t[] =
	{
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 1, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1
	};

	uint32_t tt[] =
	{
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 1, 0, 0, 0,
		0, 0, 0, 1, 1, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0
	};
	state.walls = t;
}

int main()
{
	InitWindow(400, 400, "Henlo");

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);
		draw_level(0, 0, 50, 50);
		EndDrawing();
	}

	return 0;
}