#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <stdbool.h>


#define WIDTH 700
#define HEIGHT 700
//#include "undo and redo.h"
int playerturn = 0, player = 1,moves[2] = {0},totalmoves=0,maxmoves = 0,points[2] = {0},dim=0,computer;char game=0;
SDL_Window *window;
SDL_Renderer *renderer;



void initSDL(){
    SDL_Init(SDL_INIT_VIDEO);

        window = SDL_CreateWindow("dots and boxes",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WIDTH,HEIGHT,SDL_WINDOW_SHOWN);

        renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

}

void killSDL(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void update(char world[dim][dim]){

    SDL_SetRenderDrawColor(renderer,0,0,0,255);

    SDL_RenderClear(renderer);


    for(int i=0;i<dim;i++){
        for(int j=0;j<dim;j++){
            if(world[i][j] == '0' || world[i][j] == '1'){



                SDL_SetRenderDrawColor(renderer,255,255,255,255);
                SDL_Rect ballrect = {.x = i * WIDTH/dim + 30 , .y = j * HEIGHT/dim + 30 , .w = 50 , .h = 50};

                SDL_RenderFillRect(renderer,&ballrect);
            }
            else if(world[i][j] == 'X'){

                SDL_SetRenderDrawColor(renderer,255,0,0,255);
                SDL_Rect ballrect = {.x = i * WIDTH/dim + 30 , .y = j * HEIGHT/dim + 30 , .w = 50 , .h = 50};

                SDL_RenderFillRect(renderer,&ballrect);
            }
            else if(world[i][j] == 'O'){

                SDL_SetRenderDrawColor(renderer,0,0,255,255);
                SDL_Rect ballrect = {.x = i * WIDTH/dim + 30 , .y = j * HEIGHT/dim + 30 , .w = 50 , .h = 50};

                SDL_RenderFillRect(renderer,&ballrect);
            }
        }
    }


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
            dim = 7;
            break;

        case '2':
            dim = 11;
            break;

        case '3':
            dim = 11;
            break;

        case '4':
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
            dim = 7;
            break;
        case '2':
            dim = 11;
            break;
        case '3':
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






int main(int argc,char* argv[]){
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
        char world[dim][dim];

        system("color f4");
        createworld(dim,world);


        int AIworld[dim][dim];

        int tempAI[dim][dim];

        createAIwolrd(dim,AIworld);

        createhistory(dim,history);

        initSDL();


        SDL_MouseButtonEvent event;

        bool quit = false;

        int mx1 = 0, my1 = 0, mx2 = 0, my2 = 0;


        while(totalmoves<2*((dim/2)+1)*(dim/2) && !quit){
            if(totalmoves!=0)
                p = totalmoves;
            else
                p=1;




            update(world);

            if(computer && (player == 2)){
                printf("AAAAAAA\n");
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
                            SDL_GetMouseState(&mx1,&my1);
                            break;
                    case SDL_MOUSEBUTTONUP:
                        if(event.button == SDL_BUTTON_LEFT){
                            SDL_GetMouseState(&mx2,&my2);
                        }
                        if(!((mx1/100)%2 || (my1/100)%2 || (mx2/100)%2 || (my2/100)%2)){
                            printf("%d %d %d %d  %d\n\n\n",mx1,my1,mx2,my2,player);
                            makeamove(dim,world,mx1/100,my1/100,mx2/100,my2/100,points,history,AIworld);
                            if(computer && (player == 2)){
                                printf("AAAAAAA\n");
                                makeamove(dim,world,NULL,NULL,NULL,NULL,points,history,AIworld);

                            }
                        }
                        break;

                    }
                }
            }
        }


        killSDL();

        system("cls");
        system("color 04");
        printworld(dim,world);

        system("color 0e");
        if(points[1]>points[0])
            printf("Congratulation for player no. 2 and hard luck for player no. 1");
        else
            printf("Congratulation for player no. 1 and hard luck for player no. 2");
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
