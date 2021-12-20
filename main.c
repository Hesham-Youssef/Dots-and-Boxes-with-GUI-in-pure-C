#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
int playerturn = 0, player = 1,moves[2] = {0};
void black(){
    printf("\033[1;30m");
}
void red(){
    printf("\033[1;31m");
}
void green(){
    printf("\033[1;32m");
}
void yellow(){
    printf("\033[1;33m");
}
void blue(){
    printf("\033[1;34m");
}

void purple(){
    printf("\033[1;35m");
}

void cyan(){
    printf("\033[1;36m");
}

void white(){
    printf("\033[1;37m");
}
void normal(){
    printf("\033[0m");
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






void checkforsquares(int n1,int m1,int dim,char array[dim][dim],int points[]){
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

void makeamove(int dim,char array[dim][dim],int n1,int m1,int n2,int m2,int points[]){
    int N1,M1,N2,M2;
    printf("enter the row: ");
    scanf("%d",&N1);
    printf("enter the col: ");
    scanf("%d",&M1);

    printf("enter the row: ");
    scanf("%d",&N2);
    printf("enter the col: ");
    scanf("%d",&M2);
    n1 = 2*N1-2;m1 = 2*M1-2;n2 = 2*N2-2;m2 = 2*M2-2;
    if((array[(n1+n2)/2][(m1+m2)/2] =='1'))
        return;

    else if((!(m1%2 || n1%2 ) && (((abs(n1-n2) == 2) && (m1==m2)) || ((abs(m1-m2) == 2) && (n1==n2))))){
        array[n1][m1] = '1';
        array[n2][m2] = '1';
        array[(n1+n2)/2][(m1+m2)/2] ='1';
    }
    else{
        printf("enter a valid thing");
    }


    checkforsquares(n1,m1,dim,array,points);


}











int main()
{
    int dim,points[2] = {0};
    int game;
    printf("Welcome to dots and boxes by RABSOOO team\nNew game(1)\nLoad game(2)\nLeader board(3)\nSettings(4)\nExit(5)\n");
    scanf("%d", &game);
    system("cls");
    switch(game){
        case 1:{
            printf("Enter difficulty:\nEasy(1)\nNormal(2)\nHard(3)\n");
            scanf("%d", &game);
            switch(game){
                case 1:
                    dim = 7;
                    break;
                case 2:
                    dim = 11;
                    break;
                case 3:
                    dim = 15;
                    break;
            }
            char world[dim][dim];
            createworld(dim,world);
            while(1){
            system("cls");

            printworld(dim,world);
            printf("\nFirst player: %d\n\nSecond player: %d\n\nFirst player moves: %i\n\nSecond player moves: %i\n\nTurn player no.: %d\n\n",points[0],points[1],moves[0],moves[1],player);
            makeamove(dim,world,NULL,NULL,NULL,NULL,points);

            }
            if(points[1]>points[0])
                printf("Congratulation for player no. 2 and hard luck for player no. 1");
            else if(points[0]>points[1])
                printf("Congratulation for player no. 1 and hard luck for player no. 2");
            else
                printf("Congratulation for both players!What a great game!");
            break;
        }
        case 2:
        case 3:
        case 4:
        case 5:
            break;
    }

    /*char world[dim][dim];
    createworld(dim,world);
    while(1){
    system("cls");

    printworld(dim,world);
    printf("\n %d\n",points[0]);
    printf("\n %d\n",points[1]);
    makeamove(dim,world,NULL,NULL,NULL,NULL,points);




    }


*/
    return 0;
}
