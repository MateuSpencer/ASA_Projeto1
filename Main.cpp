#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unordered_map>
#include <iostream>
#include <sstream>

using namespace std;

int find_right_top(int *arr, int size, int m){
    int aux_line = 0, aux_right_top = 0, right_top = 0;

    for(aux_line = 0; aux_line < size; aux_line++) {
        if(arr[aux_line] > aux_right_top){
            aux_right_top = arr[aux_line];
            right_top = aux_line;
            if(arr[aux_line] == m)break;
        }
    }
return right_top;
}

string board_configuration(int *arr, int size){

    std::ostringstream os;
    for(int i = 0; i < size; i++){
        os << arr[i];
    }
    return os.str();
}

unsigned long long solve(int *map, std::unordered_map<string, unsigned long long>& solutions,  int n,int m, string configuration, int right_top){
    unsigned long long total = 0;
    int aux_line = 0, max_piece = 0, skip = 0, aux_right_top = 0;
    string original_configuration = configuration;;
    int *aux_map = NULL;
    
    if( map[right_top] <= 1){//ja so é possivel configuração com 1x1s
        return 1;
    }

    if (solutions.count(configuration) != 0){
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
            if(piece == max_piece){
                aux_right_top = find_right_top(aux_map,n, (m-1));
            }else{
                aux_right_top = right_top + piece;
            }
            configuration = board_configuration(aux_map,n);
            total += solve(aux_map,solutions,n,m, configuration, aux_right_top);
        }else{
            skip = 0;
            piece = max_piece+1;
        } 
    }
    solutions[original_configuration] = total;
    free(aux_map);
    return total;
}

int main(int argc, char *argv[]){
    int n = 0,m = 0, j = 0;
    unsigned long long sol = 0;
    int *map = NULL;
    std::unordered_map<string, unsigned long long> solutions;

    cin >> j;
    n = j;
    cin >> j;
    m = j;

    map = (int*)calloc(n,sizeof(int));
    if(map == NULL){
        fprintf (stderr, "Error: not enough memory available");
        exit(0);
    }

    for(int i = 0; i<n; i++){
        cin >> j;
        map[i] = j;
    }

    int right_top = find_right_top(map,n,m);
    
    if( map[right_top] != 0){ //mapa vazio
        string configuration = board_configuration(map,n);
        sol = solve(map,solutions,n,m,configuration, right_top);
    }
    
    cout << sol << endl;

    free(map);
    return 0;    
}