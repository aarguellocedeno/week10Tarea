#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <omp.h>
using namespace std;

int main() {
    srand(time(NULL));

    int n = 6; // número de vértices
    vector<vector<int>> adj = {
        {1, 2},     // vecinos de 0
        {0, 2, 3},  // vecinos de 1
        {0, 1, 3},  // vecinos de 2
        {1, 2, 4},  // vecinos de 3
        {3, 5},     // vecinos de 4
        {4}         // vecinos de 5
    };

    int Delta = 0;
    for (auto &v : adj) Delta = max(Delta, (int)v.size());

    vector<int> color(n);
    vector<bool> mark(n, false);

    // Inicialización aleatoria en paralelo
    #pragma omp parallel for
    for (int v = 0; v < n; v++) {
        color[v] = rand() % (Delta + 1) + 1;
    }

    bool conflict = true;
    int iter = 0;

    while (conflict) {
        conflict = false;

        // Marcar vértices en conflicto
        #pragma omp parallel for
        for (int u = 0; u < n; u++) {
            for (int v : adj[u]) {
                if (color[u] == color[v]) {
                    if (u < v) mark[v] = true;
                    else       mark[u] = true;
                }
            }
        }

        // Recolorear los vértices marcados
        #pragma omp parallel for
        for (int v = 0; v < n; v++) {
            if (mark[v]) {
                mark[v] = false;

                // Buscar un color diferente a sus vecinos
                vector<bool> forbidden(Delta+2, false);
                for (int u : adj[v]) {
                    forbidden[color[u]] = true;
                }
                int c =1;
                bool flag = true;
                while ( (c <= Delta+1)and flag ) {
                    if (!forbidden[c]) {
                        color[v] = c;
                        flag=false;
                    }

                    c++;
                }

                // Hubo recoloreo, así que aún puede haber conflictos
                #pragma omp critical
                conflict = true;
            }
        }

        iter++;
    }


    
    for (int v = 0; v < n; v++) {
        cout << "Vertice " << v << " -> color " << color[v] << endl;
    }

    return 0;
}
