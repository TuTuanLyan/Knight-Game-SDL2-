//
//  TextObject.cpp
//  Knight's Challenge Game
//
//  Created by Nguyen Tu Anh Tuan.
//


#include "TextObject.h"

TextObject::TextObject()
{
	str_Text = "";
	text_color = { 0,0,0 };
	pText = NULL;

	text_w = 0;
	text_h = 0;
}

TextObject::~TextObject()
{
	Free();
}

bool TextObject::LoadFromRenderText(SDL_Renderer* dst, TTF_Font* font) {
	
	Free();
	
	SDL_Surface* Text_Suface = TTF_RenderText_Solid(font, str_Text.c_str(), text_color);
	if (Text_Suface != NULL)
	{
		pText = SDL_CreateTextureFromSurface(dst, Text_Suface);
		text_w = Text_Suface->w;
		text_h = Text_Suface->h;

		SDL_FreeSurface(Text_Suface);
	}
	else std::cout << "Khong load duoc text " << TTF_GetError();
	return pText != NULL;
}

void TextObject::Free() {
	if (pText != NULL)
	{
		SDL_DestroyTexture(pText);
		pText = NULL;
	}
}

void TextObject::SetColor(Uint32 red, Uint32 green, Uint32 blue) {
	text_color.r = red;
	text_color.g = green;
	text_color.b = blue;
}

void TextObject::SetColor(int type)
{
	
	if (type == RED_TEXT) 
	{
		SDL_Color color = { 255,0,0 };
		text_color = color;
	}
	else if (type == WHITE_TEXT)
	{
		SDL_Color color = { 255,255,255 };
		text_color = color;
	}
	else if (type == BLACK_TEXT)
	{
		SDL_Color color = { 0,0,0 };
		text_color = color;
	}
}

void TextObject::RenderText(SDL_Renderer* dst, int Xpos, int Ypos,
	SDL_Rect* clip /*= NULL*/, double angle /*= 0.0*/,
	SDL_Point* center /*= NULL*/, SDL_RendererFlip flip /*= SDL_FLIP_NONE*/)
{
	SDL_Rect renderQuad = { Xpos, Ypos, text_w, text_h };
	Rect_Text = renderQuad;
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx(dst, pText, clip, &renderQuad, angle, center, flip);
}