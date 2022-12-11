#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unordered_map>
using namespace std;

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

string board_configuration(int *arr, int size){
    string configuration = to_string(arr[0]);
    for(int i = 1; i < size; i++){
        configuration = configuration + to_string(arr[i]);
    }
    return configuration;
}

double solve(int *map, std::unordered_map<string, unsigned long long>& solutions,  int n, string configuration){
    unsigned long long total = 0;
    int right_top= 0, aux_line = 0, max_piece = 0, skip = 0;
    string original_configuration = configuration;;
    int *aux_map = NULL;

    right_top = find_right_top(map,n);
    
    if( map[right_top] <= 1){//ja so é possivel configuração com 1x1s
        return 1;
    }

    if (solutions.find(configuration) != solutions.end()){
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
            configuration = board_configuration(aux_map,n);
            total += solve(aux_map,solutions,n, configuration);
        }else{
            skip = 0;
            piece = max_piece+1;
        } 
    }
    solutions[original_configuration] = total;
    free(aux_map);
    return total;
}

int input(){
    int invalido = 1, val = 0;
    while(invalido){
        if(scanf("%d", &val) == 1){
            invalido = 0;
        }else{
            scanf("%*s");
        }
    }
    return val;
}

int main(int argc, char *argv[]){
    int n = 0;
    unsigned long long sol = 0;
    int *map = NULL;
    std::unordered_map<string, unsigned long long> solutions;

    n = input();
    input();

    map = (int*)calloc(n,sizeof(int));
    if(map == NULL){
        fprintf (stderr, "Error: not enough memory available");
        exit(0);
    }

    for(int i = 0; i<n; i++){
        map[i] = input();
    }

    int right_top = find_right_top(map,n);
    
    if( map[right_top] != 0){ //mapa vazio
        string configuration = board_configuration(map,n);
        sol = solve(map,solutions,n,configuration);
    }
    
    printf("\n%llu",sol);
    free(map);
    return 1;    
}