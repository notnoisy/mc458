#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct pizza {
    int s, t, r;
};

int max(int a, int b){
    return a > b ? a : b;
}

int KnapSack(vector<pizza> &pzs, vector< vector<int> > &dp, int N, int T, int n, int t){
    if (n >= N || t >= T) // caso base: faltam N items ou falta T minutos
        return 0;

    if (dp[n][t] != -1) // entrada ja calculada
        return dp[n][t];

    int optVal = KnapSack(pzs, dp, N, T, n + 1, t); // nao coloca o item

    int time = t + pzs[n].t;             // instante onde a pizza sera avaliada
    int st = pzs[n].s - pzs[n].r * time; // s(t) = si - ri * time
    if (time <= T && st > 0){ // possivel e faz sentido tentar colocar
            optVal = max(optVal, st + KnapSack(pzs, dp, N, T, n + 1, time)); // tenta colocar
    }

    dp[n][t] = optVal;
    return dp[n][t];
}

int OrderingCriteria(pizza pz1, pizza pz2){
    return ((double) pz1.r) / pz1.t > ((double) pz2.r) / (pz2.t);
}

int solve(vector<pizza> &pizzas, int N, int T) {
    vector< vector<int> > dp(N + 1, vector<int>(T + 1, -1));
    
    sort(pizzas.begin(), pizzas.end(), OrderingCriteria); // ordena com base no criterio guloso
    return KnapSack(pizzas, dp, N, T, 0, 0);
}

int main() {

    int N, T;
    cin >> N >> T;

    vector<pizza> pizzas(N);
    for(int i = 0; i < N; ++i)
        cin >> pizzas[i].s >> pizzas[i].t >> pizzas[i].r;

    cout << solve(pizzas, N, T) << endl;
    return 0;
}
