#include "BulletObject.h"

Bullet::Bullet() {

	bullet_x_val = 0;
	bullet_y_val = 0;

	bullet_moved = 0;

	is_bullet_move = false;

	map_x = 0;
	map_y = 0;
}

Bullet::~Bullet() {
	Free();
}

void Bullet::HandleBulletMove(const int& max_val) {
	bullet_x_pos += bullet_x_val;
	bullet_y_pos += bullet_y_val;

	bullet_moved += sqrt(bullet_x_val * bullet_x_val + bullet_y_val * bullet_y_val);

	if (bullet_moved >= max_val) {
		is_bullet_move = false;
		bullet_moved = 0;
	}
}

void Bullet::Show(SDL_Renderer* dst) {
	
	rect.x = bullet_x_pos - map_x;
	rect.y = bullet_y_pos - map_y;
	BaseObject::Render(dst);
}