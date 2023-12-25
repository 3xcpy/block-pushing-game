#include<stdio.h>
#include<stdint.h>

#include<raylib.h>

typedef enum
{
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT
} Direction;

uint32_t walls[] =
{
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1
};

uint32_t boxes[] =
{
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 1, 1, 1, 1, 0, 0,
	0, 0, 1, 0, 1, 0, 0, 0,
	0, 0, 1, 1, 1, 0, 0, 0,
	0, 0, 0, 0, 1, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0
};

struct {
	uint32_t* boxes;
	uint32_t* markers;
	uint32_t levelWidth, levelHeight;
	
	//player
	uint32_t px, py;
} state;

void set_wall(uint32_t x, uint32_t y, uint32_t val)
{
	walls[x + (y * state.levelWidth)] = val;
}

void set_box(uint32_t x, uint32_t y, uint32_t val)
{
	state.boxes[x + (y * state.levelWidth)] = val;
}

void draw_level(uint32_t offsetx, uint32_t offsety, uint32_t tilesizex, uint32_t tilesizey)
{
	//loop over every tile
	for (uint32_t y = 0; y < state.levelWidth; y++)
	{
		for (uint32_t x = 0; x < state.levelHeight; x++)
		{
			//Walls
			if (walls[x + (y * state.levelWidth)] != 0)
			{
				DrawRectangle(offsetx + (x * tilesizex), offsety + (y * tilesizey), tilesizex, tilesizey, BLACK);
			}

			if (boxes[x + (y * state.levelWidth)] != 0)
			{
				DrawRectangle(offsetx + (x * tilesizex), offsety + (y * tilesizey), tilesizex, tilesizey, BROWN);
			}
		}
	}
	
	DrawRectangle(offsetx + (state.px * tilesizex), offsety + (state.py * tilesizey), tilesizex, tilesizey, GREEN);
}

void update_level()
{
	//loop over every tile
	for (int32_t y = 0; y < state.levelWidth; y++)
	{
		for (int32_t x = 0; x < state.levelHeight; x++)
		{
			
		}
	}
}

bool push_box(uint32_t x, uint32_t y, Direction dir)
{
	uint32_t nx = x, ny = y;
	if (dir == DIR_UP)
	{
		ny -= 1;
	}
	if (dir == DIR_DOWN)
	{
		ny += 1;
	}
	if (dir == DIR_LEFT)
	{
		nx -= 1;
	}
	if (dir == DIR_RIGHT)
	{
		nx += 1;
	}

	if (walls[nx + ny * state.levelWidth] == 0 && boxes[nx + ny * state.levelWidth] == 0)
	{
		boxes[x + y * state.levelWidth] = 0;
		boxes[nx + ny * state.levelWidth] = 1;
		return true;
	}
	else if (walls[nx + ny * state.levelWidth] == 0 && boxes[nx + ny * state.levelWidth] == 1)
	{
		if (push_box(nx, ny, dir))
		{
			boxes[x + y * state.levelWidth] = 0;
			boxes[nx + ny * state.levelWidth] = 1;
			return true;
		}
	}
	return false;
}

void update_player()
{
	bool b = false;
	uint32_t tx = state.px, ty = state.py;
	Direction d;
	if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W) || IsKeyPressed(KEY_K))
	{
		ty -= 1;
		d = DIR_UP;
		b = true;
	}
	else if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S) || IsKeyPressed(KEY_J))
	{
		ty += 1;
		d = DIR_DOWN;
		b = true;
	}
	else if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_H))
	{
		tx -= 1;
		d = DIR_LEFT;
		b = true;
	}
	else if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D) || IsKeyPressed(KEY_L))
	{
		tx += 1;
		d = DIR_RIGHT;
		b = true;
	}
	
	if (b)
	{
		if (walls[tx + (ty * state.levelWidth)] == 0)
		{
			if (boxes[tx + (ty * state.levelWidth)] == 0)
			{
				state.px = tx;
				state.py = ty;
			}
			else if (boxes[tx + (ty * state.levelWidth)] == 1)
			{
				if (push_box(tx, ty, d))
				{
					state.px = tx;
					state.py = ty;
				}
			}
		}
	}
}

void update()
{
	update_player();
}

void init()
{
	state.levelWidth = 8;
	state.levelHeight = 8;

	state.px = 1;
	state.py = 1;
}

int main()
{
	InitWindow(400, 450, "Henlo");

	init();

	while (!WindowShouldClose())
	{
		update();
		BeginDrawing();
		ClearBackground(WHITE);
		draw_level(0, 50, 50, 50);
		DrawText("Hi!", 10, 10, 20, BLACK);
		EndDrawing();
	}

	return 0;
}