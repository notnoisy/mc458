#include <vector>
#include <set>
#include <iostream>
#include <random>

long long H[100100];
int MAXN;

bool has_edge(int i,int j){
    if(i==j)return 0;
    if(std::min(i,j) < 1 || std::max(i,j) > MAXN){
        // chamada invalida
        exit(1);
    }
    return H[i] > H[j];
}

void inicializa_has_edge(int n){
    std::mt19937_64 rng(n); // gerador aleatorio
    std::set<int> S;
    MAXN = n;
    for(int i=0;i<=n;i++){
        H[i] = rng();
        // garantir que nao tem repeticao:
        while(S.count(H[i]))H[i] = rng();
        //
        S.insert(H[i]);
    }
}
