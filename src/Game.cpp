#include "Game.h"
#include "TextureManager.h"
#include<iostream>
int m_currentFrame;
TextureManager m_textureManager;
Game::Game(){
 m_pWindow=NULL;
 m_pRenderer=NULL;
 m_bRunning=false;
}
bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
 // attempt to initialize SDL
 if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
 {
 std::cout << "SDL init success\n";
 // init the window
 m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
 if(m_pWindow != 0) // window init success
 {
 std::cout << "window creation success\n";
 m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
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
 m_textureManager.load("assets/animate.png", "animate", m_pRenderer);
 return true;
}
void Game::render()
{
 SDL_RenderClear(m_pRenderer);
 m_textureManager.draw("animate", 0,0, 128, 82, m_pRenderer);
 m_textureManager.drawFrame("animate", 100,100, 128, 82, 1, m_currentFrame, m_pRenderer);
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
 default:
 break;
 }
 }
}
void Game::clean()
{
 std::cout << "cleaning game\n";
 SDL_DestroyWindow(m_pWindow);
 SDL_DestroyRenderer(m_pRenderer);
 SDL_Quit();
}
void Game::update()
{
 m_currentFrame = int(((SDL_GetTicks() / 1000) % 3));
}
