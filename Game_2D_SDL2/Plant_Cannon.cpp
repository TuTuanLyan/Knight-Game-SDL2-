#include "Plant_Cannon.h"

Plant_Cannon::Plant_Cannon() {

	cannon_x_pos = 0;
	cannon_y_pos = 0;

	cannon_x_val = 0;
	cannon_y_val = 0;

	map_x = 0;
	map_y = 0;

	frame_w = 0;
	frame_h = 0;

	frame = 0;

	cannon_damage = 21;

	delay_attack = 0;

	is_attacking = false;

	Cannon_view.up = 0;
	Cannon_view.down = 0;
	Cannon_view.right = 0;
	Cannon_view.left = 0;

}

Plant_Cannon::~Plant_Cannon() {
	Free();
}

void Plant_Cannon::SetCannonView() {
	Cannon_view.up = cannon_y_pos - CANNON_SCOPE;
	Cannon_view.down = cannon_y_pos + frame_h + CANNON_SCOPE;
	Cannon_view.right = cannon_x_pos + frame_w + CANNON_SCOPE;
	Cannon_view.left = cannon_x_pos - CANNON_SCOPE;
}

bool Plant_Cannon::InCannonView(const int& x1, const int& x2, const int& y1, const int& y2) {
	if (x1 > Cannon_view.right || x2 < Cannon_view.left
		|| y1 > Cannon_view.down || y2 < Cannon_view.up)
	{
		return false;
	}
	return true;
}

bool Plant_Cannon::LoadCannonIMG(SDL_Renderer* dst) {
	bool success = BaseObject::LoadObjectIMG(dst, "SDL2game_Image/Plant_Cannon_Attack.png");
	if (success) {
		frame_w = rect.w / 8;
		frame_h = rect.h;
	}
	else std::cout << "Không tải được ảnh của Plant Cannon \n";
	return success;
}

void Plant_Cannon::SetFrame() {
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

void Plant_Cannon::ShowCannonClip(SDL_Renderer* dst) {
	LoadCannonIMG(dst);
	if (is_attacking) {
		if (delay_attack == 0) frame++;
		else delay_attack--;
	}
	else frame = 0;
	if (frame / 3 >= 8) frame = 0;

	rect.x = cannon_x_pos - map_x;
	rect.y = cannon_y_pos - map_y;

	SDL_Rect* CurrentFrame = &frame_clips[frame / 3];
	SDL_Rect renderQuad = { rect.x, rect.y, frame_clips[frame / 3].w, frame_clips[frame / 3].h };

	SDL_RenderCopy(dst, pObject, CurrentFrame, &renderQuad);
}

void Plant_Cannon::PlantCannonAction(MapInfor& map_data, PlayerObject& player) {
	bool player_in_view = InCannonView(player.GetPlayerXPos(), player.GetPlayerXPos() + player.GetFrameW(), player.GetPlayerYPos(), player.GetPlayerYPos() + player.GetFrameH());

	if (player_in_view) is_attacking = true;
	else is_attacking = false;

	cannon_x_val = 0;
	cannon_y_val++;
	if (cannon_y_val > 10) cannon_y_val = 10;

	int min_width = frame_w < TILE_SIZE ? frame_w : TILE_SIZE;
	int min_height = frame_h < TILE_SIZE ? frame_h : TILE_SIZE;

	int x1 = (cannon_x_pos) / TILE_SIZE;
	int x2 = (cannon_x_pos + min_width - 1) / TILE_SIZE;

	int y1 = (cannon_y_pos + cannon_y_val) / TILE_SIZE;
	int y2 = (cannon_y_pos + min_height + cannon_y_val - 1) / TILE_SIZE;

	if (cannon_y_val > 0) // Rơi tự do
	{
		if (map_data.Map_Tile_Infor[y2][x1] != 0 || map_data.Map_Tile_Infor[y2][x2] != 0) {
			cannon_y_pos = y2 * TILE_SIZE;
			cannon_y_pos -= min_height;
			cannon_y_val = 0;
			/*on_ground = true;*/
		}
	}

	/*slime_x_pos += x_val;*/
	cannon_y_pos += cannon_y_val;
}

void Plant_Cannon::HandleCannonAttack(SDL_Renderer* dst, PlayerObject& player) {
	bool player_in_view = InCannonView(player.GetPlayerXPos(), player.GetPlayerXPos() + player.GetFrameW(), player.GetPlayerYPos(), player.GetPlayerYPos() + player.GetFrameH());

	if (player_in_view) {
		if (frame == 15) {
			Bullet* pBullet = new Bullet();

			int delta_x = (player.GetPlayerXPos() + player.GetFrameW() / 2) - (cannon_x_pos + frame_w / 2);
			int delta_y = (player.GetPlayerYPos() + player.GetFrameH() / 2 - 10) - (cannon_y_pos);

			double distance = (double)(sqrt(delta_x * delta_x + delta_y * delta_y));

			pBullet->LoadObjectIMG(dst, "SDL2game_Image/Plant_Bullet.png");
			pBullet->SetBulletXpos(cannon_x_pos + (frame_w / 2) - pBullet->getRect().w / 2);
			pBullet->SetBulletYpos(cannon_y_pos - pBullet->getRect().h / 2);
			pBullet->SetBulletXval(CANNON_BULLET_SPEED * (1.0 * delta_x / distance));
			pBullet->SetBulletYval(CANNON_BULLET_SPEED * (1.0 * delta_y / distance));
			pBullet->SetBulletMove(true);
			Cannon_Bullet_List.push_back(pBullet);
		}
	}

	for (unsigned int i = 0; i < Cannon_Bullet_List.size(); i++)
	{
		Bullet* bullet = Cannon_Bullet_List[i];
		if (bullet != NULL) {
			if (bullet->GetBulletMove() == true) {
				bullet->SetMapXY(map_x, map_y); // lien tuc cap nhat map_x
				/*bullet->map_y = map_y;*/
				bullet->HandleBulletMove(8 * TILE_SIZE);
				bullet->Show(dst);
			}
			else {
				Cannon_Bullet_List.erase(Cannon_Bullet_List.begin() + i);
				if (bullet != NULL) {
					delete bullet;
					bullet = NULL;
				}
			}
		}
	}
}

void Plant_Cannon::DeleteBullet(const int& i) {
	int size_ = Cannon_Bullet_List.size();
	if (size_ > 0 && i < size_) {
		Bullet* bullet = Cannon_Bullet_List[i];
		Cannon_Bullet_List.erase(Cannon_Bullet_List.begin() + i);
		if (bullet != NULL) {
			delete bullet;
			bullet = NULL;
		}
	}
}

void Plant_Cannon::LoadCannonHp(SDL_Renderer* dst) {
	if (CannonHp < 0) CannonHp = 0;

	if (CannonHp < 73) {
		SDL_Rect fillRect = { rect.x - 4, rect.y - 8, 1.0 * CannonHp / 73 * 60  ,8 };
		SDL_SetRenderDrawColor(dst, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(dst, &fillRect);

		SDL_Rect outlineRect = { rect.x - 5, rect.y - 9, 62  ,10 };
		SDL_SetRenderDrawColor(dst, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderDrawRect(dst, &outlineRect);
	}
}