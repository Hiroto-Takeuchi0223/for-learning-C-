#ifndef SOLVER_H
#define SOLVER_H

#include <vector>

void solve_fem(const std::vector<double>& x_coords, 
               const std::vector<int>& elements, 
               double E, double A, double F_load, 
               std::vector<double>& u_displacements);

#endif