// Copyright (C) Simple_FEM3D Aleksey Chesnokov
// This file is part of Simple_FEM3D <https://github.com/syfjet/simple_fem3d>.
//
// Simple_FEM3D is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Simple_FEM3D is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Simple_FEM3D.  If not, see <http://www.gnu.org/licenses/>.

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
