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

#include "linalg.h"

template<class O>
Linalg<O>::Linalg(){};
template<class O>
Linalg<O>::~Linalg(){};         

template<class O>
template<class V>
void Linalg<O>::update_K_rigid(V &global_force)
{
    for (int i = 0; i < Linalg<O>::k_rigid.size(); ++i)
    {   
        if (global_force[i] == 0)
        {

            for (int j = 0; j < Linalg<O>::k_rigid[i].index.size(); ++j)
            {        
                Linalg<O>::k_rigid[i].element[j] = 0;
                
                for (int l = 0; l < Linalg<O>::k_rigid[Linalg<O>::k_rigid[i].index[j]].index.size(); ++l)
                {
                    if (Linalg<O>::k_rigid[Linalg<O>::k_rigid[i].index[j]].index[l] == i)
                    {
                        Linalg<O>::k_rigid[Linalg<O>::k_rigid[i].index[j]].element[l] = 0; 
                    }
                }

                if ((Linalg<O>::k_rigid[i].index[j] == i) && (Linalg<O>::k_rigid[i].element[j] == 0))
                {
                    Linalg<O>::k_rigid[i].element[j] = 1;
                } 
            }              
        }
    }
}


template<class O>
void Linalg<O>::solve_linear_system(O &obj)
{

    std::vector<double> global_force(3*obj.node.size(),1);
    std::vector<double> x(3*obj.node.size(),0);
    std::vector<double> x_old(3*obj.node.size(),0);      
    std::vector<double> r(3*obj.node.size(),0); 
    std::vector<double> As(3*obj.node.size(),0); 
    std::vector<double> s(3*obj.node.size(),0); 
 
    Boundary<O>::boundary_set(obj,global_force);
    Linalg<O>::update_K_rigid(global_force);  
    double tol, temp, rr, rAs, sAs, alpha, beta =0;

    for (int i = 0; i < obj.node.size(); ++i)
    {  
       global_force[3*i] = -obj.node[i].force[0]; 
       global_force[3*i+1] = -obj.node[i].force[1]; 
       global_force[3*i+2] = -obj.node[i].force[2]; 
    
    }

    s = r = global_force;

    tol = 1e-3;
    for (int k = 0; k < 100000; ++k)
    {   
        rr = 0;
        sAs = 0;
        for (int i = 0; i < Linalg<O>::k_rigid.size(); ++i)
        {   
            temp = 0;
            for (int j = 0; j < Linalg<O>::k_rigid[i].index.size(); ++j)
            {
                temp += Linalg<O>::k_rigid[i].element[j]*s[Linalg<O>::k_rigid[i].index[j]];     
            }
            As[i] = temp;
            rr += r[i]*r[i];
            sAs += s[i]*As[i];            
        }

        alpha = rr/sAs;

        double dx = 0;
        for (int i = 0; i < Linalg<O>::k_rigid.size(); ++i)
        {   
            x_old[i] = x[i];
            x[i] = x[i]-alpha*s[i];
            dx = fmax(fabs(x[i]-x_old[i])/pow(obj.cell[i].volume,0.333),dx);   
        }

        rr = 0;
        rAs = 0;
        for (int i = 0; i< Linalg<O>::k_rigid.size(); ++i)
        {
            temp = 0;
            for (int j = 0; j < Linalg<O>::k_rigid[i].index.size(); ++j)
            {
                temp+=Linalg<O>::k_rigid[i].element[j]*x[Linalg<O>::k_rigid[i].index[j]];    
            }
            r[i] = temp+global_force[i];
            rr += r[i]*r[i];  
            rAs += r[i]*As[i];
        }

        if ((rr < tol) || (dx < 1e-3))
        {
            break;
        }
        else
        {
            beta = -rAs/sAs;
            for (int i = 0; i < Linalg<O>::k_rigid.size(); ++i)
            {  
                s[i] = r[i]+beta*s[i];  
            }     
        }

        std::cout <<"iter step = "<< k <<" stab = "<< rr <<" "<< dx << std::endl;

        if (k >= 99999)
        {
            std::cout << "Not stable solution!" << std::endl;
        }
    }
    for (int i = 0; i < obj.node.size(); ++i)
    {   
        obj.node[i].displacement[0] = x[3*i];
        obj.node[i].displacement[1] = x[3*i+1];
        obj.node[i].displacement[2] = x[3*i+2];        
    }         
};
