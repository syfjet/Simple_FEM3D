#include "shift.h"

template<class O>
Shift<O>::Shift(){};
template<class O>
Shift<O>::~Shift(){};         

template<class O>
void Shift<O>::define_matrix(O &obj)
{
    std::array<std::array<double,6>,12> B_matrix_T = {{0}};    

    typename Linalg<O>::K_rigid_sparse K_rigid_;
 
    for (int i = 0; i < 3*obj.node.size(); ++i)
    {
        Linalg<O>::k_rigid.push_back(K_rigid_);
    }
    
    for (int i = 0; i < obj.cell.size(); ++i)
    {
        Geometry<O>::geometry_volume(i, obj);
        Geometry<O>::geometry_b_matrix(i, obj);
        Shift<O>::hooke(i,obj);
        Shift<O>::transform_matrix(i,obj,B_matrix_T);
        Shift<O>::get_local_matrix(i,obj,B_matrix_T);
    }

    std::vector<int> temp_index(obj.node.size(),0);
    std::vector<std::vector<std::vector<double>>> temp_k(obj.node.size(),std::vector<std::vector<double>>(3,std::vector<double>(3,0.0)));  

    for (int i = 0; i < obj.node.size(); ++i)
    {   
        std::vector<int> temp_temp;
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

                for (int ii = 0; ii < 3; ++ii)
                {
                    for (int jj = 0; jj < 3; ++jj)
                    {                    
                        temp_k[i_n][ii][jj] += obj.cell[i_c].local_K_matrix[l+jj][3*k+ii];
                    }
                }      
                temp_temp.push_back(i_n);                             
            }
        }

        for (int j = 0; j < temp_temp.size(); ++j)
        {   
            if (temp_index[temp_temp[j]] == 1)
            {
                for (int ii = 0; ii < 3; ++ii)
                {
                    for (int jj = 0; jj < 3; ++jj)
                    {
                        Linalg<O>::k_rigid[3*i+ii].index.push_back(3*temp_temp[j]+jj);
                        Linalg<O>::k_rigid[3*i+ii].element.push_back(temp_k[temp_temp[j]][jj][ii]);
                    }
                }
            }

            //This step for individual nodes not includes in the mesh
            if ((temp_index[i] == 0) && (i == temp_temp[j]))
            {
                for (int ii = 0; ii < 3; ++ii)
                {
                    for (int jj = 0; jj < 3; ++jj)
                    {
                        Linalg<O>::k_rigid[3*i+ii].index.push_back(3*temp_temp[j]+jj);
                        Linalg<O>::k_rigid[3*i+ii].element.push_back(0.0);
                    }
                }
            }  
            temp_index[temp_temp[j]] = 0;
            temp_k[temp_temp[j]][0][0] = 0;      
            temp_k[temp_temp[j]][0][1] = 0;      
            temp_k[temp_temp[j]][0][2] = 0;      
            temp_k[temp_temp[j]][1][0] = 0;      
            temp_k[temp_temp[j]][1][1] = 0;      
            temp_k[temp_temp[j]][1][2] = 0;      
            temp_k[temp_temp[j]][2][0] = 0;      
            temp_k[temp_temp[j]][2][1] = 0;      
            temp_k[temp_temp[j]][2][2] = 0;      
        }
    } 
}

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
template<class I,class V>
void Shift<O>::get_local_matrix(I i, O &obj, V &B_matrix_T)
{
    std::array<std::array<double,6>,12> temp_local_K_matrix = {{0}};
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

template<class O>
template<class I,class V>
void Shift<O>::transform_matrix(I i, O &obj, V &B_matrix_T)
{
    for (int k = 0; k < B_matrix_T.size(); ++k)
    {
        for (int j = 0; j < B_matrix_T[0].size(); ++j)
        {         
            B_matrix_T[k][j] = obj.cell[i].B_matrix[j][k];
        }
    } 
};
