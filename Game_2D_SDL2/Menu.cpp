//
//  Menu.cpp
//  Knight's Challenge Game
//
//  Created by Nguyen Tu Anh Tuan.
//


#include "Menu.h"

Menu::Menu()
{
	ButtonText[0].SetColor(170, 92, 75);
	ButtonText[1].SetColor(170, 92, 75);

	Game_State = GAME_START;

	buttonFont = NULL;

	mouse_on[0] = false;
	mouse_on[1] = false;
	
}

Menu::~Menu()
{
	menuBGR.Free();
	ButtonText[0].Free();
	ButtonText[1].Free();
}

void Menu::HandleMenuEvent(SDL_Event e)
{
	if (Game_State == GAME_START) 
	{
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			int mouseX = e.button.x;
			int mouseY = e.button.y;
			if (mouseX > ButtonText[0].GetRectText().x && mouseX < ButtonText[0].GetRectText().x + ButtonText[0].GetTextW() &&
				mouseY > ButtonText[0].GetRectText().y && mouseY < ButtonText[0].GetRectText().y + ButtonText[0].GetTextH())
			{
				mouse_on[0] = true;
				mouse_on[1] = false; 
			}
			else if (mouseX > ButtonText[1].GetRectText().x && mouseX < ButtonText[1].GetRectText().x + ButtonText[1].GetTextW() &&
				mouseY > ButtonText[1].GetRectText().y && mouseY < ButtonText[1].GetRectText().y + ButtonText[1].GetTextH())
			{
				mouse_on[0] = false;
				mouse_on[1] = true;
			}
			else
			{
				mouse_on[0] = false;
				mouse_on[1] = false;
			}

			if (e.button.button == SDL_BUTTON_LEFT)
			{
				if (mouse_on[0]) Game_State = GAME_PLAYING;
				else if (mouse_on[1])
				{
					menuBGR.Free();
					ButtonText[0].Free();
					ButtonText[1].Free();
					if(buttonFont != NULL) TTF_CloseFont(buttonFont);
					Game_State = GAME_QUIT;
					/*std::exit(0);*/
				}
			}
		}
	}
	else if (Game_State == GAME_END)
	{
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			int mouseX = e.button.x;
			int mouseY = e.button.y;
			if (mouseX > ButtonText[0].GetRectText().x && mouseX < ButtonText[0].GetRectText().x + ButtonText[0].GetTextW() &&
				mouseY > ButtonText[0].GetRectText().y && mouseY < ButtonText[0].GetRectText().y + ButtonText[0].GetTextH())
			{
				mouse_on[0] = true;
				mouse_on[1] = false;
			}
			else if (mouseX > ButtonText[1].GetRectText().x && mouseX < ButtonText[1].GetRectText().x + ButtonText[1].GetTextW() &&
				mouseY > ButtonText[1].GetRectText().y && mouseY < ButtonText[1].GetRectText().y + ButtonText[1].GetTextH())
			{
				mouse_on[0] = false;
				mouse_on[1] = true;
			}
			else
			{
				mouse_on[0] = false;
				mouse_on[1] = false;
			}

			if (e.button.button == SDL_BUTTON_LEFT)
			{
				if (mouse_on[0])
				{
					Game_State = GAME_REPLAY;
					/*std::cout << "Da Replay \n";*/
				}
					
				else if (mouse_on[1])
				{
					menuBGR.Free();
					ButtonText[0].Free();
					ButtonText[1].Free();
					if (buttonFont != NULL) TTF_CloseFont(buttonFont);
					Game_State = GAME_QUIT;
					/*std::exit(0);*/
				}
			}
		}
	}
}

void Menu::ShowMenu(SDL_Renderer* dst)
{
	menuBGR.Free();
	ButtonText[0].Free();
	ButtonText[1].Free();

	if (Game_State == GAME_START)
	{	
		buttonFont = TTF_OpenFont("Game_Font/Game_Play_Font.ttf", 36);
		if (buttonFont == NULL) std::cout << "Khong mo duoc button font!" << TTF_GetError();

		menuBGR.Free();
		menuBGR.LoadObjectIMG(dst, "SDL2game_Image/Menu_Small_BGR.png");
		menuBGR.setRect(SCREEN_WIDTH / 2 - 240, SCREEN_HEIGHT / 2 - 240);
		menuBGR.Render(dst);
		
		ButtonText[0].Free();
		ButtonText[0].SetText("PLAY");
		ButtonText[0].LoadFromRenderText(dst, buttonFont);
		ButtonText[0].RenderText(dst, menuBGR.getRect().x + 240 - ButtonText[0].GetTextW() / 2, menuBGR.getRect().x  - ButtonText[0].GetTextH() / 2);

		ButtonText[1].Free();
		ButtonText[1].SetText("EXIT");
		ButtonText[1].LoadFromRenderText(dst, buttonFont);
		ButtonText[1].RenderText(dst, menuBGR.getRect().x + 240 - ButtonText[1].GetTextW() / 2, menuBGR.getRect().x + 160 - ButtonText[1].GetTextH() / 2);
	}
	else if (Game_State == GAME_END)
	{
		buttonFont = TTF_OpenFont("Game_Font/Game_Play_Font.ttf", 36);
		if (buttonFont == NULL) std::cout << "Khong mo duoc button font!" << TTF_GetError();
		
		menuBGR.Free();
		menuBGR.LoadObjectIMG(dst, "SDL2game_Image/Menu_Small_BGR.png");
		menuBGR.setRect(SCREEN_WIDTH / 2 - 240, SCREEN_HEIGHT / 2 - 240);
		menuBGR.Render(dst);

		ButtonText[0].Free();
		ButtonText[0].SetText("REPLAY");
		ButtonText[0].LoadFromRenderText(dst, buttonFont);
		ButtonText[0].RenderText(dst, menuBGR.getRect().x + 240 - ButtonText[0].GetTextW() / 2, menuBGR.getRect().x  - ButtonText[0].GetTextH() / 2);

		ButtonText[1].Free();
		ButtonText[1].SetText("EXIT");
		ButtonText[1].LoadFromRenderText(dst, buttonFont);
		ButtonText[1].RenderText(dst, menuBGR.getRect().x + 240 - ButtonText[1].GetTextW() / 2, menuBGR.getRect().x + 160 - ButtonText[1].GetTextH() / 2);
	}
}