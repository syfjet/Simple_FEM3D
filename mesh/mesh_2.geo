//+
SetFactory("OpenCASCADE");
Box(1) = {0, 0, 0, 1, 1, 6};
Box(2) = {7, 2, 6, -7, -3, 1};
Box(3) = {6, 0, 0, 1, 1, 6};
//+
Cylinder(4) = {0.5, 0.5, -0.25, 0, 0, 0.25, 1.5, 2*Pi};
Cylinder(5) = {6.5, 0.5, -0.25, 0, 0, 0.25, 1.5, 2*Pi};
//
Cylinder(6) = {0., 0.5, 1.5, 1, 0, 0, 0.3, 2*Pi};
// +
Cylinder(7) = {0., 0.5, 3, 1, 0, 0, 0.3, 2*Pi};

Cylinder(8) = {0., 0.5, 4.5, 1, 0, 0, 0.3, 2*Pi};

BooleanDifference{ Volume{1}; Delete; }{ Volume{6}; Delete; }
BooleanDifference{ Volume{1}; Delete; }{ Volume{7}; Delete; }
BooleanDifference{ Volume{1}; Delete; }{ Volume{8}; Delete; }

BooleanFragments{ Volume{1}; Delete; }{ Volume{4}; Delete; }
BooleanFragments{ Volume{3}; Delete; }{ Volume{5}; Delete; }

BooleanFragments{ Volume{2}; Delete; }{ Volume{1}; Delete; }
BooleanFragments{ Volume{2}; Delete; }{ Volume{3}; Delete; }
//+

//
// Cylinder(7) = {6., 0.5, 1.5, 1, 0, 0, 0.3, 2*Pi};
// +
// Cylinder(8) = {6., 0.5, 3, 1, 0, 0, 0.3, 2*Pi};
// +
// Cylinder(9) = {6., 0.5, 4.5, 1, 0, 0, 0.3, 2*Pi};
// +
//+
Box(100) = {14, 2, 6, -7, -3, 1};
Box(101) = {13, 0, 0, 1, 1, 6};
Cylinder(102) = {13.5, 0.5, -0.25, 0, 0, 0.25, 1.5, 2*Pi};

BooleanFragments{ Volume{101}; Delete; }{ Volume{102}; Delete; }
BooleanFragments{ Volume{100}; Delete; }{ Volume{101}; Delete; }

BooleanFragments{ Volume{2}; Delete; }{ Volume{100}; Delete; }
//+
Transfinite Curve {111, 114, 43, 122, 52, 121, 116, 51, 50, 63, 61, 59, 49, 48, 47, 65, 44, 62, 60, 58, 46, 45, 25, 54, 53, 34, 119, 56, 55, 57, 29, 33, 131, 125, 130, 112, 68, 113, 115, 26, 27, 28, 30, 36, 64, 66, 31, 32, 35, 96, 128, 105, 100, 104, 117, 124, 109, 123, 120, 118, 97, 67, 69, 99, 98, 101, 107, 102, 103, 106, 133, 126, 127, 132, 129, 108, 110} = 30 Using Progression 1;
