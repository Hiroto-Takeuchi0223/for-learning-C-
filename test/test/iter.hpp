# ifndef INCLUDE_GUARD_ITER_HPP
# define INCLUDE_GUARD_ITER_HPP

void gen_random_matrix(double *A, const int N);
void gen_poisson_matrix(double *A, const int N);

void gen_random_vector(double *b, const int N);

double residue_normal_axb(const double *A, const double *x, const double *b, double *Ax, const int N);
void out_axb(const double *Ax, const double *b, const int N);
void out_bin(const double *a, const int n, const std::string fpath);

// void initialize_vector(double *x, const int N);

# endif // INCLUDE_GUARD_ITER_HPP
