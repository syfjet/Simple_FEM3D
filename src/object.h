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
#include <vector>
#include <array>

class Object{
public:
	class Node
	{
	public:
		int part = 0;
		std::array<double,3> coordinate = {0,0,0};	
		std::vector<int> connection;	
		std::array<double,3> force = {0};
		std::array<double,3> displacement = {0};			
	protected:
	private:				
	}; 

	class Segment
	{
	public:
		int part = 0;
		std::array<int,3> index_node;	
		int type = 0;
		double area;
	protected:
	private:					
	};  

	class Cell
	{
	public:
		int part = 0;
		std::array<int,4> index_node;	
		double volume = 0;

		double E = 0;
		double nu = 0;
		
		std::array<std::array<double,12>,6> B_matrix = {{0}};  
		std::array<std::array<double,12>,12> local_K_matrix = {{0}};

		std::array<double,6> epsilon = {{0}};
		std::array<double,6> stress = {{0}};
		double full_stress = 0;
	};
	std::vector<Node> node;			
	std::vector<Segment> segment;	
	std::vector<Cell> cell;
};


 
