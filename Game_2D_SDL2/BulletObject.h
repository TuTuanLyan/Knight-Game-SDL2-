//
//  BulletObject.h
//  Knight's Challenge Game
//
//  Created by Nguyen Tu Anh Tuan.
//

#pragma once
#ifndef BULLET_OBJECT_H
#define BULLET_OBJECT_H

#include "Common_Items.h"
#include "BaseObject.h"

class Bullet : public BaseObject
{
public:
	Bullet();
	~Bullet();
	
	void SetBulletXval(const int& xVal) { bullet_x_val = xVal; }
	void SetBulletYval(const int& yVal) { bullet_y_val = yVal; }
	int GetBulletXval() const { return bullet_x_val; }
	int GetBulletYval() const { return bullet_y_val; }

	void SetBulletXpos(const int &x) { bullet_x_pos = x; }
	void SetBulletYpos(const int& y) { bullet_y_pos = y; }

	int GetBulletXpos() const { return bullet_x_pos; }
	int GetBulletYpos() const { return bullet_y_pos; }

	void SetBulletMove(const bool& move) { is_bullet_move = move; }
	bool GetBulletMove() const { return is_bullet_move; }

	void SetMapXY(const int& map_x_, const int& map_y_) { map_x = map_x_; map_y = map_y_; }

	void HandleBulletMove(const int& max_S);
	void Show(SDL_Renderer* dst);

	

private:

	int map_x;
	int map_y;

	int bullet_x_pos;
	int bullet_y_pos;

	int bullet_x_val;
	int bullet_y_val;

	bool is_bullet_move;

	int bullet_moved;

};

#endif
