//
//  Explosion.h
//  Knight's Challenge Game
//
//  Created by Nguyen Tu Anh Tuan.
//

#pragma once
#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "Common_Items.h"
#include "BaseObject.h"

class Explosion : public BaseObject
{
public:
	Explosion();
	~Explosion();

	void SetXpos(const int& x) { ep_x_pos = x; }
	int GetXpos() const { return ep_x_pos; }

	void SetYpos(const int& y) { ep_y_pos = y; }
	int GetYpos() const { return ep_y_pos; }

	void SetCurrentFrame(const int& frame_) { frame = frame_; }

	int GetFrameW() const { return frame_w; }
	int GetFrameH() const { return frame_h; }

	void SetMapXY(const int map_x_, const int map_y_) { map_x = map_x_; map_y = map_y_; }

	bool LoadExplosionIMG(SDL_Renderer* dst);
	void ShowClip(SDL_Renderer* dst);
	void SetFrame();


private:
	int ep_x_pos;
	int ep_y_pos;

	int frame_w;
	int frame_h;

	int map_x;
	int map_y;

	int frame;
	SDL_Rect frame_clips[8];

	/*bool explo_;*/
};

#endif // !EXPLOSION_H
