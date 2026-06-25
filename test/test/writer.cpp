#include "writer.h"
#include <fstream>
#include <iostream>

void write_vtu(const std::string& filename, 
               const std::vector<double>& x_coords, 
               const std::vector<int>& elements, 
               const std::vector<double>& u_displacements) 
{
    std::ofstream ofs(filename);
    if (!ofs) {
        std::cerr << "エラー: ファイルを開けませんでした。" << std::endl;
        return;
    }

    int num_nodes = x_coords.size();
    int num_elements = elements.size() / 2;

    ofs << "<?xml version=\"1.0\"?>\n";
    ofs << "<VTKFile type=\"UnstructuredGrid\" version=\"0.1\" byte_order=\"LittleEndian\">\n";
    ofs << "  <UnstructuredGrid>\n";
    ofs << "    <Piece NumberOfPoints=\"" << num_nodes << "\" NumberOfCells=\"" << num_elements << "\">\n";

    // 1. 節点座標 (3次元空間として出力)
    ofs << "      <Points>\n";
    ofs << "        <DataArray type=\"Float64\" NumberOfComponents=\"3\" format=\"ascii\">\n";
    for (int i = 0; i < num_nodes; ++i) {
        ofs << "          " << x_coords[i] << " 0.0 0.0\n";
    }
    ofs << "        </DataArray>\n";
    ofs << "      </Points>\n";

    // 2. 要素情報
    ofs << "      <Cells>\n";
    // 接続関係 (connectivity)
    ofs << "        <DataArray type=\"Int32\" Name=\"connectivity\" format=\"ascii\">\n";
    for (int i = 0; i < num_elements; ++i) {
        ofs << "          " << elements[2 * i] << " " << elements[2 * i + 1] << "\n";
    }
    ofs << "        </DataArray>\n";
    
    // オフセット (offsets)
    ofs << "        <DataArray type=\"Int32\" Name=\"offsets\" format=\"ascii\">\n";
    for (int i = 0; i < num_elements; ++i) {
        ofs << "          " << (i + 1) * 2 << "\n";
    }
    ofs << "        </DataArray>\n";
    
    // セルタイプ (types: 1D Lineは 3)
    ofs << "        <DataArray type=\"UInt8\" Name=\"types\" format=\"ascii\">\n";
    for (int i = 0; i < num_elements; ++i) {
        ofs << "          3\n";
    }
    ofs << "        </DataArray>\n";
    ofs << "      </Cells>\n";

    // 3. 物理量（変位ベクトル）
    ofs << "      <PointData Scalars=\"Displacement\">\n";
    ofs << "        <DataArray type=\"Float64\" Name=\"Displacement\" NumberOfComponents=\"3\" format=\"ascii\">\n";
    for (int i = 0; i < num_nodes; ++i) {
        ofs << "          " << u_displacements[i] << " 0.0 0.0\n";
    }
    ofs << "        </DataArray>\n";
    ofs << "      </PointData>\n";

    ofs << "    </Piece>\n";
    ofs << "  </UnstructuredGrid>\n";
    ofs << "</VTKFile>\n";

    std::cout << "🎉 保存完了: " << filename << std::endl;
}