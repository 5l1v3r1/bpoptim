#include "bpoptim.h"

double VecProd(const alglib::real_1d_array& fa, const alglib::real_1d_array& sa) // vector to vector product
{
  double prod=0;

  size_t n = fa.length();
  for(size_t i=0; i<n; i++)
  {
    prod += fa[i]*sa[i];
  }

  return prod;
}

alglib::real_1d_array MxVecProd(const alglib::real_2d_array& mx, const alglib::real_1d_array& vec) // product of matrix (on left) to vector-column (on right)
{
  size_t n = mx.rows();
  alglib::real_1d_array res, row;
  res.setlength(n); row.setlength(n);

  for (size_t i = 0; i < n; i++) // for each matrix row
  {
    for (size_t j = 0; j < n; j++) // for each column
    {
      row(j) = mx(i,j);
    }
    res(i) = VecProd(row, vec);
  }

  return res;
}
