#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#define BLACK "\033[1;30m"
#define RED "\033[1;31m"
#define BLUE "\033[1;34m"
#define RESET "\033[1;0m"
#define realwidth 1000
#define width 700
#define height 700
//#include "undo and redo.h"
int playerturn = 0, player = 1,moves[2] = {0},totalmoves=0,maxmoves = 0,points[2] = {0},dim=0,computer;char game=0,name1[25],name2[25]="Computer",ss[1];
bool mouse = false;
SDL_Window *window;
SDL_Renderer *renderer;


void initSDL(){
    SDL_Init(SDL_INIT_VIDEO);

    IMG_Init(IMG_INIT_PNG | IMG_INIT_PNG);

    window = SDL_CreateWindow("dots and boxes",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,realwidth,height,SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

}

void killSDL(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
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
    SDL_Surface *imgredo = IMG_Load("redo.png");

    SDL_Texture *redoicon = SDL_CreateTextureFromSurface(renderer,imgredo);

    SDL_FreeSurface(imgredo);

    SDL_Rect redopos = {.x = 900,.y = 20,.w = 80,.h = 80};

    SDL_Surface *imgundo = IMG_Load("undo.png");

    SDL_Texture *undoicon = SDL_CreateTextureFromSurface(renderer,imgundo);

    SDL_FreeSurface(imgundo);

    SDL_Rect undopos = {.x = 720,.y = 20,.w = 80,.h = 80};

    SDL_Surface *imgwallpaper = IMG_Load("wallpaper.jpg");

    SDL_Texture *wallpaper = SDL_CreateTextureFromSurface(renderer,imgwallpaper);

    SDL_FreeSurface(imgwallpaper);

    SDL_Surface *imagedots = IMG_Load("dots.png");

    SDL_Texture *dots = SDL_CreateTextureFromSurface(renderer,imagedots);

    SDL_FreeSurface(imagedots);

    SDL_SetRenderDrawColor(renderer,0,0,0,255);

    SDL_RenderClear(renderer);

    SDL_Rect wallpaperpos = {.x = 0,.y = 0,realwidth,height};

    SDL_RenderCopy(renderer,wallpaper,NULL,&wallpaperpos);

    SDL_RenderCopy(renderer,redoicon,NULL,&redopos);

    SDL_RenderCopy(renderer,undoicon,NULL,&undopos);

    if(mouse){
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_GetMouseState(&linex,&liney);
        SDL_RenderDrawLine(renderer,mx1,my1,linex,liney);
    }
    for(int i=0;i<dim;i++){
        for(int j=0;j<dim;j++){
            if(world[i][j] == '0' || world[i][j] == '1'){

                SDL_SetRenderDrawColor(renderer,180,180,180,180);

                if((i%2 && !(j%2)) && world[i][j] == '1'){ // HORIZONTAL
                    SDL_Rect ballrect = {.x = (i-a) * width/dim + shift , .y = (j) * height/dim + shift , .w = wz , .h = L};
                    SDL_RenderFillRect(renderer,&ballrect); // VERTICAL
                }else if((!(i%2) && (j%2) )&& world[i][j] == '1'){
                    SDL_Rect ballrect = {.x = (i) * width/dim + shift , .y = (j-b) * height/dim + shift , .w = L , .h = hv};
                    SDL_RenderFillRect(renderer,&ballrect);
                }

            }
            else if(world[i][j] == 'X'){

                SDL_SetRenderDrawColor(renderer,255,0,0,255);
                SDL_Rect ballrect = {.x = (i-a+c) * width/dim + shift , .y = (j-b+d) * height/dim + shift , .w = wz - e , .h = hv - f};

                SDL_RenderFillRect(renderer,&ballrect);
            }
            else if(world[i][j] == 'O'){

                SDL_SetRenderDrawColor(renderer,0,0,255,255);
                SDL_Rect ballrect = {.x = (i-a+c) * width/dim + shift , .y = (j-b+d) * height/dim + shift , .w = wz - e , .h = hv - f};

                SDL_RenderFillRect(renderer,&ballrect);
            }
        }
    }
    for(int i=0;i<dim;i=i+2){
        for(int j=0;j<dim;j=j+2){
            SDL_Rect dotspos = {.x = i * width/dim + shift , .y = j * height/dim + shift , .w = L , .h = L};
            SDL_RenderCopy(renderer,dots,NULL,&dotspos);
        }
    }
    SDL_DestroyTexture(undoicon);
    SDL_DestroyTexture(redoicon);
    SDL_DestroyTexture(wallpaper);
    SDL_DestroyTexture(dots);
    SDL_RenderPresent(renderer);



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
            printf("%c  ",array[i][j]);
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

int checkforotherlines(int dim,int history[][7],char array[][dim],int n1,int m1){
    int f=0;
    if(array[n1][m1+1] == '1')
        f++;
    if(array[n1][m1-1] == '1')
        f++;
    if(array[n1+1][m1] == '1')
        f++;
    if(array[n1-1][m1] == '1')
        f++;
    return f;
}




int upperright(int n1,int m1,int dim,char array[dim][dim]){
    if((m1 == dim -1) || (n1 == 0) || array[n1-1][m1+1] == 'X' || array[n1-1][m1+1] == 'O')
        return 0;
    if(array[n1][m1+1]=='1'){
            if(array[n1-1][m1]=='1'){
                if(array[n1-1][m1+2]=='1'){
                    if(array[n1-2][m1+1]=='1'){
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
    if(array[n1][m1-1]=='1'){
            if(array[n1-1][m1]=='1'){
                if(array[n1-1][m1-2]=='1'){
                    if(array[n1-2][m1-1]=='1'){
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
    if(array[n1][m1+1]=='1'){
            if(array[n1+1][m1]=='1'){
                if(array[n1+1][m1+2]=='1'){
                    if(array[n1+2][m1+1]=='1'){
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
    if(array[n1][m1-1]=='1'){
            if(array[n1+1][m1]=='1'){
                if(array[n1+1][m1-2]=='1'){
                    if(array[n1+2][m1-1]=='1'){
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
    if(sum != 0)
        playerturn++;
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
        printf("How do you think it is supposed to undo IF YOU HAVEN'T PLAYED YET!\a\n");

    }
}

void redo(int dim,int history[][7],char array[dim][dim]){
    if(totalmoves < maxmoves && maxmoves > 0){
        int n1 = history[totalmoves][0];int m1 = history[totalmoves][1];
        array[(history[totalmoves][0]+history[totalmoves][2])/2][(history[totalmoves][1]+history[totalmoves][3])/2] ='1';

        array[history[totalmoves][0]][history[totalmoves][1]] = '1';

        array[history[totalmoves][2]][history[totalmoves][3]] = '1';

        checkforsquares(n1,m1,dim,array,history,points);
        totalmoves++;

    }else{
        printf("How do you think it is supposed to redo IF THERE IS NO UNDO MOVES!\a\n");

    }
}




void makeamove(int dim,char array[dim][dim],int n1,int m1,int n2,int m2,int points[],int history[][7],int AIworld[dim][dim]){

    if(!computer && player == 2 || player == 1){

        if((array[((n1+n2)/2)][((m1+m2)/2)] =='1') || (n1 > dim - 1) || (m1 > dim - 1) || (n2 > dim - 1) || (m2 > dim - 1) || (n1 < 0) || (m1 < 0) || (n2 < 0) || (m2 < 0) || !(((abs(n1-n2) == 2) && (m1==m2)) ^ ((abs(m1-m2) == 2) && (n1==n2)))){
            printf("enter a valid move\n");
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
        array[(history[totalmoves][0]+history[totalmoves][2])/2][(history[totalmoves][1]+history[totalmoves][3])/2] ='1';
    }
    else{
        printf("enter a valid thing");
    }

    checkforsquares(history[totalmoves][0],history[totalmoves][1],dim,array,history,points);
    history[totalmoves][4] = points[0];
    history[totalmoves][5] = points[1];

    if((totalmoves < maxmoves) && (!computer && player == 2))
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
            if(world[i][j] == '1')
                AIworld[i][j] = -100;
            else{
                if( i != 0){
                    if(world[i-1][j+1] == '1')
                         numberoflines1++;
                    if(world[i-1][j-1] == '1')
                         numberoflines1++;
                    if(world[i-2][j] == '1')
                         numberoflines1++;
                    if(numberoflines1 == 3)
                         numberoflines1 += 10;
                    else if(numberoflines1 == 2)
                        numberoflines1 -=10;
                }
                if( i != dim - 1){
                    if(world[i+1][j-1] == '1')
                         numberoflines2++;
                    if(world[i+1][j+1] == '1')
                         numberoflines2++;
                    if(world[i+2][j] == '1')
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
            if(world[i][j] == '1')
                AIworld[i][j] = -100;
            else{
                if( j != 0){
                    if(world[i-1][j-1] == '1')
                         numberoflines1++;
                    if(world[i+1][j-1] == '1')
                         numberoflines1++;
                    if(world[i][j-2] == '1')
                         numberoflines1++;
                    if(numberoflines1 == 3)
                         numberoflines1 += 10;
                    else if(numberoflines1 == 2)
                        numberoflines1 -=10;
                }
                if( j != dim-1){
                    if(world[i+1][j+1] == '1')
                         numberoflines2++;
                    if(world[i-1][j+1] == '1')
                         numberoflines2++;
                    if(world[i][j+2] == '1')
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






void oneNewGame(){
    computer = 1;
    system("cls");
    printf("Back(0)\n\nEnter difficulty:\nEasy(1)\nNormal(2)\nHard(3)\nVery hard(4)\n");
    game = _getch();
    switch(game){
        case '0':
            return newGame();
            break;
        case '1':
            printf("\nEnter player's name: ");
            gets(name1);
            dim = 7;
            break;
        case '2':
            printf("\nEnter player's name: ");
            gets(name1);
            dim = 11;
            break;
        case '3':
            printf("\nEnter player's name: ");
            gets(name1);
            dim = 11;
            break;
        case '4':
            printf("\nEnter player's name: ");
            gets(name1);
            dim = 15;
            break;
        default:
            oneNewGame();
    }
}

void twoNewGame(){
    system("cls");
    printf("Back(0)\n\nEnter difficulty:\nEasy(1)\nNormal(2)\nHard(3)\n");
    game = _getch();
    switch(game){
        case '0':
            return newGame();
            break;
        case '1':
            printf("\nEnter first player's name: ");
            gets(name1);
            printf("\nEnter second player's name: ");
            gets(name2);
            dim = 7;
            break;
        case '2':
            printf("\nEnter first player's name: ");
            gets(name1);
            printf("\nEnter second player's name: ");
            gets(name2);
            dim = 11;
            break;
        case '3':
            printf("\nEnter first player's name: ");
            gets(name1);
            printf("\nEnter second player's name: ");
            gets(name2);
            dim = 15;
            break;
        default:
            twoNewGame();
            break;
    }
}

void newGame(){
    system("cls");
    printf("Back(0)\n\nChoose a mode:\nVs Computer(1)\nVs Human(2)\n");
    game = _getch();
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
    int p=0;
    do{
    system("cls");
    system("color f1");
    printf("Welcome to dots and boxes by RABSOOO team\nNew game(1)\nLoad game(2)\nLeader board(3)\nSettings(4)\nExit(0)\n");
    game = _getch();
    system("cls");
    bool quit = false;
    switch(game){
    case '1':{
        system("color f0");
        do{
            newGame();
        }

        while(dim == 0);

        int history[2 * (dim/2) * ((dim/2) + 1)][7];
        char world[dim][dim];

        system("color f4");
        createworld(dim,world);


        int AIworld[dim][dim];

        int temp[dim][dim];

        createAIwolrd(dim,AIworld);

        createhistory(dim,history);

        initSDL();


        SDL_MouseButtonEvent event;


        int mx1 = 0, my1 = 0, mx2 = 0, my2 = 0;

        totalmoves = 0;
        player = 1;
        while(totalmoves<2*((dim/2)+1)*(dim/2) && !quit){
            if(totalmoves!=0)
                p = totalmoves;
            else
                p=1;




            update(world,mx1,my1);

            if(computer && (player == 2)){
                makeamove(dim,world,NULL,NULL,NULL,NULL,points,history,AIworld);

            }else{
            while(SDL_PollEvent(&event)){
                    int f = 0;
                    switch(event.type){
                    case SDL_QUIT:
                        quit = true;
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        if(event.button == SDL_BUTTON_LEFT)
                            mouse = true;
                            SDL_GetMouseState(&mx1,&my1);
                            if(mx1/100 == 7){
                                undo(dim,history,world);
                                while(computer && history[totalmoves][6] == 2)
                                    undo(dim,history,world);
                            }
                            else if(mx1/100 == 9){
                                redo(dim,history,world);
                                while(computer && history[totalmoves][6] == 2)
                                    redo(dim,history,world);
                            }
                            break;
                    case SDL_MOUSEBUTTONUP:
                        mouse = false;
                        if(event.button == SDL_BUTTON_LEFT){
                            SDL_GetMouseState(&mx2,&my2);
                        }
                        printf("%d %d %d %d  %d\n\n\n",mx1,my1,mx2,my2,player);
                        if(!((mx1/(height/dim))%2 || (my1/(width/dim))%2 || (mx2/(height/dim)%2 || (my2/(width/dim))%2))){
                            makeamove(dim,world,mx1/(height/dim),my1/(width/dim),mx2/(height/dim),my2/(width/dim),points,history,AIworld);
                            printf("%d %d %d %d  %d\n\n\n",mx1/(height/dim),my1/(width/dim),mx2/(height/dim),my2/(width/dim),player);
                        }
                        break;

                    }
                }
            }
        }

        system("cls");
        update(world,mx1,my1);
        while(SDL_WaitEvent(&event)){
            if(event.type == SDL_MOUSEBUTTONDOWN)
                killSDL();
        }






        if(points[1]>points[0]){
            if(!computer)
                printf("Congratulation for %s and hard luck for %s\n",name2,name1);
            else
                printf("Hard luck %s\n",name1);
        }else{
            if(!computer)
                printf("Congratulations for %s and hard luck for %s\n",name1,name2);
            else
                printf("Congratulations %s\n",name1);
        }
        printf("Press any key to proceed\n");
        ss[0]=_getch();
        break;
        scanf("%c",&argv);
    }
    case '2':
    case '3':
    case '4':
    case '0':
        printf("thanks for playing :)\n");
        break;
    default:
        printf("Enter a valid input\n");
        main(NULL,NULL);
    }
    }while(game < 1 || game >5);



    return 0;
}
/*#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
//#include "undo and redo.h"
int w=0,playerturn = 0, player = 1,moves[2] = {0},totalmoves=0,maxmoves = 0,points[2] = {0},dim=0,computer;char game=0,name1[25],name2[25]="Computer";

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


void printworld(int dim,char array[dim+2][dim+2]){
    for(int i=0;i<dim+2;i++){
        for(int j=0;j<dim+2;j++){
            printf("%c  ",array[i][j]);
        }
        printf("\n");
    }
}
void createworld(int dim,char array[dim+2][dim+2]){
    char q[6]={'1','2','3','4','5','6'};
    for(int i=0;i<dim+2;i++){
        for(int j=0;j<dim+2;j++){
            if((i==dim+1)&&j==0)
                w=0;
            if((!(j%2 || i%2))&&(i<dim)&&(j<dim))
                array[i][j]='0';
            //else if((i==dim||j==dim)&&(i<dim+1&&j<dim+1))
              //  array[i][j]='+';
            else if((((i==dim+1)&&j%2==0)||((j==dim+1)&&i%2==0))&&(!(i==dim+1&&j==dim+1))){
                array[i][j]=q[w];
                w++;
            }
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

int checkforotherlines(int dim,int history[][7],char array[dim+2][dim+2],int n1,int m1){
    int f=0;
    if(array[n1][m1+1] == '1')
        f++;
    if(array[n1][m1-1] == '1')
        f++;
    if(array[n1+1][m1] == '1')
        f++;
    if(array[n1-1][m1] == '1')
        f++;
    return f;
}




int upperright(int n1,int m1,int dim,char array[dim+2][dim+2]){
    if((m1 == dim -1) || (n1 == 0) || array[n1-1][m1+1] == 'X' || array[n1-1][m1+1] == 'O')
        return 0;
    if(array[n1][m1+1]=='1'){
            if(array[n1-1][m1]=='1'){
                if(array[n1-1][m1+2]=='1'){
                    if(array[n1-2][m1+1]=='1'){
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
int upperleft(int n1,int m1,int dim,char array[dim+2][dim+2]){
    if((m1 == 0) || (n1 == 0) || array[n1-1][m1-1] == 'X' || array[n1-1][m1-1] == 'O')
        return 0;
    if(array[n1][m1-1]=='1'){
            if(array[n1-1][m1]=='1'){
                if(array[n1-1][m1-2]=='1'){
                    if(array[n1-2][m1-1]=='1'){
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
int downright(int n1,int m1,int dim,char array[dim+2][dim+2]){
    if((m1 == dim -1) || (n1 == dim -1) || array[n1+1][m1+1] == 'X' || array[n1+1][m1+1] == 'O')
        return 0;
    if(array[n1][m1+1]=='1'){
            if(array[n1+1][m1]=='1'){
                if(array[n1+1][m1+2]=='1'){
                    if(array[n1+2][m1+1]=='1'){
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
int downleft(int n1,int m1,int dim,char array[dim+2][dim+2]){
    if((m1 == 0) || (n1 == dim-1) || array[n1+1][m1-1] == 'X' || array[n1+1][m1-1] == 'O')
        return 0;
    if(array[n1][m1-1]=='1'){
            if(array[n1+1][m1]=='1'){
                if(array[n1+1][m1-2]=='1'){
                    if(array[n1+2][m1-1]=='1'){
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
void checkforsquares(int n1,int m1,int dim,char array[dim+2][dim+2],int history[][7],int points[]){
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
    if(sum != 0)
        playerturn++;
    else{
        player=player==1?2:1;
    }

}

void undo(int dim,int history[][7],char array[dim+2][dim+2]){
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
        printf("How do you think it is supposed to undo IF YOU HAVEN'T PLAYED YET!\a\n");

    }
}

void redo(int dim,int history[][7],char array[dim+2][dim+2]){
    if(totalmoves < maxmoves && maxmoves > 0){
        int n1 = history[totalmoves][0];int m1 = history[totalmoves][1];
        array[(history[totalmoves][0]+history[totalmoves][2])/2][(history[totalmoves][1]+history[totalmoves][3])/2] ='1';

        array[history[totalmoves][0]][history[totalmoves][1]] = '1';

        array[history[totalmoves][2]][history[totalmoves][3]] = '1';

        checkforsquares(n1,m1,dim,array,history,points);
        totalmoves++;

    }else{
        printf("How do you think it is supposed to redo IF THERE IS NO UNDO MOVES!\a\n");

    }
}




void makeamove(int dim,char array[dim+2][dim+2],int n1,int m1,int n2,int m2,int points[],int history[][7],int AIworld[dim][dim]){

    if((!computer && player==2) || player == 1){

    char a1[1],A1[1],a2[1],A2[1];
    int N1,M1,N2,M2;
    printf("\nEnter the row: ");
    gets(a1);
    N1=a1[0]-48;
    if(N1 == -3){
        FILE *saved;
        saved = fopen("saved0.bin","w");
        fwrite(&dim,sizeof(int),1,saved);
        fwrite(&totalmoves,sizeof(int),1,saved);
        for(int i=0;i<totalmoves;i++){
            for(int j=0;j<7;j++)
                fwrite(&history[i][j],1,(dim+2)*(dim+2),saved);

        }
        for(int i=0;i<dim+2;i++){
            for(int j=0;j<dim+2;j++)
                fwrite(&array[i][j],1,(dim+2)*(dim+2),saved);

        }
        for(int i=0;i<2;i++)
            fwrite(&moves[i],sizeof(int),2,saved);
        fwrite(&playerturn,sizeof(int),1,saved);
        fwrite(&maxmoves,sizeof(int),1,saved);
        if(computer){
            for(int i=0;i<dim;i++){
                for(int j=0;j<dim;j++)
                    fwrite(&AIworld[i][j],1,(dim+2)*(dim+2),saved);
            }
        }
        fclose(saved);
        return;
    }
    else if(N1 == 0){
        undo(dim,history,array);
        if(computer){
            while(history[totalmoves][6] != 1)
                undo(dim,history,array);
        }
        return;
    }
    else if(N1 == -2){
        redo(dim,history,array);
        return;
    }else{
        printf("\nEnter the col: ");
        gets(A1);
        M1=A1[0]-48;
        printf("\nEnter the row: ");
        gets(a2);
        N2=a2[0]-48;
        printf("\nEnter the col: ");
        gets(A2);
        M2=A2[0]-48;
        }





    if((array[((N1+N2)-2)][((M1+M2)-2)] =='1') || (N1 > (dim/2) + 1) || (M1 > (dim/2) + 1) || (N2 > (dim/2) + 1) || (M2 > (dim/2) + 1) || (N1 < 1) || (M1 < 1) || (N2 < 1) || (M2 < 1) || !(((abs(N1-N2) == 1) && (M1==M2)) ^ ((abs(M1-M2) == 1) && (N1==N2)))){
        printf("Enter a valid move\n");
        return;
    }


    history[totalmoves][0] = 2*N1-2 ; history[totalmoves][1] = 2*M1-2 ;history[totalmoves][2] = 2*N2-2 ; history[totalmoves][3] = 2*M2-2;

    }else{
        AI(dim,array,AIworld,history);

    }

    history[totalmoves][6] = player;


    if(!(history[totalmoves][1]%2 || history[totalmoves][0]%2 )){
        array[history[totalmoves][0]][history[totalmoves][1]] = '1';
        array[history[totalmoves][2]][history[totalmoves][3]] = '1';
        array[(history[totalmoves][0]+history[totalmoves][2])/2][(history[totalmoves][1]+history[totalmoves][3])/2] ='1';
    }
    else{
        printf("Enter a valid thing\n");
    }

    checkforsquares(history[totalmoves][0],history[totalmoves][1],dim,array,history,points);
    history[totalmoves][4] = points[0];
    history[totalmoves][5] = points[1];

    if((totalmoves < maxmoves) && !computer)
        maxmoves = totalmoves;
    if((totalmoves < maxmoves) && computer)
        maxmoves--;
    maxmoves++;
    totalmoves++;
}

void AI(int dim,char world[dim+2][dim+2],int AIworld[dim][dim],int history[][7]){
    int numberoflines1,numberoflines2;
    // checks horizontal lines
    for(int i=0;i<dim;i=i+2){
        for(int j=1;j<dim;j=j+2){
            numberoflines1 = 0;
            numberoflines2 = 0;
            if(world[i][j] == '1')
                AIworld[i][j] = -100;
            else{
                if( i != 0){
                    if(world[i-1][j+1] == '1')
                         numberoflines1++;
                    if(world[i-1][j-1] == '1')
                         numberoflines1++;
                    if(world[i-2][j] == '1')
                         numberoflines1++;
                    if(numberoflines1 == 3)
                         numberoflines1 += 10;
                    else if(numberoflines1 == 2)
                        numberoflines1 -=10;
                }
                if( i != dim - 1){
                    if(world[i+1][j-1] == '1')
                         numberoflines2++;
                    if(world[i+1][j+1] == '1')
                         numberoflines2++;
                    if(world[i+2][j] == '1')
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
            if(world[i][j] == '1')
                AIworld[i][j] = -100;
            else{
                if( j != 0){
                    if(world[i-1][j-1] == '1')
                         numberoflines1++;
                    if(world[i+1][j-1] == '1')
                         numberoflines1++;
                    if(world[i][j-2] == '1')
                         numberoflines1++;
                    if(numberoflines1 == 3)
                         numberoflines1 += 10;
                    else if(numberoflines1 == 2)
                        numberoflines1 -=10;
                }
                if( j != dim-1){
                    if(world[i+1][j+1] == '1')
                         numberoflines2++;
                    if(world[i-1][j+1] == '1')
                         numberoflines2++;
                    if(world[i][j+2] == '1')
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
        printf("%d\n\n\n",i);
    }
    printf("%d %d %d \n\n\n",max,maxi,maxj);
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






void oneNewGame(){
    computer = 1;
    system("cls");
    printf("Back(0)\n\nEnter difficulty:\nEasy(1)\nNormal(2)\nHard(3)\nVery hard(4)\n");
    game = _getch();
    switch(game){
        case '0':
            return newGame();
            break;
        case '1':
            printf("\nEnter player's name: ");
            gets(name1);
            dim = 7;
            break;
        case '2':
            printf("\nEnter player's name: ");
            gets(name1);
            dim = 11;
            break;
        case '3':
            printf("\nEnter player's name: ");
            gets(name1);
            dim = 11;
            break;
        case '4':
            printf("\nEnter player's name: ");
            gets(name1);
            dim = 15;
            break;
        default:
            oneNewGame();
    }
}

void twoNewGame(){
    system("cls");
    printf("Back(0)\n\nEnter difficulty:\nEasy(1)\nNormal(2)\nHard(3)\n");
    game = _getch();
    switch(game){
        case '0':
            return newGame();
            break;
        case '1':
            printf("\nEnter first player's name: ");
            gets(name1);
            printf("\nEnter second player's name: ");
            gets(name2);
            dim = 7;
            break;
        case '2':
            printf("\nEnter first player's name: ");
            gets(name1);
            printf("\nEnter second player's name: ");
            gets(name2);
            dim = 11;
            break;
        case '3':
            printf("\nEnter first player's name: ");
            gets(name1);
            printf("\nEnter second player's name: ");
            gets(name2);
            dim = 15;
            break;
        default:
            twoNewGame();
            break;
    }
}

void newGame(){
    system("cls");
    printf("Back(0)\n\nChoose a mode:\nVs Computer(1)\nVs Human(2)\n");
    game = _getch();
    switch(game){
    case '0':
        return main();
        break;
    case '1':
        oneNewGame();
        break;
    case '2':
        twoNewGame();
        break;
    default:
        newGame();
        break;
    }
}





int main(){
    computer = 0;
    int p=0;
    do{
    system("cls");
    system("color f1");
    printf("Welcome to dots and boxes by RABSOOO team\nNew game(1)\nLoad game(2)\nLeader board(3)\nSettings(4)\nExit(0)\n");
    game = _getch();
    system("cls");
    switch(game){
    case '1':{
        system("color f0");
        do{
            newGame();
        }

        while(dim == 0);

        int history[2 * (dim/2) * ((dim/2) + 1)][7];
        char world[dim+2][dim+2];
        system("color f4");
        createworld(dim,world);


        int AIworld[dim][dim];

        createAIwolrd(dim,AIworld);


        createhistory(dim,history);


        while(totalmoves<2*((dim/2)+1)*(dim/2)){
            if(totalmoves!=0)
                p = totalmoves;
            else
                p=1;
            printhistory(dim,history);
            printf("\n\n\n\n");
            printf("Total moves:%d\t\t Maximum moves:%d\n\n",totalmoves,maxmoves);
            if(computer)
                printAIwolrd(dim,AIworld);

            printf("\n\n\n\n");

            printworld(dim,world);
            printf("\n%s: %d\n\n%s: %d\n\nFirst player moves: %i\n\nSecond player moves: %i\n\nTurn player no.: %d\n\n",name1,history[p-1][4],name2,history[p-1][5],moves[0],moves[1],player);
            printf("\n Enter -1 to redo\n\n");
            printf("\n Enter 0 to undo\n\n");
            if(!computer)
                makeamove(dim,world,NULL,NULL,NULL,NULL,points,history,NULL);
            else
                makeamove(dim,world,NULL,NULL,NULL,NULL,points,history,AIworld);
        }

        system("cls");
        system("color 04");
        printworld(dim,world);

        system("color 0e");
        if(points[1]>points[0]){
            if(!computer)
                printf("Congratulation for %s and hard luck for %s",name2,name1);
            else
                printf("Hard luck %s",name1);
        }else{
            if(!computer)
                printf("Congratulations for %s and hard luck for %s",name1,name2);
            else
                printf("Congratulations %s",name1);
        }
        return 0;
    }
    case '2':{
        computer=1;
        FILE *load;
        load = fopen("saved0.bin","r");
        fread(&dim,sizeof(int),1,load);
        fread(&totalmoves,sizeof(int),1,load);
        int history[2 * (dim/2) * ((dim/2) + 1)][7];
        char world[dim+2][dim+2];
        int AIworld[dim][dim];
        for(int i=0;i<totalmoves;i++){
            for(int j=0;j<7;j++)
                fread(&history[i][j],1,(dim+2)*(dim+2),load);

        }
        for(int i=0;i<dim+2;i++){
            for(int j=0;j<dim+2;j++)
                fread(&world[i][j],1,(dim+2)*(dim+2),load);

        }
        for(int i=0;i<2;i++)
            fread(&moves[i],sizeof(int),2,load);
        fread(&playerturn,sizeof(int),1,load);
        fread(&maxmoves,sizeof(int),1,load);
        if(computer){
            for(int i=0;i<dim;i++){
                for(int j=0;j<dim;j++)
                    fread(&AIworld[i][j],1,(dim+2)*(dim+2),load);
            }
        }
        fclose(load);
        while(totalmoves<2*((dim/2)+1)*(dim/2)){
            if(totalmoves!=0)
                p = totalmoves;
            else
                p=1;
            printhistory(dim,history);
            printf("\n\n\n\n");
            printf("Total moves:%d\t\t Maximum moves:%d\n\n",totalmoves,maxmoves);
            if(computer)
                printAIwolrd(dim,AIworld);

            printf("\n\n\n\n");

            printworld(dim,world);
            printf("\n%s: %d\n\n%s: %d\n\nFirst player moves: %i\n\nSecond player moves: %i\n\nTurn player no.: %d\n\n",name1,history[p-1][4],name2,history[p-1][5],moves[0],moves[1],player);
            printf("\n Enter -1 to redo\n\n");
            printf("\n Enter 0 to undo\n\n");
            if(!computer)
                makeamove(dim,world,NULL,NULL,NULL,NULL,points,history,NULL);
            else
                makeamove(dim,world,NULL,NULL,NULL,NULL,points,history,AIworld);
        }
    }
    case '3':
    case '4':
    case '0':
        printf("thanks for playing :)\n");
        break;
    default:
        printf("Enter a valid input\n");
        return main();
    }
    }while(game < 1 || game >5);


    return 0;
}*/
