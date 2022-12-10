#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <unordered_map>

void free_map(int **ptr_map, int N_l){
    int i = 0;
    for (i=0; i < N_l; i++){
        free(ptr_map[i]);		
    }
    free(ptr_map);
}

int concatenate(int a, int b){
    char s1[10];
    char s2[2];
    sprintf(s1, "%d", a);
    sprintf(s2, "%d", b);
    strcat(s1, s2);
    int c = atoi(s1);
    return c;
}

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

void print_array(int *arr, int size){
    printf("\n");
    for(int i=0; i<size; i++){
        printf("%d",arr[i]);
    }
    printf("\n");
}

int find_right_top(int *arr, int size){
    int aux_line = 0, aux_right_top = 0, right_top = 0;

    for(aux_line = 0; aux_line < size; aux_line++) {
        if(arr[aux_line] > aux_right_top){
            aux_right_top = arr[aux_line];
            right_top = aux_line;
        }
    }
return right_top;
}

int board_configuration(int *arr, int size){
    int configuration = arr[0];
    for(int i = 1; i < size; i++){
        configuration = concatenate(configuration,arr[i]);
    }
    return configuration;
}

int solve(int *map, std::unordered_map<int, int>& solutions,  int n, int configuration){
    int total = 0, right_top= 0, aux_line = 0, max_piece = 0, skip = 0, original_configuration = configuration;;
    int *aux_map = NULL;
    //print_array(map,n);

    right_top = find_right_top(map,n);
    
    if( map[right_top] <= 1){//ja so é possivel configuração com 1x1s
        free(aux_map);
        return 1;
    }

    if (solutions.find(configuration) != solutions.end()){
        free(aux_map);
        return solutions[configuration];
    }
    
    for(aux_line = right_top; aux_line <n; aux_line++){ // ate que tamanho de peça posso colocar
        if( map[aux_line] < map[right_top] ) break;
        max_piece ++;
    }

    aux_map = (int*)calloc(n,sizeof(int));//novo mapa para passar recursivamente
    for(int piece = 1;piece <= max_piece; piece++){
        for(aux_line = 0; aux_line < n; aux_line ++){//copy map to aux_map
            aux_map[aux_line] = map[aux_line];
        }
        for(aux_line = right_top; aux_line < (right_top + piece); aux_line++){ //retirar peça do mapa
            aux_map[aux_line] = aux_map[aux_line] - piece;
            if(aux_map[aux_line] < 0){//esta peça passa dos limites
                skip = 1;
                break;
            }
        }
        if(skip == 0){
            //print_array(aux_map,n);
            configuration = board_configuration(aux_map,n);
            total += solve(aux_map,solutions,n, configuration);
        }else{
            skip = 0;
            piece == max_piece+1;
        } 
    }
    solutions[original_configuration] = total;
    free(aux_map);
    return total;
}


int main(int argc, char *argv[]){
    int n = 0, m = 0,val = 0, line = -1, sol = 0;
    int *map = NULL;
    FILE *file_i = NULL;
    std::unordered_map<int, int> solutions;
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

    print_array(map,n);

    val = board_configuration(map,n);

    sol = solve(map,solutions,n,val);
    
    printf("\n%d",sol);
    free(map);
    return 1;    
}