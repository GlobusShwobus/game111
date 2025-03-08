#include "Grid.h"


bool InstancedGrid::IsFilled(int x, int y) {
	assert(x >= 0 && x < width && y >= 0 && y < height);//just crash because code err
	return is_occupied[y * width + x];
}
bool InstancedGrid::isNextFilled(int curr_x, int curr_y, NextTile move_dir) {
	vec2i nexttile = GetMoveDir(move_dir);
	curr_y += nexttile.y;
	curr_x += nexttile.x;

	assert(curr_x >= 0 && curr_x < width && curr_y >= 0 && curr_y < height);//1000% need to make a if case instead later

	return is_occupied[curr_y * width + curr_x];
}

void InstancedGrid::SetTile(int x, int y, TileState state) {//0 being free it, 1 being fill it
	assert(x >= 0 && x < width && y >= 0 && y < height);//just crash because code err
	is_occupied[y * width + x] = state;
}
void InstancedGrid::SetNextTile(NextTile move_dir, SDL_FRect* to_update) {//0 being free it, 1 being fill it
	vec2i nexttile = GetMoveDir(move_dir);

	int curr_x = to_update->x;
	int curr_y = to_update->y;

	curr_y += nexttile.y;
	curr_x += nexttile.x;


	assert(curr_x >= 0 && curr_x < width && curr_y >= 0 && curr_y < height);//will rework at somepoint lol
	//if didnt crash then

	SetTile(to_update->x, to_update->y, TileState_free);//free current


	to_update->x = curr_x;
	to_update->y = curr_y;

	is_occupied[curr_y * width + curr_x] = TileState_fill;
}

vec2i InstancedGrid::GetMoveDir(NextTile move_dir) {
	switch (move_dir) {
	case up:	   return { 0,-1 };
	case down:	   return { 0,1 };
	case left:	   return { -1,0 };
	case right:	   return { 1,0 };
	}
	return { 0,0 };//shit but don't move
}