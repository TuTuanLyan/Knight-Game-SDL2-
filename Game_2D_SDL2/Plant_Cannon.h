//
//  Plant_Cannon.h
//  Knight's Challenge Game
//
//  Created by Nguyen Tu Anh Tuan.
//

#pragma once
#ifndef PLANT_CANNON_H
#define PLANT_CANNON_H

#include "Common_Items.h"
#include "BaseObject.h"
#include "PlayerObject.h"
#include "BulletObject.h"

#define CANNON_SCOPE 420
#define CANNON_BULLET_SPEED 20

class Plant_Cannon : public BaseObject
{
public:
	Plant_Cannon();
	~Plant_Cannon();

	void SetCannonXpos(const int& x) { cannon_x_pos = x; }
	void SetCannonYpos(const int& y) { cannon_y_pos = y; }

	int GetCannonXpos() { return cannon_x_pos; }
	int GetCannonYpos() { return cannon_y_pos; }

	void SetCannonXval(const int& xVal) { cannon_x_val = xVal; }
	void SetCannonYval(const int& yVal) { cannon_y_val = yVal; }

	int GetCannonXval() { return cannon_x_val; }
	int GetCannonYval() { return cannon_y_val; }
	
	int GetFrameW() const { return frame_w; }
	int GetFrameH() const { return frame_h; }

	std::vector<Bullet*> GetCannonBulletList() { return Cannon_Bullet_List; }

	void SetDelayAttack(const int& delay) { delay_attack = delay; }

	void SetMapXY(const int& map_x_, const int& map_y_) { map_x = map_x_; map_y = map_y_; }
	
	int GetCannonDamage() { return cannon_damage; }

	void SetCannonView();
	bool InCannonView(const int& x1, const int& x2, const int& y1, const int& y2);

	void SetFrame();
	bool LoadCannonIMG(SDL_Renderer* dst);
	void ShowCannonClip(SDL_Renderer* dst);

	void PlantCannonAction(MapInfor& map_data, PlayerObject& player);

	void HandleCannonAttack(SDL_Renderer* dst, PlayerObject &player);

	void DeleteBullet(const int& i);

	int CannonHp = 73;
	void LoadCannonHp(SDL_Renderer* dst);

private:
	int cannon_x_pos;
	int cannon_y_pos;
	
	int cannon_x_val;
	int cannon_y_val;

	int map_x;
	int map_y;

	int frame_w;
	int frame_h;

	int delay_attack;

	///*bool on_ground;*/
	//bool is_move;
	bool is_attacking;

	int cannon_damage;

	Object_View Cannon_view;

	int frame;
	SDL_Rect frame_clips[8];

	std::vector<Bullet*> Cannon_Bullet_List;

};

#endif // !PLANT_CANNON_H
