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
#include "boundary.h"
#include "boundary.cpp"
#include "../object.h"

template<class O>
class Linalg: Boundary<O>
{	
	public:
		Linalg();
		~Linalg();
	protected:
		void solve_linear_system(O &obj);
		class K_rigid_sparse
		{	public:
			std::vector<int> index;
			std::vector<double> element; 
		};
		std::vector<K_rigid_sparse> k_rigid;
	private:
		template<class V> void update_K_rigid(V &U);

		// template<class V> double dotProduct(V &a, V &b);
		// template<class V> double dotProduct_r(V &a, O &obj);
		
}; 

 
 
