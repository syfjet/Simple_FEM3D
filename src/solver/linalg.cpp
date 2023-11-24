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
                if ((Linalg<O>::k_rigid[i].index[j] == i) && (Linalg<O>::k_rigid[i].element[j] == 0))
                {
                    Linalg<O>::k_rigid[i].element[j] = 1;
                } 
            }
            for (int k = i+1; k < Linalg<O>::k_rigid.size(); ++k)
            {   
                for (int l = 0; l < Linalg<O>::k_rigid[k].index.size(); ++l)
                {              
                    if (Linalg<O>::k_rigid[k].index[l] == i)
                    {
                        Linalg<O>::k_rigid[k].element[l] = 0;   
                    }  
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

        for (int i = 0; i < Linalg<O>::k_rigid.size(); ++i)
        {
            x[i] = x[i]-alpha*s[i];   
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

        if (rr < tol)
        {
            break;
        }
        else
        {
            beta = -rAs/sAs;
            for (int i = 0; i< Linalg<O>::k_rigid.size(); ++i)
            {  
                s[i] = r[i]+beta*s[i];  
            }     
        }

        std::cout<<"iter step = "<< k << std::endl;

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
