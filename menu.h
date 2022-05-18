#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include<iostream>
#include<algorithm>
#include<fstream>
#include<SDL.h>
#include<SDL_image.h>
#include"snakesdl.h"
#include"print.h"
#include<vector>
using namespace std;
int menugame(SDL_Renderer* renderer,SDL_Event e);
int selectmenu(SDL_Renderer* renderer,SDL_Window* window,SDL_Texture* texture,SDL_Event e);
void print_hightscore(SDL_Renderer* renderer);
bool check_highscore(int score);
bool back_menu(SDL_Event e);
int newgame(SDL_Renderer* renderer,SDL_Event e);
void onoff_music(int count,SDL_Renderer* renderer);
#endif // MENU_H_INCLUDED
