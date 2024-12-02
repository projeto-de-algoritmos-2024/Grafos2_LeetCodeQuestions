// https://leetcode.com/problems/min-cost-to-connect-all-points/

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <climits>
using namespace std;

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        vector<bool> inMST(n, false); // Rastrea se um ponto já está na MST
        vector<int> minCost(n, INT_MAX); // Custo mínimo para conectar cada ponto
        minCost[0] = 0; // Comece pelo ponto 0
        int totalCost = 0;

        // Min-heap para armazenar os custos: (custo, índice do ponto)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.push({0, 0}); // (custo, ponto)

        while (!pq.empty()) {
            auto [cost, u] = pq.top();
            pq.pop();

            // Se já está na MST, pule
            if (inMST[u]) continue;

            // Adicione o ponto `u` à MST
            inMST[u] = true;
            totalCost += cost;

            // Atualize os custos para os pontos adjacentes
            for (int v = 0; v < n; ++v) {
                if (!inMST[v]) {
                    int dist = manhattanDist(points[u], points[v]);
                    if (dist < minCost[v]) {
                        minCost[v] = dist;
                        pq.push({dist, v});
                    }
                }
            }
        }

        return totalCost;
    }

private:
    int manhattanDist(const vector<int>& p1, const vector<int>& p2) {
        return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1]);
    }
};

void executarTestes() {
    Solution sol;

    // Teste 1
    vector<vector<int>> points1 = {{0,0},{2,2},{3,10},{5,2},{7,0}};
    cout << "Teste 1: " << sol.minCostConnectPoints(points1) << " (Esperado: 20)" << endl;

    // Teste 2
    vector<vector<int>> points2 = {{3,12},{-2,5},{-4,1}};
    cout << "Teste 2: " << sol.minCostConnectPoints(points2) << " (Esperado: 18)" << endl;

}

// int main() {
//     executarTestes();
//     return 0;
// }