#include "stress_value.h"

Stress_value::Stress_value(){};
Stress_value::~Stress_value(){};         

void Stress_value::define_stress_values(Object &obj)
{
    for (int i = 0; i < obj.cell.size(); ++i)
    {
        Stress_value::epsilon(i,obj);
        Stress_value::stress(i,obj);
    }
}

void Stress_value::epsilon(int i,Object &obj)
{

    array<int,4> ii;
    array<double,12> U;

    ii[0] = obj.cell[i].index_node[0];
    ii[1] = obj.cell[i].index_node[1];
    ii[2] = obj.cell[i].index_node[2];
    ii[3] = obj.cell[i].index_node[3];

    U[0] = obj.node[ii[0]].displacement[0];
    U[1] = obj.node[ii[0]].displacement[1];
    U[2] = obj.node[ii[0]].displacement[2];
     
    U[3] = obj.node[ii[1]].displacement[0];
    U[4] = obj.node[ii[1]].displacement[1];
    U[5] = obj.node[ii[1]].displacement[2];
    
    U[6] = obj.node[ii[2]].displacement[0];
    U[7] = obj.node[ii[2]].displacement[1];
    U[8] = obj.node[ii[2]].displacement[2];

    U[9] = obj.node[ii[3]].displacement[0];
    U[10] = obj.node[ii[3]].displacement[1];
    U[11] = obj.node[ii[3]].displacement[2];

    for (int j = 0; j < U.size(); ++j)
    {
        obj.cell[i].epsilon[0] += obj.cell[i].B_matrix[0][j]*U[j];
        obj.cell[i].epsilon[1] += obj.cell[i].B_matrix[1][j]*U[j];
        obj.cell[i].epsilon[2] += obj.cell[i].B_matrix[2][j]*U[j];
        obj.cell[i].epsilon[3] += obj.cell[i].B_matrix[3][j]*U[j];     
        obj.cell[i].epsilon[4] += obj.cell[i].B_matrix[4][j]*U[j];
        obj.cell[i].epsilon[5] += obj.cell[i].B_matrix[5][j]*U[j];          
    }
}

void Stress_value::stress(int i,Object &obj)
{
    array<double,6> U;
    U[0] = obj.cell[i].epsilon[0];
    U[1] = obj.cell[i].epsilon[1];
    U[2] = obj.cell[i].epsilon[2];
    U[3] = obj.cell[i].epsilon[3];
    U[4] = obj.cell[i].epsilon[4];
    U[5] = obj.cell[i].epsilon[5];

    for (int j = 0; j < obj.cell[i].stress.size(); ++j)
    {
        for (int k = 0; k < U.size(); ++k)
        {
           
           obj.cell[i].stress[j] += Shift::hooke_matrix[j][k]*U[k];
        }
    }

//obj.cell[i].full_stress = sqrt(obj.cell[i].stress[0]*obj.cell[i].stress[0]-obj.cell[i].stress[0]*obj.cell[i].stress[1]+obj.cell[i].stress[1]*obj.cell[i].stress[1]+3.*obj.cell[i].stress[2]*obj.cell[i].stress[2]);  
};