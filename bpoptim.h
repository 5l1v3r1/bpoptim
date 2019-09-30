#include "./alglib/optimization.h"

double VecProd(const alglib::real_1d_array& fa, const alglib::real_1d_array& sa); // vector to vector product
alglib::real_1d_array MxVecProd(const alglib::real_2d_array& mx, const alglib::real_1d_array& vec); // product of matrix (on left) to vector-column (on right)
