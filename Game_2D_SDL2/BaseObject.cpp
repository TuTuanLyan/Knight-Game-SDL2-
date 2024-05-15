//
//  BaseObject.cpp
//  Knight's Challenge Game
//
//  Created by Nguyen Tu Anh Tuan.
//


// Bất kì đối tượng nào kế thừa class BaseObject đều có thể sử dụng được render và load img cùng với đó là giải phóng bộ nhớ khi chương trình kết thúc

#include "BaseObject.h"

BaseObject::BaseObject() {
	pObject = NULL;
	rect.x = 0;
	rect.y = 0;
	rect.w = 0;
	rect.h = 0;
}

BaseObject::~BaseObject() { ; }

bool BaseObject::LoadObjectIMG(SDL_Renderer* screen, std::string path){
	Free();
	
	SDL_Texture * newTexture = NULL;
	SDL_Surface* loadedIMG = IMG_Load(path.c_str());
	if (loadedIMG == NULL) {
		std::cout << "Không tải được ảnh: " << path << '\n' << IMG_GetError();
		return false;
	}	
	else
	{
		SDL_SetColorKey(loadedIMG, SDL_TRUE, SDL_MapRGB(loadedIMG->format, 167, 175, 180)/*|SDL_MapRGB(loadedIMG->format, 0, 3, 9)*/);
		newTexture = SDL_CreateTextureFromSurface(screen, loadedIMG);
		if (newTexture == NULL)
			std::cout << "Không chuyển đổi được từ Surface sang texture: " << path << "\n" << SDL_GetError();
		else
		{
			// lấy thông số của ảnh
			rect.w = loadedIMG->w;
			rect.h = loadedIMG->h;
		}
		SDL_FreeSurface(loadedIMG);
	}
	pObject = newTexture;
	return pObject != NULL;
}

void BaseObject::Render(SDL_Renderer* dst, const SDL_Rect* clip) {
	SDL_Rect renderquad = { rect.x, rect.y, rect.w, rect.h };
	SDL_RenderCopy(dst, pObject, clip, &renderquad);
}

void BaseObject::Free() {
	if (pObject != NULL) {
		SDL_DestroyTexture(pObject);
		pObject = NULL;
		rect.w = 0;
		rect.h = 0;
	}
}