#include "Common_Items.h"

bool SDL_COMMON_FUNC::CheckCollision(SDL_Rect& object1, SDL_Rect& object2)
{
	int obj1_left = object1.x + TRUE_RECT_VALUE;
	int obj1_right = object1.x + object1.w - TRUE_RECT_VALUE;
	int obj1_top = object1.y + TRUE_RECT_VALUE;
	int obj1_bottom = object1.y + object1.h - TRUE_RECT_VALUE;

	int obj2_left = object2.x + TRUE_RECT_VALUE;
	int obj2_right = object2.x + object2.w - TRUE_RECT_VALUE;
	int obj2_top = object2.y + TRUE_RECT_VALUE;
	int obj2_bottom = object2.y + object2.h - TRUE_RECT_VALUE;
	
	if (obj1_left > obj2_right || obj1_bottom < obj2_top) return false;
	else if (obj1_left > obj2_right || obj1_top > obj2_bottom) return false;
	else if (obj1_right < obj2_left || obj1_top > obj2_bottom) return false;
	else if (obj1_right < obj2_left || obj1_bottom < obj2_top) return false;

	return true;
}