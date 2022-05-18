#include <iostream>
#include<vector>
#include<ctime>
#include <SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include"snakesdl.h"
#include"print.h"
#include"menu.h"
const int WIDTH = 1280;
const int HEIGHT = 720;

void logSDLError(std::ostream& os,
const std::string &msg, bool fatal = false);
void logSDLError(std::ostream& os,
 const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
    SDL_Quit();
    exit(1);
    }
}
using namespace std;
const string WINDOW_TITLE = "An Implementation of Code.org Painter";
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer,SDL_Texture* texture);
void waitUntilKeyPressed();
point getapple();
bool eatapple(vector<point> snake,point &apple);
bool logicgame(vector<point> snake);
void audio_eat(string path,int count);
int main( int argc, char* args[] )
{
    srand(time(0));
   SDL_Window* window;
    SDL_Renderer* renderer;     // khai bao and load bg
    initSDL(window, renderer);
   Painter but(window,renderer);
   direction huong=direction::right;
    SDL_Rect toado={NULL};
    SDL_Texture* texture=moveimage(renderer,"snakegame.jpg",toado);
    SDL_Delay(1000);
    SDL_Event e;
    moveimage(renderer,"menu1.png",toado);
    int count=selectmenu(renderer,window,texture,e);            //menu
    if(count==-1)
    return 0;


do {
        audio_eat("nhacnen2.wav",count);
        huong=direction::right;
         vector<point> snake = {
        point{ WIDTH/ 2 + 40, HEIGHT/ 2 },
        point{ WIDTH/ 2 + 20, HEIGHT/ 2 },
        point{ WIDTH/ 2 , HEIGHT/ 2 },                  //khai bao snake,apple,score
        point{ WIDTH/ 2 - 20, HEIGHT/ 2 },
        point{ WIDTH/ 2 - 40, HEIGHT/ 2 },
        };
        int score=0;
        point apple=getapple();
        moveimage(renderer,"bgsnake2.png",toado);
        printsnake(snake,renderer,but,huong);
        printscore(score,renderer);
    while(logicgame(snake))
    {

        point duoicu={snake[snake.size()-1].x,snake[snake.size()-1].y};
        printapple(apple,renderer);
        if(eatapple(snake,apple))
        {
            audio_eat("eat_apple.wav",count);
            snake.push_back(duoicu);
            printapple(apple,renderer);
            score++;
            printscore(score,renderer);
        }
        input(e,renderer,huong);
        updatesnake(snake,huong);
        if(logicgame(snake)==false)
            continue;
        dauran(snake,renderer,huong);
        than(snake[1],renderer,huong);
        but.setColor(GREENPLUS_COLOR);
        printpoint(duoicu,but,renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(200);                     // speed game
    }
    SDL_Delay(500);
    Mix_HaltChannel(-1);
    check_highscore(score);
    SDL_Rect toado={470,220,500,300};
    moveimage(renderer,"endgame.png",toado);
    SDL_Delay(1000);
    int i=newgame(renderer,e);
    while(i!=100&&i!=-100)
        {
            i=newgame(renderer,e);
            SDL_Delay(500);
        }
    if(i==-100)
        break;

}while(1);

    SDL_Delay(1000);
    quitSDL(window, renderer,texture);
    return 0;
}







void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    logSDLError(std::cout, "SDL_Init", true);
    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);
    //Khi chạy trong môi trường bình thường (không chạy trong máy ảo)
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
    SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT);
}
// logicgame and eat applepoint getapple()
point getapple()
{
    int x=0;
    int y=0;
    point apple(x,y);
    while(true)
    {
    apple.x=300+(rand()%41+1)*20;
    apple.y=100+(rand()%24+1)*20;
    if((apple.y==300||apple.y==400)&&(apple.x>540&&apple.x<880)) // apple k vao 2 thanh giua
    {
        continue;
    }
    else
        break;

    }
    return apple;
}
bool eatapple(vector<point> snake,point &apple)
{


    if(snake[0].x == apple.x && snake[0].y == apple.y)
    {

        bool dem=false;
        while(true)
        {
            dem=false;
            apple=getapple();
            for(int i=1;i<snake.size();i++)
            {
                if(snake[i].x==apple.x&& snake[i].y==apple.y)
                {
                    dem=true;
                   break;
                }

            }

            if(dem==false)
                break;

        }
        return true;
    }
    else return false;

}
bool logicgame(vector<point> snake)
{
    for(int i=1;i<snake.size();i++)
    {
    if(snake[0].x==snake[i].x&&snake[0].y==snake[i].y)  // tranh can duoi
    {
        Mix_HaltMusic();
        return false;
    }
    }
    if((snake[0].x>1120||snake[0].x<300||snake[0].y<100||snake[0].y>600) // traanh ra ngoai mapp
       || ((snake[0].y==300||snake[0].y==400)&&(snake[0].x>540&&snake[0].x<880)))
       {

            return false;
       }

    return true;
}

void audio_eat(string path,int count)
{

    if(count%2==0)
    {
       Mix_Chunk* audio;
   Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096);      //audio
    audio=Mix_LoadWAV(path.c_str());
    Mix_PlayChannel(-1,audio,0);
    }
}
