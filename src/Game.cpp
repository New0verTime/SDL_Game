#include "Game.h"
#include "TextureManager.h"
#include <SDL_ttf.h>
#include<iostream>
#include<cstdlib>
int m_currentFrame;
Game::Game(){
 m_pWindow=NULL;
 m_pRenderer=NULL;
 m_bRunning=false;
}
 SDL_Texture* Game::str_to_texture(std::string str){
 SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, str.c_str(), {0,0,0} );
 SDL_Texture* textTexture = SDL_CreateTextureFromSurface(m_pRenderer,textSurface);
 mWidth=textSurface->w;
 mHeight =textSurface->h;
 SDL_FreeSurface(textSurface);
 return textTexture;
}
bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
 Snake_block.push_back({0,0});
 // attempt to initialize SDL
 if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
 {
 std::cout << "SDL init success\n";
 // init the window
 m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
 if(m_pWindow != 0) // window init success
 {
 std::cout << "window creation success\n";
 m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_PRESENTVSYNC);
 if(m_pRenderer != 0) // renderer init success
 {
 std::cout << "renderer creation success\n";
 SDL_SetRenderDrawColor(m_pRenderer,255,255,255,255);}
 else
 {
 std::cout << "renderer init fail\n";
 return false; // renderer init fail
 }
 }
 else
 {
 std::cout << "window init fail\n";
 return false; // window init fail
 }
 }
 else
 {
 std::cout << "SDL init fail\n";
 return false; // SDL init fail
 }
 std::cout << "init success\n";
 m_bRunning = true;
 gameOver = true;
 Delay=200;
TheTextureManager::Instance()->load("assets/block.png", "block", m_pRenderer);
 TheTextureManager::Instance()->load("assets/animate.png", "animate", m_pRenderer);
 TheTextureManager::Instance()->load("assets/apple.png", "apple", m_pRenderer);
 TTF_Init();
 gFont = TTF_OpenFont( "Raleway-Medium.ttf", 28 );
 apl.first=block_size*2;
 apl.second=block_size*2;
 return true;
}
void Game::render()
{
 SDL_RenderClear(m_pRenderer);
 SDL_Rect k; k.x=0; k.y=0; k.w=mWidth; k.h=mHeight;
 SDL_RenderCopy(m_pRenderer,str_to_texture("Score: "+std::to_string(score)),NULL,&k);
 for(int i=0;i<lengthofSnake-1;++i)
 TheTextureManager::Instance()->draw("block", Snake_block[i].first,Snake_block[i].second, block_size , block_size , m_pRenderer);
 TheTextureManager::Instance()->drawFrame("animate", Snake_block[lengthofSnake-1].first,Snake_block[lengthofSnake-1].second, block_size , block_size , 1, frame, m_pRenderer, SDL_FLIP_NONE,angle);
 TheTextureManager::Instance()->draw("apple", apl.first,apl.second, block_size , block_size , m_pRenderer);
 SDL_RenderPresent(m_pRenderer);
}
void Game::handleEvents()
{
 SDL_Event event;
    if(SDL_PollEvent(&event))
        {
    switch (event.type)
        {
        case SDL_QUIT:
        m_bRunning = false;
        break;
        case SDL_KEYDOWN:
        {
            switch(event.key.keysym.sym){
                case SDLK_LEFT:
                if(dirx!=block_size){
                dirx=-block_size;
                angle=180;}
                diry=0;
                break;
                case SDLK_RIGHT:
                if(dirx!=-block_size){
                dirx=block_size;
                angle=0;
                }
                diry=0;
                break;
                case SDLK_UP:
                dirx=0;
                if(diry!=block_size){
                diry=-block_size;
                angle=270;
                }
                break;
                case SDLK_DOWN:
                dirx=0;
                if(diry!=-block_size){
                diry=block_size;
                angle=90;
                }
                break;
                case SDLK_p:
                gameOver=true;
                break;
                }
            }
        default:
        break;
            }
        }
}
void Game::clean()
{
 std::cout << "cleaning game\n";
 TTF_CloseFont( gFont );
 gFont = NULL;
 SDL_DestroyWindow(m_pWindow);
 SDL_DestroyRenderer(m_pRenderer);
 SDL_Quit();
}
void Game::update()
{
 frame=(int)(3*SDL_GetTicks()/Delay)%3;
 if(SDL_GetTicks()>Mark+Delay){
 int a=Snake_block[0].first,b=Snake_block[0].second;
 if(Snake_block[lengthofSnake-1].first+dirx>block_size*9){
    Snake_block[lengthofSnake-1].first=0;
 }
 if(Snake_block[lengthofSnake-1].first+dirx<0){
    Snake_block[lengthofSnake-1].first=block_size*9;
 }
 if(Snake_block[lengthofSnake-1].second+diry>block_size*9){
    Snake_block[lengthofSnake-1].second=0;
 }
 if(Snake_block[lengthofSnake-1].second+diry<0){
    Snake_block[lengthofSnake-1].second=block_size*9;
 }
 if(Snake_block[lengthofSnake-1].first+dirx!=apl.first||Snake_block[lengthofSnake-1].second+diry!=apl.second){
    for(int i=0;i<lengthofSnake-1;++i) {if(Snake_block[i]==Snake_block[lengthofSnake-1]){m_bRunning=false; break;}  Snake_block[i]=Snake_block[i+1];}
    Snake_block[lengthofSnake-1].first+=dirx;
    Snake_block[lengthofSnake-1].second+=diry;
 }
 else{
    Snake_block.push_back({Snake_block[lengthofSnake-1].first+dirx,Snake_block[lengthofSnake-1].second+diry});
    ++lengthofSnake;
    ++score;
    apl.first=(rand()%10)*block_size;
    apl.second=(rand()%10)*block_size;
    int check=true;
    while(check){
    check=false;
    for(int i=0;i<lengthofSnake;++i){
        if(apl.first==Snake_block[i].first&&apl.second==Snake_block[i].second){
        apl.first=(rand()%10)*block_size;
        apl.second=(rand()%10)*block_size;
        check=true;
        break;
        }
    }
    }
 }
 Mark=SDL_GetTicks();
 }
}
