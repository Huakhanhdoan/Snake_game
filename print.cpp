
#include"print.h"
void hinhvuong(SDL_Renderer* renderer,Painter but)
{

       SDL_Rect filled_rect;
    filled_rect.x =but.getX();
    filled_rect.y =but.getY();
    filled_rect.w = 20;
    filled_rect.h = 20;
    SDL_RenderFillRect(renderer, &filled_rect);

}
void printpoint( point a,Painter but,SDL_Renderer* renderer)
{
    but.setPosition(a.x,a.y);
    hinhvuong(renderer,but);

}
void printapple(point apple,SDL_Renderer* renderer)
{
        SDL_Rect tao;
      tao={apple.x,apple.y,20,20};
      moveimage(renderer,"testphong.png",tao);

}
void printscore(int score,SDL_Renderer* renderer)
{
    string path=to_string(score)+".png";
    SDL_Rect toado={110,397,40,50};
    moveimage(renderer,"bgscore.png",toado);
    moveimage(renderer,path,toado);

}



void dauran(vector<point> snake,SDL_Renderer* renderer,direction huong)
  {
      SDL_Rect dauran;
      dauran={snake[0].x,snake[0].y,20,20};
      if(huong==direction::down)
      moveimage(renderer,"daurandown.jpg",dauran);
      if(huong==direction::up)
      moveimage(renderer,"dauranup.jpg",dauran);
      if(huong==direction::right)
      moveimage(renderer,"dauranright.jpg",dauran);
      if(huong==direction::left)
      moveimage(renderer,"dauleft.jpg",dauran);

  }
void than(point p,SDL_Renderer* renderer,direction huong)
  {
      SDL_Rect dauran;
      dauran={p.x,p.y,20,20};
      if(huong==direction::left||huong==direction::right)
      moveimage(renderer,"thanngang.jpg",dauran);
      if(huong==direction::up||huong==direction::down)
      moveimage(renderer,"thandoc.jpg",dauran);
  }

void printsnake(vector<point> snake,SDL_Renderer* renderer,Painter but,direction huong)
  {
      dauran(snake,renderer,huong);
      for(int i=1;i<snake.size();i++)
      {
          than(snake[i],renderer,huong);
      }

  }

SDL_Texture* moveimage(SDL_Renderer* renderer,string path,SDL_Rect toado)
  {
      SDL_Surface *bmp = IMG_Load(path.c_str() );
        if (bmp == nullptr) {
        std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
    }
    else
    SDL_SetColorKey(bmp,SDL_TRUE,SDL_MapRGB(bmp->format,0,128,0));
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, bmp);
    SDL_FreeSurface(bmp);
    if (texture == nullptr){
        std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
    }

   // SDL_RenderClear(renderer); // Fill render with color
   if(toado.h==0)
    SDL_RenderCopy(renderer, texture, NULL,NULL);
    else
    SDL_RenderCopy(renderer, texture, NULL,&toado);
    SDL_RenderPresent(renderer);
    return texture;
  }
void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
    if ( SDL_WaitEvent(&e) != 0 &&
    (e.type==SDL_KEYDOWN|| e.type == SDL_QUIT) )
    return;
    SDL_Delay(100);
 }
}


  void pause(SDL_Renderer* renderer)
{
    SDL_Rect toado;
    toado.h=78;
    toado.w=78;
    toado.x=0;
    toado.y=0;
    moveimage(renderer,"pause.png",toado);

    waitUntilKeyPressed();
    moveimage(renderer,"continue.png",toado);

}

vector<point> updatesnake(vector<point> &snake,direction huong)
{
        for(int i=snake.size()-1;i>0;i--)
        snake[i]=snake[i-1];
        switch(huong)
        {
        case direction::up :
        {

            snake[0].y-=20;

        break;
        }
        case direction::down:
        {
        snake[0].y+=20;

        break;

        }

        case  direction::left :
        {
        snake[0].x-=20;
        break;
        }
        case direction::right :
        {
        snake[0].x+=20;
        break;
        }

        }
        return snake;

  };
direction input(SDL_Event e,SDL_Renderer* renderer,direction &huong)
{
    while(SDL_PollEvent( &e ))
    {

    if (e.type == SDL_KEYUP) {

    if(e.key.keysym.sym==SDLK_UP&&huong!=direction::down)
     {
         huong=direction::up;
       return direction::up;
     }
    if(e.key.keysym.sym==SDLK_DOWN&&huong!=direction::up)
      {
         huong=direction::down;
       return direction::down;
     }
    if(e.key.keysym.sym==SDLK_LEFT&&huong!=direction::right)
     {
         huong=direction::left;
       return direction::left;
     }
    if(e.key.keysym.sym==SDLK_RIGHT&&huong!=direction::left)
      {
         huong=direction::right;
       return direction::right;
     }
    if(e.key.keysym.sym==SDLK_q)
    {

    pause(renderer);
    }

    }

    }

};

