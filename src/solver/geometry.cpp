#include "geometry.h"

template<class O>
Geometry<O>::Geometry(){};
template<class O>
Geometry<O>::~Geometry(){};         

template<class O>
template<class I>
void Geometry<O>::geometry_volume(I i, O &obj)
{

    std::array<int,4> index;
    double sig = 0.0;

    for (int j = 0; j < obj.cell[i].index_node.size(); ++j)
    {   
        if (j == 0)
        {
            index[0] = obj.cell[i].index_node[1];
            index[1] = obj.cell[i].index_node[2];
            index[2] = obj.cell[i].index_node[3];
            index[4] = obj.cell[i].index_node[0];            
            sig = 1.0;           
        }
        if (j == 1)
        {
            index[0] = obj.cell[i].index_node[0];
            index[1] = obj.cell[i].index_node[2];
            index[2] = obj.cell[i].index_node[3];
            index[3] = obj.cell[i].index_node[1];            
            sig = -1.0;        
        }
      
        if (j == 2)
        {
            index[0] = obj.cell[i].index_node[0];
            index[1] = obj.cell[i].index_node[1];
            index[2] = obj.cell[i].index_node[3];
            index[3] = obj.cell[i].index_node[2];            
            sig = 1.0;         
        }
        if (j == 3)
        {
            index[0] = obj.cell[i].index_node[0];
            index[1] = obj.cell[i].index_node[1];
            index[2] = obj.cell[i].index_node[2];
            index[3] = obj.cell[i].index_node[3];            
            sig = -1.0;  
        }
    
        Geometry<O>::B[j] =  sig*((obj.node[index[1]].coordinate[1]-obj.node[index[0]].coordinate[1])*(obj.node[index[2]].coordinate[2]-obj.node[index[0]].coordinate[2]) - \
                               (obj.node[index[1]].coordinate[2]-obj.node[index[0]].coordinate[2])*(obj.node[index[2]].coordinate[1]-obj.node[index[0]].coordinate[1]))/6.0;

        Geometry<O>::C[j] =  sig*((obj.node[index[1]].coordinate[2]-obj.node[index[0]].coordinate[2])*(obj.node[index[2]].coordinate[0]-obj.node[index[0]].coordinate[0]) - \
                               (obj.node[index[1]].coordinate[0]-obj.node[index[0]].coordinate[0])*(obj.node[index[2]].coordinate[2]-obj.node[index[0]].coordinate[2]))/6.0;

        Geometry<O>::D[j] =  sig*((obj.node[index[1]].coordinate[0]-obj.node[index[0]].coordinate[0])*(obj.node[index[2]].coordinate[1]-obj.node[index[0]].coordinate[1]) - \
                               (obj.node[index[1]].coordinate[1]-obj.node[index[0]].coordinate[1])*(obj.node[index[2]].coordinate[0]-obj.node[index[0]].coordinate[0]))/6.0;
    }

    std::array<std::array<double,3>,4> a;  
    std::array<std::array<double,3>,4> b;  
    std::array<std::array<double,3>,4> c; 

    for (int j = 0; j < a[0].size();++j)
    {
        a[0][j] = obj.node[index[1]].coordinate[j]-obj.node[index[0]].coordinate[j]; 
        b[0][j] = obj.node[index[2]].coordinate[j]-obj.node[index[0]].coordinate[j];
        c[0][j] = obj.node[index[3]].coordinate[j]-obj.node[index[0]].coordinate[j];

        a[1][j] = obj.node[index[0]].coordinate[j]-obj.node[index[1]].coordinate[j];
        b[1][j] = obj.node[index[2]].coordinate[j]-obj.node[index[1]].coordinate[j];
        c[1][j] = obj.node[index[3]].coordinate[j]-obj.node[index[1]].coordinate[j];

        a[2][j] = obj.node[index[0]].coordinate[j]-obj.node[index[2]].coordinate[j];
        b[2][j] = obj.node[index[1]].coordinate[j]-obj.node[index[2]].coordinate[j];
        c[2][j] = obj.node[index[3]].coordinate[j]-obj.node[index[2]].coordinate[j];

        a[3][j] = obj.node[index[0]].coordinate[j]-obj.node[index[3]].coordinate[j];
        b[3][j] = obj.node[index[1]].coordinate[j]-obj.node[index[3]].coordinate[j];
        c[3][j] = obj.node[index[2]].coordinate[j]-obj.node[index[3]].coordinate[j];
    }

    obj.cell[i].volume = abs(b[0][0]*(a[0][1]*c[0][2]-a[0][2]*c[0][1])-b[0][1]*(a[0][0]*c[0][2]-a[0][2]*c[0][0])+b[0][2]*(a[0][0]*c[0][1]-a[0][1]*c[0][0]))/6.0;    
}

template<class O>
template<class I>
void Geometry<O>::geometry_b_matrix(I i, O &obj)
{

    obj.cell[i].B_matrix[0][0] = Geometry<O>::B[0]/obj.cell[i].volume;
    obj.cell[i].B_matrix[0][3] = Geometry<O>::B[1]/obj.cell[i].volume;
    obj.cell[i].B_matrix[0][6] = Geometry<O>::B[2]/obj.cell[i].volume;
    obj.cell[i].B_matrix[0][9] = Geometry<O>::B[3]/obj.cell[i].volume;
  
    obj.cell[i].B_matrix[1][1] = Geometry<O>::C[0]/obj.cell[i].volume;
    obj.cell[i].B_matrix[1][4] = Geometry<O>::C[1]/obj.cell[i].volume;
    obj.cell[i].B_matrix[1][7] = Geometry<O>::C[2]/obj.cell[i].volume;
    obj.cell[i].B_matrix[1][10] = Geometry<O>::C[3]/obj.cell[i].volume;

    obj.cell[i].B_matrix[2][2] = Geometry<O>::D[0]/obj.cell[i].volume;
    obj.cell[i].B_matrix[2][5] = Geometry<O>::D[1]/obj.cell[i].volume;
    obj.cell[i].B_matrix[2][8] = Geometry<O>::D[2]/obj.cell[i].volume;
    obj.cell[i].B_matrix[2][11] = Geometry<O>::D[3]/obj.cell[i].volume;



    obj.cell[i].B_matrix[3][0] = Geometry<O>::C[0]/obj.cell[i].volume;
    obj.cell[i].B_matrix[3][3] = Geometry<O>::C[1]/obj.cell[i].volume;
    obj.cell[i].B_matrix[3][6] = Geometry<O>::C[2]/obj.cell[i].volume;
    obj.cell[i].B_matrix[3][9] = Geometry<O>::C[3]/obj.cell[i].volume;
   

    obj.cell[i].B_matrix[3][1] = Geometry<O>::B[0]/obj.cell[i].volume;
    obj.cell[i].B_matrix[3][4] = Geometry<O>::B[1]/obj.cell[i].volume;
    obj.cell[i].B_matrix[3][7] = Geometry<O>::B[2]/obj.cell[i].volume;
    obj.cell[i].B_matrix[3][10] = Geometry<O>::B[3]/obj.cell[i].volume;



    obj.cell[i].B_matrix[4][1] = Geometry<O>::D[0]/obj.cell[i].volume;
    obj.cell[i].B_matrix[4][4] = Geometry<O>::D[1]/obj.cell[i].volume;
    obj.cell[i].B_matrix[4][7] = Geometry<O>::D[2]/obj.cell[i].volume;
    obj.cell[i].B_matrix[4][10] = Geometry<O>::D[3]/obj.cell[i].volume;


    obj.cell[i].B_matrix[4][2] = Geometry<O>::C[0]/obj.cell[i].volume;
    obj.cell[i].B_matrix[4][5] = Geometry<O>::C[1]/obj.cell[i].volume;
    obj.cell[i].B_matrix[4][8] = Geometry<O>::C[2]/obj.cell[i].volume;
    obj.cell[i].B_matrix[4][11] = Geometry<O>::C[3]/obj.cell[i].volume;
      

    obj.cell[i].B_matrix[5][0] = Geometry<O>::D[0]/obj.cell[i].volume;
    obj.cell[i].B_matrix[5][3] = Geometry<O>::D[1]/obj.cell[i].volume;
    obj.cell[i].B_matrix[5][6] = Geometry<O>::D[2]/obj.cell[i].volume;
    obj.cell[i].B_matrix[5][9] = Geometry<O>::D[3]/obj.cell[i].volume;
  

    obj.cell[i].B_matrix[5][2] = Geometry<O>::B[0]/obj.cell[i].volume;
    obj.cell[i].B_matrix[5][5] = Geometry<O>::B[1]/obj.cell[i].volume;
    obj.cell[i].B_matrix[5][8] = Geometry<O>::B[2]/obj.cell[i].volume;
    obj.cell[i].B_matrix[5][11] = Geometry<O>::B[3]/obj.cell[i].volume;

};
