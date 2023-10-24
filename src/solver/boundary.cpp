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