#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
int playerturn = 0, player = 1,moves[2] = {0},totalmoves=0,maxmoves = 0,points[2] = {0};








void printhistory(int dim,int history[][7]){
    for(int i=0;i<24;i++){
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

int checkforotherlines(int dim,int history[][dim],char array[][dim],int n1,int m1){
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
void checkforsquares(int n1,int m1,int dim,char array[dim][dim],int history[][dim],int points[]){
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

void undo(int dim,int history[][dim],char array[dim][dim]){
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
        if(player==history[totalmoves][6])
            playerturn-=2;
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
        printf("how do you think supposed to undo IF YOU HAVEN'T PLAYER YET RE-FUCKING-TARD");

    }
}

void redo(int dim,int history[][dim],char array[dim][dim]){
    if(totalmoves <= maxmoves && maxmoves > 0){
        int n1 = history[totalmoves][0];int m1 = history[totalmoves][1];
        array[(history[totalmoves][0]+history[totalmoves][2])/2][(history[totalmoves][1]+history[totalmoves][3])/2] ='1';

        array[history[totalmoves][0]][history[totalmoves][1]] = '1';

        array[history[totalmoves][2]][history[totalmoves][3]] = '1';

        checkforsquares(n1,m1,dim,array,history,points);
        totalmoves++;

    }else{
        printf("how do you think supposed to undo IF YOU HAVEN'T PLAYER YET RE-FUCKING-TARD");

    }
}













void makeamove(int dim,char array[dim][dim],int n1,int m1,int n2,int m2,int points[],int history[][7]){
    char N1temp,M1temp,N2temp,M2temp;
    int N1,M1,N2,M2;
    printf("enter the row: ");
    scanf("%d",&N1);
    if(N1 == 0){
        undo(dim,history,array);
        return;
    }
    else if(N1 == -1){
        redo(dim,history,array);
        return;
    }else{
        printf("enter the col: ");
        scanf("%d",&M1);
        printf("enter the row: ");
        scanf("%d",&N2);
        printf("enter the col: ");
        scanf("%d",&M2);
    }





    if((array[((N1+N2)-2)][((M1+M2)-2)] =='1') || (N1 > (dim/2) + 1) || (M1 > (dim/2) + 1) || (N2 > (dim/2) + 1) || (M2 > (dim/2) + 1) || (N1 < 1) || (M1 < 1) || (N2 < 1) || (M2 < 1) || !(((abs(N1-N2) == 1) && (M1==M2)) ^ ((abs(M1-M2) == 1) && (N1==N2)))){
        printf("enter a valid move\n");
        return;
    }


    history[totalmoves][0] = 2*N1-2 ; history[totalmoves][1] = 2*M1-2 ;history[totalmoves][2] = 2*N2-2 ; history[totalmoves][3] = 2*M2-2;
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

    if(totalmoves < maxmoves)
        maxmoves = totalmoves;

        maxmoves++;
        totalmoves++;
}











int main()
{
    int dim=0;
    int game=0;
    do{
    system("color f1");
    printf("Welcome to dots and boxes by RABSOOO team\nNew game(1)\nLoad game(2)\nLeader board(3)\nSettings(4)\nExit(5)\n");
    scanf("%d", &game);
    system("cls");
    switch(game){
        case 1:{
            system("color f0");
            printf("Enter difficulty:\nEasy(1)\nNormal(2)\nHard(3)\n");
            do{
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
                    default:
                        printf("\nenter a valid input: ");

                }
            }while(dim == 0);

            int history[2 * (dim/2) * ((dim/2) + 1)][7];
            char world[dim][dim];

            system("color f4");
            createworld(dim,world);


            createhistory(dim,history);


            do{

            printhistory(dim,history);
            printf("\n\n\n\n");
            printf("total moves:%d\t\t\t maximum moves%d\n\n",totalmoves,maxmoves);
            printworld(dim,world);

            printf("\nFirst player: %d\n\nSecond player: %d\n\nFirst player moves: %i\n\nSecond player moves: %i\n\nTurn player no.: %d\n\n",history[totalmoves-1][4],history[totalmoves-1][5],moves[0],moves[1],player);

            printf("\n enter -1 to redo\n\n");

            printf("\n enter 0 to undo\n\n");

            makeamove(dim,world,NULL,NULL,NULL,NULL,points,history);


            }while(1);

            system("cls");

            printworld(dim,world);



            printf("\nFirst player: %d\n\nSecond player: %d\n\nFirst player moves: %i\n\nSecond player moves: %i\n\nTurn player no.: %d\n\n",history[totalmoves][4],history[totalmoves][5],moves[0],moves[1],player);
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
            printf("thanks for playing  : ^)\n");
            break;
        default:
            printf("Enter a valid input\n\n");
    }
    }while(game < 1 || game >5);


    return 0;
}
