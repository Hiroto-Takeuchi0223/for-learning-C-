#include "solver.h"
#include <cmath>
#include <iostream>

void solve_fem(const std::vector<double>& x_coords, 
               const std::vector<int>& elements, 
               double E, double A, double F_load, 
               std::vector<double>& u_displacements) 
{
    int num_nodes = x_coords.size();
    int num_elements = elements.size() / 2;
    
    // 全体剛性行列 (N x N) と 荷重ベクトル (N) の初期化
    // ※将来のGPU化では、ここを「疎行列(Sparse Matrix)」形式にするのが一般的です。
    std::vector<std::vector<double>> K_global(num_nodes, std::vector<double>(num_nodes, 0.0));
    std::vector<double> F_global(num_nodes, 0.0);
    
    // 右端に外力を付加
    F_global[num_nodes - 1] = F_load;
    
    // 1. 要素剛性マトリクスのアセンブリ
    for (int e = 0; e < num_elements; ++e) {
        int node1 = elements[2 * e];
        int node2 = elements[2 * e + 1];
        
        double x1 = x_coords[node1];
        double x2 = x_coords[node2];
        double le = x2 - x1; // 要素長
        
        // 要素剛性の計算
        double ke_val = (E * A) / le;
        
        // 全体マトリクスへ足し合わせ
        K_global[node1][node1] += ke_val;
        K_global[node1][node2] += -ke_val;
        K_global[node2][node1] += -ke_val;
        K_global[node2][node2] += ke_val;
    }
    
    // 2. 境界条件の適用 (左端 x=0 を完全固定)
    int fixed_node = 0;
    for (int j = 0; j < num_nodes; ++j) {
        K_global[fixed_node][j] = 0.0;
        K_global[j][fixed_node] = 0.0;
    }
    K_global[fixed_node][fixed_node] = 1.0;
    F_global[fixed_node] = 0.0;
    
    // 3. 連立一次方程式を解く (単純なガウスの消去法)
    u_displacements.assign(num_nodes, 0.0);
    std::vector<double> F_tmp = F_global;
    
    // 前進消去
    for (int i = 0; i < num_nodes; ++i) {
        for (int j = i + 1; j < num_nodes; ++j) {
            double ratio = K_global[j][i] / K_global[i][i];
            for (int k = i; k < num_nodes; ++k) {
                K_global[j][k] -= ratio * K_global[i][k];
            }
            F_tmp[j] -= ratio * F_tmp[i];
        }
    }
    // 後退代入
    for (int i = num_nodes - 1; i >= 0; --i) {
        double sum = 0.0;
        for (int j = i + 1; j < num_nodes; ++j) {
            sum += K_global[i][j] * u_displacements[j];
        }
        u_displacements[i] = (F_tmp[i] - sum) / K_global[i][i];
    }
}