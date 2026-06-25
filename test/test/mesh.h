#ifndef MESH_H
#define MESH_H

#include <vector>

// 1次元メッシュを生成する関数
// x_coords: 各節点のX座標
// elements: 各要素を構成する節点番号（1つの要素に2ノードなので、サイズは num_elements * 2）
void generate_mesh(double L, int num_elements, 
                   std::vector<double>& x_coords, 
                   std::vector<int>& elements);

#endif