#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
//#include "undo and redo.h"
int playerturn = 0, player = 1,moves[2] = {0},totalmoves=0,maxmoves = 0,points[2] = {0},dim=0,computer;char game=0;

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

    if((!computer && player==2) || player == 1){

    char term;
    int N1,M1,N2,M2,f=0;
    printf("\nenter the row: ");
    scanf("%d", &N1);

    if(N1 == 0){
        undo(dim,history,array);
        if(computer)
            while(history[totalmoves][6] != 1)
                undo(dim,history,array);
        return;
    }
    else if(N1 == -1){
        redo(dim,history,array);


        return;
    }else{
        printf("\nenter the col: ");
        scanf("%d", &M1);

        printf("\nenter the row: ");
        scanf("%d", &N2);

        printf("\nenter the col: ");
        scanf("%d", &M2);

        }





    if((array[((N1+N2)-2)][((M1+M2)-2)] =='1') || (N1 > (dim/2) + 1) || (M1 > (dim/2) + 1) || (N2 > (dim/2) + 1) || (M2 > (dim/2) + 1) || (N1 < 1) || (M1 < 1) || (N2 < 1) || (M2 < 1) || !(((abs(N1-N2) == 1) && (M1==M2)) ^ ((abs(M1-M2) == 1) && (N1==N2)))){
        printf("enter a valid move\n");
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
        printf("enter a valid thing");
    }

    checkforsquares(history[totalmoves][0],history[totalmoves][1],dim,array,history,points);
    history[totalmoves][4] = points[0];
    history[totalmoves][5] = points[1];

    if((totalmoves < maxmoves) && !computer)
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
        char world[dim][dim];

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
            printf("total moves:%d\t\t maximum moves:%d\n\n",totalmoves,maxmoves);
            if(computer)
                printAIwolrd(dim,AIworld);

            printf("\n\n\n\n");

            printworld(dim,world);
            printf("\nFirst player: %d\n\nSecond player: %d\n\nFirst player moves: %i\n\nSecond player moves: %i\n\nTurn player no.: %d\n\n",history[p-1][4],history[p-1][5],moves[0],moves[1],player);
            printf("\n enter -1 to redo\n\n");
            printf("\n enter 0 to undo\n\n");
            if(!computer)
                makeamove(dim,world,NULL,NULL,NULL,NULL,points,history,NULL);
            else
                makeamove(dim,world,NULL,NULL,NULL,NULL,points,history,AIworld);
        }

        system("cls");
        system("color 04");
        printworld(dim,world);

        system("color 0e");
        if(points[1]>points[0])
            printf("Congratulation for player no. 2 and hard luck for player no. 1");
        else
            printf("Congratulation for player no. 1 and hard luck for player no. 2");
        break;
    }
    case '2':
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
}
