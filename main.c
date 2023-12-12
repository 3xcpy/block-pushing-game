#include<stdio.h>

#include<raylib.h>

struct {
	bool** level;
	int levelWidth, levelHeight;
	
	//player
	int px, py;
} state;

void setWall(int x, int y, bool val)
{
	state.level[0][y * state.levelWidth + x];
}

int main()
{
	return 0;
}