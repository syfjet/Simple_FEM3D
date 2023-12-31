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

#include "construction_mesh.h"

Construction_mesh::Construction_mesh(){}
Construction_mesh::~Construction_mesh(){}

void Construction_mesh::node_connection(Object &obj)
{	
	int c_node;
	for (int i = 0; i < obj.cell.size();++i)
	{	
		for (int j = 0; j < obj.cell[i].index_node.size(); ++j)
		{	
			c_node = obj.cell[i].index_node[j];
			obj.node[c_node].connection.push_back(i);
		}
	}
	std::cout<<"node_connection end"<<std::endl;
};


// void Construction_mesh::bound_construct(Object &obj)
// {	

// 	for (int i = 0; i < obj.segment.size();++i) //
// 	{	
// 		vector <int> index_cell;
// 		for (int j = 0; j < obj.segment[i].index_node.size();++j)
// 		{
// 			for (int k = 0; k < obj.node[obj.segment[i].index_node[j]].connection.size();++k)
// 			{
// 				index_cell.push_back(obj.node[obj.segment[i].index_node[j]].connection[k]);
// 			}
// 		}

// 		for (int j = 0; j < index_cell.size();++j)
// 		{	
// 			int pos = 0;
// 			for (int k = j; k < index_cell.size();++k)
// 			{
// 				if (index_cell[j] == index_cell[k])
// 				{
// 					++pos;
// 					if (pos == 3)
// 					{
// 						obj.segment[i].cell = index_cell[j];
// 					}
// 				}
// 			}
// 		}
// 		index_cell.clear();

// 	}
// };


// void Construction_mesh::cell_connection(Object &obj)
// {
//     int i_node;
// 	for (int i = 0; i < obj.cell.size();++i) //
// 	{	
// 		vector<int> cell_massive;
       
// 		for (int j = 0; j < obj.cell[i].index_node.size(); ++j)
// 		{
// 			i_node = obj.cell[i].index_node[j];
// 			for (int k = 0; k < obj.node[i_node].connection.size(); ++k)
// 			{
// 				cell_massive.push_back(obj.node[i_node].connection[k]);
// 			}
// 		}

// 		for (int j = 0; j < cell_massive.size();++j)
// 		{	
// 			int pos = 0;
// 			for (int k = j; k < cell_massive.size(); ++k)
// 			{	
// 				if ((cell_massive[j] == cell_massive[k]) && (cell_massive[k] != i) && (cell_massive[j] != i) )
// 				{
// 					++pos;
// 				}
// 			}	
// 			if (pos == 4)
// 			{
//                 Construction_mesh::orientation_cell_cell(cell_massive[j],obj.cell[i].connection,obj.cell[i].index_node,obj.cell[cell_massive[j]].index_node);
// 			}
// 		}
// 		cell_massive.clear();
// 	}
// 	cout<<"cell_connection end"<<endl;
// }


// void Construction_mesh::orientation_cell_cell(int index,array<int,4> &connection, array<int,4> &index_node, array<int,4> &index_node_contact_cell)
// {
//     auto posit
//     {
//         [](int ind, int &index, int (&pos)[4], array<int,4> &connection,int &flag)
//         {
//             ++pos[ind];
//             if (pos[ind] == 3)
//             {
//                 connection[ind] = index;
//                 flag = 1;
//             }           
//         }
//     };

//     int pos[] = {0,0,0,0};
//     int flag = 0;
//     for (int i = 0; i < connection.size();++i)
//     {
//             if (index_node[0] == index_node_contact_cell[i] || index_node[1] == index_node_contact_cell[i] || index_node[2] == index_node_contact_cell[i])
//         {
//             posit(0,index,pos,connection,flag);
//         }
//         if (index_node[0] == index_node_contact_cell[i] || index_node[1] == index_node_contact_cell[i] || index_node[3] == index_node_contact_cell[i])
//         {
//             posit(1,index,pos,connection,flag);
//         }
//         if (index_node[0] == index_node_contact_cell[i] || index_node[2] == index_node_contact_cell[i] || index_node[3] == index_node_contact_cell[i])
//         {
//             posit(2,index,pos,connection,flag);
//         }
//         if (index_node[1] == index_node_contact_cell[i] || index_node[2] == index_node_contact_cell[i] || index_node[3] == index_node_contact_cell[i])
//         {
//             posit(3,index,pos,connection,flag);
//         }
//         if (flag == 1){break;}
//     }
// }