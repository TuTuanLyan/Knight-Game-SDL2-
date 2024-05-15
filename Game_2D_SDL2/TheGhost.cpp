//
//  TheGhost.cpp
//  Knight's Challenge Game
//
//  Created by Nguyen Tu Anh Tuan.
//


#include "TheGhost.h"

Ghost::Ghost() {
	ghost_x_pos = 0;
	ghost_y_pos = 0;

	ghost_x_val = 0;
	ghost_y_val = 0;

	map_x = 0;
	map_y = 0;

	frame_w = 0;
	frame_h = 0;

	frame = 0;

	ghost_damage = 51;

	status = LEFT_STATUS;

	is_attacking = false;

	ghost_max_distance = 8 * TILE_SIZE;

	Ghost_view.up = 0;
	Ghost_view.down = 0;
	Ghost_view.right = 0;
	Ghost_view.left = 0;
}

Ghost::~Ghost() {
	Free();
}

void Ghost::SetGhostView() {
	Ghost_view.up = ghost_y_pos - GHOST_SCOPE;
	Ghost_view.down = ghost_y_pos + frame_h + GHOST_SCOPE;
	Ghost_view.right = ghost_x_pos + frame_w + GHOST_SCOPE;
	Ghost_view.left = ghost_x_pos - GHOST_SCOPE;
}

bool Ghost::InGhostView(const int& x1, const int& x2, const int& y1, const int& y2) {
	if (x1 > Ghost_view.right || x2 < Ghost_view.left
		|| y1 > Ghost_view.down || y2 < Ghost_view.up)
	{
		return false;
	}
	return true;
}

bool Ghost::LoadGhostIMG(SDL_Renderer* dst, std::string path) {
	bool success = BaseObject::LoadObjectIMG(dst, path.c_str());
	if (success) {
		frame_w = rect.w;
		frame_h = rect.h;
	}
	else std::cout << "Tải ảnh thất bại: " << path << '\n' << SDL_GetError() << '\n';
	return success;
}

void Ghost::ShowGhostClip(SDL_Renderer* dst) {
	if (ghost_max_distance > 0)
	{
		if (status == LEFT_STATUS) LoadGhostIMG(dst, "SDL2game_Image/Ghost_left.png");
		if (status == RIGHT_STATUS) LoadGhostIMG(dst, "SDL2game_Image/Ghost_right.png");
	}
	else return;


	rect.x = (ghost_x_pos - map_x);
	rect.y = (ghost_y_pos - map_y);

	/*SDL_Rect* CurrentFrame = &frame_clips[frame];*/
	SDL_Rect RenderQuad = { rect.x, rect.y, frame_w, frame_h };

	SDL_RenderCopy(dst, pObject, NULL, &RenderQuad);
}

void Ghost::GhostAction(MapInfor& map_data, PlayerObject& player) {
	bool player_in_view = InGhostView(player.GetPlayerXPos(), player.GetPlayerXPos() + player.GetFrameW(), player.GetPlayerYPos(), player.GetPlayerYPos() + player.GetFrameH());

	if (player_in_view) {
		is_attacking = true;
	}

	if (abs(ghost_x_pos + frame_w/2 - player.GetPlayerXPos() - player.GetFrameW()/2) < 10 &&
		abs(ghost_y_pos + frame_h/2 - player.GetPlayerYPos() - player.GetFrameH()/2) < 10)
	{
		ghost_max_distance = 0;
		/*is_collide = true*/;
		is_attacking = false;
		return;
	}

	if (is_attacking) {
		if (player.GetPlayerXPos() >= ghost_x_pos) {
			status = RIGHT_STATUS;
		}
		else if (player.GetPlayerXPos() < ghost_x_pos) {
			status = LEFT_STATUS;
		}


		int delta_x = (player.GetPlayerXPos() + player.GetFrameW() / 2) - (ghost_x_pos + frame_w / 2);
		int delta_y = (player.GetPlayerYPos() + player.GetFrameH() / 2 - 10) - (ghost_y_pos);

		double distance = (double)(sqrt(delta_x * delta_x + delta_y * delta_y));

		ghost_x_val = GHOST_SPEED * (1.0 * delta_x / distance);
		ghost_y_val = GHOST_SPEED * (1.0 * delta_y / distance);
	}

	ghost_x_pos += ghost_x_val;
	ghost_y_pos += ghost_y_val;

	ghost_max_distance -= (int)(sqrt(ghost_x_val * ghost_x_val + ghost_y_val * ghost_y_val));
	if (ghost_max_distance <= 0) {
		/*is_collide = true;*/
		is_attacking = false;
	}
}

//void Ghost::GhostExplosion(SDL_Renderer* dst,const int fr) {
//	if (ghost_max_distance <= 0)
//	{
//		explosion.LoadExplosionIMG(dst);
//		explosion.SetFrame();
//		explosion.setRect(this->rect.x + frame_w / 2, this->rect.y + frame_h / 2);
//		explosion.SetCurrentFrame(fr);
//		explosion.Render(dst);
//		explosion.Free();
//	}
//}