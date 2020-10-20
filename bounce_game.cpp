/*
 *Author:Love Panta
 *Date:20/3/2019
 */
#include<stdio.h>
#include <conio.h>
#include <graphics.h>
#include <dos.h>
#include<stdlib.h>
#define windowMaxX (1700)
#define windowMaxY (750)
// parameters declaration
int Score;
int fallCount;
struct BounceBall
{
  int speedX;
  int speedY;
  int ballX;
  int ballY;
  int xSpeedBall;
  int ySpeedBall;
  int ballRadius;
  int barX;
  int barY;
  int barWidth;
  int barHeight;
  int barSpeed;
  char outputText[20];
};
//function declaration
struct BounceBall* initilize();
void operation(struct BounceBall *);
void setOutputWindow(struct BounceBall *);
void DrawBall(struct BounceBall *);
void DrawBar(struct BounceBall *);
void play();
void setMenu();

int main()
{
 initwindow(windowMaxX,windowMaxY);
 setbkcolor(7);
 cleardevice();
 setMenu();
 getch();
 play();
 getch();
 closegraph();
}

struct BounceBall* initilize()
{
    BounceBall *constrain=(struct BounceBall *)malloc(sizeof(struct BounceBall));
    constrain->speedX=7;
    constrain->speedY=5;
    constrain->xSpeedBall=constrain->speedX;
    constrain->ySpeedBall=constrain->speedY;
    constrain->ballY=30;
    constrain->barX=150;
    constrain->barY=700;
    constrain->barSpeed=20;
    constrain->ballRadius=15;
    constrain->barHeight=10;
    constrain->barWidth=150;
    return constrain;
}
void DrawBall(struct BounceBall * ball)
{    setcolor(RED);
     setfillstyle(SOLID_FILL,BLUE);
     circle(ball->ballX,ball->ballY, ball->ballRadius);
     floodfill(ball->ballX, ball->ballY, RED);
}

void DrawBar(struct BounceBall *Bar)
{
setcolor(RED);
setfillstyle(SOLID_FILL,BLUE);
bar(Bar->barX,Bar->barY,Bar->barX+Bar->barWidth,Bar->barY+Bar->barHeight);
}

void setMenu()
{
 settextstyle(4,0,6);
 setcolor(RED);
 outtextxy(300,100,"BOUNCING PINBALL");
 outtextxy(5,300,"ENTER ANY KEY TO START THE GAME");
 setfillstyle(SOLID_FILL,BLUE);
 circle(550,500, 50);
 floodfill(550,500, RED);
 bar(400,600,700,620);
}

void setOutputWindow(struct BounceBall *game){
delay(1);
cleardevice();
settextstyle(4,0,6);
setcolor(RED);
outtextxy( 350,300,"GAMEOVER");
sprintf(game->outputText,"YOUR TOTAL SCORE IS %d",Score);
outtext(game->outputText);
delay(1000);
cleardevice();
settextstyle(4,0,5);
setcolor(RED);
outtextxy(50,300,"RESTART THE GAME:");
outtextxy(50,400,"PRESS ANY KEY");
delay(2000);
getch();
}

void operation(struct BounceBall *game)
{ //get the random position for ball and slider
game->ballX=(rand()%(getmaxx()-200))+100;
game->barX=(rand()%(getmaxx()-300))+100;

while(1)
{// get input data from the keyboard
if (game->barX>game->barSpeed && (game->barX+game->barWidth < getmaxx()-game->barSpeed))
 {
  if(GetAsyncKeyState(VK_LEFT))
    game->barX=game->barX-game->barSpeed;
  else if(GetAsyncKeyState(VK_RIGHT))
    game->barX+=game->barSpeed;
 }

else if (game->barX<game->barSpeed)
{
  if(GetAsyncKeyState(VK_RIGHT))
    game->barX+=game->barSpeed;
}
else
{
  if(GetAsyncKeyState(VK_LEFT))
    game->barX=game->barX-game->barSpeed;
}
game->ballX+=game->xSpeedBall;
game->ballY+=game->ySpeedBall;

if(game->ballX>=getmaxx()-game->ballRadius)
           game->xSpeedBall=-game->speedX;

else if (game->ballX<=game->ballRadius)
           game->xSpeedBall=game->speedX;

else if (game->ballY<=game->ballRadius)
           game->ySpeedBall=game->speedY;

else if(game->ballY>=(game->barY-game->ballRadius) && game->ballX>=game->barX-25 && game->ballX<=game->barX+game->barWidth+25)
    {
      if(game->ballY == (game->barY-game->ballRadius))
      {
          Score+=10;
          game->speedY+=2;
          game->speedX++;
      }
      if (game->ballX>=game->barX-25 && game->ballX <= (game->barX + game->barWidth/2))
      {
          game->xSpeedBall=-game->speedX;
          game->ySpeedBall=-game->speedY;
      }
      else if((game->ballX <= game->barX+game->barWidth+25) && game->ballX >= (game->barX + game->barWidth/2))
      {
          game->xSpeedBall=game->speedX;
          game->ySpeedBall=-game->speedY;
      }
    }

else if(game->ballY>=game->barY-30 && ((game->ballX<=game->barX-15) || game->ballX>=(game->barX+game->barWidth+15)))
    {
       fallCount++;
       BounceBall *game=initilize();
       if (game!=NULL)
       {
         operation(game);
       }
    }
if (fallCount>5)
{
    break;
}
DrawBall(game);
DrawBar(game);
delay(1);
cleardevice();
  }
}
void play()
{
  while(1)
 {
   fallCount=0;
   Score=0;
   BounceBall *game=initilize();
   if (game!=NULL)
   {
   operation(game);
   setOutputWindow(game);
   }
 }
}
