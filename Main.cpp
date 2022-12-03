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



/*
mete o tile 1x1 no atnto esquerdo de baixo e ve se da
se der - tentar meter um 2x2 etc

*/



int main(int argc, char *argv[]){
    
    int i = 0, j = 0, k = 0, l = 0,r = 0, t = 0, val = 0, consecutive = 0, consecutive2 = 0;
    int n = 0, m = 0, sol = 0, line = -1, totalTiles = 0, configurations = 0;
    int **map = NULL;
    int **solutions = NULL;
    int **config_patterns = NULL;
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

    //2D Array for all possible configurations
    config_patterns = (int**)calloc(configurations,sizeof(int*));
    if(config_patterns == NULL){
        fprintf (stderr, "Error: not enough memory available");
        fclose(file_i);
        exit(0);
    }
    for(i=0; i < configurations; i++){
        config_patterns[i] = (int*)calloc(m,sizeof(int));
        if(config_patterns[i] == NULL){
            free_map(config_patterns, i);
            fclose(file_i);
            fprintf (stderr, "Error: not enough memory available");
            exit(0);
        }			
    }
    //NUMBER THE Array with all combinations
    k = 0;
    for(i=0; i<m; i++){
        k = pow(2,i);
        for(j=k;j<configurations; j += 2*k ){
            for(l=0 ;l<k ;l++ ){
                config_patterns[j+l][i] = 1;
            }
        }
    }
    //2D Array for Dynamic Programming Results
    solutions = (int**)calloc(n,sizeof(int*));
    if(solutions == NULL){
        fprintf (stderr, "Error: not enough memory available");
        fclose(file_i);
        exit(0);
    }
    for(i=0; i < n; i++){
        solutions[i] = (int*)calloc(configurations,sizeof(int));
        if(solutions[i] == NULL){
            free_map(solutions, i);
            fclose(file_i);
            fprintf (stderr, "Error: not enough memory available");
            exit(0);
        }			
    }

    for(i=0;i<configurations; i++){//number of possible tilings for all configurations in the first line (only one (with 1x1 tiles))
        solutions[n-1][i] = 1;
    }
    
    for (i = n-2; i >= 0; i--) { //goes through all lines from the one above the last to the first one
        solutions[i][0] += solutions[i + 1][configurations -1];// The number of valid configurations for this empty column is the same as the ones from the previous column  when full full
        //atenção que pode nao ser o mais a direita, maybe começar a proucurar da direita para a esquerda pelo primeiro que nao seja 0
        print_map(solutions,n,configurations);//TODO Remove 
        for (k = 2; k <= (n-i); k++) { //TODO - confirm (n-i) -- try placing blocks from 2x2 to linexline
            //for a yxy piece, you have to look to the solutions from line y-1 lines back
            for (j = 1; j < configurations; j++) { //iterate through the 2^m possible configuartions in a line (skip the 0, already filled above) 
                //TODO se a configuração nao pertencer aos limites da escada, acho que devia passar logo para a proxima linha ou peça, aka break ->nao pertence se tiver um 1 fora dos limites da escada
                solutions[i][j] += solutions[i-1][configurations -1];
                // this and all valid partial configuartion are possible from the last fullest configuration by adding only 1x1 blocks at least
                    //atençao tal como encima que o ultimo estado mais completo pode nao ser o ultimo, proucurar da direita para a esquerda pelo primeiro diferente de 0
                consecutive = 0;
                for(l=0; l<m; l++){//try to fit piece in present configuration
                    if(config_patterns[j][l] == 1){//try to find as many consecutive blocks as the piece side
                        consecutive++;
                    }else{
                        consecutive = 0;
                    }
                    if(consecutive == k){//see which botom configurations are compatible and then deal with the space left on the side if any
                        consecutive = 0;
                        
                        for(r=0; r<configurations; r++){//iterate through all the possible cconfigurations for the bottom of the bloc to fit - make sure configurations are valid in the stairs
                            for(r=0; r<m; r++){
                                if(config_patterns[j][l] == 0){
                                        consecutive++;
                                    }else{
                                        consecutive = 0;
                                    }
                                    if(consecutive == k){}



                            }


                        }







                    }
                }

            }

        }
    }
    free_map(map, n);
    free_map(solutions, n);
    return solutions[0][configurations -1];    
}