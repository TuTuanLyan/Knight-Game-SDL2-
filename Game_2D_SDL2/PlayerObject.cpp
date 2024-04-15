#include "PlayerObject.h"

PlayerObject::PlayerObject() {
	player_x_pos = 0;
	player_y_pos = 320;

	x_val = 0;
	y_val = 0;

	frame_w = 0;
	frame_h = 0;

	map_x = 0;
	map_y = 0;
	
	status = 0;

	frame = 0;

	is_motion = false;
	on_ground = false;

	is_die = false;

	WALK_LEFT = false;
	WALK_RIGHT = false;
	JUMP = false;

	bullet_dame = 21;

}

PlayerObject::~PlayerObject() {
	Free();
}

bool PlayerObject::LoadPlayerIMG(SDL_Renderer* dst, std::string path) {
	bool success = BaseObject::LoadObjectIMG(dst, path.c_str());
	if (success) {
		frame_w = rect.w / 8;
		frame_h = rect.h;
	}
	else std::cout << "Tải ảnh thất bại: " << path << '\n' << SDL_GetError() << '\n';
	return success;
}

void PlayerObject::SetFrame() {
	if (frame_w > 0 && frame_h > 0) {
		for (int i = 0; i < 8; i++) {
			frame_clips[i].x = i * frame_w;
			frame_clips[i].y = 0;
			frame_clips[i].w = frame_w;
			frame_clips[i].h = frame_h;
		}
	}
	else std::cout << "Không set được frame! \n";
}

void PlayerObject::ShowClip(SDL_Renderer* dst) {
	
	/*if (!on_ground && status == 0) LoadPlayerIMG(dst, "SDL2game_Image/jump_right.png");*/

	if (on_ground)
	{
		if (status == LEFT_STATUS) LoadPlayerIMG(dst, "SDL2game_Image/player_walk_left.png");
		if (status == RIGHT_STATUS) LoadPlayerIMG(dst, "SDL2game_Image/player_walk_right.png");
	}
	else
	{
		if (status == LEFT_STATUS) LoadPlayerIMG(dst, "SDL2game_Image/player_jump_left.png");
		if (status == RIGHT_STATUS) LoadPlayerIMG(dst, "SDL2game_Image/player_jump_right.png");
	}
	
	
	/*SetFrame();*/

	if (is_motion) frame++;
	else frame = 0;
	if (frame/2 >= 8) frame = 0;

	rect.x = (player_x_pos - map_x);
	rect.y = (player_y_pos - map_y);

	SDL_Rect* CurrentFrame = &frame_clips[frame/2];
	SDL_Rect RenderQuad = { rect.x, rect.y, frame_clips[frame/2].w, frame_clips[frame/2].h };

	SDL_RenderCopy(dst, pObject, CurrentFrame, &RenderQuad);
}


void PlayerObject::HandleEvent(SDL_Event &event, SDL_Renderer* dst) {
	
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_RIGHT:
			is_motion = true;
			WALK_RIGHT = true;
			WALK_LEFT = false;
			status = RIGHT_STATUS;
			if (on_ground) LoadPlayerIMG(dst, "SDL2game_Image/player_walk_right.png");
			else LoadPlayerIMG(dst, "SDL2game_Image/player_jump_right.png");
			break;
		case SDLK_LEFT:
			is_motion = true;
			WALK_LEFT = true;
			WALK_RIGHT = false;
			status = LEFT_STATUS;
			if (on_ground) LoadPlayerIMG(dst, "SDL2game_Image/player_walk_left.png");
			else LoadPlayerIMG(dst, "SDL2game_Image/player_jump_left.png");
			break;
		default:
			is_motion = false;
			break;
		}
	}
	else if (event.type == SDL_KEYUP) {
		switch (event.key.keysym.sym) {
		case SDLK_RIGHT:
			is_motion = false;
			WALK_RIGHT = false;
			x_val = 0;
			break;
		case SDLK_LEFT:
			is_motion = false;
			WALK_LEFT = false;
			x_val = 0;
			break;
		}
	}

	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_UP) JUMP = true;
	}

	if (event.type == SDL_MOUSEBUTTONDOWN) 
	{
		if (event.button.button == SDL_BUTTON_LEFT) {
			Bullet* pBullet = new Bullet();

			pBullet->LoadObjectIMG(dst, "SDL2game_Image/player_bullet.png");
			
			if (status == RIGHT_STATUS || status == 0)
			{
				pBullet->SetBulletXpos(player_x_pos + frame_w - 10);
				pBullet->SetBulletYpos(player_y_pos + 26);
				/*pBullet->setRect(this->rect.x + frame_w - 10, this->rect.y + 25);*/
				pBullet->SetBulletXval(24);
				pBullet->SetBulletMove(true);
			}
			else if (status == LEFT_STATUS)
			{
				pBullet->SetBulletXpos(player_x_pos + 10);
				pBullet->SetBulletYpos(player_y_pos + 26);
				/*pBullet->setRect(this->rect.x + 10, this->rect.y + 25);*/
				pBullet->SetBulletXval(-24);
				pBullet->SetBulletMove(true);
			}
			pBullet_List.push_back(pBullet);
		}
	}

}

void PlayerObject::PlayerMovement(MapInfor& map_data) {
	x_val = 0;
	y_val++;
	if (y_val >= 10) y_val = 10;

	if (WALK_LEFT) {
		x_val = -PLAYER_SPEED;
	}
	else if (WALK_RIGHT) {
		x_val = PLAYER_SPEED;
	}

	if (JUMP) {
		if (on_ground) {
			y_val = -PLAYER_JUMP_VALUE;
			on_ground = false;
		}
		JUMP = false;
		on_ground = false;
	}

	CheckCollideMap(map_data);
	PlayerOnMap(map_data);
}

void PlayerObject::CheckCollideMap(MapInfor& map_data) {
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	int min_width = frame_w < TILE_SIZE ? frame_w : TILE_SIZE;
	int min_height = frame_h < TILE_SIZE ? frame_h : TILE_SIZE;

	// Check Horizontal
	x1 = (player_x_pos + x_val) / TILE_SIZE;
	x2 = (player_x_pos + min_width + x_val  - 1) / TILE_SIZE;

	y1 = (player_y_pos) / TILE_SIZE;
	y2 = (player_y_pos + min_height - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < 500)
	{
		if (x_val < 0) // player đang di chuyển về bên trái
		{
			if (map_data.Map_Tile_Infor[y1][x1] != 0 || map_data.Map_Tile_Infor[y2][x1] != 0) {
				player_x_pos = (x1 + 1) * TILE_SIZE;
				x_val = 0;
			}
		}
		else if (x_val > 0) // player đang doi chuyển về bên phải
		{
			if (map_data.Map_Tile_Infor[y1][x2] != 0 || map_data.Map_Tile_Infor[y2][x2] != 0) {
				player_x_pos = x2 * TILE_SIZE;
				player_x_pos -= min_width;
				x_val = 0;	
			}
		}
	}

	//Check vertical
	x1 = (player_x_pos) / TILE_SIZE;
	x2 = (player_x_pos + min_width - 1) / TILE_SIZE;

	y1 = (player_y_pos + y_val) / TILE_SIZE;
	y2 = (player_y_pos + min_height + y_val - 1) / TILE_SIZE;

	if (y1 >= 0)
	{
		if (y_val > 0) // Player rơi tự do
		{
			if (map_data.Map_Tile_Infor[y2][x1] != 0 || map_data.Map_Tile_Infor[y2][x2] != 0) {
				player_y_pos = y2 * TILE_SIZE;
				player_y_pos -= min_height;
				y_val = 0;
				on_ground = true;
			}
			else if(map_data.Map_Tile_Infor[y2][x1] == 0 && map_data.Map_Tile_Infor[y2][x2] == 0){
				on_ground = false;
			}
		}
		else if (y_val < 0) // Player  nhảy
		{
			if (map_data.Map_Tile_Infor[y1][x1] != 0 || map_data.Map_Tile_Infor[y1][x2] != 0) {
				player_y_pos = (y1 + 1) * TILE_SIZE;
				y_val = 0;
			}
		}
	}

	player_x_pos += x_val;

	if (player_x_pos < 0) player_x_pos = 0;
	else if (player_x_pos + frame_w > map_data.end_x) player_x_pos = map_data.end_x - frame_w;

	player_y_pos += y_val;
	if (player_y_pos + frame_h >= SCREEN_HEIGHT) PlayerHp = 0;
}

void PlayerObject::PlayerOnMap(MapInfor& map_data) {
	map_data.start_x = player_x_pos - SCREEN_WIDTH / 2 + TILE_SIZE;
	if (map_data.start_x < 0) map_data.start_x = 0;
	else if (map_data.start_x + SCREEN_WIDTH >= map_data.end_x) map_data.start_x = map_data.end_x - SCREEN_WIDTH;
	 
	map_data.start_y = player_y_pos - SCREEN_HEIGHT / 2;
	if (map_data.start_y < 0) map_data.start_y = 0;
	else if (map_data.start_y + SCREEN_HEIGHT >= map_data.end_y) map_data.start_y = map_data.end_y - SCREEN_HEIGHT;

}

void PlayerObject::HandleFireBullet(SDL_Renderer* dst) {
	for (unsigned int i = 0; i < pBullet_List.size(); i++)
	{
		Bullet* bullet = pBullet_List[i];
		if (bullet != NULL) {
			if (bullet->GetBulletMove() == true) {
				bullet->SetMapXY(map_x, map_y); // lien tuc cap nhatp map_x
				/*bullet->map_y = map_y;*/
				bullet->HandleBulletMove(7 * TILE_SIZE);
				bullet->Show(dst);
			}
			else {
				pBullet_List.erase(pBullet_List.begin() + i);
				if (bullet != NULL) {
					delete bullet;
					bullet = NULL;
				}
			}
		}
	}
}

void PlayerObject::DelletBullet(const int& i) {
	int size_ = pBullet_List.size();
	if (size_ > 0 && i < size_) {
		Bullet* bullet = pBullet_List[i];
		pBullet_List.erase(pBullet_List.begin() + i);
		if (bullet != NULL) {
			delete bullet;
			bullet = NULL;
		}
	}
}

void PlayerObject::LoadHpStatus(SDL_Renderer* dst) {
	SDL_Rect fillRect = { 43, 25,1.0*PlayerHp/266*200 ,18};
	SDL_SetRenderDrawColor(dst, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(dst, &fillRect);

	SDL_Rect outlineRect = { 42, 24,  201 ,20};
	SDL_SetRenderDrawColor(dst, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderDrawRect(dst, &outlineRect);
}