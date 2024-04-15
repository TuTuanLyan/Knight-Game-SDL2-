#pragma once
#ifndef TEXT_OBJECT_H
#define TEXT_OBJECT_H

#include "Common_Items.h"

class TextObject
{
public:
	TextObject();
	~TextObject();

	enum TextColor
	{
		RED_TEXT = 0,
		WHITE_TEXT = 1,
		BLACK_TEXT = 2
	};

	void SetText(const std::string& TEXT) { str_Text = TEXT; }
	std::string GetText() const { return str_Text; }

	SDL_Rect GetRectText() { return Rect_Text; }

	int GetTextW() const { return text_w; }
	int GetTextH() const { return text_h; }

	/*bool LoadTextFromFile(std::string path);*/
	bool LoadFromRenderText(SDL_Renderer* dst, TTF_Font* font);
	void Free();

	void SetColor(Uint32 red, Uint32 green, Uint32 blue);
	void SetColor(int type);

	void RenderText(SDL_Renderer* dst, int Xpos, int Ypos,
					SDL_Rect* clip = NULL, double angle = 0.0, 
					SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);


private:
	std::string str_Text;//Nội dung text;
	SDL_Color text_color;//Màu của text
	SDL_Texture* pText;
	SDL_Rect Rect_Text;

	//Các thông số của text
	int text_w;
	int text_h;

};

#endif // !TEXT_OBJECT_H
