#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//TODO
/******************************************************************************
 * free_map
 *
 * Arguments: ptr_map - ponteiro para o mapa (tabela)
 *            N_l - numero de linhas 
 * Returns: (void)
 *
 * Description: liberta o mapa
 *****************************************************************************/
void free_map(int **ptr_map, int N_l){
    int i = 0;
    for (i=0; i < N_l; i++){
        free(ptr_map[i]);		
    }
    free(ptr_map);
}

//TODO
/******************************************************************************
 * Concatenate
 *
 * Arguments: a - numero que ficará à esquerda
 *            b - número que ficará à direita
 * Returns: c - concatenação dos números
 *
 * Description: junta dois numeros transformando-o num só
 *****************************************************************************/
int concatenate(int a, int b){
    char s1[10];
    char s2[2];
    sprintf(s1, "%d", a);
    sprintf(s2, "%d", b);
    strcat(s1, s2);
    int c = atoi(s1);
    return c;
}

//TODO
/******************************************************************************
 * getnext 
 *
 * Arguments: file_i - ponteiro para o ficheiro de entrada
 *            
 * Returns: i - próximo numero
 *
 * Description: retira o proximo numero da lista de entrada
 *****************************************************************************/

int getNextInput(FILE *file_i){
    char c = 0;
    int i = 0,j = 0;
    while (c<48 || 57<c){ //find the next numeric character
        c = fgetc(file_i);
        if (c == -1)return -1;//reached the end of the file
    }
    i = (c - 48);
    c = fgetc(file_i);//get next numbers
    while(c>=48 && c<=57){
        j = (c - 48);
        i = concatenate(i,j);
        c = fgetc(file_i);
    }
    return i;
}





void print_map(int **ptr_map,int N_l,int N_c){
    int i,j;
    for(i=0;i<N_l; i++){
        printf("%d  ----  ",i);
        for(j=0;j<N_c; j++){
            printf("%d ", ptr_map[i][j]);
        }
        printf("\n");
    }

}





int main(int argc, char *argv[]){
    
    int i = 0, val = 0;
    int n = 0, m = 0, sol = 0, line = -1;
    int **ptr_map = NULL; //double pointer for the map
    FILE *file_i = NULL;

    if( argc == 2 ){
        file_i = fopen("test.txt", "r"); //argv[1]
    }else{
        return -1;
    }
    
    n = getNextInput(file_i);
    m = getNextInput(file_i);

    ptr_map = (int**)calloc(n,sizeof(int*));
    if(ptr_map == NULL){
        fprintf (stderr, "Error: not enough memory available");
        fclose(file_i);
        exit(0);
    }
    for(i=0; i < n; i++){
        ptr_map[i] = (int*)calloc(m,sizeof(int));
        if(ptr_map[i] == NULL){
            free_map(ptr_map, i);
            fclose(file_i);
            fprintf (stderr, "Error: not enough memory available");
            exit(0);
        }			
    }

    while(val = getNextInput(file_i) != -1){
        line++;
        for(i = line; i <line ; i++)
        ptr_map[val][i] = 1;
    }

    print_map(ptr_map,n,m);

    free_map(ptr_map, n);
    fclose(file_i);
    return sol;    
}