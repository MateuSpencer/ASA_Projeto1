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


//TODO Remove
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


int place(int size ,int **ptr_map){
    
//placeTile()
}

/*
mete o tile 1x1 no atnto esquerdo de baixo e ve se da
se der - tentar meter um 2x2 etc

*/



int main(int argc, char *argv[]){
    
    int i = 0, j = 0, k = 0, val = 0, max = 0;
    int n = 0, m = 0, sol = 0, line = -1, totalTiles = 0;
    int **map = NULL;
    int **partial_map = NULL;
    FILE *file_i = NULL;
    /*
    if( argc == 2 ){
        file_i = fopen(argv[1], "r"); //
    }else{
        return -1;
    }
    */

    file_i = fopen("test.txt", "r"); //TODO - Remove


    n = getNextInput(file_i);
    m = getNextInput(file_i);

    map = (int**)calloc(n,sizeof(int*));
    if(map == NULL){
        fprintf (stderr, "Error: not enough memory available");
        fclose(file_i);
        exit(0);
    }
    for(i=0; i < n; i++){
        map[i] = (int*)calloc(m,sizeof(int));
        if(map[i] == NULL){
            free_map(map, i);
            fclose(file_i);
            fprintf (stderr, "Error: not enough memory available");
            exit(0);
        }			
    }

    val = getNextInput(file_i);
    while(val != -1){
        line++;
        for(i = 0; i <val ; i++){
            map[line][i] = 1;
            totalTiles++;
        }
        val = getNextInput(file_i);
    }
//DEVIA DELIMITAR O MAPA ATE ONDE ELE ACTAUALLY COMEÇA sem contar com celulas que nao podem ser tiled, e mudar o m e n
    fclose(file_i);

    print_map(map,n,m);//TODO Remove
    
    partial_map = (int**)calloc(n,sizeof(int*));
    if(partial_map == NULL){
        fprintf (stderr, "Error: not enough memory available");
        fclose(file_i);
        exit(0);
    }
    for(i=0; i < n; i++){
        partial_map[i] = (int*)calloc(m,sizeof(int));
        if(partial_map[i] == NULL){
            free_map(partial_map, i);
            fclose(file_i);
            fprintf (stderr, "Error: not enough memory available");
            exit(0);
        }			
    }
    if (n>m){
        max = n;
    }else{
        max = m;
    }
    
    partial_map[0][m] = 1 //number of possible tilings for a board with size 0 = 1
    //criar array com as 2^m disposições que a linha pode ter
    for (i = n; i > 0; i--) { //avança nas linhas da de baixo para a mais acima ---------------- ve la se os indices tao bem
        for (j = 0; j < m; j++) { //avançar pelas 2^m disposições da linha e tentar meter peças tendo em conta a linha anterior?

            dp[i][0] += dp[i - 1][7];// The number of empty states for this column is the number of full states in the previous column.

            for (k = 2; k < max; k++) {
                 //o que importa é tentar meter um de 2x2 ate max(m,n) x max(m,n)
                //1x1 da sempre paar por 
                
            }
        }
    }


    free_map(map, n);
    free_map(partial_map, n);
    return partial_map[][m];    
}