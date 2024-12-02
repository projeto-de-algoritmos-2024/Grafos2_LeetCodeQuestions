// https://leetcode.com/problems/minimum-number-of-days-to-disconnect-island/description/
// Strongly Connected Components

#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    void dfs(int x, int y, vector<vector<int>>& grid, vector<vector<bool>>& visited) {
        int m = grid.size(), n = grid[0].size();
        if (x < 0 || y < 0 || x >= m || y >= n || visited[x][y] || grid[x][y] == 0)
            return;

        visited[x][y] = true;


        // Visita os vizinhos possíveis daquele nó, que no caso são as 4 direções.
        dfs(x + 1, y, grid, visited);
        dfs(x - 1, y, grid, visited);
        dfs(x, y + 1, grid, visited);
        dfs(x, y - 1, grid, visited);
    }

    // Conta o número de ilhas no grid
    int countIslands(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        int islands = 0;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1 && !visited[i][j]) {
                    islands++;
                    // Caso o grid esteja fortemente conectado, a DFS irá marcar todos os caminhos válidos como visitado, ou seja,
                    // toda vez que o for encontra um ponto não visitado de valor 1, quer dizer que é o inicio de uma ilha nova
                    dfs(i, j, grid, visited);
                }
            }
        }

        return islands;
    }

    int minDays(vector<vector<int>>& grid) {
        // Verificar se o grid já está desconectado
        if (countIslands(grid) != 1) return 0;

        int m = grid.size(), n = grid[0].size();

        // Faz o teste removendo apenas um ponto de valor 1 do grafo, verificando se o grafo ficaria desconectado.
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    grid[i][j] = 0;
                    if (countIslands(grid) != 1) return 1;
                    grid[i][j] = 1;
                }
            }
        }

        // Faz o teste removendo dois pontos de valor 1 do grafo, verificando se o grafo ficaria desconectado.
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    grid[i][j] = 0;
                    for (int x = 0; x < m; ++x) {
                        for (int y = 0; y < n; ++y) {
                            if (grid[x][y] == 1) {
                                grid[x][y] = 0; 
                                if (countIslands(grid) != 1) return 2;
                                grid[x][y] = 1; 
                            }
                        }
                    }
                    grid[i][j] = 1;
                }
            }
        }

        return 2;
    }
};

void executarTestes() {
    Solution sol;

    // Teste 1
    vector<vector<int>> grid1 = {{0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}};
    cout << "Teste 1: " << sol.minDays(grid1) << " (Esperado: 2)" << endl;

    // Teste 2
    vector<vector<int>> grid2 = {{1, 1}};
    cout << "Teste 2: " << sol.minDays(grid2) << " (Esperado: 2)" << endl;

    
}

// Função principal
// int main() {
//     executarTestes();
//     return 0;
// }