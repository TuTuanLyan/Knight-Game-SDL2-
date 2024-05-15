/*

 ________   ________  ___  ___      ___    ___ _______   ________          _________  ___  ___          ________  ________   ___  ___         _________  ___  ___  ________  ________
|\   ___  \|\   ____\|\  \|\  \    |\  \  /  /|\  ___ \ |\   ___  \       |\___   ___\\  \|\  \        |\   __  \|\   ___  \|\  \|\  \       |\___   ___\\  \|\  \|\   __  \|\   ___  \
\ \  \\ \  \ \  \___|\ \  \\\  \   \ \  \/  / | \   __/|\ \  \\ \  \      \|___ \  \_\ \  \\\  \       \ \  \|\  \ \  \\ \  \ \  \\\  \      \|___ \  \_\ \  \\\  \ \  \|\  \ \  \\ \  \
 \ \  \\ \  \ \  \  __\ \  \\\  \   \ \    / / \ \  \_|/_\ \  \\ \  \          \ \  \ \ \  \\\  \       \ \   __  \ \  \\ \  \ \   __  \          \ \  \ \ \  \\\  \ \   __  \ \  \\ \  \
  \ \  \\ \  \ \  \|\  \ \  \\\  \   \/  /  /   \ \  \_|\ \ \  \\ \  \          \ \  \ \ \  \\\  \       \ \  \ \  \ \  \\ \  \ \  \ \  \          \ \  \ \ \  \\\  \ \  \ \  \ \  \\ \  \
   \ \__\\ \__\ \_______\ \_______\__/  / /      \ \_______\ \__\\ \__\          \ \__\ \ \_______\       \ \__\ \__\ \__\\ \__\ \__\ \__\          \ \__\ \ \_______\ \__\ \__\ \__\\ \__\
    \|__| \|__|\|_______|\|_______|\___/ /        \|_______|\|__| \|__|           \|__|  \|_______|        \|__|\|__|\|__| \|__|\|__|\|__|           \|__|  \|_______|\|__|\|__|\|__| \|__|
                                  \|___|/


                                                                ___           ___    ___ ________  ________
                                                               |\  \         |\  \  /  /|\   __  \|\   ___  \
                                                               \ \  \        \ \  \/  / | \  \|\  \ \  \\ \  \
                                                                \ \  \        \ \    / / \ \   __  \ \  \\ \  \
                                                                 \ \  \____    \/  /  /   \ \  \ \  \ \  \\ \  \
                                                                  \ \_______\__/  / /      \ \__\ \__\ \__\\ \__\
                                                                   \|_______|\___/ /        \|__|\|__|\|__| \|__|
                                                                            \|___|/

                                                                          My SDL2 game project - Knight Game
                                                          
*/

//
//  main.cpp
//  Knight's Challenge Game
//
//  Created by Nguyen Tu Anh Tuan.
//

#include "Common_Items.h"
#include "BaseObject.h"
#include "PlayerObject.h"
#include "GameMap.h"
#include "Timer.h"
#include "Slime.h"
#include "Plant_Cannon.h"
#include "TheGhost.h"
#include "Explosion.h"
#include "TextObject.h"
#include "Menu.h"

//Hàm
bool init();
void close();

void SetThreatsPos(std::string path);
void SpawnThreats();

void RunSlimes(MapInfor& map_data);
void RunPlantCannons(MapInfor& map_data);
void RunGhost(MapInfor& map_data);

void ShowPlayerScore();

void ResetDataGame(int &delay_player_event);

void GameOver(MapInfor& map_data, int &delay_player_event);

//Biến
int player_score;

int Threats_Pos[10][500];

std::vector <Slime*> Slime_List;
std::vector <Plant_Cannon*> Plant_Cannon_List;
std::vector <Ghost*> Ghost_List;

Menu menu;
BaseObject Background;
GameMap Map;
PlayerObject player;
Explosion explosion;
BaseObject Player_Icon;
TextObject Score;

// Main***********************************************************************************************************************************
int main(int argc, char* argv[]) {

    Timer FPS_timer;

    if (!init()) {
        std::cout << "Khoi tao that bai! \n";
        return -1;
    }

    bool GameRunning = true;

    int delay_player_event = 1;

    menu.SetGameState(GAME_START);

    SetThreatsPos("map/threats_map_pos.txt");
    
    Background.LoadObjectIMG(g_Renderer, "SDL2game_Image/Background.png");

    Map.SetInforMap("map/MAP02DATAaft.txt");
    Map.LoadBlockIMG(g_Renderer);
    
    player.LoadPlayerIMG(g_Renderer, "SDL2game_Image/player_walk_right.png");
    player.SetFrame();
    player_score = 0;
   
    explosion.LoadExplosionIMG(g_Renderer);
    explosion.SetFrame();

    //Khởi tạo threats
    SpawnThreats();
    
    Player_Icon.LoadObjectIMG(g_Renderer, "SDL2game_Image/Player_Icon.png");
    Player_Icon.setRect(8, 8);
    
    Score.SetColor(TextObject::WHITE_TEXT);
    
    while (GameRunning)
    {
        FPS_timer.START();
        while (SDL_PollEvent(&g_Event) != 0) {
            if (g_Event.type == SDL_QUIT)  GameRunning = false;
            menu.HandleMenuEvent(g_Event);
            if (menu.GetGameState() == GAME_PLAYING)
            {
                if (delay_player_event == 0) player.HandleEvent(g_Event, g_Renderer);
                else delay_player_event--;

            }
        }

        SDL_SetRenderDrawColor(g_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(g_Renderer);

        Background.Render(g_Renderer, NULL);

        MapInfor map_data = Map.GetMapInfor();

        player.HandleFireBullet(g_Renderer);
        player.SetMapXY(map_data.start_x, map_data.start_y);
        if(menu.GetGameState() == GAME_PLAYING) player.PlayerMovement(map_data);

        Map.SetMap(map_data);

        player.ShowClip(g_Renderer);
        Map.DrawMap(g_Renderer);

        //Chạy slime
        RunSlimes(map_data);

        //Chạy Cannon
        RunPlantCannons(map_data);

        //Chạy Ghost
        RunGhost(map_data);

        if (player.PlayerHp <= 0) player.PlayerHp = 0;

        player.LoadHpStatus(g_Renderer);
        Player_Icon.Render(g_Renderer);

        //Bullet Check
        std::vector<Bullet*> player_bullet_list = player.GetBulletList();
        for (int i = 0; i < player_bullet_list.size(); i++)
        {
            Bullet* bullet = player_bullet_list[i];
            if (bullet != NULL) {
                for (int j = 0; j < Slime_List.size(); j++)
                {
                    Slime* slime = Slime_List[j];
                    if (slime != NULL) 
                    {
                        SDL_Rect slime_rect;
                        slime_rect.x = slime->getRect().x;
                        slime_rect.y = slime->getRect().y;
                        

                        SDL_Rect bullet_rect = bullet->getRect();

                        if (abs(slime_rect.x - bullet_rect.x) <= 10 * TILE_SIZE && abs(slime_rect.y - bullet_rect.y) <= 10 * TILE_SIZE)
                        {
                            slime_rect.w = slime->GetFrameW();
                            slime_rect.h = slime->GetFrameH();

                            bool is_collision = SDL_COMMON_FUNC::CheckCollision(bullet_rect, slime_rect);

                            if (is_collision) {
                                for (int fr = 0; fr < 24; fr++)
                                {
                                    explosion.SetMapXY(map_data.start_x, map_data.start_y);
                                    explosion.SetXpos(bullet->GetBulletXpos() + bullet->getRect().w / 2 - explosion.GetFrameW() / 2);
                                    explosion.SetYpos(bullet->GetBulletYpos() + bullet->getRect().h / 2 - explosion.GetFrameH() / 2);
                                    explosion.SetCurrentFrame(fr / 3);
                                    explosion.ShowClip(g_Renderer);
                                }
                                player.DelletBullet(i);                               
                                slime->SlimeHp -= player.GetBulletDamage();
                                if (slime->SlimeHp <= 0) {
                                    /*slime->SlimeHp = 0;*/
                                    slime->Free();
                                    player_score++;
                                    Slime_List.erase(Slime_List.begin() + j);
                                    if (slime != NULL) {
                                        delete slime;
                                        slime = NULL;
                                    }
                                }
                            }
                        }
                    }
                }
                for (int j = 0; j < Plant_Cannon_List.size(); j++)
                {
                    Plant_Cannon* cannon = Plant_Cannon_List[j];
                    if (cannon != NULL)
                    {
                        SDL_Rect cannon_rect;
                        cannon_rect.x = cannon->getRect().x;
                        cannon_rect.y = cannon->getRect().y;
                        

                        SDL_Rect bullet_rect = bullet->getRect();

                        if (abs(cannon_rect.x - bullet_rect.x) <= 10 * TILE_SIZE && abs(cannon_rect.y - bullet_rect.y) <= 10 * TILE_SIZE)
                        {
                            cannon_rect.w = cannon->GetFrameW();
                            cannon_rect.h = cannon->GetFrameH();

                            bool is_collision = SDL_COMMON_FUNC::CheckCollision(bullet_rect, cannon_rect);

                            if (is_collision) {
                                for (int fr = 0; fr < 24; fr++)
                                {
                                    explosion.SetMapXY(map_data.start_x, map_data.start_y);
                                    explosion.SetXpos(bullet->GetBulletXpos() + bullet->getRect().w / 2 - explosion.GetFrameW() / 2);
                                    explosion.SetYpos(bullet->GetBulletYpos() + bullet->getRect().h / 2 - explosion.GetFrameH() / 2);
                                    explosion.SetCurrentFrame(fr / 3);
                                    explosion.ShowClip(g_Renderer);
                                }
                                player.DelletBullet(i);
                                cannon->CannonHp -= player.GetBulletDamage();
                                if (cannon->CannonHp <= 0) {
                                    cannon->Free();
                                    player_score++;
                                    Plant_Cannon_List.erase(Plant_Cannon_List.begin() + j);
                                    if (cannon != NULL) {
                                        delete cannon;
                                        cannon = NULL;
                                    }
                                }
                            }
                        }    
                    }
                }
            }
        }

        ShowPlayerScore();
        
        if (menu.GetGameState() == GAME_REPLAY) ResetDataGame(delay_player_event);

        if (menu.GetGameState() == GAME_QUIT) GameRunning = false;

        //Game Over!
        /*if (player.PlayerHp == 0 || player.GetPlayerXPos() == map_data.end_x - player.GetFrameW()) {
            delay_player_event = 1;

            player.SetDie(true);
            player.SetMotion(false);
            menu.SetGameState(GAME_END);

            player.SetMotion(false);
            player.SetFalseJump();

            for (int j = 0; j < Slime_List.size(); j++)
            {
                Slime* slime = Slime_List[j];
                slime->Free();
                Slime_List.erase(Slime_List.begin() + j);
                if (slime != NULL) {
                    delete slime;
                    slime = NULL;
                }
            }
            for (int j = 0; j < Plant_Cannon_List.size(); j++)
            {
                Plant_Cannon* cannon = Plant_Cannon_List[j];
                cannon->Free();
                Plant_Cannon_List.erase(Plant_Cannon_List.begin() + j);
                if (cannon != NULL) {
                    delete cannon;
                    cannon = NULL;
                }
            }
            for (int j = 0; j < Ghost_List.size(); j++)
            {
                Ghost* ghost = Ghost_List[j];
                ghost->Free();
                Ghost_List.erase(Ghost_List.begin() + j);
                if (ghost != NULL) {
                    delete ghost;
                    ghost = NULL;
                }
            }
        }*/
        GameOver(map_data, delay_player_event);

        menu.ShowMenu(g_Renderer);

        SDL_RenderPresent(g_Renderer);

        int real_time = FPS_timer.get_ticks();
        int time_one_frame = 1000 / FPS;

        if (real_time < time_one_frame)
        {
            int delay_time = time_one_frame - real_time;
            SDL_Delay(delay_time);
        }
    }
    close();
    return 0;
}

//Khởi tạo hàm***************************************************************************************************************************
bool init() {
    bool success = true;
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Khởi tạo thất bại \n" << SDL_GetError() << '\n';
        return false;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_Window = SDL_CreateWindow(Window_Title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (g_Window == NULL) return false;
    else {
        g_Renderer = SDL_CreateRenderer(g_Window, -1, SDL_RENDERER_ACCELERATED/*|SDL_RENDERER_PRESENTVSYNC*/);
        if (g_Renderer == NULL) {
            std::cout << "Tạo renderer thất bại! \n" << SDL_GetError() << '\n';
            success = false;
        }
        else {
            SDL_SetRenderDrawColor(g_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags)) success = false;

            if (TTF_Init() == -1)
            {
                std::cout << "SDL_ttf không thể khởi tạo! SDL_ttf Error: " << TTF_GetError() << '\n';
                success = false;
            }
            else
            {
                gFont = TTF_OpenFont("Game_Font/Game_Play_Font.ttf", 16);
                if (gFont == NULL) {
                    std::cout << "Không mở được font game! " << TTF_GetError() <<'\n';
                    success = false;
                }

                buttonFont = TTF_OpenFont("Game_Font/Game_Play_Font.ttf", 36);
                if (buttonFont == NULL) {
                    std::cout << "Không mở được font button! " << TTF_GetError() << '\n';
                    success = false;
                }
            }
        }
    }
    return success;
}

void close() {

    SDL_DestroyRenderer(g_Renderer);
    g_Renderer = NULL;
    SDL_DestroyWindow(g_Window);
    g_Window = NULL;
    TTF_CloseFont(gFont);
    gFont = NULL;
    TTF_CloseFont(buttonFont);
    buttonFont = NULL;


    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void SetThreatsPos(std::string path) {
    std::ifstream file(path);
    if (file)
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 500; j++)
            {
                if (!file.eof()) {
                    file >> Threats_Pos[i][j];
                }
            }
        }
    }
    else std::cout << "Không thể mở map " << path << '\n';
    file.close();
}

void SpawnThreats() {
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 500; j++)
        {
            int threat_index = Threats_Pos[i][j];
            if (threat_index == 2)
            {
                Slime* pSlime = new Slime();
                if (pSlime != NULL) {
                    pSlime->LoadSlimeIMG(g_Renderer);
                    pSlime->SetFrame();
                    pSlime->SetSlimeXpos(j * TILE_SIZE);
                    pSlime->SetSlimeYpos(i * TILE_SIZE);
                    Slime_List.push_back(pSlime);
                }
            }

            if (threat_index == 3)
            {
                Plant_Cannon* pCannon = new Plant_Cannon();
                if (pCannon != NULL) {
                    pCannon->LoadCannonIMG(g_Renderer);
                    pCannon->SetFrame();
                    pCannon->SetCannonXpos(j * TILE_SIZE);
                    pCannon->SetCannonYpos(i * TILE_SIZE);
                    Plant_Cannon_List.push_back(pCannon);
                }
            }

            if (threat_index == 4)
            {
                Ghost* pGhost = new Ghost();
                if (pGhost != NULL) {
                    pGhost->LoadGhostIMG(g_Renderer, "SDL2game_Image/Ghost_left.png");
                    pGhost->SetGhostXpos(j * TILE_SIZE);
                    pGhost->SetGhostYpos(i * TILE_SIZE);
                    Ghost_List.push_back(pGhost);
                }
            }
        }
    }
}

void ShowPlayerScore() {
    std::string str_score = "YOUR SCORES: ";
    std::string score_val = std::to_string(player_score);
    str_score += score_val;
    Score.SetText(str_score);
    Score.LoadFromRenderText(g_Renderer, gFont);
    Score.RenderText(g_Renderer, SCREEN_WIDTH - 225, 24);
}

void GameOver(MapInfor &map_data, int &delay_player_event) {
    if (player.PlayerHp == 0 || player.GetPlayerXPos() == map_data.end_x - player.GetFrameW()) {
        delay_player_event = 1;

        player.SetDie(true);
        player.SetMotion(false);
        menu.SetGameState(GAME_END);

        player.SetMotion(false);
        player.SetFalseJump();

        for (int j = 0; j < Slime_List.size(); j++)
        {
            Slime* slime = Slime_List[j];
            slime->Free();
            Slime_List.erase(Slime_List.begin() + j);
            if (slime != NULL) {
                delete slime;
                slime = NULL;
            }
        }
        for (int j = 0; j < Plant_Cannon_List.size(); j++)
        {
            Plant_Cannon* cannon = Plant_Cannon_List[j];
            cannon->Free();
            Plant_Cannon_List.erase(Plant_Cannon_List.begin() + j);
            if (cannon != NULL) {
                delete cannon;
                cannon = NULL;
            }
        }
        for (int j = 0; j < Ghost_List.size(); j++)
        {
            Ghost* ghost = Ghost_List[j];
            ghost->Free();
            Ghost_List.erase(Ghost_List.begin() + j);
            if (ghost != NULL) {
                delete ghost;
                ghost = NULL;
            }
        }
    }
}

void ResetDataGame(int &delay_player_event) {
    delay_player_event = 1;

    player.SetDie(false);
    player.PlayerHp = 266;
    player.SetPlayerXpos(0);
    player.SetPlayerYpos(320);
    player.SetPlayerXval(0);
    player.SetPlayerYval(0);
    player.SetPlayerStatus(RIGHT_STATUS);
    player.SetMotion(false);
    player.SetFalseJump();


    player.LoadPlayerIMG(g_Renderer, "SDL2game_Image/player_walk_right.png");
    player.SetFrame();
    player_score = 0;


    for (int j = 0; j < Slime_List.size(); j++)
    {
        Slime* slime = Slime_List[j];
        slime->Free();
        Slime_List.erase(Slime_List.begin() + j);
        if (slime != NULL) {
            delete slime;
            slime = NULL;
        }
    }
    for (int j = 0; j < Plant_Cannon_List.size(); j++)
    {
        Plant_Cannon* cannon = Plant_Cannon_List[j];
        cannon->Free();
        Plant_Cannon_List.erase(Plant_Cannon_List.begin() + j);
        if (cannon != NULL) {
            delete cannon;
            cannon = NULL;
        }
    }
    for (int j = 0; j < Ghost_List.size(); j++)
    {
        Ghost* ghost = Ghost_List[j];
        ghost->Free();
        Ghost_List.erase(Ghost_List.begin() + j);
        if (ghost != NULL) {
            delete ghost;
            ghost = NULL;
        }
    }

    SpawnThreats();

    menu.SetGameState(GAME_PLAYING);
}

void RunSlimes(MapInfor& map_data) {
    for (int i = 0; i < Slime_List.size(); i++)
    {
        Slime* slime = Slime_List[i];

        slime->SetMapXY(map_data.start_x, map_data.start_y);
        slime->SetSlimeView();

        if (abs(slime->GetSlimeXpos() - player.GetPlayerXPos()) < 640)
        {
            if (menu.GetGameState() == GAME_PLAYING) slime->HandleSlimeAttack(g_Renderer, player);
            if (menu.GetGameState() == GAME_PLAYING) slime->SlimeActions(map_data, player);
            for (int j = 0; j < 8; j++)
            {
                std::vector<Bullet*> bullet_list = slime->GetSlimeBulletList(j);
                for (int k = 0; k < bullet_list.size(); k++)
                {
                    Bullet* bullet = bullet_list.at(k);
                    if (bullet != NULL)
                    {
                        SDL_Rect player_rect;
                        player_rect.x = player.getRect().x;
                        player_rect.y = player.getRect().y;

                        SDL_Rect bullet_rect = bullet->getRect();

                        if (abs(player_rect.x - bullet_rect.x) <= 10 * TILE_SIZE && abs(player_rect.y - bullet_rect.y) <= 10 * TILE_SIZE)
                        {
                            player_rect.w = player.GetFrameW();
                            player_rect.h = player.GetFrameH();

                            bool is_collision = SDL_COMMON_FUNC::CheckCollision(bullet_rect, player_rect);
                            if (is_collision)
                            {
                                for (int fr = 0; fr < 24; fr++)
                                {
                                    explosion.SetMapXY(map_data.start_x, map_data.start_y);
                                    explosion.SetXpos(bullet->GetBulletXpos() + bullet->getRect().w / 2 - explosion.GetFrameW() / 2);
                                    explosion.SetYpos(bullet->GetBulletYpos() + bullet->getRect().h / 2 - explosion.GetFrameH() / 2);
                                    explosion.SetCurrentFrame(fr / 3);
                                    explosion.ShowClip(g_Renderer);
                                }
                                /*explosion.Free();*/
                                slime->DeleteBullet(j, k);
                                player.PlayerHp -= slime->GetSlimeDamage();

                            }
                        }
                    }
                }
            }
            slime->LoadSlimeHp(g_Renderer);
            slime->ShowSlimeClip(g_Renderer);
        }
    }
}
void RunPlantCannons(MapInfor& map_data) {
    for (int i = 0; i < Plant_Cannon_List.size(); i++)
    {
        Plant_Cannon* plant_cannon = Plant_Cannon_List[i];

        plant_cannon->SetMapXY(map_data.start_x, map_data.start_y);
        plant_cannon->SetCannonView();

        if (abs(plant_cannon->GetCannonXpos() - player.GetPlayerXPos()) < 640)
        {
            if (menu.GetGameState() == GAME_PLAYING) plant_cannon->HandleCannonAttack(g_Renderer, player);
            if (menu.GetGameState() == GAME_PLAYING) plant_cannon->PlantCannonAction(map_data, player);
            std::vector<Bullet*> bullet_list = plant_cannon->GetCannonBulletList();
            for (int j = 0; j < bullet_list.size(); j++)
            {
                Bullet* bullet = bullet_list.at(j);
                if (bullet != NULL)
                {
                    SDL_Rect player_rect;
                    player_rect.x = player.getRect().x;
                    player_rect.y = player.getRect().y;

                    SDL_Rect bullet_rect = bullet->getRect();

                    if (abs(player_rect.x - bullet_rect.x) <= 10 * TILE_SIZE && abs(player_rect.y - bullet_rect.y) <= 10 * TILE_SIZE)
                    {
                        player_rect.w = player.GetFrameW();
                        player_rect.h = player.GetFrameH();

                        bool is_collision = SDL_COMMON_FUNC::CheckCollision(bullet_rect, player_rect);
                        if (is_collision)
                        {
                            for (int fr = 0; fr < 24; fr++)
                            {
                                explosion.SetMapXY(map_data.start_x, map_data.start_y);
                                explosion.SetXpos(bullet->GetBulletXpos() + bullet->getRect().w / 2 - explosion.GetFrameW() / 2);
                                explosion.SetYpos(bullet->GetBulletYpos() + bullet->getRect().h / 2 - explosion.GetFrameH() / 2);
                                explosion.SetCurrentFrame(fr / 3);
                                explosion.ShowClip(g_Renderer);
                            }
                            /*explosion.Free();*/
                            plant_cannon->DeleteBullet(j);
                            player.PlayerHp -= plant_cannon->GetCannonDamage();
                        }
                    }
                }
            }

            plant_cannon->LoadCannonHp(g_Renderer);
            plant_cannon->ShowCannonClip(g_Renderer);
        }

    }
}
void RunGhost(MapInfor& map_data) {
    for (int i = 0; i < Ghost_List.size(); i++)
    {
        Ghost* ghost = Ghost_List[i];

        ghost->SetMapXY(map_data.start_x, map_data.start_y);
        ghost->SetGhostView();

        if (abs(ghost->GetGhostXpos() - player.GetPlayerXPos()) < 640)
        {
            if (menu.GetGameState() == GAME_PLAYING) ghost->GhostAction(map_data, player);
            SDL_Rect ghost_rect = ghost->getRect();

            SDL_Rect player_rect;
            player_rect.x = player.getRect().x;
            player_rect.y = player.getRect().y;

            if (abs(player_rect.x - ghost_rect.x) <= 10 * TILE_SIZE && abs(player_rect.y - ghost_rect.y) <= 10 * TILE_SIZE)
            {
                player_rect.w = player.GetFrameW();
                player_rect.h = player.GetFrameH();

                bool is_collision = SDL_COMMON_FUNC::CheckCollision(ghost_rect, player_rect);
                if (is_collision)
                {

                    player.PlayerHp -= ghost->GetGhostDamage();
                    Ghost_List.erase(Ghost_List.begin() + i);
                    ghost->Free();
                }

            }

            ghost->ShowGhostClip(g_Renderer);
        }

    }
}