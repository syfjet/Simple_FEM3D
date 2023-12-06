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

#pragma once
#include <iostream>
#include <regex>
#include <fstream>
#include <cmath>
#include "../object.h"
#include "../numerical.h"
#include "construction_mesh.h" 

class Read_input_file: public Numerical, protected Construction_mesh
{	
public:
	Read_input_file();
	~Read_input_file();
	string mesh_file;		
	void read(string input_file,Object &obj, Numerical &numer);

protected:

private:
	void read_mesh(Object &obj);
	void boundary_init(Object &obj,std::vector <int>& number,std::vector <string>& type_boundary);
	void cell_init(Object &obj,vector <int>& parts,std::vector <double>& E, vector <double>& nu);
};
