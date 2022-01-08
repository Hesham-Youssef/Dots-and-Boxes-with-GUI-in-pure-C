#ifndef UNDO_H_INCLUDED
#define UNDO_H_INCLUDED
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
void undo(int dim,int history[][7],char array[dim][dim],int *totalmoves,int *p1,int *p2,int *M1,int *M2,int *play){
    if(*totalmoves > 0){
        *totalmoves-=1;
        int tM = *totalmoves;
        int n1 = history[tM][0] , m1 = history[tM][1] ,  n2 = history[tM][2] ,  m2 = history[tM][3];
        array[(history[tM][0]+history[tM][2])/2][(history[tM][1]+history[tM][3])/2] =' ';
        if(!(checkforotherlines(dim,history,array,history[tM][0],history[tM][1]) >= 1))
            array[history[tM][0]][history[tM][1]] = '0';

        if(!(checkforotherlines(dim,history,array,history[tM][2],history[tM][3]) >= 1))
            array[history[tM][2]][history[tM][3]] = '0';

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
            else if(m1==dim-1)
                array[(n1+n2)/2][m1-1]=' ';
            else{
                array[(n1+n2)/2][m1+1]=' ';
                array[(n1+n2)/2][m1-1]=' ';
            }
        }

        if(*play==history[tM][6]){
            switch(*play){
                case 1:
                    *p1 = history[tM-1][4];
                    break;
                case 2:
                    *p2 = history[tM-1][5];
                    break;
            }
        }
        *play = history[tM][6];
        switch(*play){
            case 1:
                *M1-=1;
                break;
            case 2:
                *M2-=1;
                break;
        }
    }else{
        printf("\a");

    }
}


#endif // UNDO_H_INCLUDED
