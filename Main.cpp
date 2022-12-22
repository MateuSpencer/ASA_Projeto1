#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <sstream>

using namespace std;

int find_right_top(vector<int> vect,  int m){
    int aux_line = 0, aux_right_top = 0, right_top = 0, size = vect.size();

    for(aux_line = 0; aux_line < size; aux_line++) {
        if(vect[aux_line] > aux_right_top){
            aux_right_top = vect[aux_line];
            right_top = aux_line;
            if(vect[aux_line] == m)break;
        }
    }
return right_top;
}

size_t hash_func(std::vector<int>& vec) {
    std::size_t seed = vec.size();
    for(auto x : vec) {
        x = ((x >> 16) ^ x) * 0x45d9f3b;
        x = ((x >> 16) ^ x) * 0x45d9f3b;
        x = (x >> 16) ^ x;
        seed ^= x + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
}

unsigned long long solve(vector<int> map, std::unordered_map<uint64_t, unsigned long long>& solutions, int m, int right_top){
    unsigned long long total = 0;
    int aux_line = 0, max_piece = 0, skip = 0, aux_right_top = 0, size = map.size();
    uint64_t configuration = 0;
    
    if( map[right_top] <= 1){//ja so é possivel configuração com 1x1s
        return 1;
    }
    configuration = hash_func(map);
    if (solutions.count(configuration) != 0){
        return solutions[configuration];
    }
    
    for(aux_line = right_top; aux_line <size; aux_line++){ // ate que tamanho de peça posso colocar
        if( map[aux_line] < map[right_top] ) break;
        max_piece ++;
    }

    vector<int> aux_map;
    for(int piece = 1;piece <= max_piece; piece++){
        aux_map.clear();
        for(aux_line = 0; aux_line < size; aux_line ++){//copy map to aux_map
            aux_map.push_back(map[aux_line]);
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
                aux_right_top = find_right_top(aux_map, (m-1));
            }else{
                aux_right_top = right_top + piece;
            }
            total += solve(aux_map,solutions,m, aux_right_top);
        }else{
            skip = 0;
            piece = max_piece+1;
        } 
    }
    solutions[configuration] = total;
    return total;
}

int main(){
    int n = 0,m = 0, j = 0, first = 1;
    unsigned long long sol = 0;
    vector<int> map;
    std::unordered_map<uint64_t, unsigned long long> solutions;

    cin >> j;
    n = j;
    cin >> j;
    m = j;

    for(int i = 0; i<n; i++){
        cin >> j;
        if(first != 1 ||  j != 0 ){
            first = 0;
            map.push_back(j);
        }
    }
    
    if( !map.empty()){ //mapa vazio
        int right_top = find_right_top(map,m);
        sol = solve(map,solutions,m, right_top);
    }
    
    cout << sol << endl;
    return 0;    
}