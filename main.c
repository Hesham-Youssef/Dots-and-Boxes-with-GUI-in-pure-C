#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

void printworld(int rows,int cols,char array[rows][cols]){
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            printf("%c  ",array[i][j]);
        }
        printf("\n");
    }
}
void createworld(int rows,int cols,char array[rows][cols]){
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            if(!(j%2 || i%2))
                array[i][j]='0';
            else
                array[i][j]=' ';
        }
    }
}

int upperright(int n1,int m1,int rows,int cols,char array[rows][cols]){
    if((m1 == cols -1) || (n1 == 0) || array[n1-1][m1+1] == '1')
        return 0;
    if(array[n1][m1+1]=='1'){
            if(array[n1-1][m1]=='1'){
                if(array[n1-1][m1+2]=='1'){
                    if(array[n1-2][m1+1]=='1'){
                        array[n1-1][m1+1] = '1';
                        return 1;
                    }
                }
            }
    }
    return 0;
}
int upperleft(int n1,int m1,int rows,int cols,char array[rows][cols]){
    if((m1 == 0) || (n1 == 0) || array[n1-1][m1-1] == '1')
        return 0;
    if(array[n1][m1-1]=='1'){
            if(array[n1-1][m1]=='1'){
                if(array[n1-1][m1-2]=='1'){
                    if(array[n1-2][m1-1]=='1'){
                        array[n1-1][m1-1] = '1';
                        return 1;
                    }
                }
            }
    }
    return 0;
}
int downright(int n1,int m1,int rows,int cols,char array[rows][cols]){
    if((m1 == cols -1) || (n1 == rows -1) || array[n1+1][m1+1] == '1')
        return 0;
    if(array[n1][m1+1]=='1'){
            if(array[n1+1][m1]=='1'){
                if(array[n1+1][m1+2]=='1'){
                    if(array[n1+2][m1+1]=='1'){
                        array[n1+1][m1+1] = '1';
                        return 1;
                    }
                }
            }
    }
    return 0;
}
int downleft(int n1,int m1,int rows,int cols,char array[rows][cols]){
    if((m1 == 0) || (n1 == rows-1) || array[n1+1][m1-1] == '1')
        return 0;
    if(array[n1][m1-1]=='1'){
            if(array[n1+1][m1]=='1'){
                if(array[n1+1][m1-2]=='1'){
                    if(array[n1+2][m1-1]=='1'){
                        array[n1+1][m1-1] = '1';
                        return 1;
                    }
                }
            }
    }
    return 0;
}






void checkforsquares(int n1,int m1,int rows,int cols,char array[rows][cols],int points[]){

    points[0] += upperright(n1,m1,rows,cols,array) + upperleft(n1,m1,rows,cols,array) + downright(n1,m1,rows,cols,array) + downleft(n1,m1,rows,cols,array);
}

void makeamove(int rows,int cols,char array[rows][cols],int n1,int m1,int n2,int m2,int points[]){
    printf("enter the row: ");
    scanf("%d",&n1);
    printf("enter the col: ");
    scanf("%d",&m1);

    printf("enter the row: ");
    scanf("%d",&n2);
    printf("enter the col: ");
    scanf("%d",&m2);

    if((array[(n1+n2)/2][(m1+m2)/2] =='1'))
        return;

    if((!(m1%2 || n1%2 ) && (((abs(n1-n2) == 2) && (m1==m2)) || ((abs(m1-m2) == 2) && (n1==n2))))){
        array[n1][m1] = '1';
        array[n2][m2] = '1';
        array[(n1+n2)/2][(m1+m2)/2] ='1';
    }
    else{
        printf("enter a valid thing");
    }


    checkforsquares(n1,m1,rows,cols,array,points);


}











int main()
{
    int rows=7,cols=7,points[2] = {0};
    char world[rows][cols];
    createworld(rows,cols,world);
    while(1){
    system("cls");

    printworld(rows,cols,world);
    printf("\n %d\n",points[0]);
    printf("\n %d\n",points[1]);
    makeamove(rows,cols,world,NULL,NULL,NULL,NULL,points);




    }



    return 0;
}
