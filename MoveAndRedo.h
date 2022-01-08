#ifndef MOVEANDREDO_H_INCLUDED
#define MOVEANDREDO_H_INCLUDED
#include "AI.h"
int upperRight(int n1,int m1,int dim,char array[dim][dim],int play){
    if((m1 == dim -1) || (n1 == 0) || array[n1-1][m1+1] == 'X' || array[n1-1][m1+1] == 'O')
        return 0;
    if(array[n1][m1+1]!=' '){
            if(array[n1-1][m1]!=' '){
                if(array[n1-1][m1+2]!=' '){
                    if(array[n1-2][m1+1]!=' '){
                        switch(play){
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
int upperLeft(int n1,int m1,int dim,char array[dim][dim],int play){
    if((m1 == 0) || (n1 == 0) || array[n1-1][m1-1] == 'X' || array[n1-1][m1-1] == 'O')
        return 0;
    if(array[n1][m1-1]!=' '){
            if(array[n1-1][m1]!=' '){
                if(array[n1-1][m1-2]!=' '){
                    if(array[n1-2][m1-1]!=' '){
                        switch(play){
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
int downRight(int n1,int m1,int dim,char array[dim][dim],int play){
    if((m1 == dim -1) || (n1 == dim -1) || array[n1+1][m1+1] == 'X' || array[n1+1][m1+1] == 'O')
        return 0;
    if(array[n1][m1+1]!=' '){
            if(array[n1+1][m1]!=' '){
                if(array[n1+1][m1+2]!=' '){
                    if(array[n1+2][m1+1]!=' '){
                        switch(play){
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
int downLeft(int n1,int m1,int dim,char array[dim][dim],int play){
    if((m1 == 0) || (n1 == dim-1) || array[n1+1][m1-1] == 'X' || array[n1+1][m1-1] == 'O')
        return 0;
    if(array[n1][m1-1]!=' '){
            if(array[n1+1][m1]!=' '){
                if(array[n1+1][m1-2]!=' '){
                    if(array[n1+2][m1-1]!=' '){
                        switch(play){
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
void checkForSquares(int n1,int m1,int dim,char array[dim][dim],int history[][7],int **p1,int **p2, int **M1,int **M2,int **play){
    int sum=0;
    sum = upperRight(n1,m1,dim,array,**play) + upperLeft(n1,m1,dim,array,**play) + downRight(n1,m1,dim,array,**play) + downLeft(n1,m1,dim,array,**play);
    if(**play==2)
        **p2 += sum;
    else
        **p1 += sum;
    switch(**play){
        case 1:
            **M1+=1;
            break;
        case 2:
            **M2+=1;
    }
    if(sum == 0)
        **play=**play==1?2:1;
}
void makeMove(int dim,char array[dim][dim],int n1,int m1,int n2,int m2,int history[][7],int AIworld[dim][dim],int com,int *play,int *totalmoves,int *maxmoves,int *p1,int *p2,int *M1,int *M2){
    int tM = *totalmoves;
    if(!com && *play == 2 || *play == 1){

        if((array[((n1+n2)/2)][((m1+m2)/2)] !=' ') || (n1 > dim - 1) || (m1 > dim - 1) || (n2 > dim - 1) || (m2 > dim - 1) || (n1 < 0) || (m1 < 0) || (n2 < 0) || (m2 < 0) || !(((abs(n1-n2) == 2) && (m1==m2)) ^ ((abs(m1-m2) == 2) && (n1==n2)))){

            return;
        }
        history[tM][0] = n1 ; history[tM][1] = m1 ;history[tM][2] = n2 ; history[tM][3] = m2;

    }else{
        AI(dim,array,AIworld,history,tM);
    }

    history[tM][6] = *play;


    if(!(history[tM][1]%2 || history[tM][0]%2 )){
        array[history[tM][0]][history[tM][1]] = '1';
        array[history[tM][2]][history[tM][3]] = '1';
        if(*play == 1)
            array[(history[tM][0]+history[tM][2])/2][(history[tM][1]+history[tM][3])/2] ='2';
        else if(*play == 2)
            array[(history[tM][0]+history[tM][2])/2][(history[tM][1]+history[tM][3])/2] ='3';
    }


    checkForSquares(history[tM][0],history[tM][1],dim,array,history,&p1,&p2,&M1,&M2,&play);
    history[tM][4] = *p1;
    history[tM][5] = *p2;

    if(*totalmoves < *maxmoves)
        *maxmoves = *totalmoves;

    *maxmoves+=1;
    *totalmoves+=1;
}
void redo(int dim,int history[][7],char array[dim][dim],int *totalmoves,int maxmoves,int *p1,int *p2, int *M1,int *M2,int *play){
    if(*totalmoves < maxmoves && (maxmoves > 1)){
        int tM = *totalmoves;
        int n1 = history[tM][0];int m1 = history[tM][1];
        if(history[tM][6] == 1)
            array[(history[tM][0]+history[tM][2])/2][(history[tM][1]+history[tM][3])/2] ='2';
        else if(history[tM][6] == 2)
            array[(history[tM][0]+history[tM][2])/2][(history[tM][1]+history[tM][3])/2] ='3';
        array[history[tM][0]][history[tM][1]] = '1';

        array[history[tM][2]][history[tM][3]] = '1';

        checkForSquares(n1,m1,dim,array,history,&p1,&p2,&M1,&M2,&play);
        *totalmoves+=1;

    }else
        printf("\a");
}
#endif // MOVEANDREDO_H_INCLUDED
