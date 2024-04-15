#include "Explosion.h"

Explosion:: Explosion() {
	ep_x_pos = 0;
	ep_y_pos = 0;

	frame_w = 0;
	frame_h = 0;

	map_x = 0;
	map_y = 0;

	frame = 0;
}

Explosion::~Explosion() {
	Free();
}

bool Explosion::LoadExplosionIMG(SDL_Renderer* dst) {
	bool success = BaseObject::LoadObjectIMG(dst, "SDL2game_Image/explosion.png");
	if (success) {
		frame_w = rect.w / 8;
		frame_h = rect.h;
	}
	else std::cout << "Tải ảnh vụ nổ thất bại! " << '\n' << SDL_GetError() << '\n';
	return success;
}

void Explosion::SetFrame() {
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

void Explosion::ShowClip(SDL_Renderer* dst) {
	rect.x = (ep_x_pos - map_x);
	rect.y = (ep_y_pos - map_y);

	SDL_Rect* CurrentFrame = &frame_clips[frame];
	SDL_Rect RenderQuad = { rect.x, rect.y, frame_clips[frame].w, frame_clips[frame].h };

	SDL_RenderCopy(dst, pObject, CurrentFrame, &RenderQuad);
}