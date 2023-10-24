#include "solver.h"

template <class O> 
Solver<O>::Solver(){};
template <class O> 
Solver<O>::~Solver(){};         

template <class O> 
void Solver<O>::FEM_solver(O &obj)
{
    Shift<O>::define_matrix(obj);    

    Linalg<O>::solve_linear_system(obj);    
    Stress_value<O>::define_stress_values(obj);
    Out::out_paraview(obj);
};
