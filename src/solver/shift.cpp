#include "shift.h"

template<class O>
Shift<O>::Shift(){};
template<class O>
Shift<O>::~Shift(){};         

template<class O>
template<class I>
void Shift<O>::hooke(I i,O &obj)
{   
    double cof;
    cof = obj.cell[i].E*(1.0-obj.cell[i].nu)/((1.0+obj.cell[i].nu)*(1.0-2.0*obj.cell[i].nu));

    Shift<O>::hooke_matrix[0][0] = cof;
    Shift<O>::hooke_matrix[0][1] = cof*obj.cell[i].nu/(1.0-obj.cell[i].nu);
    Shift<O>::hooke_matrix[0][2] = cof*obj.cell[i].nu/(1.0-obj.cell[i].nu);

    Shift<O>::hooke_matrix[1][0] = cof*obj.cell[i].nu/(1.0-obj.cell[i].nu);
    Shift<O>::hooke_matrix[1][1] = cof;
    Shift<O>::hooke_matrix[1][2] = cof*obj.cell[i].nu/(1.0-obj.cell[i].nu);

    Shift<O>::hooke_matrix[2][0] = cof*obj.cell[i].nu/(1.0-obj.cell[i].nu);
    Shift<O>::hooke_matrix[2][1] = cof*obj.cell[i].nu/(1.0-obj.cell[i].nu);
    Shift<O>::hooke_matrix[2][2] = cof;   

    Shift<O>::hooke_matrix[3][3] = 0.5*cof*(1.0-2.0*obj.cell[i].nu)/(1.0-obj.cell[i].nu);
    Shift<O>::hooke_matrix[4][4] = 0.5*cof*(1.0-2.0*obj.cell[i].nu)/(1.0-obj.cell[i].nu);
    Shift<O>::hooke_matrix[5][5] = 0.5*cof*(1.0-2.0*obj.cell[i].nu)/(1.0-obj.cell[i].nu);     

}

template<class O>
void Shift<O>::define_matrix(O &obj)
{
    array<array<double,6>,12> B_matrix_T = {{0}};    
    array<array<double,6>,12> temp_local_K_matrix = {{0}};

    vector<int> temp_index(obj.node.size(),0);
    vector<vector<vector<double>>> temp_k(obj.node.size(),vector<vector<double>>(3,vector<double>(3,0.0)));  
    // vector<double> temp_kx1(obj.node.size()); 
    // vector<double> temp_ky1(obj.node.size());
    // vector<double> temp_kz1(obj.node.size());    
    // vector<double> temp_kx2(obj.node.size());
    // vector<double> temp_ky2(obj.node.size());
    // vector<double> temp_kz2(obj.node.size());    
    // vector<double> temp_kx3(obj.node.size());
    // vector<double> temp_ky3(obj.node.size());
    // vector<double> temp_kz3(obj.node.size());  
    
    typename Linalg<O>::K_rigid_sparse K_rigid_;
 
    for (int i = 0; i < 3*obj.node.size(); ++i)
    {
        Linalg<O>::k_rigid.push_back(K_rigid_);
    }

    for (int i = 0; i < obj.cell.size(); ++i)
    {
        Geometry::geometry_area(i, obj);
        Geometry::geometry_b_matrix(i, obj);
        Shift<O>::hooke(i,obj);
 
        for (int k = 0; k < B_matrix_T.size(); ++k)
        {
            for (int j = 0; j < B_matrix_T[0].size(); ++j)
            {         
                B_matrix_T[k][j] = obj.cell[i].B_matrix[j][k];
            }
        }
        double temp;
        for (int k = 0; k < temp_local_K_matrix.size(); ++k)
        {
            for (int j = 0; j < temp_local_K_matrix[0].size(); ++j)
            {   
                temp = 0;
                for (int l = 0; l < B_matrix_T[0].size(); ++l)
                {
                    temp += B_matrix_T[k][l]*Shift<O>::hooke_matrix[l][j];
                }   
                temp_local_K_matrix[k][j] = temp;
            }
        }

        for (int k = 0; k < obj.cell[i].local_K_matrix.size(); ++k)
        {
            for (int j = 0; j < obj.cell[i].local_K_matrix[0].size(); ++j)
            {   
                temp = 0;
                for (int l = 0; l < temp_local_K_matrix[0].size(); ++l)
                {
                    temp += temp_local_K_matrix[k][l]*obj.cell[i].B_matrix[l][j]; 
                }
                obj.cell[i].local_K_matrix[k][j] = temp*obj.cell[i].volume;
            }
        } 
      
    }

    for (int i = 0; i < obj.node.size(); ++i)
    {
        for (int j = 0; j < obj.node.size(); ++j)
        {
            temp_index[j] = 0;
            temp_k[j][0][0] = 0;
            temp_k[j][1][0] = 0;
            temp_k[j][2][0] = 0;            
            temp_k[j][0][1] = 0;
            temp_k[j][1][1] = 0;        
            temp_k[j][2][1] = 0; 
            temp_k[j][0][2] = 0;
            temp_k[j][1][2] = 0;        
            temp_k[j][2][2] = 0;                    
        }
     
        int i_c,i_n,l;
        for (int j = 0; j < obj.node[i].connection.size(); ++j)
        {   
            i_c = obj.node[i].connection[j];

            for (int k = 0; k < obj.cell[i_c].index_node.size(); ++k)
            {   
                i_n = obj.cell[i_c].index_node[k];
                
                if (i == i_n)
                {
                    l = 3*k;
                }
            }    
            for (int k = 0; k < obj.cell[i_c].index_node.size(); ++k)
            {   
                i_n = obj.cell[i_c].index_node[k];
                temp_index[i_n] = 1; 

                temp_k[i_n][0][0] +=  obj.cell[i_c].local_K_matrix[l][3*k];   
                temp_k[i_n][1][0] +=  obj.cell[i_c].local_K_matrix[l][3*k+1];
                temp_k[i_n][2][0] +=  obj.cell[i_c].local_K_matrix[l][3*k+2];                
                temp_k[i_n][0][1] +=  obj.cell[i_c].local_K_matrix[l+1][3*k];   
                temp_k[i_n][1][1] +=  obj.cell[i_c].local_K_matrix[l+1][3*k+1];
                temp_k[i_n][2][1] +=  obj.cell[i_c].local_K_matrix[l+1][3*k+2]; 
                temp_k[i_n][0][2] +=  obj.cell[i_c].local_K_matrix[l+2][3*k];   
                temp_k[i_n][1][2] +=  obj.cell[i_c].local_K_matrix[l+2][3*k+1];
                temp_k[i_n][2][2] +=  obj.cell[i_c].local_K_matrix[l+2][3*k+2];                                                  
            }
        }

        for (int j = 0; j < obj.node.size(); ++j)
        {   
            if (temp_index[j] > 0)
            {
                Linalg<O>::k_rigid[3*i].index.push_back(3*j);
                Linalg<O>::k_rigid[3*i].index.push_back(3*j+1);
                Linalg<O>::k_rigid[3*i].index.push_back(3*j+2);
                Linalg<O>::k_rigid[3*i].element.push_back(temp_k[j][0][0]);
                Linalg<O>::k_rigid[3*i].element.push_back(temp_k[j][1][0]);
                Linalg<O>::k_rigid[3*i].element.push_back(temp_k[j][2][0]);

                Linalg<O>::k_rigid[3*i+1].index.push_back(3*j);
                Linalg<O>::k_rigid[3*i+1].index.push_back(3*j+1);
                Linalg<O>::k_rigid[3*i+1].index.push_back(3*j+2);
                Linalg<O>::k_rigid[3*i+1].element.push_back(temp_k[j][0][1]);
                Linalg<O>::k_rigid[3*i+1].element.push_back(temp_k[j][1][1]);
                Linalg<O>::k_rigid[3*i+1].element.push_back(temp_k[j][2][1]);

                Linalg<O>::k_rigid[3*i+2].index.push_back(3*j);
                Linalg<O>::k_rigid[3*i+2].index.push_back(3*j+1);
                Linalg<O>::k_rigid[3*i+2].index.push_back(3*j+2);
                Linalg<O>::k_rigid[3*i+2].element.push_back(temp_k[j][0][2]);
                Linalg<O>::k_rigid[3*i+2].element.push_back(temp_k[j][1][2]);
                Linalg<O>::k_rigid[3*i+2].element.push_back(temp_k[j][2][2]);

            }

            //This step for individual nodes not includes in the mesh
            if ((temp_index[i] == 0) && (i == j))
            {
                Linalg<O>::k_rigid[3*i].index.push_back(3*j);
                Linalg<O>::k_rigid[3*i].index.push_back(3*j+1);
                Linalg<O>::k_rigid[3*i].index.push_back(3*j+2);

                Linalg<O>::k_rigid[3*i].element.push_back(0.0);
                Linalg<O>::k_rigid[3*i].element.push_back(0.0);
                Linalg<O>::k_rigid[3*i].element.push_back(0.0);

                Linalg<O>::k_rigid[3*i+1].index.push_back(3*j);
                Linalg<O>::k_rigid[3*i+1].index.push_back(3*j+1);
                Linalg<O>::k_rigid[3*i+1].index.push_back(3*j+2);
                Linalg<O>::k_rigid[3*i+1].element.push_back(0.0); 
                Linalg<O>::k_rigid[3*i+1].element.push_back(0.0);    
                Linalg<O>::k_rigid[3*i+1].element.push_back(0.0); 

                Linalg<O>::k_rigid[3*i+2].index.push_back(3*j);
                Linalg<O>::k_rigid[3*i+2].index.push_back(3*j+1);
                Linalg<O>::k_rigid[3*i+2].index.push_back(3*j+2);
                Linalg<O>::k_rigid[3*i+2].element.push_back(0.0); 
                Linalg<O>::k_rigid[3*i+2].element.push_back(0.0);  
                Linalg<O>::k_rigid[3*i+2].element.push_back(0.0);  
            }            
        }
    }  
};
