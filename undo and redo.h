#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

void undo(int dim,int history[][dim],char array[dim][dim],int *h,int *i,int *u,int *x,int *y){
    int totalmoves = &h;int player = &i;int playerturn = &u;int moves[2] = {0};moves[0] = &x;moves[1] = &y;
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

void redo(int dim,int history[][dim],char array[dim][dim],int *h,int *i,int *u,int *x,int *y,int *p,int *a,int *b){
    int totalmoves = &h;int player = &i;int playerturn = &u;int moves[2] = {0};moves[0] = &x;moves[1] = &y;int maxmoves = &p;
    int points[2] = {0};points[0] = &a;points[2] = &b;
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
