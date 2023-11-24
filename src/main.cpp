#include <iostream>
#include "numerical.h"
#include "object.h"
#include "reader/read_input_file.h"

#include "solver/solver.h"
#include "solver/solver.cpp"

int main()
{
	std::string name_file;  

	Object obj;	                                      // create object
	Numerical numer;	                              // create numerical

	Read_input_file *read_file = new Read_input_file;
	cin >> name_file;	                              // read name input file
 	read_file -> read(name_file,obj,numer); 
 	delete read_file;
 	Solver<Object> *mech_solver = new Solver<Object>;
 	mech_solver->FEM_solver(obj);                     // start solver
 	delete mech_solver;
	return 0;		
} 
