#ifndef PRINT_H_INCLUDED
#define PRINT_H_INCLUDED
#include<iostream>
#include<SDL.h>
#include<SDL_mixer.h>
#include<SDL_image.h>
#include"snakesdl.h"
#include<vector>
using namespace std;
enum class direction
{
    up,down,left,right
};
SDL_Texture* moveimage(SDL_Renderer* renderer,string path,SDL_Rect toado);
void hinhvuong(SDL_Renderer* renderer,Painter but);
void printpoint( point a,Painter but,SDL_Renderer* renderer);
void printapple(point apple,SDL_Renderer* renderer);
void printscore(int score,SDL_Renderer* renderer);
void than(point p,SDL_Renderer* renderer,direction huong);
void dauran(vector<point> snake,SDL_Renderer* renderer,direction huong);
void printsnake(vector<point> snake,SDL_Renderer* renderer,Painter but,direction huong);
direction input(SDL_Event e,SDL_Renderer* renderer,direction &huong);
vector<point> updatesnake(vector<point> &snake,direction huong);
void waitUntilKeyPressed();
void pause(SDL_Renderer* renderer);
#endif // PRINT_H_INCLUDED
