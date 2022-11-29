#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <math.h>

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
    int n = 0, m = 0, sol = 0, line = -1, totalTiles = 0, configurations = 0;
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
//TODO DEVIA DELIMITAR O MAPA ATE ONDE ELE ACTAUALLY COMEÇA sem contar com celulas que nao podem ser tiled, e mudar o m e n
    fclose(file_i);

print_map(map,n,m);//TODO Remove

    
    configurations = pow(2,m); //number of possible partial configuartions in a line to iterate through

    //2D Array for Dynamic Programming Results
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
    
    partial_map[0][configurations -1] = 1; //number of possible tilings for the first line (only one (with 1x1 tiles))
    
    for (i = n-2; i >= 0; i--) { //goes through all lines from the one above the last to the first one
        partial_map[i][configurations -1] += partial_map[i - 1][configurations -1];// The number of valid configurations for this empty column is the same as the ones from the previous column  when full full
        for (j = 0; j < configurations; j++) { //iterate through the 2^m possible configuartions in a line 
            
            partial_map[i][j] += partial_map[i-1][configurations -1]; // this partial configuartion is possible from the last full configuration by adding only 1x1 blocks at least
            //Verificar se esta configuração ta dentro dos limites da escada?
            for (k = 2; k < max; k++) {
                //Figure Out on each configuration, how many possible ways there are to reach it, given the previous line configuration wit all the possiblr pieces
                //o que importa é tentar meter um de 2x2 ate max(m,n) x max(m,n)
                //Acho que é preciso ter em conta nao so a linha anterior, mas se for uma peça lxl, l linhas anteriores
                //might become unfiesable          
            }
        }
    }
    free_map(map, n);
    free_map(partial_map, n);
    return partial_map[0][configurations -1];    
}