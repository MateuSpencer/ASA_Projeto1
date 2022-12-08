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

int last_line_result(int **solutions, int line, int configurations){
    int i = 0, val = 0;
    for(i = configurations-1; i >= 0; i--){
        if(solutions[line+1][i] != 0) return solutions[line+1][i];
    }
    return val;  
}

//TODO REMOVE?
int configuration_number(int **configuration_patterns, int configuration, int start, int finish){
    int i = 0,rem = 0, decimal = 0;
    long long binary = configuration_patterns[configuration][start];
    for(i = start+1; i<= finish; i++){
        concatenate(binary,configuration_patterns[configuration][i]);
    }
    i = 0;
    while (binary!=0) {
        rem = binary % 10;
        binary /= 10;
        decimal += rem * pow(2, i);
        ++i;
    }
    return decimal;
}
//REMOVE??
int full_piece_configuration(int piece_size){
    int configuration = 1;
    for (int i = 1; i < piece_size; i++){
        configuration *= 2;
        configuration += 1;
    }
    return configuration;
}


//dada uma configuração ver desde que estados a consigo alcançare somar esses as maneiras de chegar a este estado
int solve_configuration(int *map, int **solutions, int **configuration_patterns,int configurations,int n, int m, int line, int top_configuration, int bottom_line_configuration){
    int sum = 0, piece = 0, square = 0, first = -1, top_consecutive_square = 0;

    //Base Case
    if(n == 1 || m == 1){
        return 1;
    }

    for(square=0; square<m; square++){
        if(configuration_patterns[top_configuration][square] == 1){//consecutive blocks
            if(first == -1)first = square;
            //if(first == -2)first = square-1;
            top_consecutive_square++;
        }else{
            first = -1;
            top_consecutive_square = 0;
        }
        if(top_consecutive_square != 0){//see which botom configurations are compatible and then deal with the space left on the side if any
            //top_consecutive_square = 1;
            //first == -2;
            for(piece = 1; piece <= top_consecutive_square; piece++){
                //sum += solve_configuration(map, solutions, configuration_patterns, configurations, n, m, line, top_configuration, bottom_line_configuration);
                //ver em que configuração estou e adicionar ao sum , maybe recebr a configuraçã0 da chamada mae
            // de que linha? ter em conta a peça
            //
            //
            //
            //
            }
        }
    }
    return sum;
}

int solve(int *map, int **configuration_patterns, int n, int m, int bottom_line_configuration, int top_line_configuration){
    int i = 0;
    int configurations = 0, line = 0, top_configuration = 0;
    int **solutions = NULL;

    configurations = pow(2,m);
    //2D Array for partial States Results
    solutions = (int**)calloc(n,sizeof(int*));
    if(solutions == NULL){
        fprintf (stderr, "Error: not enough memory available");
        //fclose(file_i);
        exit(0);
    }
    for(line=0; line < n; line++){
        solutions[line] = (int*)calloc(configurations,sizeof(int));
        if(solutions[line] == NULL){
            //teria de voltar a tras e fechar todos
            free_map(solutions, line);
            //fclos                               e(file_i);
            fprintf (stderr, "Error: not enough memory available");
            exit(0);
        }			
    }
    //Bottom Line Solutions
    if(bottom_line_configuration == 0){
        for(i = 0; i < configurations; i++){//number of possible tilings for all configurations in the first line (only one (with 1x1 tiles))
            solutions[n-1][i] = 1;
        }
    }else{
        solutions[n-1][bottom_line_configuration] = 1;
    }

    for (line = n-2; line >= 0; line--){//iterates lines from bottom to top (excuding the bottom most)
            if(top_line_configuration != 0 && line == 0){
                for (top_configuration = 0; top_configuration < configurations; top_configuration++) {//iterate through the 2^m possible configuartions in a line
                    if(log2(top_configuration) > map[line])break;

                    /*TODO*/solutions[line][top_configuration] += last_line_result(solutions,line,configurations);//always reachable with 1x1s// Devia ser so se for 0, ps senao ja foi posto o valor quando tentei por a peça anterior, maybe mais straight forward se fizer loop para a peça 1?
                    /*TODO*/print_map(solutions,n,configurations);//Remove

                    solve_configuration(map, solutions, configuration_patterns, configurations, n, m, line, top_configuration, bottom_line_configuration);
                }
            }else{
                solve_configuration(map, solutions, configuration_patterns, configurations, n, m, line, top_configuration, bottom_line_configuration);
            }
    }
    return last_line_result(solutions,-1,configurations);
}


int main(int argc, char *argv[]){
    int i = 0, j = 0, k = 0, l = 0,r = 0, t = 0, val = 0, first = -1, consecutive = 0, consecutive2 = 0;
    int n = 0, m = 0, sol = 0, line = -1, configurations = 0;
    int *map = NULL;
    int **configuration_patterns = NULL;
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

    map = (int*)calloc(n,sizeof(int));
    if(map == NULL){
        fprintf (stderr, "Error: not enough memory available");
        fclose(file_i);
        exit(0);
    }

    val = getNextInput(file_i);
    while(val != -1){
        line++;
        map[line] = val;
        val = getNextInput(file_i);
    }
    fclose(file_i);

    configurations = pow(2,m); //number of possible partial configuartions in a line to iterate through

    //2D Array for all possible configurations
    configuration_patterns = (int**)calloc(configurations,sizeof(int*));
    if(configuration_patterns == NULL){
        fprintf (stderr, "Error: not enough memory available");
        fclose(file_i);
        exit(0);
    }
    for(i=0; i < configurations; i++){
        configuration_patterns[i] = (int*)calloc(m,sizeof(int));
        if(configuration_patterns[i] == NULL){
            free_map(configuration_patterns, i);
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
                configuration_patterns[j+l][i] = 1;
            }
        }
    }

    sol = solve(map,configuration_patterns,n,m,0,0);
    
    printf("\n%d",sol);
    free(map);
    free_map(configuration_patterns, m);
    return 1;    
}