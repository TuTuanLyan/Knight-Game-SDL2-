#pragma once
#ifndef BASE_OBJECT_H
#define BASE_OBJECT_H

#include "Common_Items.h"

class BaseObject
{
public:
	BaseObject();
	~BaseObject();
	
	void setRect(const int& x, const int& y) {
		rect.x = x;
		rect.y = y;
	}
	SDL_Rect getRect() const {
		return rect;
	}
	SDL_Texture* GetObject() const {
		return pObject;
	}

	virtual bool LoadObjectIMG(SDL_Renderer* screen, std::string path);
	void Render(SDL_Renderer* dst, const SDL_Rect* clip = NULL);
	void Free();

protected:
	SDL_Texture* pObject;
	SDL_Rect rect;
};

#endif
