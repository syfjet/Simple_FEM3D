#include "linalg.h"

Linalg::Linalg(){};
Linalg::~Linalg(){};         

void Linalg::update_K_rigid(vector<double> &global_force)
{
    for (int i = 0; i < Linalg::k_rigid.size(); ++i)
    {   
        if (global_force[i] == 0)
        {
            for (int j = 0; j < Linalg::k_rigid[i].index.size(); ++j)
            {        
                Linalg::k_rigid[i].element[j] = 0;
                if ((Linalg::k_rigid[i].index[j] == i) && (Linalg::k_rigid[i].element[j] == 0))
                {
                    Linalg::k_rigid[i].element[j] = 1;
                } 
            }
            for (int k = i+1; k < Linalg::k_rigid.size(); ++k)
            {   
                for (int l = 0; l < Linalg::k_rigid[k].index.size(); ++l)
                {              
                    if (Linalg::k_rigid[k].index[l] == i)
                    {
                        Linalg::k_rigid[k].element[l] = 0;   
                    }  
                }
            }                  
        }
    }
}
void Linalg::solve_linear_system(Object &obj)
{

    vector<double> global_force(3*obj.node.size(),1);
    vector<double> x(3*obj.node.size(),0); 
    vector<double> r(3*obj.node.size(),0); 
    vector<double> As(3*obj.node.size(),0); 
    vector<double> s(3*obj.node.size(),0); 
 
    Boundary::boundary_set(obj,global_force);
    Linalg::update_K_rigid(global_force);
    double tol, temp,rr,rAs,sAs,alpha,beta;


    for (int i = 0; i < obj.node.size(); ++i)
    {  
       global_force[3*i] = obj.node[i].force[0]; 
       global_force[3*i+1] = obj.node[i].force[1]; 
       global_force[3*i+2] = obj.node[i].force[2]; 
    }

    tol = 1e-3;
    for (int i = 0; i< Linalg::k_rigid.size(); ++i)
    {   
        r[i] = -global_force[i];
        s[i] = r[i];
    }

    for (int k = 0; k < 10000; ++k)
    {   
        rr = 0;
        sAs = 0;
        for (int i = 0; i < Linalg::k_rigid.size(); ++i)
        {   
            temp = 0;
            for (int j = 0; j < Linalg::k_rigid[i].index.size(); ++j)
            {
                temp += Linalg::k_rigid[i].element[j]*s[Linalg::k_rigid[i].index[j]];     
            }
            As[i] = temp;
            rr += r[i]*r[i];
            sAs += s[i]*As[i];            
        }

        alpha = rr/sAs;

        for (int i = 0; i < Linalg::k_rigid.size(); ++i)
        {
            x[i] = x[i]-alpha*s[i];   
        }

        rr = 0;
        beta = 0;
        rAs = 0;
        sAs = 0;

        for (int i = 0; i< Linalg::k_rigid.size(); ++i)
        {
            temp = 0;
            for (int j = 0; j < Linalg::k_rigid[i].index.size(); ++j)
            {
                temp+=Linalg::k_rigid[i].element[j]*x[Linalg::k_rigid[i].index[j]];    
            }
            r[i] = temp-global_force[i];
            rr += r[i]*r[i];  
            rAs += r[i]*As[i];
            sAs += s[i]*As[i];
        }

        if (rr < tol)
        {
            break;
        }
        else
        {
            beta = -rAs/sAs;
            for (int i = 0; i< Linalg::k_rigid.size(); ++i)
            {  
                s[i] = r[i]+beta*s[i];  
            }     
        }
        cout<<"iter step = "<<k<<endl;

        if (k >= 9999)
        {
            cout<<"Not stable solution!"<<endl;
        }

    }
    for (int i = 0; i < obj.node.size(); ++i)
    {   
        obj.node[i].displacement[0] = x[3*i];
        obj.node[i].displacement[1] = x[3*i+1];
        obj.node[i].displacement[2] = x[3*i+2];        
    }         
};
