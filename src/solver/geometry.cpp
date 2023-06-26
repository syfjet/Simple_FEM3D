#include "geometry.h"

Geometry::Geometry(){};
Geometry::~Geometry(){};         

void Geometry::geometry_area(int i, Object &obj)
{
    int jm,jp,jpp,jn[3];
    array<double,4> index;
    double sig = 0;

    for (int j = 0; j < index.size(); ++j)
    {   
        
        if (j == 0)
        {
            jn[0] = obj.cell[i].index_node[1];
            jn[1] = obj.cell[i].index_node[2];
            jn[2] = obj.cell[i].index_node[3];
            sig = 1.0;           
        }
        if (j == 1)
        {
            jn[0] = obj.cell[i].index_node[0];
            jn[1] = obj.cell[i].index_node[2];
            jn[2] = obj.cell[i].index_node[3];
            sig = -1.0;        
        }
      
        if (j == 2)
        {
            jn[0] = obj.cell[i].index_node[0];
            jn[1] = obj.cell[i].index_node[1];
            jn[2] = obj.cell[i].index_node[3];
            sig = 1.0;         
        }
        if (j == 3)
        {
            jn[0] = obj.cell[i].index_node[0];
            jn[1] = obj.cell[i].index_node[1];
            jn[2] = obj.cell[i].index_node[2];
            sig = -1.0;  
        }
    
        Geometry::B[j] =  sig*((obj.node[jn[1]].coordinate[1]-obj.node[jn[0]].coordinate[1])*(obj.node[jn[2]].coordinate[2]-obj.node[jn[0]].coordinate[2]) - \
                               (obj.node[jn[1]].coordinate[2]-obj.node[jn[0]].coordinate[2])*(obj.node[jn[2]].coordinate[1]-obj.node[jn[0]].coordinate[1]))/6.;

        Geometry::C[j] =  sig*((obj.node[jn[1]].coordinate[2]-obj.node[jn[0]].coordinate[2])*(obj.node[jn[2]].coordinate[0]-obj.node[jn[0]].coordinate[0]) - \
                               (obj.node[jn[1]].coordinate[0]-obj.node[jn[0]].coordinate[0])*(obj.node[jn[2]].coordinate[2]-obj.node[jn[0]].coordinate[2]))/6.;

        Geometry::D[j] =  sig*((obj.node[jn[1]].coordinate[0]-obj.node[jn[0]].coordinate[0])*(obj.node[jn[2]].coordinate[1]-obj.node[jn[0]].coordinate[1]) - \
                               (obj.node[jn[1]].coordinate[1]-obj.node[jn[0]].coordinate[1])*(obj.node[jn[2]].coordinate[0]-obj.node[jn[0]].coordinate[0]))/6.;
    }

    array<array<double,3>,4> a;  
    array<array<double,3>,4> b;  
    array<array<double,3>,4> c; 

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

void Geometry::geometry_b_matrix(int i, Object &obj)
{

    obj.cell[i].B_matrix[0][0] = Geometry::B[0]/obj.cell[i].volume;
    obj.cell[i].B_matrix[0][3] = Geometry::B[1]/obj.cell[i].volume;
    obj.cell[i].B_matrix[0][6] = Geometry::B[2]/obj.cell[i].volume;
    obj.cell[i].B_matrix[0][9] = Geometry::B[3]/obj.cell[i].volume;
  
    obj.cell[i].B_matrix[1][1] = Geometry::C[0]/obj.cell[i].volume;
    obj.cell[i].B_matrix[1][4] = Geometry::C[1]/obj.cell[i].volume;
    obj.cell[i].B_matrix[1][7] = Geometry::C[2]/obj.cell[i].volume;
    obj.cell[i].B_matrix[1][10] = Geometry::C[3]/obj.cell[i].volume;

    obj.cell[i].B_matrix[2][2] = Geometry::D[0]/obj.cell[i].volume;
    obj.cell[i].B_matrix[2][5] = Geometry::D[1]/obj.cell[i].volume;
    obj.cell[i].B_matrix[2][8] = Geometry::D[2]/obj.cell[i].volume;
    obj.cell[i].B_matrix[2][11] = Geometry::D[3]/obj.cell[i].volume;




    obj.cell[i].B_matrix[3][0] = Geometry::C[0]/obj.cell[i].volume;
    obj.cell[i].B_matrix[3][3] = Geometry::C[1]/obj.cell[i].volume;
    obj.cell[i].B_matrix[3][6] = Geometry::C[2]/obj.cell[i].volume;
    obj.cell[i].B_matrix[3][9] = Geometry::C[3]/obj.cell[i].volume;
   

    obj.cell[i].B_matrix[3][1] = Geometry::B[0]/obj.cell[i].volume;
    obj.cell[i].B_matrix[3][4] = Geometry::B[1]/obj.cell[i].volume;
    obj.cell[i].B_matrix[3][7] = Geometry::B[2]/obj.cell[i].volume;
    obj.cell[i].B_matrix[3][10] = Geometry::B[3]/obj.cell[i].volume;



    obj.cell[i].B_matrix[4][1] = Geometry::D[0]/obj.cell[i].volume;
    obj.cell[i].B_matrix[4][4] = Geometry::D[1]/obj.cell[i].volume;
    obj.cell[i].B_matrix[4][7] = Geometry::D[2]/obj.cell[i].volume;
    obj.cell[i].B_matrix[4][10] = Geometry::D[3]/obj.cell[i].volume;


    obj.cell[i].B_matrix[4][2] = Geometry::C[0]/obj.cell[i].volume;
    obj.cell[i].B_matrix[4][5] = Geometry::C[1]/obj.cell[i].volume;
    obj.cell[i].B_matrix[4][8] = Geometry::C[2]/obj.cell[i].volume;
    obj.cell[i].B_matrix[4][11] = Geometry::C[3]/obj.cell[i].volume;
      

    obj.cell[i].B_matrix[5][0] = Geometry::D[0]/obj.cell[i].volume;
    obj.cell[i].B_matrix[5][3] = Geometry::D[1]/obj.cell[i].volume;
    obj.cell[i].B_matrix[5][6] = Geometry::D[2]/obj.cell[i].volume;
    obj.cell[i].B_matrix[5][9] = Geometry::D[3]/obj.cell[i].volume;
  

    obj.cell[i].B_matrix[5][2] = Geometry::B[0]/obj.cell[i].volume;
    obj.cell[i].B_matrix[5][5] = Geometry::B[1]/obj.cell[i].volume;
    obj.cell[i].B_matrix[5][8] = Geometry::B[2]/obj.cell[i].volume;
    obj.cell[i].B_matrix[5][11] = Geometry::B[3]/obj.cell[i].volume;

};
