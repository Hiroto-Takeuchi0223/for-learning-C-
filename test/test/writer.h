#ifndef WRITER_H
#define WRITER_H

#include <string>
#include <vector>

void write_vtu(const std::string& filename, 
               const std::vector<double>& x_coords, 
               const std::vector<int>& elements, 
               const std::vector<double>& u_displacements);

#endif