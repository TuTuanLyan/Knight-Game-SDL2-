#pragma once
#ifndef COMMON_ITEMS_H
#define COMMON_ITEMS_H

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <map>
#include <Windows.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>


// Các biến toàn cục (g_)
const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 640;

const int FPS = 25;

#define Window_Title "Knight's Challenge Game"

static SDL_Window* g_Window = NULL;
static SDL_Renderer* g_Renderer = NULL;
static SDL_Event g_Event;
static TTF_Font* gFont = NULL;
static TTF_Font* buttonFont = NULL;

#define TILE_SIZE 64

#define PLAYER_SPEED 10;
#define PLAYER_JUMP_VALUE 15
#define TRUE_RECT_VALUE 4

#define RIGHT_STATUS 17
#define LEFT_STATUS -17


enum Game_State
{
	GAME_START = 4267,
	GAME_PLAYING = 2873,
	/*GAME_PAUSE = 1299,*/
	GAME_REPLAY = 923,
	GAME_END = 491,
	GAME_QUIT =37
};

struct MapInfor
{
	int start_x = 0;
	int start_y = 0;

	int end_x = 500*64;
	int end_y = SCREEN_HEIGHT;

	int Map_Tile_Infor[10][500];

};

struct Object_View
{
	int up;
	int down;

	int right;
	int left;
};

namespace SDL_COMMON_FUNC
{
	bool CheckCollision(SDL_Rect &object1, SDL_Rect &object2);
};

#endif

