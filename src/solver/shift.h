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
#include "../object.h"
#include "geometry.h"
#include "geometry.cpp"
#include "linalg.h"

template<class O>
class Shift: Geometry<O>, virtual Linalg<O>
{	
	public:
		Shift();
		~Shift();
		void define_matrix(O &obj); 
		std::array<std::array<double,6>,6> hooke_matrix = {{0}};
	protected:
		template<class I> void hooke(I i,O &obj);
	private:
		template<class I,class V> void transform_matrix(I i, O &obj, V &B_matrix_T);
		template<class I,class V> void get_local_matrix(I i, O &obj, V &B_matrix_T);
}; 

 
 
