#include "out.h"

template <class O> 
Out<O>::Out(){};
template <class O> 
Out<O>::~Out(){};       

template <class O> 
void Out<O>::out_paraview(O &obj)
{
        std::ofstream output;
        output.open("results/results.vtu");
        if (output.is_open())
        {
            output << "<VTKFile type='UnstructuredGrid' version='0.1' byte_order='BigEndian'>"<<"\n";
            output << "<UnstructuredGrid>"<<"\n";
            output << "<Piece NumberOfPoints='"<<obj.node.size()<<"' NumberOfCells='"<<obj.cell.size()<<"'>"<<"\n";
            output << "<Points>"<<"\n";
            output << "<DataArray type='Float64' NumberOfComponents='3' Format='ascii'>"<<"\n";
 
            for (int i = 0;i<obj.node.size();++i)
            {
                output << obj.node[i].coordinate[0]<< " " <<obj.node[i].coordinate[1]<< " " <<obj.node[i].coordinate[2]<<"\n";
            }
            output << "</DataArray>"<<"\n";
            output << "</Points>"<<"\n";

            output << "<PointData Vectors='Velocity'>"<<"\n";
            output << "<DataArray type='Float64' Name='ux' Format='ascii'>"<<"\n";
 
            for (int i = 0;i<obj.node.size();++i)
            {
                output << obj.node[i].displacement[0]<<"\n";
            }
            output << "</DataArray>"<<"\n";

            output << "<DataArray type='Float64' Name='uy' Format='ascii'>"<<"\n";
 
            for (int i = 0;i<obj.node.size();++i)
            {
                output << obj.node[i].displacement[1]<<"\n";
            }
            output << "</DataArray>"<<"\n";

            output << "<DataArray type='Float64' Name='uz' Format='ascii'>"<<"\n";
 
            for (int i = 0;i<obj.node.size();++i)
            {
                output << obj.node[i].displacement[2]<<"\n";
            }
            output << "</DataArray>"<<"\n";

            output << "<DataArray type='Float64' Name='abs(u)' Format='ascii'>"<<"\n";
 
            for (int i = 0;i<obj.node.size();++i)
            {
                output << sqrt(pow(obj.node[i].displacement[0],2)+pow(obj.node[i].displacement[1],2)+pow(obj.node[i].displacement[2],2))<<"\n";
            }
            output << "</DataArray>"<<"\n";
            output << "</PointData>"<<"\n";
 


            output << "<CellData Scalars='scalars'>"<<"\n";

            output << "<DataArray type='Float64' Name='Parts' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
             output << obj.cell[i].part<<"\n";
            }    
            output << "</DataArray>"<<"\n";


            output << "<DataArray type='Float64' Name='e_x' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                output << obj.cell[i].epsilon[0]<<"\n";
            }   
            output << "</DataArray>"<<"\n";

            output << "<DataArray type='Float64' Name='e_y' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                output << obj.cell[i].epsilon[1]<<"\n";
            }   
            output << "</DataArray>"<<"\n";

            output << "<DataArray type='Float64' Name='e_z' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                output << obj.cell[i].epsilon[2]<<"\n";
            }   
            output << "</DataArray>"<<"\n";

            output << "<DataArray type='Float64' Name='gamma_xy' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                output << obj.cell[i].epsilon[3]<<"\n";
            }   
            output << "</DataArray>"<<"\n";

            output << "<DataArray type='Float64' Name='gamma_yz' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                output << obj.cell[i].epsilon[4]<<"\n";
            }   
            output << "</DataArray>"<<"\n";

            output << "<DataArray type='Float64' Name='gamma_zx' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                output << obj.cell[i].epsilon[5]<<"\n";
            }   
            output << "</DataArray>"<<"\n";

            output << "<DataArray type='Float64' Name='stress_x' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                output << obj.cell[i].stress[0]<<"\n";
            }   
            output << "</DataArray>"<<"\n";

            output << "<DataArray type='Float64' Name='stress_y' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                output << obj.cell[i].stress[1]<<"\n";
            }   
            output << "</DataArray>"<<"\n";

            output << "<DataArray type='Float64' Name='stress_z' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                output << obj.cell[i].stress[2]<<"\n";
            }   
            output << "</DataArray>"<<"\n";


            output << "<DataArray type='Float64' Name='tau_xy' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                output << obj.cell[i].stress[3]<<"\n";
            }   
            output << "</DataArray>"<<"\n";

            output << "<DataArray type='Float64' Name='tau_yz' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                output << obj.cell[i].stress[4]<<"\n";
            }   
            output << "</DataArray>"<<"\n";

            output << "<DataArray type='Float64' Name='tau_zx' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                output << obj.cell[i].stress[5]<<"\n";
            }   
            output << "</DataArray>"<<"\n";

            output << "<DataArray type='Float64' Name='stress' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                output << obj.cell[i].full_stress<<"\n";
            }   
            output << "</DataArray>"<<"\n";
 

            output << "<DataArray type='Float64' Name='volume' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                output << obj.cell[i].volume<<"\n";
            }   
            output << "</DataArray>"<<"\n";

             
            output << "</CellData>"<<"\n"; 

            output << "<Cells>"<<"\n";     
            output << "<DataArray type='Int32' Name='connectivity' format='ascii'>"<<"\n";     
            for (int i = 0;i<obj.cell.size();++i)
            {
                for (int j = 0;j < obj.cell[i].index_node.size();++j)
                {
                    output << obj.cell[i].index_node[j] << " ";
                    output<<"\n";
                } 
            }   
            output << "</DataArray>"<<"\n";
            output << "<DataArray type='Int32' Name='offsets' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                output << 4*(i+1) <<"\n";
            }   
            output << "</DataArray>"<<"\n";
            output << "<DataArray type='Int32' Name='types' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                output << 10 <<"\n";
            }     
            output << "</DataArray>"<<"\n";    
            output << "</Cells>"<<"\n";
            output << "</Piece>"<<"\n";
            output << "</UnstructuredGrid>"<<"\n"; 
            output << "</VTKFile>"<<"\n";                  
        }
        output.close();
        output.open("results/results_move.vtu");
        if (output.is_open())
        {
            output << "<VTKFile type='UnstructuredGrid' version='0.1' byte_order='BigEndian'>"<<"\n";
            output << "<UnstructuredGrid>"<<"\n";
            output << "<Piece NumberOfPoints='"<<obj.node.size()<<"' NumberOfCells='"<<obj.cell.size()<<"'>"<<"\n";
            output << "<Points>"<<"\n";
            output << "<DataArray type='Float64' NumberOfComponents='3' Format='ascii'>"<<"\n";
 
            for (int i = 0;i<obj.node.size();++i)
            {
                output << obj.node[i].coordinate[0]+obj.node[i].displacement[0]<< " " <<obj.node[i].coordinate[1]+obj.node[i].displacement[1]<< " " <<obj.node[i].coordinate[2]+obj.node[i].displacement[2]<<"\n";
            }
            output << "</DataArray>"<<"\n";
            output << "</Points>"<<"\n";

            output << "<CellData Scalars='scalars'>"<<"\n";

            output << "<DataArray type='Float64' Name='Parts' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
             output << obj.cell[i].part<<"\n";
            }    
            output << "</DataArray>"<<"\n";


            output << "<DataArray type='Float64' Name='e_x' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                output << obj.cell[i].epsilon[0]<<"\n";
            }   
            output << "</DataArray>"<<"\n";

            output << "<DataArray type='Float64' Name='e_y' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                output << obj.cell[i].epsilon[1]<<"\n";
            }   
            output << "</DataArray>"<<"\n";

            output << "<DataArray type='Float64' Name='e_z' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                output << obj.cell[i].epsilon[2]<<"\n";
            }   
            output << "</DataArray>"<<"\n";

            output << "<DataArray type='Float64' Name='gamma_xy' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                output << obj.cell[i].epsilon[3]<<"\n";
            }   
            output << "</DataArray>"<<"\n";

            output << "<DataArray type='Float64' Name='gamma_yz' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                output << obj.cell[i].epsilon[4]<<"\n";
            }   
            output << "</DataArray>"<<"\n";

            output << "<DataArray type='Float64' Name='gamma_zx' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                output << obj.cell[i].epsilon[5]<<"\n";
            }   
            output << "</DataArray>"<<"\n";

            output << "<DataArray type='Float64' Name='stress_x' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                output << obj.cell[i].stress[0]<<"\n";
            }   
            output << "</DataArray>"<<"\n";

            output << "<DataArray type='Float64' Name='stress_y' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                output << obj.cell[i].stress[1]<<"\n";
            }   
            output << "</DataArray>"<<"\n";

            output << "<DataArray type='Float64' Name='stress_z' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                output << obj.cell[i].stress[2]<<"\n";
            }   
            output << "</DataArray>"<<"\n";


            output << "<DataArray type='Float64' Name='tau_xy' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                output << obj.cell[i].stress[3]<<"\n";
            }   
            output << "</DataArray>"<<"\n";

            output << "<DataArray type='Float64' Name='tau_yz' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                output << obj.cell[i].stress[4]<<"\n";
            }   
            output << "</DataArray>"<<"\n";

            output << "<DataArray type='Float64' Name='tau_zx' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                output << obj.cell[i].stress[5]<<"\n";
            }   
            output << "</DataArray>"<<"\n";
            output << "<DataArray type='Float64' Name='stress' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                output << obj.cell[i].full_stress<<"\n";
            }   
            output << "</DataArray>"<<"\n";
 

            output << "<DataArray type='Float64' Name='volume' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                output << obj.cell[i].volume<<"\n";
            }   
            output << "</DataArray>"<<"\n";

             
            output << "</CellData>"<<"\n"; 

            output << "<Cells>"<<"\n";     
            output << "<DataArray type='Int32' Name='connectivity' format='ascii'>"<<"\n";     
            for (int i = 0;i<obj.cell.size();++i)
            {
                for (int j = 0;j < obj.cell[i].index_node.size();++j)
                {
                    output << obj.cell[i].index_node[j] << " ";
                    output <<"\n";
                }
            }   
            output << "</DataArray>"<<"\n";
            output << "<DataArray type='Int32' Name='offsets' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                output << 4*(i+1) <<"\n";
            }   
            output << "</DataArray>"<<"\n";
            output << "<DataArray type='Int32' Name='types' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                output << 10 <<"\n";
            }   
            output << "</DataArray>"<<"\n";    
            output << "</Cells>"<<"\n";
            output << "</Piece>"<<"\n";
            output << "</UnstructuredGrid>"<<"\n"; 
            output << "</VTKFile>"<<"\n";                  
        }
        output.close();        
};
