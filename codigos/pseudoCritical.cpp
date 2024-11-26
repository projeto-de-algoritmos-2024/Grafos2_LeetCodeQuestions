// https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/description/
// Algoritmo de prim

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <climits>
using namespace std;

// Classe para representar um conjunto disjunto (Union-Find) com compressão de caminho e união por rank.
class ConjuntoDisjunto {
public:
    // Construtor: inicializa os pais e ranks de cada elemento.
    ConjuntoDisjunto(int tamanho) {
        rank = vector<int>(tamanho, 1);
        pai.resize(tamanho);
        for (int i = 0; i < tamanho; ++i) pai[i] = i;
    }

    // Encontra o representante (raiz) do conjunto ao qual o elemento pertence.
    int encontrarRaiz(int x) {
        if (x == pai[x]) return x;
        return pai[x] = encontrarRaiz(pai[x]); // Compressão de caminho.
    }

    // Une dois conjuntos distintos, usando o rank para otimizar.
    void unirConjuntos(int x, int y) {
        int raizX = encontrarRaiz(x), raizY = encontrarRaiz(y);
        if (raizX == raizY) return; // Já estão no mesmo conjunto.
        if (rank[raizX] > rank[raizY]) swap(raizX, raizY);
        pai[raizX] = raizY;
        if (rank[raizX] == rank[raizY]) rank[raizY]++;
    }

private:
    vector<int> pai, rank;
};

// Classe principal para encontrar arestas críticas e pseudo-críticas em uma MST (Árvore Geradora Mínima).
class Solution {
public:
    // Encontra e classifica as arestas críticas e pseudo-críticas de uma MST.
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        adicionarIndicesArestas(edges);

        ordenarArestasPorPeso(edges);

        int mstOriginal = calcularPrim(n, edges, -1);

        vector<int> criticas, pseudoCriticas;

        // Verifica cada aresta para determinar se é crítica ou pseudo-crítica.
        for (int i = 0; i < edges.size(); ++i) {
            if (mstOriginal < calcularPrim(n, edges, i)) {
                criticas.push_back(edges[i][3]);
            } else if (mstOriginal == calcularPrim(n, edges, -1, i)) {
                pseudoCriticas.push_back(edges[i][3]);
            }
        }

        return {criticas, pseudoCriticas};
    }

private:
    // Adiciona índices únicos a cada aresta para rastrear suas posições originais.
    void adicionarIndicesArestas(vector<vector<int>>& edges) {
        for (int i = 0; i < edges.size(); ++i) {
            edges[i].push_back(i);
        }
    }

    // Ordena as arestas pelo peso em ordem crescente.
    void ordenarArestasPorPeso(vector<vector<int>>& edges) {
        sort(edges.begin(), edges.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[2] < b[2];
        });
    }

    // Calcula o peso da MST usando o algoritmo de Prim, com a opção de ignorar ou forçar uma aresta.
    int calcularPrim(int n, const vector<vector<int>>& edges, int ignorarAresta, int forcarAresta = -1) {
        ConjuntoDisjunto conjunto(n);
        int pesoTotal = 0;

        // Força a inclusão de uma aresta específica na MST, se necessário.
        if (forcarAresta != -1) {
            pesoTotal += edges[forcarAresta][2];
            conjunto.unirConjuntos(edges[forcarAresta][0], edges[forcarAresta][1]);
        }

        // Itera sobre as arestas para construir a MST, ignorando a aresta especificada.
        for (int i = 0; i < edges.size(); ++i) {
            if (i == ignorarAresta) continue;
            const auto& edge = edges[i];
            if (conjunto.encontrarRaiz(edge[0]) == conjunto.encontrarRaiz(edge[1])) continue; // Evita ciclos.
            conjunto.unirConjuntos(edge[0], edge[1]);
            pesoTotal += edge[2];
        }

        // Verifica se o grafo é conexo. Retorna um valor alto (INT_MAX) se não for.
        for (int i = 0; i < n; ++i) {
            if (conjunto.encontrarRaiz(i) != conjunto.encontrarRaiz(0)) return INT_MAX;
        }

        return pesoTotal; 
    }
};

// Função para exibir o resultado de forma legível
void exibirResultado(const vector<vector<int>>& resultado) {
    cout << "Arestas Críticas: ";
    for (int aresta : resultado[0]) {
        cout << aresta << " ";
    }
    cout << endl;

    cout << "Arestas Pseudo-Críticas: ";
    for (int aresta : resultado[1]) {
        cout << aresta << " ";
    }
    cout << endl;
}

// Função para executar os casos de teste
void runTests() {
    Solution sol;

    // Teste 1
    vector<vector<int>> edges1 = {
        {0, 1, 1}, 
        {1, 2, 1}, 
        {2, 3, 2}, 
        {0, 3, 2}, 
        {0, 4, 3}, 
        {3, 4, 3}, 
        {1, 4, 6}
    };
    cout << "Test Case 1: ";
    vector<vector<int>> result1 = sol.findCriticalAndPseudoCriticalEdges(5, edges1);
    cout << "Critical: ";
    for (int x : result1[0]) cout << x << " ";
    cout << "| Pseudo-Critical: ";
    for (int x : result1[1]) cout << x << " ";
    cout << endl;

    // Teste 2
    vector<vector<int>> edges2 = {
        {0, 1, 1}, 
        {1, 2, 1}, 
        {2, 3, 1}, 
        {0, 3, 1}
    };
    cout << "Test Case 2: ";
    vector<vector<int>> result2 = sol.findCriticalAndPseudoCriticalEdges(4, edges2);
    cout << "Critical: ";
    for (int x : result2[0]) cout << x << " ";
    cout << "| Pseudo-Critical: ";
    for (int x : result2[1]) cout << x << " ";
    cout << endl;
}

int main() {
    runTests();
    return 0;
}