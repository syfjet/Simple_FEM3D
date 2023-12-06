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

#include "boundary.h"

template<class O>
Boundary<O>::Boundary(){};
template<class O>
Boundary<O>::~Boundary(){};         

template<class O>
template<class V>
void Boundary<O>::boundary_set(O &obj,V &global_force)
{

    for (int i = 0; i < obj.segment.size(); ++i)
    {
        if (obj.segment[i].type == 1)
        {
            global_force[3*obj.segment[i].index_node[0]] = 0; 
            global_force[3*obj.segment[i].index_node[0]+1] = 0; 
            global_force[3*obj.segment[i].index_node[0]+2] = 0; 

            global_force[3*obj.segment[i].index_node[1]] = 0; 
            global_force[3*obj.segment[i].index_node[1]+1] = 0;  
            global_force[3*obj.segment[i].index_node[1]+2] = 0;      
            
            global_force[3*obj.segment[i].index_node[2]] = 0; 
            global_force[3*obj.segment[i].index_node[2]+1] = 0;  
            global_force[3*obj.segment[i].index_node[2]+2] = 0;                                 
        }
        else if (obj.segment[i].type == 2)
        {
            global_force[3*obj.segment[i].index_node[0]] = 0; 
            global_force[3*obj.segment[i].index_node[1]] = 0;   
            global_force[3*obj.segment[i].index_node[2]] = 0;                                                    
        }
        else if (obj.segment[i].type == 3)
        {
            global_force[3*obj.segment[i].index_node[0]+1] = 0; 
            global_force[3*obj.segment[i].index_node[1]+1] = 0;   
            global_force[3*obj.segment[i].index_node[2]+1] = 0;                          
        }
        else if (obj.segment[i].type == 4)
        {
            global_force[3*obj.segment[i].index_node[0]+2] = 0; 
            global_force[3*obj.segment[i].index_node[1]+2] = 0;   
            global_force[3*obj.segment[i].index_node[2]+2] = 0;                          
        }        
    }
 
};