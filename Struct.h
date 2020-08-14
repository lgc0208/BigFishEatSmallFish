#pragma once

struct player
{
	int x;
	int y;
	bool live = true;
	int size = 1;
	int score = 0;
};

struct fish
{
	int x;
	int y;
	int size;
	bool live = true;
};