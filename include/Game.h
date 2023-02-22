#ifndef GAME_H
#define GAME_H
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>
#include <vector>
class Game
{
public:
 Game();
 ~Game();
 bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
 void render();
 void update();
 void handleEvents();
 SDL_Texture* str_to_texture(std::string str);
 void clean();
 bool running() { return m_bRunning; }
private:
 const int block_size=75;
 double angle=0;
 int score=0;
 int Delay,Mark=0;
 int frame=0;
 int x=0,y=0,mWidth,mHeight;
 int lengthofSnake=1;
 std::vector<std::pair<int,int>> Snake_block;
 std::pair<int,int> apl;
 TTF_Font *gFont;
 int dirx=0,diry=0;
 SDL_Window* m_pWindow;
 SDL_Renderer* m_pRenderer;
 bool m_bRunning,gameOver;
};

#endif // GAME_H

