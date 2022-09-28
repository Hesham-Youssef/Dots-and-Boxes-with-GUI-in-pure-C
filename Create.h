#ifndef CREATE_AND_PRINT_H_INCLUDED
#define CREATE_AND_PRINT_H_INCLUDED
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
void createAIwolrd(int dim,int AIworld[dim][dim]){
    for(int i=0;i<dim;i++){
        for(int j=0;j<dim;j++){
            AIworld[i][j] = 0;
        }
    }
}
void logging(int dim,int totalmoves,char array[dim][dim],int history[][7]){
    int i,j;
    FILE *log;
    log=fopen("Logging.txt","a");
    for(i=0;i<totalmoves;i++){
        for(j=0;j<7;j++)
            fprintf(log,"%d-",history[i][j]);
        fprintf(log,"\n");
    }fprintf(log,"\n\n");
    for(i=0;i<dim;i++){
        for(j=0;j<dim;j++)
            fprintf(log,"%c-",array[i][j]);
        fprintf(log,"\n");
    }fprintf(log,"\n\n");
    fclose(log);
}
#endif // CREATE_AND_PRINT_H_INCLUDED
