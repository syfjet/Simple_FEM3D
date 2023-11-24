#include "read_input_file.h"
Read_input_file::Read_input_file(){};
Read_input_file::~Read_input_file(){};		 

void Read_input_file::read(string input_file,Object &obj, Numerical &numer)
{
	string line,text;

	ifstream in (input_file,ios::in);
	if (in.is_open())
	{	
		while (getline(in,line))
		{
			if (regex_replace(line, regex(" "), "") == "#START_INPUT#")
			{
				std::cout << line << std::endl;
			}

			if (regex_replace(line, regex(" "), "") == "#END_INPUT#")
			{
				std::cout << line << std::endl;
			}

			if (regex_replace(line, regex(" "), "") == "MESH")
			{	
				in >> Read_input_file::mesh_file; 	
				Read_input_file::read_mesh(obj);
				Construction_mesh::node_connection(obj); 
			}

			if (regex_replace(line, regex(" "), "")  == "METRIC")
			{	
				in >> numer.metric;
						
				for (int i = 0; i < obj.node.size(); ++i)
				{
					obj.node[i].coordinate[0] = obj.node[i].coordinate[0]*numer.metric;
					obj.node[i].coordinate[1] = obj.node[i].coordinate[1]*numer.metric;	
					obj.node[i].coordinate[2] = obj.node[i].coordinate[2]*numer.metric; 	
				}	
			}

			if (regex_replace(line, regex(" "), "")  == "BOUNDARY")
			{	
				int number_boundary;
				std::vector <int> number;
				std::vector <string> type_boundary;
				
				in >> text;
				in >> number_boundary;

				for (int i = 0; i < number_boundary; ++i)
				{	
					in >> text;
					number.push_back(stoi(text));

					in >> text;
					type_boundary.push_back(text);
				}
	
				Read_input_file::boundary_init(obj,number,type_boundary);					
			}			
			if (regex_replace(line, regex(" "), "")  == "INITIAL")
			{	
				int num = 0;
				std::vector <int> parts;
				std::vector <double> E;
				std::vector <double> nu;

				in >> text;
				in >> num;
				in >> text >> text >> text;
				for (int i = 0; i < num; ++i)
				{
					in >> text;
					parts.push_back(stoi(regex_replace(text, regex(" "), "")));

					in >> text;
					E.push_back(stod(regex_replace(text, regex(" "), "")));

					in >> text;
					nu.push_back(stod(regex_replace(text, regex(" "), "")));
				}
				Read_input_file::cell_init(obj,parts,E,nu);
			}
			if (regex_replace(line, regex(" "), "")  == "SOURCE")
			{	
				in >> text;
				if (regex_replace(text, regex(" "), "") == "num")
				{	
					int num = 0;
					in >> num;
					for(int k = 0; k < num; ++k)
					{
						in >> text;
						
						if (regex_replace(text, regex(" "), "") == "point")
						{	

							double x0 = 0, y0 = 0, z0 = 0, fx = 0, fy = 0, fz = 0;
							double min_ = 1e20, d = 0;
							int index;
							in >> text >> text >> text >> text >> text >> text;
							in >> x0 >> y0 >> z0 >> fx >> fy >> fz;
							for (int i = 0; i < obj.node.size(); ++i)
							{
								d = sqrt(pow((obj.node[i].coordinate[0] - x0),2) + pow((obj.node[i].coordinate[1] - y0),2) + pow((obj.node[i].coordinate[2] - z0),2));
								if (d < min_)
								{
									min_ = d;
									index = i;
								}
							}

							obj.node[index].force[0] = fx;
							obj.node[index].force[1] = fy;	
							obj.node[index].force[2] = fz;	

						}
						if (regex_replace(text, regex(" "), "") == "boundary")
						{
 
							double fx = 0, fy = 0, fz = 0;
							int part = 0;

							in >> text >> text >> text >> text;
							in >> part >> fx >> fy >> fz;

							double a[3],b[3],area;
							for (int i = 0; i < obj.segment.size(); ++i)
							{
								if (obj.segment[i].part == part)
	  							{

								a[0] = obj.node[obj.segment[i].index_node[1]].coordinate[0]-obj.node[obj.segment[i].index_node[0]].coordinate[0];
								a[1] = obj.node[obj.segment[i].index_node[1]].coordinate[1]-obj.node[obj.segment[i].index_node[0]].coordinate[1];
								a[2] = obj.node[obj.segment[i].index_node[1]].coordinate[2]-obj.node[obj.segment[i].index_node[0]].coordinate[2];

								b[0] = obj.node[obj.segment[i].index_node[2]].coordinate[0]-obj.node[obj.segment[i].index_node[0]].coordinate[0];
								b[1] = obj.node[obj.segment[i].index_node[2]].coordinate[1]-obj.node[obj.segment[i].index_node[0]].coordinate[1];
								b[2] = obj.node[obj.segment[i].index_node[2]].coordinate[2]-obj.node[obj.segment[i].index_node[0]].coordinate[2];

								area = 0.5*abs(a[1]*b[2]-a[2]*b[1]-(a[0]*b[2]-a[2]*b[0])+(a[0]*b[1]-a[1]*b[0]));

								obj.node[obj.segment[i].index_node[0]].force[0] += fx*0.333*area;
								obj.node[obj.segment[i].index_node[0]].force[1] += fy*0.333*area;
								obj.node[obj.segment[i].index_node[0]].force[2] += fz*0.333*area;

								obj.node[obj.segment[i].index_node[1]].force[0] += fx*0.333*area;
								obj.node[obj.segment[i].index_node[1]].force[1] += fy*0.333*area;
								obj.node[obj.segment[i].index_node[1]].force[2] += fz*0.333*area;

								obj.node[obj.segment[i].index_node[2]].force[0] += fx*0.333*area;
								obj.node[obj.segment[i].index_node[2]].force[1] += fy*0.333*area;
								obj.node[obj.segment[i].index_node[2]].force[2] += fz*0.333*area;									
																								
	  							}
							}	
						}
					}
				}
			}
 		}
	}
}

void Read_input_file::boundary_init(Object &obj,vector <int>& number,vector <string>& type_boundary)
{	

 	for (int i = 0; i < obj.segment.size();++i)
 	{	
 		for (int j = 0; j < number.size();++j)
 		{
 			if (obj.segment[i].part == number[j])
 			{
				if (type_boundary[j] == "fix")
				{
					obj.segment[i].type = 1;
				}
				else if (type_boundary[j] == "fix_x")
				{
					obj.segment[i].type = 2;				
				}
				else if (type_boundary[j] == "fix_y")
				{
					obj.segment[i].type = 3;
				}
				else if (type_boundary[j] == "fix_z")
				{
					obj.segment[i].type = 4;
				}				
 			}
 		}
 	}
}

void Read_input_file::cell_init(Object &obj,vector <int>& parts,vector <double>& E, vector <double>& nu)
{	

 	for (int i = 0; i < obj.cell.size();++i)
 	{	
 		for (int j = 0; j < parts.size();++j)
 		{
 			if (obj.cell[i].part == parts[j] && parts[j] > 0)
 			{
				obj.cell[i].E = E[j];
				obj.cell[i].nu = nu[j];
 			}
 		}
 	}
}

void Read_input_file::read_mesh(Object &obj)
{	
	string line;
	double _node;
	int _segment,_cell;
	int n_node,n_segment,n_cell;

	ifstream in (Read_input_file::mesh_file,ios::in);
	if (in.is_open())
	{	
		while (getline(in,line))
		{	
			if (regex_replace(line, regex(" "), "") == "Vertices")
			{
				Object::Node node_;
				in >> n_node;
				obj.node.reserve(n_node);
				for (int i = 0; i < n_node; ++i)
				{
					obj.node.push_back(node_);
					for (int j = 0; j < obj.node[i].coordinate.size()+1; ++j)
					{	
						in >> _node;
						if (j < obj.node[i].coordinate.size()){obj.node[i].coordinate[j] = _node;}
						if (j == obj.node[i].coordinate.size()){obj.node[i].part = _node;}
					}
				}
				cout << "Vertices end" << endl;
			}

			if (regex_replace(line, regex(" "), "")  == "Triangles")
			{	

				Object::Segment segment_;
				in >> n_segment;	
				obj.segment.reserve(n_segment);
				for (int i = 0; i < n_segment; ++i)
 				{
 			 		obj.segment.push_back(segment_);
 					for (int j = 0; j < obj.segment[i].index_node.size()+1; ++j)
 					{	
 					 	in >> _segment;
 					 	if (j < obj.segment[i].index_node.size()){obj.segment[i].index_node[j] = _segment-1;}
 					 	if (j == obj.segment[i].index_node.size()){obj.segment[i].part = _segment;}
 					}
				}
				cout<<"Triangles end"<<endl;
			}

			if (regex_replace(line, regex(" "), "")  == "Tetrahedra")
			{	
				Object::Cell cell_;
				in >> n_cell;	
				obj.cell.reserve(n_cell);
				for (int i = 0; i < n_cell; ++i)
 				{	
 					obj.cell.push_back(cell_);
 					for (int j = 0; j < obj.cell[i].index_node.size()+1; ++j)
 					{	
 					 	in >> _cell;
 					 	if (j < obj.cell[i].index_node.size())
 					 		{
 					 			obj.cell[i].index_node[j] = _cell-1;
 					 		}
 					 	if (j == obj.cell[i].index_node.size()){obj.cell[i].part = _cell;}
 					}	
				}
				std::cout << "Tetrahedra end" << std::endl;
			}
 		}
	}
};