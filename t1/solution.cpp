#include "lib.hpp"
#include <iostream>
#include <vector>

using namespace std;

void MergePaths(vector<int>& V, int start, int mid, int end){
    int nl = mid - start + 1, 
        nr = end - mid;
    int Left[nl], Right[nr];

    // copia os valores de V para Left e Right

    for (int i = start; i <= mid; i++)
        Left[i - start] = V[i];

    for (int i = mid + 1; i <= end; i++)
        Right[i - mid - 1] = V[i];

    int i, j, k;
    i = nl - 1; // ponteiro do final de Left[0..nl-1]
    j = nr - 1; // ponteiro do final de Right[0..nr-1]

    for (k = end; k >= start; k--){
        if (i >= 0 && j >= 0)
            if ( !has_edge(Left[i], Right[j])){ 
                V[k] = Left[i];
                i--;
            } else {
                V[k] = Right[j];
                j--;
            }
        else if (i < 0){ // Left acabou
            V[k] = Right[j];
            j--;

        } else{ // Right acabou
            V[k] = Left[i];
            i--;
        }
    }
}

void MergeSortPath(vector<int>& V, int start, int end){
    if (start < end) {                    // O(1)
        int mid  = (start + end) / 2;     // O(1)
        MergeSortPath(V, start, mid);     // T(n/2)
        MergeSortPath(V, mid + 1, end);   // T(n/2)
        MergePaths(V, start, mid, end);   // O(n)
    }

}

vector<int> solve(int n) {
    vector<int> path;

    // path := [1, 2, 3, .. n - 1, n]
    for (int i = 1; i <= n; i++)   // O(n)
        path.push_back(i);

    // encontra o caminho hamiltoniano
    MergeSortPath(path, 0, n - 1); // O(nlog(n))

    return path;
}

int main(int argc, char *argv[]) {

    char *filename = NULL;
    if(argc > 1)
        filename = argv[1];

    int n;
    initialize_has_edge(n, filename);

    vector<int> path = solve(n);
    int result = check_path(path, n);
    cout << result << '\n';
    return result;
}
