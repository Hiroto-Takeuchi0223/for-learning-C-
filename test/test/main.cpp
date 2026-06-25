#include <iostream>
#include <vector>
#include "mesh.h"
#include "solver.h"
#include "writer.h"

int main() {
    std::cout << "=== 1次元FEM静弾性解析 (C++版) スタート ===" << std::endl;
    
    // --- パラメータ設定 ---
    double L = 1.0;          // 棒の長さ (m)
    int num_elem = 10;       // 要素分割数
    double E = 2e11;         // ヤング率 (Pa)
    double A = 0.01;         // 断面積 (m^2)
    double F_load = 1e5;     // 右端荷重 (N)
    
    // データ格納用のコンテナ（GPU転送を見据えた連続メモリ）
    std::vector<double> x_coords;
    std::vector<int> elements;
    std::vector<double> u_displacements;
    
    // 1. メッシュ生成
    generate_mesh(L, num_elem, x_coords, elements);
    
    // 2. FEM計算
    solve_fem(x_coords, elements, E, A, F_load, u_displacements);
    
    // 理論値の検算
    double theoretical = (F_load * L) / (E * A);
    std::cout << "最大変位 (FEM): " << u_displacements.back() << " m" << std::endl;
    std::cout << "最大変位 (理論): " << theoretical << " m" << std::endl;
    
    // 3. 結果の出力
    write_vtu("fem_result.vtu", x_coords, elements, u_displacements);
    
    return 0;
}