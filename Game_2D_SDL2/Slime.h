#pragma once
#ifndef SLIME_H
#define SLIME_H

#include "Common_Items.h"
#include "BaseObject.h"
#include "PlayerObject.h"
#include "BulletObject.h"

#define SLIME_SPEED 4
#define SlIME_BULLET_SPEED 10
#define SLIME_SCOPE 200

class Slime : public BaseObject
{
public:
	Slime();
	~Slime();

	void SetSlimeXpos(const int& x) { slime_x_pos = x; }
	int GetSlimeXpos() { return slime_x_pos; }

	void SetSlimeYpos(const int& y) { slime_y_pos = y; }
	int GetSlimeYpos() { return slime_y_pos; }

	void SetSlimeXval(const int& xVal) { x_val = xVal; }
	int GetSlimeXval() { return x_val; }

	void SetSlimeYval(const int& yVal) { y_val = yVal; }
	int GetSlimeYval() { return y_val; }

	int GetFrameW() const { return frame_w; }
	int GetFrameH() const { return frame_h; }

	void SetSlimeView();
	bool InSlimeView(const int& x1, const int& x2, const int& y1, const int& y2);
	std::vector<Bullet*> GetSlimeBulletList(const int& i) { return slime_bullet_list[i]; }
	int GetSlimeDamage() { return slime_damage; }

	void SetFrame();
	bool LoadSlimeIMG(SDL_Renderer* dst);
	void ShowSlimeClip(SDL_Renderer* dst);

	void SlimeActions(MapInfor &map_data, PlayerObject &player);
	void CheckCollideMap(MapInfor& map_data);
	void SetMapXY(const int &map_x_, const int &map_y_) { map_x = map_x_; map_y = map_y_; }

	void HandleSlimeAttack(SDL_Renderer* dst, PlayerObject &player);
	void DeleteBullet(const int& i, const int& j);

	int SlimeHp = 103;
	void LoadSlimeHp(SDL_Renderer* dst);

private:
	int slime_x_pos;
	int slime_y_pos;

	int x_val;
	int y_val;

	int map_x;
	int map_y;

	int frame_w;
	int frame_h;

	bool on_ground;
	bool is_move;
	bool is_attacking;

	int status;

	int slime_damage;

	Object_View Slime_view;

	int frame;
	SDL_Rect frame_clips[8];

	std::vector<Bullet*> slime_bullet_list[8]; // Mảng động các vector đạn 
	/*int max_S;*/
};

#endif 
