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

int solve(int *map, int **configuration_patterns, int n, int m, int bottom_line_configuration){
    int i = 0, top_consecutive_square = 0,bottom_consecutive_space = 0, first = 0, fits = 0, config = 0;
    int configurations, line = 0, piece = 0, top_configuration = 0, square = 0, bottom_line = 0,bottom_configuration = 0, space = 0;
    int **solutions = NULL;
    //Base Case
    if(n == 1 || m == 1){
        return 1;
    }
    //MeOMOIZATION
/*
acho que o numero de soluções paar um quadrado com uma configuração encima é o mesmo que esse quadrado com essa configuração embaixo? invertida?
assim sendo as sao declaradas fora da função
quando é que ja ha resultados?
sobreposição?
    if(solutions[][] != 0){
        returnsolutions[][] =
    }
*/

configurations = pow(2,m);

    //2D Array for Dynamic Programming Results
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


/*função can fit que dado o tamanho da peça e onde começa, e a configuração de baixo diz se cabe lá
e quando estamos a iterar por todas as compinações de baixo e se trata da linha 1 so faço para a configuração de baixo que recebi
e eu devia re fazewr todas as configurações nestas chamadas do solve pq podem ter tamanhos inferiores*/

    for (line = n-2; line >= 0; line--){//iterates lines from bottom to top (excuding the bottom most)
        print_map(solutions,n,configurations);//TODO Remove
        for ( piece = 2; piece <= 2; piece++) { //n-line//try placing blocks from 2x2 to linexline
            for (top_configuration = 0; top_configuration < configurations; top_configuration++) {//iterate through the 2^m possible configuartions in a line
                if(top_configuration == 31){
                    top_configuration = 31;
                }
                if(log2(top_configuration) > map[line])break;
                solutions[line][top_configuration] += last_line_result(solutions,line,configurations);
                print_map(solutions,n,configurations);//TODO Remove 
                top_consecutive_square = 0;
                first = -1;
                for(square=0; square<m; square++){//l//see if the current piece can fulfill this configuration
                    if(configuration_patterns[top_configuration][square] == 1){//try to find as many consecutive blocks as the piece side
                        if(first == -1)first = square;
                        if(first == -2)first = square-1;
                        top_consecutive_square++;
                    }else{
                        first = -1;
                        top_consecutive_square = 0;
                    }
                    if(top_consecutive_square == piece){//see which botom configurations are compatible and then deal with the space left on the side if any
                        top_consecutive_square = 1;
                        bottom_line = line+piece-1;
                        if(bottom_line_configuration == 0){
                            for(bottom_configuration=0; bottom_configuration<configurations; bottom_configuration++){//r//iterate through all the possible cconfigurations for the bottom of the bloc to fit
                                if(log2(bottom_configuration) > map[bottom_line])break;
                                bottom_consecutive_space = 0;
                                for(space=first; space<(first+piece); space++){
                                    if(configuration_patterns[bottom_configuration][space] == 0) bottom_consecutive_space++;
                                }
                                if(bottom_consecutive_space == piece){
                                    fits = 1;
                                    break;
                                }
                            }
                        }else{
                            if(log2(bottom_line_configuration) <= map[bottom_line]){
                                bottom_consecutive_space = 0;
                                for(space=first; space<(first+piece); space++){
                                    if(configuration_patterns[bottom_line_configuration][space] == 0) bottom_consecutive_space++;
                                }
                                if(bottom_consecutive_space == piece){
                                    fits = 1;
                                }
                            }
                        }
                        if(fits){
                            fits = 0;
                            bottom_consecutive_space = 1;
                                //TODO acho que este nao tem de tar aqui
                                //solutions[line][top_configuration] += solutions[bottom_line][bottom_configuration];
                                print_map(solutions,n,configurations);//TODO Remove
                                if(first>0){//space on the left
                                    config = configuration_number(configuration_patterns, bottom_configuration,0, (first -1));
                                    solutions[line][top_configuration] += solve(map,configuration_patterns,piece,first,config);
                                }
                                if(first+piece < m){//passar espaço à esquerda
                                    config = configuration_number(configuration_patterns, bottom_configuration,first+piece, m-1);
                                    solutions[line][top_configuration] += solve(map,configuration_patterns,piece,m-(first+piece),config);
                                }
                                
                                print_map(solutions,n,configurations);//TODO Remove
                        }
                        first = -2;
                    }
                }
            }
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

    sol = solve(map,configuration_patterns,n,m,0);
    
    printf("\n%d",sol);
    free(map);
    free_map(configuration_patterns, m);
    return 1;    
}