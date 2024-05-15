//
//  PlayerObject.h
//  Knight's Challenge Game
//
//  Created by Nguyen Tu Anh Tuan.
//

#pragma once
#ifndef PLAYER_OBJECT_H
#define PLAYER_OBJECT_H

#include "Common_Items.h"
#include "BaseObject.h"
#include "GameMap.h"
#include "BulletObject.h"

class PlayerObject : public BaseObject
{
public:
	PlayerObject();
	~PlayerObject();

	bool motion() {
		return is_motion;
	}

	void SetMotion(bool motion_) { is_motion = motion_; }
	void SetFalseJump() { JUMP = false; }

	void SetPlayerXpos(const int& x) { player_x_pos = x; }
	void SetPlayerXval(const int& xVal) { x_val = xVal; }

	void SetPlayerYpos(const int& y) { player_y_pos = y; }
	void SetPlayerYval(const int& yVal) { y_val = yVal; }

	void SetDie(const bool isd) { is_die = isd; }
	bool GetDieState() const { return is_die; }

	int GetPlayerXPos() const { return player_x_pos; }
	int GetPlayerYPos() const { return player_y_pos; }

	int GetFrameW() const { return frame_w; }
	int GetFrameH() const { return frame_h; }

	void SetPlayerStatus(int state_) { status = state_; }

	bool LoadPlayerIMG(SDL_Renderer* dst, std::string path);
	void ShowClip(SDL_Renderer* dst);
	void HandleEvent(SDL_Event &event, SDL_Renderer* dst);
	void SetFrame();

	void PlayerMovement(MapInfor& map_data);
	void CheckCollideMap(MapInfor& map_data);
	void SetMapXY(const int map_x_, const int map_y_) { map_x = map_x_; map_y = map_y_; }
	void PlayerOnMap(MapInfor& map_data);

	int GetBulletDamage() { return bullet_dame; }

	void SetBulletList(std::vector<Bullet*> bullet_list_) { pBullet_List = bullet_list_; }
	std::vector<Bullet*> GetBulletList() { return pBullet_List; }
	void HandleFireBullet(SDL_Renderer* dst);

	void DelletBullet(const int& i);

	int PlayerHp = 266;

	void LoadHpStatus(SDL_Renderer* dst);

private:
	int player_x_pos;
	int player_y_pos;

	int x_val;
	int y_val;

	int frame_w;
	int frame_h;

	int map_x;
	int map_y;

	int status;

	int frame;
	SDL_Rect frame_clips[8];

	std::vector<Bullet*> pBullet_List;

	int bullet_dame;

	bool is_motion;
	bool on_ground;

	bool is_die;

	bool WALK_LEFT;
	bool WALK_RIGHT;
	bool JUMP;

};

#endif 
