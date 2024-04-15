#include "Slime.h"

Slime::Slime() {
	slime_x_pos = 0;
	slime_y_pos = 0;

	x_val = 0;
	y_val = 0;

	frame_w = 0;
	frame_h = 0;

	on_ground = false;
	is_attacking = false;
	is_move = false;

	slime_damage = 17;

	Slime_view.up = 0;
	Slime_view.down = 0;
	Slime_view.right = 0;
	Slime_view.left = 0;

	frame = 0;

	status = LEFT_STATUS;

	map_x = 0;
	map_y = 0;

}

Slime::~Slime() {
	Free();
}

bool Slime::InSlimeView(const int& x1, const int& x2, const int& y1, const int& y2) {
	if (x1 > Slime_view.right || x2 < Slime_view.left 
		|| y1 > Slime_view.down || y2 < Slime_view.up) 
		/*
		x1y1_______x2y1
		.            .
		.            .
		.            .
		x1y2........x2y2
		*/

	{
		return false;
	}
	return true;
}

void Slime::SetSlimeView() {
	Slime_view.up = slime_y_pos - SLIME_SCOPE;
	Slime_view.down = slime_y_pos + frame_h + SLIME_SCOPE;
	Slime_view.right = slime_x_pos + frame_w + SLIME_SCOPE;
	Slime_view.left = slime_x_pos - SLIME_SCOPE;
}

bool Slime::LoadSlimeIMG(SDL_Renderer* dst) {
	bool success = BaseObject::LoadObjectIMG(dst, "SDL2game_Image/Slime_Attack.png");
	if (success) {
		frame_w = rect.w / 8;
		frame_h = rect.h;
	}
	else std::cout << "Không tải được ảnh của Slime \n";
	return success;
}

void Slime::SetFrame() {
	if (frame_w > 0 && frame_h > 0) {
		for (int i = 0; i < 8; i++) {
			frame_clips[i].x = i * frame_w;
			frame_clips[i].y = 0;
			frame_clips[i].w = frame_w;
			frame_clips[i].h = frame_h;
		}
	}
	else std::cout << "Frame Error! \n";
}

void Slime::ShowSlimeClip(SDL_Renderer* dst) {
	LoadSlimeIMG(dst);
	if (is_attacking) frame++;
	else frame = 0;
	if (frame/3 >= 8) frame = 0;

	rect.x = slime_x_pos - map_x;
	rect.y = slime_y_pos - map_y;

	SDL_Rect* CurrentFrame = &frame_clips[frame/3];
	SDL_Rect renderQuad = { rect.x, rect.y, frame_clips[frame/3].w, frame_clips[frame/3].h };

	SDL_RenderCopy(dst, pObject, CurrentFrame, &renderQuad);
}

void Slime::SlimeActions(MapInfor& map_data, PlayerObject &player) {
	bool player_in_view = InSlimeView(player.GetPlayerXPos(), player.GetPlayerXPos() + player.GetFrameW(), player.GetPlayerYPos(), player.GetPlayerYPos() + player.GetFrameH());
	if (player_in_view) 
	{
		is_attacking = true;
		is_move = false;
		/*x_val = 0;
		y_val = 0;*/
	}
	else 
	{
		is_attacking = false;
		is_move = true;
	}

	x_val = 0;
	y_val++;
	if (y_val > 10) y_val = 10;

	if (is_attacking)
	{
		x_val = 0;
		y_val = 0;
	}

	if (is_move) 
	{
		if (status == RIGHT_STATUS) x_val = SLIME_SPEED;
		if (status == LEFT_STATUS) x_val = -SLIME_SPEED;
	}
	

	CheckCollideMap(map_data);
}

void Slime::CheckCollideMap(MapInfor& map_data)
{
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	int min_width = frame_w <= TILE_SIZE ? frame_w : TILE_SIZE;
	int min_height = frame_h <= TILE_SIZE ? frame_h : TILE_SIZE;

	// Check Horizontal
	x1 = (slime_x_pos + x_val) / TILE_SIZE;
	x2 = (slime_x_pos + min_width + x_val - 1) / TILE_SIZE;

	y1 = (slime_y_pos) / TILE_SIZE;
	y2 = (slime_y_pos + min_height - 1) / TILE_SIZE;

	if (x_val > 0) { // Đang di chuyển về bên phải
		if (map_data.Map_Tile_Infor[y1][x2] != 0 || map_data.Map_Tile_Infor[y2][x2] != 0) {
			slime_x_pos = x2 * TILE_SIZE;
			slime_x_pos -= min_width;
			x_val = 0;
			status = LEFT_STATUS;
		}
		//Tự quay đầu khi thấy vực thẳm
		if (map_data.Map_Tile_Infor[y2 + 1][x1] == 0 || map_data.Map_Tile_Infor[y2 + 1][x2] == 0) {
			x_val = 0;
			status = LEFT_STATUS;
		}
	}
	else if (x_val < 0) { // Đang di chuyển về bên trái
		
		if (map_data.Map_Tile_Infor[y1][x1] != 0 || map_data.Map_Tile_Infor[y2][x1] != 0) {
			slime_x_pos = (x1 + 1) * TILE_SIZE;
			x_val = 0;
			status = RIGHT_STATUS;
		}
		//Tự quay đầu khi thấy vực thẳm
		if (map_data.Map_Tile_Infor[y2 + 1][x2] == 0 || map_data.Map_Tile_Infor[y2 + 1][x1] == 0) {
			x_val = 0;
			status = RIGHT_STATUS; // QUay dau sai;
		}
	}

	//Check vertical
	x1 = (slime_x_pos) / TILE_SIZE;
	x2 = (slime_x_pos + min_width - 1) / TILE_SIZE;

	y1 = (slime_y_pos + y_val) / TILE_SIZE;
	y2 = (slime_y_pos + min_height + y_val - 1) / TILE_SIZE;

	if (y_val > 0) // Rơi tự do
	{
		if (map_data.Map_Tile_Infor[y2][x1] != 0 || map_data.Map_Tile_Infor[y2][x2] != 0) {
			slime_y_pos = y2 * TILE_SIZE;
			slime_y_pos -= min_height;
			y_val = 0;
			on_ground = true;
		}
	}

	slime_x_pos += x_val;
	slime_y_pos += y_val;
}

// Slime Bullet 
void Slime::HandleSlimeAttack(SDL_Renderer* dst, PlayerObject &player) {
	bool player_in_view = InSlimeView(player.GetPlayerXPos(), player.GetPlayerXPos() + player.GetFrameW(), player.GetPlayerYPos(), player.GetPlayerYPos() + player.GetFrameH());

	/*int x = rect.x;
	int y = rect.y;*/

	if (player_in_view) {
		if (frame == 15) {
			for (int i = 0; i < 8; i++) 
			{
				Bullet* pBullet = new Bullet();

				pBullet->LoadObjectIMG(dst, "SDL2game_Image/Slime_Bullet.png");
				pBullet->SetBulletXpos(slime_x_pos + (frame_w / 2) - pBullet->getRect().w/2);
				pBullet->SetBulletYpos(slime_y_pos + (frame_h / 2) - pBullet->getRect().h/2) ;
				pBullet->SetBulletXval((double)(SlIME_BULLET_SPEED * cos(1.0 * i * M_PI / 4)));
				pBullet->SetBulletYval((double)(SlIME_BULLET_SPEED * sin(1.0 * i * M_PI / 4)));
				pBullet->SetBulletMove(true);
				slime_bullet_list[i].push_back(pBullet);
			}
		}
	}

	for (int i = 0; i < 8; i++)
	{
		for (unsigned int j = 0; j < slime_bullet_list[i].size(); j++)
		{
			Bullet* bullet = slime_bullet_list[i][j];
			if (bullet != NULL) {
				if (bullet->GetBulletMove() == true) {
					bullet->SetMapXY(map_x, map_y); // lien tuc cap nhatp map_x
					/*bullet->map_y = map_y;*/
					bullet->HandleBulletMove(4 * TILE_SIZE);
					bullet->Show(dst);
				}
				else {
					slime_bullet_list[i].erase(slime_bullet_list[i].begin() + j);
					if (bullet != NULL) {
						delete bullet;
						bullet = NULL;
					}
				}
			}
		}
	}
}

void Slime::DeleteBullet(const int& i, const int& j) {
	int size_ = slime_bullet_list[i].size();
	if (size_ > 0 && j < size_) {
		Bullet* bullet = slime_bullet_list[i][j];
		slime_bullet_list[i].erase(slime_bullet_list[i].begin() + j);
		if (bullet != NULL) {
			delete bullet;
			bullet = NULL;
		}
	}
}

void Slime::LoadSlimeHp(SDL_Renderer* dst) {
	if (SlimeHp < 0) SlimeHp = 0;

	if (SlimeHp < 103) {
		SDL_Rect fillRect = { rect.x - 8, rect.y - 10, 1.0 * SlimeHp / 103 * 70  ,8 };
		SDL_SetRenderDrawColor(dst, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(dst, &fillRect);

		SDL_Rect outlineRect = { rect.x - 9, rect.y - 11, 72  ,10 };
		SDL_SetRenderDrawColor(dst, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderDrawRect(dst, &outlineRect);
	}
}