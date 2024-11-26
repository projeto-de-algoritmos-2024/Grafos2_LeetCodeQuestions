//https://leetcode.com/problems/minimum-cost-to-reach-destination-in-time/
// Algoritmo de Djikstra

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <climits>

using namespace std;

class Solution {
private:
    // Função que implementa o algoritmo de Dijkstra modificado
    int dijkstra(int tempoMaximo, vector<vector<pair<int, int>>>& grafo, vector<int>& taxasPassagem) {
        int n = taxasPassagem.size();

        // Usar Dijkstra modificado para rastrear tempo e custo
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> filaPrioridade;
        filaPrioridade.emplace(taxasPassagem[0], 0, 0); // (custo, tempo, nó)

        vector<vector<int>> menorCusto(n, vector<int>(tempoMaximo + 1, INT_MAX));
        menorCusto[0][0] = taxasPassagem[0];

        while (!filaPrioridade.empty()) {
            auto [custo, tempo, u] = filaPrioridade.top();
            filaPrioridade.pop();

            // Expandir os vizinhos
            for (const auto& [v, tempoViagem] : grafo[u]) {
                int novoTempo = tempo + tempoViagem;
                int novoCusto = custo + taxasPassagem[v];

                // Se o tempo excede o máximo permitido, ignorar
                if (novoTempo > tempoMaximo) continue;

                // Se encontramos um caminho melhor para o nó v em novoTempo
                if (novoCusto < menorCusto[v][novoTempo]) {
                    menorCusto[v][novoTempo] = novoCusto;
                    filaPrioridade.emplace(novoCusto, novoTempo, v);
                }
            }
        }

        // Encontrar o menor custo para alcançar o nó destino (n - 1) dentro de tempoMaximo
        int resultado = INT_MAX;
        for (int t = 0; t <= tempoMaximo; ++t) {
            resultado = min(resultado, menorCusto[n - 1][t]);
        }

        return resultado == INT_MAX ? -1 : resultado;
    }

    // Função para construir o grafo a partir das arestas fornecidas
    vector<vector<pair<int, int>>> construirGrafo(int n, vector<vector<int>>& arestas) {
        vector<vector<pair<int, int>>> grafo(n);
        for (const auto& aresta : arestas) {
            int u = aresta[0], v = aresta[1], tempo = aresta[2];
            grafo[u].emplace_back(v, tempo);
            grafo[v].emplace_back(u, tempo);
        }
        return grafo;
    }

public:
    int minCost(int tempoMaximo, vector<vector<int>>& arestas, vector<int>& taxasPassagem) {
        int n = taxasPassagem.size();
        // Construir o grafo como uma lista de adjacências
        vector<vector<pair<int, int>>> grafo = construirGrafo(n, arestas);

        // Chamar a função Dijkstra para encontrar o menor custo
        return dijkstra(tempoMaximo, grafo, taxasPassagem);
    }
};

// Função para rodar os testes
void executarTestes() {
    Solution sol;

    // Teste 1
    int tempoMaximo1 = 30;
    vector<vector<int>> arestas1 = {{0,1,10},{1,2,10},{2,5,10},{0,3,1},{3,4,10},{4,5,15}};
    vector<int> taxasPassagem1 = {5,1,2,20,20,3};
    cout << "Teste 1: " << sol.minCost(tempoMaximo1, arestas1, taxasPassagem1) << endl; // Esperado: 11

    // Teste 2
    int tempoMaximo2 = 29;
    vector<vector<int>> arestas2 = {{0,1,10},{1,2,10},{2,5,10},{0,3,1},{3,4,10},{4,5,15}};
    vector<int> taxasPassagem2 = {5,1,2,20,20,3};
    cout << "Teste 2: " << sol.minCost(tempoMaximo2, arestas2, taxasPassagem2) << endl; // Esperado: 48

    // Teste 3
    int tempoMaximo3 = 25;
    vector<vector<int>> arestas3 = {{0,1,10},{1,2,10},{2,5,10},{0,3,1},{3,4,10},{4,5,15}};
    vector<int> taxasPassagem3 = {5,1,2,20,20,3};
    cout << "Teste 3: " << sol.minCost(tempoMaximo3, arestas3, taxasPassagem3) << endl; // Esperado: -1
}

// int main() {
//     executarTestes(); // Chama a função de testes
//     return 0;
// }
