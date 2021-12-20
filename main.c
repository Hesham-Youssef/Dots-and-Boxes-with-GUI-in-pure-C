#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
int playerTurn = 0, player = 1,moves[2] = {0},totalMoves=0,movesBack=0,sum=0;
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


void printHistory(int dim,int array[2 * (dim/2) * ((dim/2) + 1)][7]){
    for(int i=0;i<2 * (dim/2) * ((dim/2) + 1);i++){
        for(int j=0;j<7;j++){
            printf("  %d -",array[i][j]);
        }
        printf("\n");
    }
}



void printWorld(int dim,char array[dim][dim]){
    for(int i=0;i<dim;i++){
        for(int j=0;j<dim;j++){
            printf("%c  ",array[i][j]);
        }
        printf("\n");
    }
}
void createWorld(int dim,char array[dim][dim]){
    for(int i=0;i<dim;i++){
        for(int j=0;j<dim;j++){
            if(!(j%2 || i%2))
                array[i][j]='0';
            else
                array[i][j]=' ';
        }
    }
}
void createHistoryAndLastMoves(int dim,int history[2 * (dim/2) * ((dim/2) + 1)][7],int lastmoves[2 * (dim/2) * ((dim/2) + 1)][7]){
    for(int i=0;i<2 * (dim/2) * ((dim/2) + 1);i++){
        for(int j=0;j<7;j++){
            history[i][j] = 0;
        }
    }
}
void writeHistory(int n1,int m1,int n2,int m2,int points0,int points1,int player,int totalmoves,int dim,int history[2 * (dim/2) * ((dim/2) + 1)][7]){
    history[totalmoves][0] = n1;
    history[totalmoves][1] = m1;
    history[totalmoves][2] = n2;
    history[totalmoves][3] = m2;
    history[totalmoves][4] = points0;
    history[totalmoves][5] = points1;
    history[totalmoves][6] = player;
}



int upperRight(int n1,int m1,int dim,char array[dim][dim]){
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
int upperLeft(int n1,int m1,int dim,char array[dim][dim]){
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
int downRight(int n1,int m1,int dim,char array[dim][dim]){
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
int downLeft(int n1,int m1,int dim,char array[dim][dim]){
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






void checkForSquares(int n1,int m1,int dim,char array[dim][dim],int points[]){
    sum = upperRight(n1,m1,dim,array) + upperLeft(n1,m1,dim,array) + downRight(n1,m1,dim,array) + downLeft(n1,m1,dim,array);
    if(playerTurn % 2)
        points[1] += sum;
    else
        points[0] += sum;
    playerTurn++;
    switch(player){
        case 1:
            moves[0]++;
            break;
        case 2:
            moves[1]++;
    }
}

void undo(int dim,int history[2*(dim/2)*((dim/2)+1)][7],int lastMoves[2*(dim/2)*((dim/2)+1)][7],int points[2],int moves[2],int player,int playerTurn){
    if(totalMoves==0){
        points[0]=0;points[1]=0;moves[0]=0;moves[1]=0;playerTurn=0;player=1;
    }else{
        if(points[0]>history[totalMoves-1][4]||points[1]>history[totalMoves-1][5])
            playerTurn--;
        points[0]=history[totalMoves-1][4];points[1]=history[totalMoves-1][5];player=history[totalMoves][6];
        switch(player){
            case 1:
                moves[0]--;
                break;
            case 2:
                moves[1]--;
        }
    }
    for(int i=0;i<dim;i++){
        lastMoves[movesBack][i] = history[totalMoves][i];
        history[totalMoves][i] = 0;
    }
    movesBack++;
    playerTurn--;
}
void redo(int dim,int history[2*(dim/2)*((dim/2)+1)][7],int lastMoves[2*(dim/2)*((dim/2)+1)][7],int points[2],int moves[2],int player){
    for(int i=0;i<dim;i++){
        history[totalMoves][i] = lastMoves[movesBack][i];
        lastMoves[movesBack][i] = 0;
    }
    totalMoves++;
}
void printRedo(int dim,int movesBack,int lastMoves[2*(dim/2)*((dim/2)+1)][7]){
    if(movesBack!=0){
        for(int j=0;j<movesBack;j++){
            for(int k=0;k<dim;k++)
                printf("%i- ",lastMoves[j][k]);
        }
        printf("\n");
    }
}
void makeA_Move(int dim,char array[dim][dim],int n1,int m1,int n2,int m2,int points[2],int moves[2],int history[2 * (dim/2) * ((dim/2) + 1)][7],int lastMoves[2 * (dim/2) * ((dim/2) + 1)][7]){
    int N1,M1,N2,M2;
    printf("enter the row: ");
    scanf("%d",&N1);
    printf("enter the col: ");
    scanf("%d",&M1);
    printf("enter the row: ");
    scanf("%d",&N2);
    printf("enter the col: ");
    scanf("%d",&M2);

    if(N1 == 0 && M1 == 0 && N2 == 0 && M2 == 0){
        if(totalMoves!=0){
            totalMoves--;
            N1=history[totalMoves][0];M1=history[totalMoves][1];N2=history[totalMoves][2];M2=history[totalMoves][3];
            undo(dim,history,lastMoves,points,moves,player,playerTurn);
            n1 = 2*N1-2;m1 = 2*M1-2;n2 = 2*N2-2;m2 = 2*M2-2;
            array[(n1+n2)/2][(m1+m2)/2] =' ';
            if(array[n1+1][m1]!=1&&array[n1-1][m1]!=1&&array[n1][m1+1]!=1&&array[n1][m1-1]!=1)
                array[n1][m1] = '0';
            if(array[n2+1][m2]!=1&&array[n2-1][m2]!=1&&array[n2][m2+1]!=1&&array[n2][m2-1]!=1)
                array[n2][m2] = '0';
            if(n1==n2){
                array[n1+1][(m1+m2)/2]=' ';
                array[n1-1][(m1+m2)/2]=' ';
            }else{
                array[(n1+n2)/2][m1+1]=' ';
                array[(n1+n2)/2][m1-1]=' ';
            }
            return;
        }else{
            printf("You should start");
            return;
        }
    }
    else if(N1 == -1 && M1 == -1 && N2 == -1 && M2 == -1){
        if(movesBack!=0){
            movesBack--;
            redo(dim,history,lastMoves,points,moves,player);
            N1=history[totalMoves][0];M1=history[totalMoves][1];N2=history[totalMoves][2];M2=history[totalMoves][3];
            n1 = 2*N1-2;m1 = 2*M1-2;n2 = 2*N2-2;m2 = 2*M2-2;
            array[n1][m1] = '1';
            array[n2][m2] = '1';
            array[(n1+n2)/2][(m1+m2)/2] ='1';
            checkForSquares(n1,m1,dim,array,points);
            return;
        }else{
            printf("No redo left");
            return;
        }
    }
    else{
        n1 = 2*N1-2;m1 = 2*M1-2;n2 = 2*N2-2;m2 = 2*M2-2;


        if((array[(n1+n2)/2][(m1+m2)/2] =='1') || (n1 > dim) || (m1 > dim) || (n2 > dim) || (m2 > dim) ||(n1 < 0) || (m1 < 0) || (n2 < 0) || (m2 < 0)){
            printf("enter a valid move\n");
            return;
        }
        else if((!(m1%2 || n1%2 ) && (((abs(n1-n2) == 2) && (m1==m2)) || ((abs(m1-m2) == 2) && (n1==n2))))){
            array[n1][m1] = '1';
            array[n2][m2] = '1';
            array[(n1+n2)/2][(m1+m2)/2] ='1';
        }
        else{
            printf("enter a valid thing");
        }


        checkForSquares(n1,m1,dim,array,points);

        writeHistory(N1,M1,N2,M2,points[0],points[1],player,totalMoves,dim,history);

        if(sum != 0)
            playerTurn++;
        else{
            player=player==1?2:1;
        }

        totalMoves++;
    }
}







int main()
{
    int dim=0,points[2] = {0};
    int game=0;
    do{
    printf("Welcome to dots and boxes by RABSOOO team\nNew game(1)\nLoad game(2)\nLeader board(3)\nSettings(4)\nExit(5)\n");
    scanf("%d", &game);
    system("cls");
    switch(game){
        case 1:{
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
                        printf("\nEnter a valid input: ");

                }
            }while(dim == 0);

            int history[2 * (dim/2) * ((dim/2) + 1)][7],lastMoves[2 * (dim/2) * ((dim/2) + 1)][7];
            char world[dim][dim];


            createWorld(dim,world);


            createHistoryAndLastMoves(dim,history,lastMoves);


            do{
            system("cls");
            printHistory(dim,history);
            printf("______________________________________________________\n");
            printWorld(dim,world);

            printf("\nFirst player: %d\n\nSecond player: %d\n\nFirst player moves: %i\n\nSecond player moves: %i\n\nTurn player no.: %d\n\n",points[0],points[1],moves[0],moves[1],player);

            printf("\nEnter 0,0,0,0 to undo\t\t\tEnter -1,-1,-1,-1 to redo\n\n");




            makeA_Move(dim,world,NULL,NULL,NULL,NULL,points,moves,history,lastMoves);

            printHistory(dim,history);

            }while((moves[0] + moves[1]) < 2 * (dim/2) * (dim/2 + 1));

            system("cls");

            printWorld(dim,world);



            printf("\nFirst player: %d\n\nSecond player: %d\n\nFirst player moves: %i\n\nSecond player moves: %i\n\nTurn player no.: %d\n\nT=\n\n",points[0],points[1],moves[0],moves[1],player,totalMoves);
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
