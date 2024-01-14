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
#include <array>
#include "../object.h"

template<class O>
class Geometry
{	
	public:
		Geometry();
		~Geometry();
	protected:
		template<class I> 	void geometry_volume(I i, O &obj);
		template<class I> 	void geometry_b_matrix(I i, O &obj);
	private:
		std::array<double,8> B = {0,0,0,0};
		std::array<double,8> C = {0,0,0,0};
		std::array<double,8> D = {0,0,0,0};
}; 

 
 
