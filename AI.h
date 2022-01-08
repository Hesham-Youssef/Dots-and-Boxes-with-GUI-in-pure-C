#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
void AI(int dim,char world[dim][dim],int AIworld[dim][dim],int history[][7],int totalmoves){
    int numberoflines1,numberoflines2;
    // checks horizontal lines
    for(int i=0;i<dim;i=i+2){
        for(int j=1;j<dim;j=j+2){
            numberoflines1 = 0;
            numberoflines2 = 0;
            if(world[i][j] != ' ')
                AIworld[i][j] = -100;
            else{
                if( i != 0){
                    if(world[i-1][j+1] != ' ')
                         numberoflines1++;
                    if(world[i-1][j-1] != ' ')
                         numberoflines1++;
                    if(world[i-2][j] != ' ')
                         numberoflines1++;
                    if(numberoflines1 == 3)
                         numberoflines1 += 10;
                    else if(numberoflines1 == 2)
                        numberoflines1 -=10;
                }
                if( i != dim - 1){
                    if(world[i+1][j-1] != ' ')
                         numberoflines2++;
                    if(world[i+1][j+1] != ' ')
                         numberoflines2++;
                    if(world[i+2][j] != ' ')
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
            if(world[i][j] != ' ')
                AIworld[i][j] = -100;
            else{
                if( j != 0){
                    if(world[i-1][j-1] != ' ')
                         numberoflines1++;
                    if(world[i+1][j-1] != ' ')
                         numberoflines1++;
                    if(world[i][j-2] != ' ')
                         numberoflines1++;
                    if(numberoflines1 == 3)
                         numberoflines1 += 10;
                    else if(numberoflines1 == 2)
                        numberoflines1 -=10;
                }
                if( j != dim-1){
                    if(world[i+1][j+1] != ' ')
                         numberoflines2++;
                    if(world[i-1][j+1] != ' ')
                         numberoflines2++;
                    if(world[i][j+2] != ' ')
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
    int maxi=0,maxj=0,max=-100;
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

#endif // AI_H_INCLUDED
