#include<stdio.h>
#include<stdint.h>

#include<raylib.h>

// The level Array has a "layer" for every type of tile so you can easily add more.

struct {
	uint32_t** level;
	uint32_t levelWidth, levelHeight;
	uint32_t tileCount;
	uint32_t* colors;
	
	//player
	uint32_t px, py;
} state;

void set_tile(int tile, int x, int y, int val)
{
	state.level[tile][y * state.levelWidth + x] = val;
}

void setWall(int x, int y, bool val)
{
	set_tile(0, x, y, val);
}

void setBox(int x, int y, bool val)
{
	set_tile(1, x, y, val);
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
	for (int32_t i = 0; i < state.tileCount; i++)
	{
		for (int32_t x = 0; x < state.levelWidth; x++)
		{
			for (int32_t y = 0; y < state.levelHeight; y++)
			{
				DrawRectangle(offsetx + (x * tilesizex), offsety + (y * tilesizey), tilesizex, tilesizey, BLACK);
			}
		}
	}
}

void init()
{

}

int main()
{
	InitWindow(400, 400, "Henlo");

	while (!WindowShouldClose())
	{
		BeginDrawing();
		draw_level(0, 0, 50, 50);
		EndDrawing();
	}

	return 0;
}