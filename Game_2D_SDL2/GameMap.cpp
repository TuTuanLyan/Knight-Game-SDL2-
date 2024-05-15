//
//  GameMap.cpp
//  Knight's Challenge Game
//
//  Created by Nguyen Tu Anh Tuan.
//


#include "GameMap.h"

void GameMap::SetInforMap(std::string path)
{
	// Mở file của map 1
	std::ifstream file(path);
	if (file)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 500; j++)
			{
				if (!file.eof()) {
					file >> map_data.Map_Tile_Infor[i][j];
				}
			}
		}
	}
	else std::cout << "Không thể mở map " << path << '\n';
	file.close();
	//Kiểm tra xem đọc file đúng không

	/*std::cout << path << '\n';
	int cnt = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 500; j++)
		{
			std::cout << map_data.Map_Tile_Infor[i][j] << ' ';
			cnt++;
		}
		std::cout << '\n';
	}
	std::cout << cnt << '\n';*/
}

bool GameMap::LoadBlockIMG(SDL_Renderer* dst) {
	bool success = Block_Map.LoadObjectIMG(dst, "SDL2game_Image/Block_1.png");
	if (!success) std::cout << "Không tải được ảnh block! \n";
	return success;
}

void GameMap::DrawMap(SDL_Renderer* dst) {
	int x1 = (abs(map_data.start_x) % TILE_SIZE) * -1;
	int x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

	int map_index_x = abs(map_data.start_x) / TILE_SIZE;
	int map_index_y = 0;

	for (int i = map_data.start_y; i < map_data.end_y; i += TILE_SIZE)
	{
		map_index_x = abs(map_data.start_x) / TILE_SIZE;
		for (int j = x1; j < x2; j += TILE_SIZE)
		{
			int val = map_data.Map_Tile_Infor[map_index_y][map_index_x];
			if (val == 1)
			{
				Block_Map.setRect(j, i);
				Block_Map.Render(dst);
			}
			map_index_x++;
		}
		map_index_y++;
	}

}
