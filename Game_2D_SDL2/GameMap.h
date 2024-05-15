//
//  GameMap.h
//  Knight's Challenge Game
//
//  Created by Nguyen Tu Anh Tuan.
//

#pragma once
#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "Common_Items.h"
#include "BaseObject.h"

class GameMap
{
public:
	GameMap() { ; }
	~GameMap() { ; }

	MapInfor GetMapInfor() { return map_data; }
	void SetMap(MapInfor& map_after) { map_data = map_after; }

	void SetInforMap(std::string);
	bool LoadBlockIMG(SDL_Renderer* dst);
	void DrawMap(SDL_Renderer* dst);


private:
	BaseObject Block_Map;
	MapInfor map_data;

};


#endif