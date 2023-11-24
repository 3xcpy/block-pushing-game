#include<stdio.h>

#include<raylib.h>

#define WORLD_WIDTH 8
#define WORLD_HEIGHT 8

#define BOX_COUNT 2

int world[WORLD_WIDTH][WORLD_HEIGHT] =
{ 
{ 0, 0, 0, 0, 0, 0, 0, 0 },
{ 1, 0, 0, 0, 0, 0, 0, 0 },
{ 1, 0, 0, 1, 0, 0, 0, 0 },
{ 1, 0, 0, 0, 0, 0, 0, 0 },
{ 1, 0, 0, 0, 1, 0, 0, 0 },
{ 1, 0, 0, 0, 0, 0, 0, 0 },
{ 1, 0, 0, 0, 0, 0, 0, 0 },
{ 1, 0, 0, 0, 0, 0, 0, 0 } 
};

typedef struct box
{
	int x;
	int y;
} box;



struct
{
	int x;
	int y;
} p;

void draw_world()
{
	int cell_size = GetRenderHeight() / WORLD_HEIGHT;

	for (int x = 0; x < WORLD_WIDTH; x++)
	{
		for (int y = 0; y < WORLD_HEIGHT; y++)
		{
			if (world[y][x] == 0)
			{
				DrawRectangle(x * cell_size, y * cell_size, cell_size, cell_size, WHITE);
			}

			if (world[y][x] == 1)
			{
				DrawRectangle(x * cell_size, y * cell_size, cell_size, cell_size, BLACK);
			}
		}
	}

	DrawRectangle(p.x * cell_size, p.y * cell_size, cell_size, cell_size, BLUE);
}

void handle_input()
{
	if (IsKeyPressed(KEY_UP))
	{
		if(world[p.y - 1][p.x] == 0)
			p.y -= 1;
	}
	if (IsKeyPressed(KEY_DOWN))
	{
		if(world[p.y + 1][p.x] == 0)
			p.y += 1;
	}
	if (IsKeyPressed(KEY_LEFT))
	{
		if(world[p.y][p.x - 1] == 0)
			p.x -= 1;
	}
	if (IsKeyPressed(KEY_RIGHT))
	{
		if(world[p.y][p.x + 1] == 0)
			p.x += 1;
	}
}

void validate_values()
{
	if (p.x < 0)
		p.x = 0;
	if (p.x > WORLD_WIDTH - 1)
		p.x = WORLD_WIDTH - 1;
	if (p.y < 0)
		p.y = 0;
	if (p.y > WORLD_HEIGHT - 1)
		p.y = WORLD_HEIGHT - 1;
}

int main()
{
	InitWindow(400, 400, "Blocks!");

	SetTargetFPS(60);

	p.x = 0;
	p.y = 0;

	while (!WindowShouldClose())
	{
		handle_input();

		validate_values();

		BeginDrawing();
		draw_world();
		EndDrawing();
	}

	return 0;
}