#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <string.h>
#define realwidth 1000
#define width 700
#define height 700
//#include "undo and redo.h"
int e=0,f=0,p,x=0,playerturn = 0, player = 1,moves[2] = {0},totalmoves=0,maxmoves = 0,points[2] = {0},dim=0,computer,starttime,endtime,diftime = 0;
char game=0,name1[25],name2[25]="Computer",ss[1],sG;
bool mouse = false, SDLrun = false,quit = false,ran = false;
FILE *saved;
SDL_Window *window;
SDL_Renderer *renderer;
TTF_Font *font;
SDL_Surface *imgwallpaper;
SDL_Surface *saveimg;
SDL_Surface *imgredo;
SDL_Surface *imgundo;
SDL_Surface *returnbuttonimg;
SDL_Surface *imagedots;
SDL_Texture *wallpaper;
SDL_Texture *redoicon;
SDL_Texture *undoicon;
SDL_Texture *dots;
SDL_Texture *saveicon;
SDL_Texture *returnbutton;
SDL_Surface *logoimg;
SDL_Texture *logo;
void initSDL(){
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG | IMG_INIT_PNG);

    window = SDL_CreateWindow("dots and boxes",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,realwidth,height,SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    font = TTF_OpenFont("Lato-Italic.ttf",23);

    imgwallpaper = IMG_Load("wallpaper.jpg");
    saveimg = IMG_Load("saveicon.png");
    imgredo = IMG_Load("redo.png");
    imgundo = IMG_Load("undo.png");
    returnbuttonimg = IMG_Load("BACK.png");
    imagedots = IMG_Load("dots.png");
    logoimg = IMG_Load("LOGO.jpg");
    wallpaper = SDL_CreateTextureFromSurface(renderer,imgwallpaper);
    redoicon = SDL_CreateTextureFromSurface(renderer,imgredo);
    undoicon = SDL_CreateTextureFromSurface(renderer,imgundo);
    dots = SDL_CreateTextureFromSurface(renderer,imagedots);
    saveicon = SDL_CreateTextureFromSurface(renderer,saveimg);
    returnbutton = SDL_CreateTextureFromSurface(renderer,returnbuttonimg);
    logo = SDL_CreateTextureFromSurface(renderer,logoimg);
}

void killSDL(){
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}


void update(char world[dim][dim],int mx1,int my1){
    int shift,L,wz,hv,e,f,linex,liney;
    float a,b,c,d;
    switch(dim){
    case 7:
        a = 0.8;
        b = 0.8;
        c = 0.3;
        d = 0.3;
        e = 20;
        f = 20;
        shift = 30;
        L = 50;
        wz = 200;
        hv = 200;
        break;
    case 11:
        a = 0.65;
        b = 0.6;
        c = 0.38;
        d = 0.35;
        e = 15;
        f = 15;
        shift = 8;
        L = 50;
        wz = 130;
        hv = 125;
        break;
    case 15:
        a = 0.65;
        b = 0.65;
        c = 0.29;
        d = 0.24;
        e = 15;
        f = 15;
        shift = 8;
        L = 30;
        wz = 90;
        hv = 90;
        break;

    }
    char scoreline[30] = "";
    char scorenum[5] = "";
    strcat(scoreline,name1);
    strcat(scoreline," (1): ");
    itoa(points[0],scorenum,10);
    strcat(scoreline,scorenum);

    SDL_Rect pos = {.x = 0,.y = 0,realwidth,height};

    SDL_RenderCopy(renderer,wallpaper,NULL,&pos);




    SDL_Color color = {200,200,200,255};

    SDL_Surface *scoretextimg1 = TTF_RenderText_Blended(font,scoreline,color);

    SDL_Texture *scoretext1 = SDL_CreateTextureFromSurface(renderer,scoretextimg1);

    SDL_FreeSurface(scoretextimg1);

    pos.x = 710;
    pos.y = 300;

    SDL_QueryTexture(scoretext1,NULL,NULL,&pos.w,&pos.h);

    SDL_RenderCopy(renderer,scoretext1,NULL,&pos);

    SDL_DestroyTexture(scoretext1);


    scoreline[0] = '\0';
    scorenum[0] = '\0';
    if(!computer){
        strcat(scoreline,name2);
        strcat(scoreline," (2): ");
        itoa(points[1],scorenum,10);
        strcat(scoreline,scorenum);
    }else{
        strcat(scoreline,"Computer (2): ");
        itoa(points[1],scorenum,10);
        strcat(scoreline,scorenum);
    }
    SDL_Surface *scoretextimg2 = TTF_RenderText_Blended(font,scoreline,color);

    SDL_Texture *scoretext2 = SDL_CreateTextureFromSurface(renderer,scoretextimg2);

    SDL_FreeSurface(scoretextimg2);

    pos.x = 710;
    pos.y = 320;

    SDL_QueryTexture(scoretext2,NULL,NULL,&pos.w,&pos.h);

    SDL_RenderCopy(renderer,scoretext2,NULL,&pos);

    SDL_DestroyTexture(scoretext2);

    scoreline[0] = '\0';
    scorenum[0] = '\0';
    strcat(scoreline,"PLAYER TURN : ");
    itoa(player,scorenum,10);
    strcat(scoreline,scorenum);

    SDL_Surface *playerturntextimg = TTF_RenderText_Blended(font,scoreline,color);

    SDL_Texture *playerturntext = SDL_CreateTextureFromSurface(renderer,playerturntextimg);

    SDL_FreeSurface(playerturntextimg);

    pos.x = 710;
    pos.y = 350;

    SDL_QueryTexture(playerturntext,NULL,NULL,&pos.w,&pos.h);

    SDL_RenderCopy(renderer,playerturntext,NULL,&pos);

    SDL_DestroyTexture(playerturntext);


    scoreline[0] = '\0';
    scorenum[0] = '\0';
    strcat(scoreline,"PLAYER ONE MOVES: ");
    itoa(moves[0],scorenum,10);
    strcat(scoreline,scorenum);

    SDL_Surface *player1movesimg = TTF_RenderText_Blended(font,scoreline,color);

    SDL_Texture *player1moves = SDL_CreateTextureFromSurface(renderer,player1movesimg);

    SDL_FreeSurface(player1movesimg);

    pos.x = 710;
    pos.y = 380;

    SDL_QueryTexture(player1moves,NULL,NULL,&pos.w,&pos.h);

    SDL_RenderCopy(renderer,player1moves,NULL,&pos);

    SDL_DestroyTexture(player1moves);


    scoreline[0] = '\0';
    scorenum[0] = '\0';
    strcat(scoreline,"PLAYER TWO MOVES: ");
    itoa(moves[1],scorenum,10);
    strcat(scoreline,scorenum);

    SDL_Surface *player2movesimg = TTF_RenderText_Blended(font,scoreline,color);

    SDL_Texture *player2moves = SDL_CreateTextureFromSurface(renderer,player2movesimg);

    SDL_FreeSurface(player2movesimg);

    pos.x = 710;
    pos.y = 400;

    SDL_QueryTexture(player2moves,NULL,NULL,&pos.w,&pos.h);

    SDL_RenderCopy(renderer,player2moves,NULL,&pos);

    SDL_DestroyTexture(player2moves);

    scoreline[0] = '\0';
    scorenum[0] = '\0';
    strcat(scoreline,"REMAINED MOVES: ");
    itoa((2 * (dim/2) * (dim/2 + 1)) - (moves[0] + moves[1]),scorenum,10);

    strcat(scoreline,scorenum);

    SDL_Surface *remainedmovesimg = TTF_RenderText_Blended(font,scoreline,color);

    SDL_Texture *remainedmove = SDL_CreateTextureFromSurface(renderer,remainedmovesimg);

    SDL_FreeSurface(remainedmovesimg);

    pos.x = 710;
    pos.y = 430;

    SDL_QueryTexture(remainedmove,NULL,NULL,&pos.w,&pos.h);

    SDL_RenderCopy(renderer,remainedmove,NULL,&pos);

    SDL_DestroyTexture(remainedmove);

    endtime = SDL_GetTicks();
    scoreline[0] = '\0';
    scorenum[0] = '\0';
    strcat(scoreline,"TIME: ");
    itoa(((((endtime - starttime)/1000 + diftime)/60)%60),scorenum,10);
    strcat(scoreline,scorenum);
    strcat(scoreline," : ");
    itoa(((((endtime - starttime)/1000)+diftime)%60),scorenum,10);

    strcat(scoreline,scorenum);

    SDL_Surface *timepassedimg = TTF_RenderText_Blended(font,scoreline,color);

    SDL_Texture *timepassed = SDL_CreateTextureFromSurface(renderer,timepassedimg);

    SDL_FreeSurface(timepassedimg);

    pos.x = 710;
    pos.y = 460;

    SDL_QueryTexture(timepassed,NULL,NULL,&pos.w,&pos.h);

    SDL_RenderCopy(renderer,timepassed,NULL,&pos);

    SDL_DestroyTexture(timepassed);



    pos.x = 710;
    pos.y = 120;
    pos.w = 100;
    pos.h = 100;
    SDL_RenderCopy(renderer,saveicon,NULL,&pos);


    pos.x = 900;
    pos.y = 20;
    pos.w = 80;
    pos.h = 80;
    SDL_RenderCopy(renderer,redoicon,NULL,&pos);



    pos.x = 720;
    pos.y = 20;
    pos.w = 80;
    pos.h = 80;
    SDL_RenderCopy(renderer,undoicon,NULL,&pos);









    SDL_Texture *returnbutton = SDL_CreateTextureFromSurface(renderer,returnbuttonimg);


    pos.x = 700;
    pos.y = 600;
    pos.w = 280;
    pos.h = 50;

    SDL_RenderCopy(renderer,returnbutton,NULL,&pos);

    SDL_DestroyTexture(returnbutton);


    if(mouse){
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_GetMouseState(&linex,&liney);
        SDL_RenderDrawLine(renderer,mx1,my1,linex,liney);
    }
    for(int i=0;i<dim;i++){
        for(int j=0;j<dim;j++){
            if(world[i][j] == '0' || world[i][j] == '2' || world[i][j] == '3'){

                if((i%2 && !(j%2)) && world[i][j] != ' '){ // HORIZONTAL
                    pos.x = (i-a) * width/dim + shift;
                    pos.y = (j) * height/dim + shift;
                    pos.w = wz;
                    pos.h = L;
                    if(world[i][j] == '2')
                        SDL_SetRenderDrawColor(renderer,230,0,0,255);
                    else if(world[i][j] == '3')
                        SDL_SetRenderDrawColor(renderer,0,0,230,255);

                    SDL_RenderFillRect(renderer,&pos);
                }else if((!(i%2) && (j%2) )&& world[i][j] != ' '){ // VERTICAL
                    pos.x = (i) * width/dim + shift;
                    pos.y = (j-b) * height/dim + shift;
                    pos.w = L;
                    pos.h = hv;
                    if(world[i][j] == '2')
                        SDL_SetRenderDrawColor(renderer,230,0,0,255);
                    else if(world[i][j] == '3')
                        SDL_SetRenderDrawColor(renderer,0,0,230,255);
                    SDL_RenderFillRect(renderer,&pos);
                }

            }
            else if(world[i][j] == 'X'){

                SDL_SetRenderDrawColor(renderer,180,0,0,255);
                pos.x = (i-a+c) * width/dim + shift;
                pos.y = (j-b+d) * height/dim + shift;
                pos.w = wz - e;
                pos.h = hv - f;

                SDL_RenderFillRect(renderer,&pos);
            }
            else if(world[i][j] == 'O'){

                SDL_SetRenderDrawColor(renderer,0,0,180,255);
                pos.x = (i-a+c) * width/dim + shift;
                pos.y = (j-b+d) * height/dim + shift;
                pos.w = wz - e;
                pos.h = hv - f;

                SDL_RenderFillRect(renderer,&pos);
            }
        }
    }
    for(int i=0;i<dim;i=i+2){
        for(int j=0;j<dim;j=j+2){
            pos.x = i * width/dim + shift;
            pos.y = j * height/dim + shift;
            pos.w = L;
            pos.h = L;
            SDL_RenderCopy(renderer,dots,NULL,&pos);
        }
    }

    SDL_RenderPresent(renderer);

}

void updatesave(bool save){
    SDL_Rect pos;
    SDL_Surface *save1iconimg = IMG_Load("1saveimg.png");
    SDL_Texture *save1icon = SDL_CreateTextureFromSurface(renderer,save1iconimg);
    SDL_FreeSurface(save1iconimg);
    if(save){
        pos.x = 800;
        pos.y = 120;
        pos.w = 120;
        pos.h = 80;
    }
    else{
        pos.x = 600;
        pos.y = 500;
        pos.w = 120;
        pos.h = 80;
    }

    SDL_RenderCopy(renderer,save1icon,NULL,&pos);
    SDL_DestroyTexture(save1icon);

    SDL_Surface *save2iconimg = IMG_Load("2saveimg.png");
    SDL_Texture *save2icon = SDL_CreateTextureFromSurface(renderer,save2iconimg);
    SDL_FreeSurface(save2iconimg);
    if(save){
        pos.x = 900;
        pos.y = 120;
        pos.w = 120;
        pos.h = 80;
    }else{
        pos.x = 700;
        pos.y = 500;
        pos.w = 120;
        pos.h = 80;
    }
    SDL_RenderCopy(renderer,save2icon,NULL,&pos);
    SDL_DestroyTexture(save2icon);

    SDL_Surface *save3iconimg = IMG_Load("3saveimg.png");
    SDL_Texture *save3icon = SDL_CreateTextureFromSurface(renderer,save3iconimg);
    SDL_FreeSurface(save3iconimg);
    if(save){
        pos.x = 800;
        pos.y = 180;
        pos.w = 120;
        pos.h = 80;
    }else{
        pos.x = 800;
        pos.y = 500;
        pos.w = 120;
        pos.h = 80;
    }
    SDL_RenderCopy(renderer,save3icon,NULL,&pos);
    SDL_DestroyTexture(save3icon);

    SDL_Surface *save4iconimg = IMG_Load("4saveimg.png");
    SDL_Texture *save4icon = SDL_CreateTextureFromSurface(renderer,save4iconimg);
    SDL_FreeSurface(save4iconimg);
    if(save){
        pos.x = 900;
        pos.y = 180;
        pos.w = 120;
        pos.h = 80;
    }else{
        pos.x = 270;
        pos.y = 500;
        pos.w = 120;
        pos.h = 80;
    }
    SDL_RenderCopy(renderer,save4icon,NULL,&pos);
    SDL_DestroyTexture(save4icon);

    SDL_Surface *save5iconimg = IMG_Load("5saveimg.png");
    SDL_Texture *save5icon = SDL_CreateTextureFromSurface(renderer,save5iconimg);
    SDL_FreeSurface(save5iconimg);
    if(save){
        pos.x = 800;
        pos.y = 230;
        pos.w = 120;
        pos.h = 80;
    }else{
        pos.x = 170;
        pos.y = 500;
        pos.w = 120;
        pos.h = 80;
    }
    SDL_RenderCopy(renderer,save5icon,NULL,&pos);
    SDL_DestroyTexture(save5icon);
    printf("sadas");


    SDL_RenderPresent(renderer);
}
void gamemenu(){

    SDL_Rect pos = {.x = 0,.y = 0,realwidth,height};
    SDL_RenderCopy(renderer,wallpaper,NULL,&pos);


    SDL_Surface *logoimg = IMG_Load("LOGO.jpg");
    SDL_Texture *logo = SDL_CreateTextureFromSurface(renderer,logoimg);
    SDL_FreeSurface(logoimg);
    pos.x = 250;
    pos.y = 0;
    pos.w = 500;
    pos.h = 300;
    SDL_RenderCopy(renderer,logo,NULL,&pos);
    SDL_DestroyTexture(logo);

    SDL_Surface *newgameiconimg = IMG_Load("NEWGAME.png");
    SDL_Texture *newgameicon = SDL_CreateTextureFromSurface(renderer,newgameiconimg);
    SDL_FreeSurface(newgameiconimg);
    pos.x = 350;
    pos.y = 400;
    pos.w = 300;
    pos.h = 80;
    SDL_RenderCopy(renderer,newgameicon,NULL,&pos);
    SDL_DestroyTexture(newgameicon);

    SDL_Surface *loadgameiconimg = IMG_Load("LOADGAME.png");
    SDL_Texture *loadgameicon = SDL_CreateTextureFromSurface(renderer,loadgameiconimg);
    SDL_FreeSurface(loadgameiconimg);
    pos.x = 350;
    pos.y = 500;
    pos.w = 300;
    pos.h = 80;
    SDL_RenderCopy(renderer,loadgameicon,NULL,&pos);
    SDL_DestroyTexture(loadgameicon);

    SDL_Surface *leaderboardiconimg = IMG_Load("LEADERBOARD.png");
    SDL_Texture *leaderboardicon = SDL_CreateTextureFromSurface(renderer,leaderboardiconimg);
    SDL_FreeSurface(leaderboardiconimg);
    pos.x = 350;
    pos.y = 600;
    pos.w = 300;
    pos.h = 80;
    SDL_RenderCopy(renderer,leaderboardicon,NULL,&pos);
    SDL_DestroyTexture(leaderboardicon);


    SDL_RenderPresent(renderer);
}

void newgamemenu(){
    SDL_Surface *imgwallpaper = IMG_Load("wallpaper.jpg");
    SDL_Texture *wallpaper = SDL_CreateTextureFromSurface(renderer,imgwallpaper);
    SDL_FreeSurface(imgwallpaper);
    SDL_Rect pos = {.x = 0,.y = 0,realwidth,height};
    SDL_RenderCopy(renderer,wallpaper,NULL,&pos);
    SDL_DestroyTexture(wallpaper);

    SDL_Surface *logoimg = IMG_Load("LOGO.jpg");
    SDL_Texture *logo = SDL_CreateTextureFromSurface(renderer,logoimg);
    SDL_FreeSurface(logoimg);
    pos.x = 250;
    pos.y = 0;
    pos.w = 500;
    pos.h = 300;
    SDL_RenderCopy(renderer,logo,NULL,&pos);
    SDL_DestroyTexture(logo);

    SDL_Surface *newgameiconimg = IMG_Load("vscomputer.png");
    SDL_Texture *newgameicon = SDL_CreateTextureFromSurface(renderer,newgameiconimg);
    SDL_FreeSurface(newgameiconimg);
    pos.x = 350;
    pos.y = 400;
    pos.w = 300;
    pos.h = 80;
    SDL_RenderCopy(renderer,newgameicon,NULL,&pos);
    SDL_DestroyTexture(newgameicon);

    SDL_Surface *loadgameiconimg = IMG_Load("vsplayer.png");
    SDL_Texture *loadgameicon = SDL_CreateTextureFromSurface(renderer,loadgameiconimg);
    SDL_FreeSurface(loadgameiconimg);
    pos.x = 350;
    pos.y = 500;
    pos.w = 300;
    pos.h = 80;
    SDL_RenderCopy(renderer,loadgameicon,NULL,&pos);
    SDL_DestroyTexture(loadgameicon);

    SDL_Surface *leaderboardiconimg = IMG_Load("BACK.png");
    SDL_Texture *leaderboardicon = SDL_CreateTextureFromSurface(renderer,leaderboardiconimg);
    SDL_FreeSurface(leaderboardiconimg);
    pos.x = 350;
    pos.y = 600;
    pos.w = 300;
    pos.h = 80;
    SDL_RenderCopy(renderer,leaderboardicon,NULL,&pos);
    SDL_DestroyTexture(leaderboardicon);


    SDL_RenderPresent(renderer);
}

void difcultnewgamemenu(){
    SDL_Surface *imgwallpaper = IMG_Load("wallpaper.jpg");
    SDL_Texture *wallpaper = SDL_CreateTextureFromSurface(renderer,imgwallpaper);
    SDL_FreeSurface(imgwallpaper);
    SDL_Rect pos = {.x = 0,.y = 0,realwidth,height};
    SDL_RenderCopy(renderer,wallpaper,NULL,&pos);
    SDL_DestroyTexture(wallpaper);

    SDL_Surface *logoimg = IMG_Load("LOGO.jpg");
    SDL_Texture *logo = SDL_CreateTextureFromSurface(renderer,logoimg);
    SDL_FreeSurface(logoimg);
    pos.x = 250;
    pos.y = 0;
    pos.w = 500;
    pos.h = 300;
    SDL_RenderCopy(renderer,logo,NULL,&pos);
    SDL_DestroyTexture(logo);

    SDL_Surface *newgameiconimg = IMG_Load("EASYBUTTON.png");
    SDL_Texture *newgameicon = SDL_CreateTextureFromSurface(renderer,newgameiconimg);
    SDL_FreeSurface(newgameiconimg);
    pos.x = 350;
    pos.y = 300;
    pos.w = 300;
    pos.h = 80;
    SDL_RenderCopy(renderer,newgameicon,NULL,&pos);
    SDL_DestroyTexture(newgameicon);

    SDL_Surface *loadgameiconimg = IMG_Load("NORMALBUTTON.png");
    SDL_Texture *loadgameicon = SDL_CreateTextureFromSurface(renderer,loadgameiconimg);
    SDL_FreeSurface(loadgameiconimg);
    pos.x = 350;
    pos.y = 400;
    pos.w = 300;
    pos.h = 80;
    SDL_RenderCopy(renderer,loadgameicon,NULL,&pos);
    SDL_DestroyTexture(loadgameicon);

    SDL_Surface *HARDgameiconimg = IMG_Load("HARDBUTTON.png");
    SDL_Texture *HARDgameicon = SDL_CreateTextureFromSurface(renderer,HARDgameiconimg);
    SDL_FreeSurface(HARDgameiconimg);
    pos.x = 350;
    pos.y = 500;
    pos.w = 300;
    pos.h = 80;
    SDL_RenderCopy(renderer,HARDgameicon,NULL,&pos);
    SDL_DestroyTexture(HARDgameicon);


    SDL_Surface *leaderboardiconimg = IMG_Load("BACKBUTTON.png");
    SDL_Texture *leaderboardicon = SDL_CreateTextureFromSurface(renderer,leaderboardiconimg);
    SDL_FreeSurface(leaderboardiconimg);
    pos.x = 350;
    pos.y = 600;
    pos.w = 300;
    pos.h = 80;
    SDL_RenderCopy(renderer,leaderboardicon,NULL,&pos);
    SDL_DestroyTexture(leaderboardicon);


    SDL_RenderPresent(renderer);
}
void leaderboard(){
    char scoreline[30] = "";
    char scorenum[5] = "";
    SDL_Color color = {200,200,200,255};
    font = TTF_OpenFont("Lato-Italic.ttf",36);

    SDL_Surface *imgwallpaper = IMG_Load("wallpaper.jpg");
    SDL_Texture *wallpaper = SDL_CreateTextureFromSurface(renderer,imgwallpaper);
    SDL_FreeSurface(imgwallpaper);
    SDL_Rect pos = {.x = 0,.y = 0,realwidth,height};
    SDL_RenderCopy(renderer,wallpaper,NULL,&pos);
    SDL_DestroyTexture(wallpaper);

    SDL_Surface *scoretextimg1 = TTF_RenderText_Blended(font,"<vs Computer>",color);
    SDL_Texture *scoretext1 = SDL_CreateTextureFromSurface(renderer,scoretextimg1);
    SDL_FreeSurface(scoretextimg1);
    pos.x = 60 ;
    pos.y = 50 ;
    SDL_QueryTexture(scoretext1,NULL,NULL,&pos.w,&pos.h);
    SDL_RenderCopy(renderer,scoretext1,NULL,&pos);
    SDL_DestroyTexture(scoretext1);

    scoretextimg1 = TTF_RenderText_Blended(font,"<vs Player>",color);
    scoretext1 = SDL_CreateTextureFromSurface(renderer,scoretextimg1);
    SDL_FreeSurface(scoretextimg1);
    pos.x = 560 ;
    pos.y = 50 ;
    SDL_QueryTexture(scoretext1,NULL,NULL,&pos.w,&pos.h);
    SDL_RenderCopy(renderer,scoretext1,NULL,&pos);
    SDL_DestroyTexture(scoretext1);

    int j,y,u=0;char names[10][25],v[10],i=0,score[10];
    FILE *bS;
    for(u=0;u<2;u++){
        if(u==0){
            bS=fopen("Ranks1.bin","r");
        }else{
            bS=fopen("Ranks2.bin","r");
            i=0;
        }
        fread(&i,sizeof(char),1,bS);
        for(j=0;j<i;j++){
            fread(&v[j],sizeof(char),1,bS);
            fread(names+j,sizeof(char),v[j],bS);
            fread(&score[j],sizeof(char),1,bS);
            scoreline[0] = '\0';
            scorenum[0] = '\0';
            strncat(scoreline,names[j],v[j]);
            strcat(scoreline," : ");
            itoa(score[j],scorenum,10);
            strcat(scoreline,scorenum);

            SDL_Surface *scoretextimg1 = TTF_RenderText_Blended(font,scoreline,color);

            SDL_Texture *scoretext1 = SDL_CreateTextureFromSurface(renderer,scoretextimg1);

            SDL_FreeSurface(scoretextimg1);

            pos.x = 100 + u * 500;
            pos.y = 110 + j*60;

            SDL_QueryTexture(scoretext1,NULL,NULL,&pos.w,&pos.h);

            SDL_RenderCopy(renderer,scoretext1,NULL,&pos);

            SDL_DestroyTexture(scoretext1);

        }
        fclose(bS);
    }
    SDL_RenderPresent(renderer);
    font = TTF_OpenFont("Lato-Italic.ttf",23);

}
void displaygameresult(){
    char scoreline[30] = "CONGRATULATIONS ";
    SDL_Color color = {255,255,255,255};
    font = TTF_OpenFont("Lato-Italic.ttf",50);
        if(points[1]>points[0]){
            if(!computer){
                strcat(scoreline,name2);
                scores(points[1],strlen(name2),name2);
            }
            else{
                strcat(scoreline,"Computer");
            }
        }else if(points[1] < points[0]){
            strcat(scoreline,name1);
            scores(points[0],strlen(name1),name1);
        }else{
            scoreline[0] = '\0';
            strcat(scoreline,"WELL PLAYEd A TIE");

        }
    strcat(scoreline," !!!");
    SDL_Surface *scoretextimg1 = TTF_RenderText_Blended(font,scoreline,color);
    SDL_Texture *scoretext1 = SDL_CreateTextureFromSurface(renderer,scoretextimg1);
    SDL_FreeSurface(scoretextimg1);
    SDL_Rect pos = {.x = 100,.y = 150};
    SDL_QueryTexture(scoretext1,NULL,NULL,&pos.w,&pos.h);
    SDL_RenderCopy(renderer,scoretext1,NULL,&pos);
    SDL_DestroyTexture(scoretext1);





    scoretextimg1 = TTF_RenderText_Blended(font,"Press anywhere to return.",color);
    scoretext1 = SDL_CreateTextureFromSurface(renderer,scoretextimg1);
    SDL_FreeSurface(scoretextimg1);
    pos.x = 250;
    pos.y = 350;
    SDL_QueryTexture(scoretext1,NULL,NULL,&pos.w,&pos.h);
    SDL_RenderCopy(renderer,scoretext1,NULL,&pos);
    SDL_DestroyTexture(scoretext1);
    SDL_RenderPresent(renderer);
    font = TTF_OpenFont("Lato-Italic.ttf",23);
}
void nameinput(){
    font = TTF_OpenFont("Lato-Italic.ttf",40);

    SDL_Surface *imgwallpaper = IMG_Load("wallpaper.jpg");
    SDL_Texture *wallpaper = SDL_CreateTextureFromSurface(renderer,imgwallpaper);
    SDL_FreeSurface(imgwallpaper);
    SDL_Rect pos = {.x = 0,.y = 0,realwidth,height};
    SDL_RenderCopy(renderer,wallpaper,NULL,&pos);
    SDL_DestroyTexture(wallpaper);

    SDL_Surface *logoimg = IMG_Load("LOGO.jpg");
    SDL_Texture *logo = SDL_CreateTextureFromSurface(renderer,logoimg);
    SDL_FreeSurface(logoimg);
    pos.x = 250;
    pos.y = 0;
    pos.w = 500;
    pos.h = 300;
    SDL_RenderCopy(renderer,logo,NULL,&pos);
    SDL_DestroyTexture(logo);

    pos.x = 300;
    pos.y = 400;
    pos.w = 350;
    pos.h = 60;
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderFillRect(renderer,&pos);

    SDL_Color color = {200,200,200,255};
    SDL_Surface *scoretextimg1 = TTF_RenderText_Blended(font,"Player One :",color);
    SDL_Texture *scoretext1 = SDL_CreateTextureFromSurface(renderer,scoretextimg1);
    SDL_FreeSurface(scoretextimg1);
    pos.x = 100;
    pos.y = 400;
    SDL_QueryTexture(scoretext1,NULL,NULL,&pos.w,&pos.h);
    SDL_RenderCopy(renderer,scoretext1,NULL,&pos);
    SDL_DestroyTexture(scoretext1);

    imgwallpaper = IMG_Load("PLAY.png");
    wallpaper = SDL_CreateTextureFromSurface(renderer,imgwallpaper);
    SDL_FreeSurface(imgwallpaper);
    pos.x = 300;
    pos.y = 600;
    pos.w = 300;
    pos.h = 80;
    SDL_RenderCopy(renderer,wallpaper,NULL,&pos);
    SDL_DestroyTexture(wallpaper);


    if(!computer){
        pos.x = 300;
        pos.y = 500;
        pos.w = 350;
        pos.h = 60;
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_RenderFillRect(renderer,&pos);

        SDL_Color color = {200,200,200,255};
        SDL_Surface *scoretextimg1 = TTF_RenderText_Blended(font,"Player Two :",color);
        SDL_Texture *scoretext1 = SDL_CreateTextureFromSurface(renderer,scoretextimg1);
        SDL_FreeSurface(scoretextimg1);
        pos.x = 100;
        pos.y = 500;
        SDL_QueryTexture(scoretext1,NULL,NULL,&pos.w,&pos.h);
        SDL_RenderCopy(renderer,scoretext1,NULL,&pos);
        SDL_DestroyTexture(scoretext1);

    }


    name1[0] = '\0';
    if(!computer)
        name2[0] = '\0';
    char tempname[20] = "";
    int p = 0;
    bool done = false;
    SDL_Event event;
    int mx,my;
    while( !done )
        {
            bool renderText = false;
            while( (SDL_PollEvent( &event ) != 0))
            {
                if( event.type == SDL_QUIT )
                {
                    killSDL();
                    quit = true;
                    done = true;
                    return;
                }

                else if(event.type == SDL_MOUSEBUTTONDOWN){
                    SDL_GetMouseState(&mx,&my);
                    if(mx<700 && mx>300 && my>500 && my<560){
                        SDL_StartTextInput();
                        strcpy(tempname,name2);
                        p = 2;
                    }
                    else if(mx<700 && mx>300 && my>400 && my<460){
                        SDL_StartTextInput();
                        strcpy(tempname,name1);
                        p = 1;
                    }
                    else if(mx>300 && mx<600 && my>600 && my<680)
                        done =true;
                    else{
                        SDL_StopTextInput();
                        p = 0;
                    }
                }
                if(p){
                        if( event.type == SDL_KEYDOWN )
                        {
                            if( event.key.keysym.sym == SDLK_BACKSPACE && strlen(tempname) > 0 )
                            {
                                tempname[strlen(tempname)-1] = '\0';
                                renderText = true;
                            }
                            else if( event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL )
                            {
                                SDL_SetClipboardText(tempname);
                            }
                            else if( event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL )
                            {
                                strncat(tempname,SDL_GetClipboardText(),12-strlen(tempname));
                                renderText = true;
                            }
                        }
                        else if( event.type == SDL_TEXTINPUT )
                        {
                            if( !( SDL_GetModState() & KMOD_CTRL && ( event.text.text[ 0 ] == 'c' || event.text.text[ 0 ] == 'C' || event.text.text[ 0 ] == 'v' || event.text.text[ 0 ] == 'V' ) || strlen(tempname)>11 ) )
                            {
                                strncat(tempname,event.text.text,1);
                                renderText = true;
                            }
                        }
                }
            }
            if( renderText )
            {
                pos.x = 0;
                pos.y = 0;
                pos.w = realwidth;
                pos.h = height;
                SDL_RenderCopy(renderer,wallpaper,NULL,&pos);


                pos.x = 250;
                pos.y = 0;
                pos.w = 500;
                pos.h = 300;
                SDL_RenderCopy(renderer,logo,NULL,&pos);


                pos.x = 300;
                pos.y = 400;
                pos.w = 350;
                pos.h = 60;
                SDL_SetRenderDrawColor(renderer,255,255,255,255);
                SDL_RenderFillRect(renderer,&pos);

                color.r = 200;
                color.g = 200;
                color.b = 200;
                SDL_Surface *scoretextimg1 = TTF_RenderText_Blended(font,"Player One :",color);
                SDL_Texture *scoretext1 = SDL_CreateTextureFromSurface(renderer,scoretextimg1);
                SDL_FreeSurface(scoretextimg1);
                pos.x = 100;
                pos.y = 400;
                SDL_QueryTexture(scoretext1,NULL,NULL,&pos.w,&pos.h);
                SDL_RenderCopy(renderer,scoretext1,NULL,&pos);
                SDL_DestroyTexture(scoretext1);
                color.r = 0;
                color.g = 0;
                color.b = 0;
                if(!computer){
                    pos.x = 300;
                    pos.y = 500;
                    pos.w = 350;
                    pos.h = 60;
                    SDL_SetRenderDrawColor(renderer,255,255,255,255);
                    SDL_RenderFillRect(renderer,&pos);

                    SDL_Color color = {200,200,200,255};
                    SDL_Surface *scoretextimg1 = TTF_RenderText_Blended(font,"Player Two :",color);
                    SDL_Texture *scoretext1 = SDL_CreateTextureFromSurface(renderer,scoretextimg1);
                    SDL_FreeSurface(scoretextimg1);
                    pos.x = 100;
                    pos.y = 500;
                    SDL_QueryTexture(scoretext1,NULL,NULL,&pos.w,&pos.h);
                    SDL_RenderCopy(renderer,scoretext1,NULL,&pos);
                    SDL_DestroyTexture(scoretext1);

                }
                if(p == 1){
                    scoretextimg1 = TTF_RenderText_Blended(font,tempname,color);
                    scoretext1 = SDL_CreateTextureFromSurface(renderer,scoretextimg1);
                    SDL_FreeSurface(scoretextimg1);
                    pos.x = 310;
                    pos.y = 400;
                    SDL_QueryTexture(scoretext1,NULL,NULL,&pos.w,&pos.h);
                    SDL_RenderCopy(renderer,scoretext1,NULL,&pos);
                    SDL_DestroyTexture(scoretext1);
                    strcpy(name1,tempname);
                }else if(p == 2){
                    strcpy(name2,tempname);
                }

                scoretextimg1 = TTF_RenderText_Blended(font,name1,color);
                scoretext1 = SDL_CreateTextureFromSurface(renderer,scoretextimg1);
                SDL_FreeSurface(scoretextimg1);
                pos.x = 310;
                pos.y = 400;
                SDL_QueryTexture(scoretext1,NULL,NULL,&pos.w,&pos.h);
                SDL_RenderCopy(renderer,scoretext1,NULL,&pos);
                SDL_DestroyTexture(scoretext1);
                if(!computer){
                    scoretextimg1 = TTF_RenderText_Blended(font,name2,color);
                    scoretext1 = SDL_CreateTextureFromSurface(renderer,scoretextimg1);
                    SDL_FreeSurface(scoretextimg1);
                    pos.x = 310;
                    pos.y = 500;
                    SDL_QueryTexture(scoretext1,NULL,NULL,&pos.w,&pos.h);
                    SDL_RenderCopy(renderer,scoretext1,NULL,&pos);
                    SDL_DestroyTexture(scoretext1);
                }
                imgwallpaper = IMG_Load("PLAY.png");
                wallpaper = SDL_CreateTextureFromSurface(renderer,imgwallpaper);
                SDL_FreeSurface(imgwallpaper);
                pos.x = 300;
                pos.y = 600;
                pos.w = 300;
                pos.h = 80;
                SDL_RenderCopy(renderer,wallpaper,NULL,&pos);
                SDL_DestroyTexture(wallpaper);
            }
            SDL_RenderPresent(renderer);
			}
			SDL_StopTextInput();
			font = TTF_OpenFont("Lato-Italic.ttf",23);
}


void printAIwolrd(int dim,int AIworld[dim][dim]){
    for(int i=0;i<dim;i++){
        for(int j=0;j<dim;j++){
            printf("%d  ",AIworld[i][j]);
        }
        printf("\n");
    }
}
void createAIwolrd(int dim,int AIworld[dim][dim]){
    for(int i=0;i<dim;i++){
        for(int j=0;j<dim;j++){
            AIworld[i][j] = 0;
        }
    }
}


void printhistory(int dim,int history[][7]){
    for(int i=0;i<maxmoves;i++){
        for(int j=0;j<7;j++){
            printf("  %d -",history[i][j]);
        }
        printf("\n");
    }
}


void printworld(int dim,char array[dim][dim]){
    for(int i=0;i<dim;i++){
        for(int j=0;j<dim;j++){
            printf("%c  ",array[j][i]);
        }
        printf("\n");
    }
}
void createworld(int dim,char array[dim][dim]){
    for(int i=0;i<dim;i++){
        for(int j=0;j<dim;j++){
            if(!(j%2 || i%2))
                array[i][j]='0';
            else
                array[i][j]=' ';
        }
    }
}
void createhistory(int dim,int history[2 * (dim/2) * ((dim/2) + 1)][7]){
    for(int i=0;i<2 * (dim/2) * ((dim/2) + 1);i++){
        for(int j=0;j<7;j++){
            history[i][j] = 0;
        }
    }
}
void resetarray(int array[]){
    for(int i=0;i<2;i++)
        array[i] = 0;
}

int checkforotherlines(int dim,int history[][7],char array[][dim],int n1,int m1){
    int f=0;
    if(array[n1][m1+1] != ' ')
        f++;
    if(array[n1][m1-1] != ' ')
        f++;
    if(array[n1+1][m1] != ' ')
        f++;
    if(array[n1-1][m1] != ' ')
        f++;
    return f;
}




int upperright(int n1,int m1,int dim,char array[dim][dim]){
    if((m1 == dim -1) || (n1 == 0) || array[n1-1][m1+1] == 'X' || array[n1-1][m1+1] == 'O')
        return 0;
    if(array[n1][m1+1]!=' '){
            if(array[n1-1][m1]!=' '){
                if(array[n1-1][m1+2]!=' '){
                    if(array[n1-2][m1+1]!=' '){
                        switch(player){
                            case 1:
                                array[n1-1][m1+1] = 'X';
                                break;
                            case 2:

                                array[n1-1][m1+1] = 'O';
                                break;
                        }
                        return 1;
                    }
                }
            }
    }
   return 0;
}
int upperleft(int n1,int m1,int dim,char array[dim][dim]){
    if((m1 == 0) || (n1 == 0) || array[n1-1][m1-1] == 'X' || array[n1-1][m1-1] == 'O')
        return 0;
    if(array[n1][m1-1]!=' '){
            if(array[n1-1][m1]!=' '){
                if(array[n1-1][m1-2]!=' '){
                    if(array[n1-2][m1-1]!=' '){
                        switch(player){
                            case 1:
                                array[n1-1][m1-1] = 'X';
                                break;
                            case 2:

                                array[n1-1][m1-1] = 'O';
                                break;
                        }
                        return 1;
                    }
                }
            }
    }
    return 0;
}
int downright(int n1,int m1,int dim,char array[dim][dim]){
    if((m1 == dim -1) || (n1 == dim -1) || array[n1+1][m1+1] == 'X' || array[n1+1][m1+1] == 'O')
        return 0;
    if(array[n1][m1+1]!=' '){
            if(array[n1+1][m1]!=' '){
                if(array[n1+1][m1+2]!=' '){
                    if(array[n1+2][m1+1]!=' '){
                        switch(player){
                            case 1:

                                array[n1+1][m1+1] = 'X';
                                break;
                            case 2:

                                array[n1+1][m1+1] = 'O';
                                break;
                        }
                        return 1;
                    }
                }
            }
    }
    return 0;
}
int downleft(int n1,int m1,int dim,char array[dim][dim]){
    if((m1 == 0) || (n1 == dim-1) || array[n1+1][m1-1] == 'X' || array[n1+1][m1-1] == 'O')
        return 0;
    if(array[n1][m1-1]!=' '){
            if(array[n1+1][m1]!=' '){
                if(array[n1+1][m1-2]!=' '){
                    if(array[n1+2][m1-1]!=' '){
                        switch(player){
                            case 1:

                                array[n1+1][m1-1] = 'X';
                                break;
                            case 2:

                                array[n1+1][m1-1] = 'O';
                                break;
                        }
                        return 1;
                    }
                }
            }
    }
    return 0;
}
void checkforsquares(int n1,int m1,int dim,char array[dim][dim],int history[][7],int points[]){
    int sum=0;
    sum = upperright(n1,m1,dim,array) + upperleft(n1,m1,dim,array) + downright(n1,m1,dim,array) + downleft(n1,m1,dim,array);
    if(playerturn % 2)
        points[1] += sum;
    else
        points[0] += sum;
    playerturn++;
    switch(player){
        case 1:
            moves[0]++;
            break;
        case 2:
            moves[1]++;
    }
    if(sum != 0){
        playerturn++;
    }
    else{
        player=player==1?2:1;
    }

}

void undo(int dim,int history[][7],char array[dim][dim]){
    if(totalmoves > 0){
        totalmoves--;
        int n1 = history[totalmoves][0] , m1 = history[totalmoves][1] ,  n2 = history[totalmoves][2] ,  m2 = history[totalmoves][3];
        array[(history[totalmoves][0]+history[totalmoves][2])/2][(history[totalmoves][1]+history[totalmoves][3])/2] =' ';
        if(!(checkforotherlines(dim,history,array,history[totalmoves][0],history[totalmoves][1]) >= 1))
            array[history[totalmoves][0]][history[totalmoves][1]] = '0';

        if(!(checkforotherlines(dim,history,array,history[totalmoves][2],history[totalmoves][3]) >= 1))
            array[history[totalmoves][2]][history[totalmoves][3]] = '0';

        if(n1==n2){
            if(n1==0)
                array[n1+1][(m1+m2)/2]=' ';
            else if(n1==dim-1)
                array[n1-1][(m1+m2)/2]=' ';
            else{
                array[n1+1][(m1+m2)/2]=' ';
                array[n1-1][(m1+m2)/2]=' ';
            }
        }else{
            if(m1==0)
                array[(n1+n2)/2][m1+1]=' ';
            else if(n1==dim-1)
                array[(n1+n2)/2][m1-1]=' ';
            else{
                array[(n1+n2)/2][m1+1]=' ';
                array[(n1+n2)/2][m1-1]=' ';
            }
        }
        if(player==history[totalmoves][6]){
            playerturn-=2;
            switch(player){
            case 1:
                points[0]--;
                break;
            case 2:
                points[1]--;
            }
        }
        else
            playerturn--;
        player = history[totalmoves][6];
        switch(player){
            case 1:
                moves[0]--;
                break;
            case 2:
                moves[1]--;
                break;
        }
    }else{
        printf("\a");

    }
}

void redo(int dim,int history[][7],char array[dim][dim]){
    if(totalmoves < maxmoves && (maxmoves > 1)){
        int n1 = history[totalmoves][0];int m1 = history[totalmoves][1];
        if(history[totalmoves][6] == 1)
            array[(history[totalmoves][0]+history[totalmoves][2])/2][(history[totalmoves][1]+history[totalmoves][3])/2] ='2';
        else if(history[totalmoves][6] == 2)
            array[(history[totalmoves][0]+history[totalmoves][2])/2][(history[totalmoves][1]+history[totalmoves][3])/2] ='3';
        array[history[totalmoves][0]][history[totalmoves][1]] = '1';

        array[history[totalmoves][2]][history[totalmoves][3]] = '1';

        checkforsquares(n1,m1,dim,array,history,points);
        totalmoves++;

    }else{
        printf("\a");

    }
}

void saveGame(int totalmoves,int dim,int AIworld[dim][dim],char array[dim][dim],int history[][7]){
    if(x==0){
        SDL_Event event;
        int mx,my;
        bool done = false;
        updatesave(true);
        done = false;
        while(!done){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                killSDL();
                quit = true;
                done = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&mx,&my);
                    if(mx/100 == 8 && my/100 == 1){
                        sG = '1';
                        done = true;
                    }
                    else if(mx/100 == 9 && my/100 == 1){
                        sG = '2';
                        done = true;
                    }
                    else if(mx/100 == 8 && my/100 == 2 && my%100 < 50){
                        sG = '3';
                        done = true;
                    }
                    else if(mx/100 == 9 && my/100 == 2){
                        sG = '4';
                        done = true;
                    }
                    else if(mx/100 == 8 && my/100 == 2 && my%100 > 50){
                        sG = '5';
                        done = true;
                    }
                    else if(mx/100 == 7 && my/100 == 1){
                        return;
                    }
                    break;
            }

        }
        if(sG=='5'){
            saved = fopen("saved5.bin","w");
            x=5;
        }
        else if(sG=='1'){
            saved = fopen("saved1.bin","w");
            x=1;
        }
        else if(sG=='2'){
            saved = fopen("saved2.bin","w");
            x=2;
        }
        else if(sG=='3'){
            saved = fopen("saved3.bin","w");
            x=3;
        }
        else if(sG=='4'){
            saved = fopen("saved4.bin","w");
            x=4;
        }
        else{
            return;
        }
    }else{
        if(sG=='5')
            saved = fopen("saved5.bin","w");
        else if(sG=='1')
            saved = fopen("saved1.bin","w");
        else if(sG=='2')
            saved = fopen("saved2.bin","w");
        else if(sG=='3')
            saved = fopen("saved3.bin","w");
        else if(sG=='4')
            saved = fopen("saved4.bin","w");
    }
    fwrite(&computer,sizeof(int),1,saved);
    fwrite(&dim,sizeof(int),1,saved);
    fwrite(&totalmoves,sizeof(int),1,saved);
    for(int i=0;i<totalmoves;i++){
        for(int j=0;j<7;j++)
            fwrite(&history[i][j],1,(dim)*(dim),saved);

    }
    for(int i=0;i<dim;i++){
        for(int j=0;j<dim;j++)
            fwrite(&array[i][j],1,(dim)*(dim),saved);

    }
    for(int i=0;i<2;i++)
        fwrite(&moves[i],sizeof(int),2,saved);
    fwrite(&playerturn,sizeof(int),1,saved);
    fwrite(&maxmoves,sizeof(int),1,saved);

    if(computer){
        for(int i=0;i<dim;i++){
            for(int j=0;j<dim;j++)
                fwrite(&AIworld[i][j],1,(dim)*(dim),saved);
        }
    }
    char tempdif[10];
    itoa(((endtime - starttime)/1000)+diftime,tempdif,10);
    fwrite(&tempdif,sizeof(char),10,saved);
    int e = strlen(name1);
    int f = strlen(name2);
    fwrite(&e,sizeof(int),1,saved);fwrite(&name1,sizeof(char),e,saved);
    if(!computer)
        fwrite(&f,sizeof(int),1,saved);fwrite(&name2,sizeof(char),f,saved);

    fclose(saved);
}





void makeamove(int dim,char array[dim][dim],int n1,int m1,int n2,int m2,int points[],int history[][7],int AIworld[dim][dim]){

    if(!computer && player == 2 || player == 1){

        if((array[((n1+n2)/2)][((m1+m2)/2)] !=' ') || (n1 > dim - 1) || (m1 > dim - 1) || (n2 > dim - 1) || (m2 > dim - 1) || (n1 < 0) || (m1 < 0) || (n2 < 0) || (m2 < 0) || !(((abs(n1-n2) == 2) && (m1==m2)) ^ ((abs(m1-m2) == 2) && (n1==n2)))){

            return;
        }
        history[totalmoves][0] = n1 ; history[totalmoves][1] = m1 ;history[totalmoves][2] = n2 ; history[totalmoves][3] = m2;

    }else{
        AI(dim,array,AIworld,history);
    }

    history[totalmoves][6] = player;


    if(!(history[totalmoves][1]%2 || history[totalmoves][0]%2 )){
        array[history[totalmoves][0]][history[totalmoves][1]] = '1';
        array[history[totalmoves][2]][history[totalmoves][3]] = '1';
        if(player == 1)
            array[(history[totalmoves][0]+history[totalmoves][2])/2][(history[totalmoves][1]+history[totalmoves][3])/2] ='2';
        else if(player == 2)
            array[(history[totalmoves][0]+history[totalmoves][2])/2][(history[totalmoves][1]+history[totalmoves][3])/2] ='3';
    }


    checkforsquares(history[totalmoves][0],history[totalmoves][1],dim,array,history,points);
    history[totalmoves][4] = points[0];
    history[totalmoves][5] = points[1];

    if((totalmoves < maxmoves))
        maxmoves = totalmoves;

        maxmoves++;
        totalmoves++;
}

void AI(int dim,char world[dim][dim],int AIworld[dim][dim],int history[][7]){
    int numberoflines1,numberoflines2;
    // checks horizontal lines
    for(int i=0;i<dim;i=i+2){
        for(int j=1;j<dim;j=j+2){
            numberoflines1 = 0;
            numberoflines2 = 0;
            if(world[i][j] != ' ')
                AIworld[i][j] = -100;
            else{
                if( i != 0){
                    if(world[i-1][j+1] != ' ')
                         numberoflines1++;
                    if(world[i-1][j-1] != ' ')
                         numberoflines1++;
                    if(world[i-2][j] != ' ')
                         numberoflines1++;
                    if(numberoflines1 == 3)
                         numberoflines1 += 10;
                    else if(numberoflines1 == 2)
                        numberoflines1 -=10;
                }
                if( i != dim - 1){
                    if(world[i+1][j-1] != ' ')
                         numberoflines2++;
                    if(world[i+1][j+1] != ' ')
                         numberoflines2++;
                    if(world[i+2][j] != ' ')
                         numberoflines2++;
                    if(numberoflines2 == 3)
                        numberoflines2 +=10;
                    else if(numberoflines2 == 2)
                        numberoflines2 -=10;
                }
                AIworld[i][j] = numberoflines1 + numberoflines2;
            }
        }
    }
    //checks vertical lines
    for(int i=1;i<dim;i=i+2){
        for(int j=0;j<dim;j=j+2){
            numberoflines1 = 0;
            numberoflines2 = 0;
            if(world[i][j] != ' ')
                AIworld[i][j] = -100;
            else{
                if( j != 0){
                    if(world[i-1][j-1] != ' ')
                         numberoflines1++;
                    if(world[i+1][j-1] != ' ')
                         numberoflines1++;
                    if(world[i][j-2] != ' ')
                         numberoflines1++;
                    if(numberoflines1 == 3)
                         numberoflines1 += 10;
                    else if(numberoflines1 == 2)
                        numberoflines1 -=10;
                }
                if( j != dim-1){
                    if(world[i+1][j+1] != ' ')
                         numberoflines2++;
                    if(world[i-1][j+1] != ' ')
                         numberoflines2++;
                    if(world[i][j+2] != ' ')
                         numberoflines2++;
                    if(numberoflines2 == 3)
                        numberoflines2 +=10;
                    else if(numberoflines2 == 2)
                        numberoflines2 -=10;
                }
                AIworld[i][j] = numberoflines1 + numberoflines2;
            }
        }
    }
    int maxi,maxj,max=-100;
    for(int i=1;i<dim;i=i+2){
        for(int j=0;j<dim;j=j+2){
            if(AIworld[i][j] > max){
                max = AIworld[i][j];
                maxi = i;
                maxj = j;
            }
        }
    }
    for(int i=0;i<dim;i=i+2){
        for(int j=1;j<dim;j=j+2){
            if(AIworld[i][j] > max){
                max = AIworld[i][j];
                maxi = i;
                maxj = j;
            }
        }
    }
    if(!(maxi%2)){
        history[totalmoves][0] = maxi;
        history[totalmoves][1] = maxj-1;
        history[totalmoves][2] = maxi;
        history[totalmoves][3] = maxj+1;
    }else{
        history[totalmoves][0] = maxi-1;
        history[totalmoves][1] = maxj;
        history[totalmoves][2] = maxi+1;
        history[totalmoves][3] = maxj;

    }


}

int scores(int point,int l,char name[l]){
    int j,y[10],u=0,t;char names[10][25],v[10],i=0,score[10]={0};
    FILE *lB;
    if(computer)
        lB = fopen("Ranks1.bin","r");
    else
        lB = fopen("Ranks2.bin","r");
    fread(&i,sizeof(char),1,lB);
    if(i!=0){
        for(j=0;j<i;j++){
            fread(&v[j],sizeof(char),1,lB);
            fread(names+j,sizeof(char),v[j],lB);
            fread(&score[j],sizeof(char),1,lB);
            if(point<=score[j])
                u++;
        }
        fclose(lB);
    }
    if(i!=9)
        i++;
    if(u!=9){
        if(computer)
            lB = fopen("Ranks1.bin","w");
        else
            lB = fopen("Ranks2.bin","w");
        fwrite(&i,sizeof(char),1,lB);
        for(j=0;j<u;j++){
            fwrite(&v[j],sizeof(char),1,lB);
            fwrite(names+j,sizeof(char),v[j],lB);
            fwrite(&score[j],sizeof(char),1,lB);
        }
        fwrite(&l,sizeof(char),1,lB);
        fwrite(name,sizeof(char),l,lB);
        fwrite(&point,sizeof(char),1,lB);
        for(j=u;j<i-1;j++){
            fwrite(&v[j],sizeof(char),1,lB);
            fwrite(names+j,sizeof(char),v[j],lB);
            fwrite(&score[j],sizeof(char),1,lB);
        }
    }
    fclose(lB);
    return;
}

void loadGame(){
    updatesave(false);
    FILE *load;
    SDL_MouseButtonEvent event;
    int mx,my;
    bool done = false;
    while(!done){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                    quit = true;
                    killSDL();
                    return;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(event.button == SDL_BUTTON_LEFT){
                    SDL_GetMouseState(&mx,&my);
                    if(((mx/100 == 6) && (mx>620)) && my/100 == 5){
                        sG = '1';
                        done = true;
                    }
                    else if((mx/100 == 7 && mx > 723)  && my/100 == 5){
                        sG = '2';
                        done = true;
                    }
                    else if((mx/100 == 8 && mx > 823) && my/100 == 5){
                        sG = '3';
                        done = true;
                    }
                    else if(((mx > 290) && (mx < 370))&& my/100 == 5){
                        sG = '4';
                        done = true;
                    }
                    else if(((mx>180) && (mx<270))&& my/100 == 5){
                        sG = '5';
                        done = true;
                    }
                    else if(((mx>350) && (mx<670))&& my/100 == 5){
                        sG = '6';
                        done = true;
                    }
                    break;
            }
        }

    }

    if(sG=='5'){
        load = fopen("saved5.bin","r");
        x=5;
    }
    else if(sG=='1'){
        load = fopen("saved1.bin","r");
        x=1;
    }
    else if(sG=='2'){
        load = fopen("saved2.bin","r");
        x=2;
    }
    else if(sG=='3'){
        load = fopen("saved3.bin","r");
        x=3;
    }
    else if(sG=='4'){
        load = fopen("saved4.bin","r");
        x=4;
    }
    else
        return;
    fread(&computer,sizeof(int),1,load);
    fread(&dim,sizeof(int),1,load);
    fread(&totalmoves,sizeof(int),1,load);
    int history[2 * (dim/2) * ((dim/2) + 1)][7];
    char world[dim][dim];
    int AIworld[dim][dim];
    for(int i=0;i<totalmoves;i++){
        for(int j=0;j<7;j++)
            fread(&history[i][j],1,(dim)*(dim),load);

    }
    for(int i=0;i<dim;i++){
        for(int j=0;j<dim;j++)
            fread(&world[i][j],1,(dim)*(dim),load);

    }
    for(int i=0;i<2;i++)
        fread(&moves[i],sizeof(int),2,load);
    fread(&playerturn,sizeof(int),1,load);
    fread(&maxmoves,sizeof(int),1,load);
    if(computer){
        for(int i=0;i<dim;i++){
            for(int j=0;j<dim;j++)
                fread(&AIworld[i][j],1,(dim)*(dim),load);
        }
    }
    char tempdif[10];
    fread(&tempdif,sizeof(char),10,load);
    diftime = atoi(tempdif);
    fread(&e,sizeof(int),1,load);fread(&name1,sizeof(char),e,load);
    if(!computer)
        fread(&f,sizeof(int),1,load);fread(&name2,sizeof(char),f,load);

    fclose(load);
    points[0] = history[totalmoves-1][4];
    points[1] = history[totalmoves-1][5];
    int mx1 = 0, my1 = 0, mx2 = 0, my2 = 0;
    starttime = SDL_GetTicks();
    while(totalmoves<2*((dim/2)+1)*(dim/2) && !quit){
        if(totalmoves!=0)
            p = totalmoves;
        else
            p=1;
        update(world,mx1,my1);
        if(computer && (player == 2)){
            makeamove(dim,world,NULL,NULL,NULL,NULL,points,history,AIworld);
        }else{
        SDL_PollEvent(&event);
                switch(event.type){
                case SDL_QUIT:
                    quit = true;
                    killSDL();
                    goto end;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if(event.button == SDL_BUTTON_LEFT){
                        mouse = true;
                        SDL_GetMouseState(&mx1,&my1);
                        if(mx1/100 == 7 && my1/100 == 0){
                            undo(dim,history,world);
                            while(computer && history[totalmoves][6] == 2)
                                undo(dim,history,world);
                        }
                        else if(mx1/100 == 9 && my1/100 == 0){
                            redo(dim,history,world);
                            while(computer && history[totalmoves][6] == 2 && totalmoves < maxmoves)
                                redo(dim,history,world);
                        }
                        else if(mx1/100 == 7 && my1/100 == 1){
                                saveGame(totalmoves,dim,AIworld,world,history);
                        }
                        else if(mx1 > 720 && my1/100 == 6){
                                goto end;
                        }else
                            mouse = true;
                    }
                        break;
                case SDL_MOUSEBUTTONUP:
                    mouse = false;
                    if(event.button == SDL_BUTTON_LEFT){
                        SDL_GetMouseState(&mx2,&my2);
                    }
                    if(!((mx1/(height/dim))%2 || (my1/(width/dim))%2 || (mx2/(height/dim)%2 || (my2/(width/dim))%2))){
                        makeamove(dim,world,mx1/(height/dim),my1/(width/dim),mx2/(height/dim),my2/(width/dim),points,history,AIworld);
                    }
                    break;
                }
        }
    }
        update(world,mx1,my1);
        done = false;
        x=0;
        if(totalmoves==2*((dim/2)+1)*(dim/2)){
            if(points[1]>points[0]){
                if(!computer){
                    displaygameresult(name2);
                    scores(points[1],strlen(name2),name2);
                }
                else{
                    displaygameresult("Computer");

                }
            }else{
                if(!computer){

                    displaygameresult(name1);
                }else{

                    displaygameresult(name1);
                }
                scores(points[0],strlen(name1),name1);
            }
        }

        while(!done){
            while(SDL_PollEvent(&event) && !quit){
                switch(event.type){
                    case SDL_QUIT:
                        killSDL();
                        quit = true;
                        return;
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        done = true;
                        break;
                }
            }
        }
    end:
}




void oneNewGame(){
    difcultnewgamemenu();
    SDL_MouseButtonEvent event;
    bool done = false;
    int mx1,my1;
    while(!done && !quit){
        while(SDL_WaitEvent(&event) && !done){
        switch(event.type){
            case SDL_QUIT:
                quit = true;
                killSDL();
                return;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(event.button == SDL_BUTTON_LEFT){
                    SDL_GetMouseState(&mx1,&my1);

                    if(mx1>380 && mx1<610){
                    switch(my1/100){
                    case 3:
                        game = '1';
                        done = true;
                        break;
                    case 4:
                        game = '2';
                        done = true;
                        break;
                    case 5:
                        game = '3';
                        done = true;
                        break;
                    case 6:
                        game = '0';
                        done = true;
                    }
                    }
            }
        }
    }
    }
    computer = 1;

    switch(game){
        case '0':
            return newGame();
            break;
        case '1':
            do{
            nameinput();
            }while((strlen(name1) > 12 || strlen(name1) == 0) && !quit);
            dim = 7;
            break;
        case '2':
            do{
            nameinput();
            }while((strlen(name1) > 12 || strlen(name1) == 0) && !quit);
            dim = 11;
            break;
        case '3':
            do{
            nameinput();
            }while((strlen(name1) > 12 || strlen(name1) == 0) && !quit);
            dim = 15;
            break;
        default:
            oneNewGame();

    }
}

void twoNewGame(){
    difcultnewgamemenu();
    SDL_MouseButtonEvent event;
    bool done = false;
    int mx1,my1;
    while(!done && !quit){
        while(SDL_WaitEvent(&event) && !done){
        switch(event.type){
            case SDL_QUIT:
                quit = true;
                killSDL();
                return;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(event.button == SDL_BUTTON_LEFT){
                    SDL_GetMouseState(&mx1,&my1);
                    if(mx1>380 && mx1<610){
                    switch(my1/100){
                    case 3:
                        game = '1';
                        done = true;
                        break;
                    case 4:
                        game = '2';
                        done = true;
                        break;
                    case 5:
                        game = '3';
                        done = true;
                        break;
                    case 6:
                        game = '0';
                        done = true;
                    }
                    }
            }
        }
    }
    }

    switch(game){
        case '0':
            return newGame();
            break;
        case '1':
            do{
            nameinput();
            }while((strlen(name1) > 12 || strlen(name2) > 12 || strlen(name1) == 0 || strlen(name2) == 0) && !quit);
            dim = 7;
            break;
        case '2':
            do{
            nameinput();
            }while((strlen(name1) > 12 || strlen(name2) > 12 || strlen(name1) == 0 || strlen(name2) == 0) && !quit);
            dim = 11;
            break;
        case '3':
            do{
            nameinput();
            }while((strlen(name1) > 12 || strlen(name2) > 12 || strlen(name1) == 0 || strlen(name2) == 0) && !quit);
            dim = 15;
            break;
        default:
            twoNewGame();
            break;
    }
}

void newGame(){
    newgamemenu();
    SDL_MouseButtonEvent event;
    bool done = false;
    int mx1,my1;
    game = '0';
    while(!done && !quit){
        while(SDL_WaitEvent(&event) && !done){
        switch(event.type){
            case SDL_QUIT:
                quit = true;
                killSDL();
                return;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(event.button == SDL_BUTTON_LEFT){
                    SDL_GetMouseState(&mx1,&my1);
                    if(mx1>350 && mx1<650){
                    switch(my1/100){
                        case 4:
                            game = '1';
                            done = true;
                            break;
                        case 5:
                            game = '2';
                            done = true;
                            break;
                        case 6:
                            game = '0';
                            done = true;
                            break;
                    }
                }
                }
            }
        }
    }
    switch(game){
    case '0':
        main(NULL,NULL);
        break;
    case '1':
        computer = 1;
        oneNewGame();
        break;
    case '2':
        computer = 0;
        twoNewGame();
        break;
    default:
        newGame();
        break;
    }
}



int main(int argc,char* argv[]){
    do{
    if(!SDLrun){
        initSDL();
        SDLrun = true;
    }
    jump:
    x = 0;
    diftime = 0;
    gamemenu();
    SDL_MouseButtonEvent event;
    int mx1 = 0, my1 = 0, mx2 = 0, my2 = 0;
    bool done = false;
    while(!done && !quit){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                quit = true;
                killSDL();
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(event.button == SDL_BUTTON_LEFT){
                    SDL_GetMouseState(&mx1,&my1);

                    printf(""); // leave it as it is!!!!!

                    if(my1/100 == 4 && (mx1>350 && mx1<650)){
                        game = '1';
                        done = true;
                    }
                    else if(my1/100 == 5 && (mx1>380 && mx1<630)){
                        game = '2';
                        done = true;
                    }
                    else if(my1/100 == 6 && (mx1>380 && mx1<630)){
                        game = '3';
                        done = true;
                    }
                    break;
            }
        }
    }

    switch(game){
    case '1':{
        do{
            newGame();
        }while(dim == 0 && !quit);
        if(quit)
            return 0;
        int history[2 * (dim/2) * ((dim/2) + 1)][7];
        char world[dim][dim];

        createworld(dim,world);


        int AIworld[dim][dim];

        createAIwolrd(dim,AIworld);

        createhistory(dim,history);

        resetarray(points);

        resetarray(moves);

        playerturn = 0;

        SDL_MouseButtonEvent click;

        totalmoves = 0;
        player = 1;
        starttime = SDL_GetTicks();
        ran = false;
        while(totalmoves<2*((dim/2)+1)*(dim/2) && !quit){
            if(totalmoves!=0)
                p = totalmoves;
            else
                p=1;
            update(world,mx1,my1);
            ran = true;
            if(computer && (player == 2)){
                makeamove(dim,world,NULL,NULL,NULL,NULL,points,history,AIworld);
                SDL_Delay(100);
            }else{
            SDL_PollEvent(&click);
                    switch(click.type){
                    case SDL_QUIT:
                            quit = true;
                            killSDL();
                            goto end;
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        if(click.button == SDL_BUTTON_LEFT){
                            SDL_GetMouseState(&mx1,&my1);
                            if(mx1/100 == 7 && my1/100 == 0){
                                undo(dim,history,world);
                                while(computer && history[totalmoves][6] == 2)
                                    undo(dim,history,world);
                            }
                            else if(mx1/100 == 9 && my1/100 == 0){
                                redo(dim,history,world);
                                while(computer && history[totalmoves][6] == 2 && totalmoves < maxmoves)
                                    redo(dim,history,world);
                            }
                            else if(mx1/100 == 7 && my1/100 == 1){
                                saveGame(totalmoves,dim,AIworld,world,history);
                                if(quit)
                                    return 0;
                            }
                            else if(mx1 > 720 && my1/100 == 6){
                                    goto jump;

                            }else
                                mouse = true;
                        }
                            break;
                    case SDL_MOUSEBUTTONUP:
                        if(!mouse)
                            break;
                        mouse = false;
                        if(click.button == SDL_BUTTON_LEFT){
                            SDL_GetMouseState(&mx2,&my2);
                        }
                        if(!((mx1/(height/dim))%2 || (my1/(width/dim))%2 || (mx2/(height/dim)%2 || (my2/(width/dim))%2))){
                            makeamove(dim,world,mx1/(height/dim),my1/(width/dim),mx2/(height/dim),my2/(width/dim),points,history,AIworld);
                        }

                        break;

                    }

            }
        }
        update(world,mx1,my1);
        x=0;
        displaygameresult();
        done = false;
        while(!done){
        while(SDL_WaitEvent(&event) && !quit && !done){
            switch(event.type){
                case SDL_QUIT:
                        killSDL();
                        quit = true;
                        done = true;
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        done = true;
                        break;
                }
            }
        }

        break;
    }
    case '2':
        loadGame();
        if(quit){
            goto end;
        }
        break;
    case '3':
        leaderboard();
        done = false;
        while(!done){
            while(SDL_WaitEvent(&event) && !quit && !done){
                switch(event.type){
                    case SDL_QUIT:
                        done = true;
                        killSDL();
                        quit = true;
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        done = true;
                        break;
                }
            }
        }
        break;
    case '4':
    case '0':
        break;
    }
    }while(!quit);


    end:
    return 0;
}
