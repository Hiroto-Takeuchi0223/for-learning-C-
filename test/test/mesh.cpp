#include "mesh.h"

void generate_mesh(double L, int num_elements, 
                   std::vector<double>& x_coords, 
                   std::vector<int>& elements) 
{
    int num_nodes = num_elements + 1;
    
    // 節点座標のメモリ確保と計算
    x_coords.resize(num_nodes);
    double dx = L / num_elements;
    for (int i = 0; i < num_nodes; ++i) {
        x_coords[i] = i * dx;
    }
    
    // 要素構成のメモリ確保と計算（1次元配列としてフラットに格納）
    elements.resize(num_elements * 2);
    for (int i = 0; i < num_elements; ++i) {
        elements[2 * i]     = i;     // 要素iの左側節点
        elements[2 * i + 1] = i + 1; // 要素iの右側節点
    }
}