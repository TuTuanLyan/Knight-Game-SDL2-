//
//  TheGhost.h
//  Knight's Challenge Game
//
//  Created by Nguyen Tu Anh Tuan.
//

#pragma once
#ifndef THE_GHOST_H
#define THE_GHOST_H

#include "Common_Items.h"
#include "BaseObject.h"
#include "PlayerObject.h"
#include "Explosion.h"

#define GHOST_SCOPE 120
#define GHOST_SPEED 10

class Ghost : public BaseObject 
{
public:
	Ghost();
	~Ghost();

	void SetGhostXpos(const int& x) { ghost_x_pos = x; }
	void SetGhostYpos(const int& y) { ghost_y_pos = y; }

	int GetGhostXpos() { return ghost_x_pos; }
	int GetGhostYpos() { return ghost_y_pos; }

	void SetGhostXval(const int& xVal) { ghost_x_val = xVal; }
	void SetGhostYval(const int& yVal) { ghost_y_val = yVal; }

	int GetGhostXval() { return ghost_x_val; }
	int GetGhostYval() { return ghost_y_val; }

	int GetFrameW() const { return frame_w; }
	int GetFrameH() const { return frame_h; }

	/*bool GetGhostCollision() const { return is_collide; }*/

	int GetGhostDamage() { return ghost_damage; }

	void SetMapXY(const int& map_x_, const int& map_y_) { map_x = map_x_; map_y = map_y_; }

	void SetGhostView();
	bool InGhostView(const int& x1, const int& x2, const int& y1, const int& y2);

	/*void SetFrame();*/
	bool LoadGhostIMG(SDL_Renderer* dst,std::string path);
	void ShowGhostClip(SDL_Renderer* dst);

	void GhostAction(MapInfor& map_data, PlayerObject& player);
	/*void GhostExplosion(SDL_Renderer* dst, const int fr);*/

private:
	int ghost_x_pos;
	int ghost_y_pos;

	int ghost_x_val;
	int ghost_y_val;

	int ghost_max_distance;

	int map_x;
	int map_y;

	int frame;

	int frame_w;
	int frame_h;

	int status;
	
	int ghost_damage;

	bool is_attacking;
	/*bool is_collide;*/

	/*Explosion explosion;*/

	Object_View Ghost_view;

};

#endif // !THE_GHOST_H
