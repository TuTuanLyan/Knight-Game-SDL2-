#pragma once
#ifndef MENU_H
#define MENU_H

#include "Common_Items.h"
#include "TextObject.h"
#include "BaseObject.h"

class Menu
{
public:
	Menu();
	/*Menu(SDL_Renderer* g_Renderer);*/
	~Menu();

	/*enum MenuState
	{
		MENU_SHOWN,
		MENU_HIDDEN
	};*/

	void SetGameState(int state_) { Game_State = state_; }
	int GetGameState() const { return Game_State; }

	void HandleMenuEvent(SDL_Event event);
	void ShowMenu(SDL_Renderer* dst);


private:
	int Game_State;
	/*int Menu_State;*/

	/*SDL_Renderer* g_Renderer = NULL;*/

	/*TTF_Font* menuFont;*/

	/*TextObject MenuText;*/
	TextObject ButtonText[2];

	BaseObject menuBGR;

	bool mouse_on[2];
};


#endif // !MENU_H
