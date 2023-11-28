//+
SetFactory("OpenCASCADE");
Box(1) = {0, 0, 0, 1, 1, 6};
//+
Cylinder(2) = {0.5, 0.5, -0.25, 0, 0, 0.25, 1.5, 2*Pi};

Cylinder(3) = {0., 0.5, 1.5, 1, 0, 0, 0.3, 2*Pi};
//+
Cylinder(4) = {0., 0.5, 3, 1, 0, 0, 0.3, 2*Pi};
//+
Cylinder(5) = {0., 0.5, 4.5, 1, 0, 0, 0.3, 2*Pi};

//+
BooleanDifference{ Volume{1}; Delete; }{ Volume{3}; Delete; }
//+
BooleanDifference{ Volume{1}; Delete; }{ Volume{4}; Delete; }
//+
BooleanDifference{ Volume{1}; Delete; }{ Volume{5}; Delete; }
//+
BooleanUnion{ Volume{1}; Delete; }{ Volume{2}; Delete; }
//+
//+
Box(3) = {7, 0, 6, -7, 1, 1};
//+

Box(2) = {6, 0, 0, 1, 1, 6};
//+
Cylinder(6) = {6.5, 0.5, -0.25, 0, 0, 0.25, 1.5, 2*Pi};

Cylinder(7) = {6., 0.5, 1.5, 1, 0, 0, 0.3, 2*Pi};
//+
Cylinder(8) = {6., 0.5, 3, 1, 0, 0, 0.3, 2*Pi};
//+
Cylinder(9) = {6., 0.5, 4.5, 1, 0, 0, 0.3, 2*Pi};
//+
BooleanDifference{ Volume{2}; Delete; }{ Volume{9}; Delete; }
//+
BooleanDifference{ Volume{2}; Delete; }{ Volume{7}; Delete; }
BooleanDifference{ Volume{2}; Delete; }{ Volume{8}; Delete; }
//+
BooleanUnion{ Volume{6}; Delete; }{ Volume{2}; Delete; }
//+
BooleanUnion{ Volume{3}; Delete; }{ Volume{4}; Delete; }
//+
BooleanUnion{ Volume{2}; Delete; }{ Volume{1}; Delete; }
//+
//+
Transfinite Curve {45, 47} = 2 Using Progression 1;
//+
Transfinite Curve {29, 46, 34, 48} = 30 Using Progression 1;
//+
Transfinite Curve {21, 13, 19, 10, 25, 30, 35, 2} = 10 Using Progression 1;
//+
Transfinite Curve {20, 12, 22, 14, 18, 9, 3, 1} = 40 Using Progression 1;
//+
Transfinite Curve {15, 17, 11, 8} = 30 Using Progression 1;
//+
Transfinite Curve {16,23,24,4} = 10 Using Progression 1;
//+

Transfinite Curve {26, 33, 40, 5, 32, 28, 27, 31, 36, 6, 38, 7} = 10 Using Progression 1;
//+
Transfinite Curve {42, 44, 43, 41, 39, 37} = 10 Using Progression 1;
