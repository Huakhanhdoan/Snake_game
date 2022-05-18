#include"menu.h"
int menugame(SDL_Renderer* renderer,SDL_Event e)
{

     while(SDL_PollEvent( &e ))
    {
     if(e.type == SDL_MOUSEBUTTONDOWN)
    {
        int mouse_x=e.motion.x;
        int mouse_y=e.motion.y;
        if((mouse_x>450&&mouse_x<850)&&(mouse_y>200&&mouse_y<280))   //start
        {

        return 10;
        }
          else if((mouse_x>450&&mouse_x<850)&&(mouse_y>330&&mouse_y<400)) //high score
        {

        return 20;

        }
        else if((mouse_x>450&&mouse_x<850)&&(mouse_y>450&&mouse_y<530)) //exit
        {

        return -30;

        }
        else if(mouse_x>902&&mouse_x<1116&&mouse_y>9&&mouse_y<123)
        {
            return 50;                      // music
        }
          else  return 40;       //khong chon gi

    }
}
}
int selectmenu(SDL_Renderer* renderer,SDL_Window* window,SDL_Texture* texture,SDL_Event e)
{
    int count =0;

    bool temp=true;
while(temp)
{

  switch(menugame(renderer,e))
    {
  case -30:      //exit
        {
    SDL_Delay(200);
     quitSDL(window, renderer,texture);
    return -1;
    break;
        }
    case 10:        //start
        {
    temp=false;
  SDL_Delay(100);
  continue;
        }
    case 20:
        {
            print_hightscore(renderer);
            while(!back_menu(e))
            {
            SDL_Delay(200);                 //backmenu

            }
            SDL_Rect toado={NULL};
            moveimage(renderer,"menu1.png",toado);
            onoff_music(count,renderer);
            break;
        }
    case 50:
        {
            count++;
         onoff_music(count,renderer);
    }
    }
}
return count;
}
void onoff_music(int count,SDL_Renderer* renderer)
{
       SDL_Rect toado;
    toado.h=110;
    toado.w=108;
    toado.x=907;
    toado.y=11;
    if(count%2==0)
    moveimage(renderer,"music.png",toado);
    else
    moveimage(renderer,"turnoff_music.png",toado);
}
void print_hightscore(SDL_Renderer* renderer)
{
    SDL_Rect toado={NULL};

    moveimage(renderer,"highscore.png",toado);
    int score[3];
    ifstream highscore("score.txt");
     highscore>>score[0]>>score[1]>>score[2];
     string path=to_string(score[0])+".png";
     toado={620,215,48,60};
     moveimage(renderer,path,toado);
     path=to_string(score[1])+".png";
     toado={620,335,48,60};
     moveimage(renderer,path,toado);
     path=to_string(score[2])+".png";
     toado={620,460,48,60};
     moveimage(renderer,path,toado);

}
bool check_highscore(int score)
{
    int top[4];
    ifstream highscore("score.txt");
     highscore>>top[0]>>top[1]>>top[2];
    if(score<top[2])
    return false;
    else{
   top[3]=score;
    sort(top,top+4);
    ofstream newhighscore("score.txt");
  newhighscore<<top[3]<<" "<<top[2]<<" "<<top[1];
  return true;
    }
}
bool back_menu(SDL_Event e)
{
    while(SDL_PollEvent( &e ))
    {
     if(e.type == SDL_MOUSEBUTTONDOWN)
    {
        int mouse_x=e.motion.x;
        int mouse_y=e.motion.y;
        if((mouse_x>910&&mouse_x<1000)&&(mouse_y>30&&mouse_y<110))
        {
            return true;
        }
    else return false;
  }

    }
}
int newgame(SDL_Renderer* renderer,SDL_Event e)
{

     while(SDL_PollEvent( &e ))
    {
     if(e.type == SDL_MOUSEBUTTONDOWN)
    {
        int mouse_x=e.motion.x;
        int mouse_y=e.motion.y;
        if((mouse_x>510&&mouse_x<1020)&&(mouse_y>260&&mouse_y<330))   //start
        {

        return 100;
       }


        else if((mouse_x>510&&mouse_x<1020)&&(mouse_y>400&&mouse_y<470)) //exit
        {

        return -100;

        }
        else return 300;

    }

    }
}


