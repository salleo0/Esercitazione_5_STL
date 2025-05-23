#pragma once

#include <iostream>
#include "PolygonalMesh.hpp"

using namespace std;

namespace PolygonalLibrary 
{
// Import the polygonal mesh and test if the mesh is correct
// mesh: a PolygonalMesh struct
// return the result of the reading, true if is successful, false otherwise
bool ImportMesh(PolygonalMesh& mesh);

// Import the Cell0D properties from Cell0D.csv file
// mesh: a PolygonalMesh struct
// return the result of the reading, true if is successful, false otherwise
bool ImportCell0Ds(PolygonalMesh& mesh);

// Import the Cell1D properties from Cell1Ds.csv file
// mesh: a PolygonalMesh struct
// return the result of the reading, true if is successful, false otherwise
bool ImportCell1Ds(PolygonalMesh& mesh);

// Import the Cell2D properties from Cell2Ds.csv file
// mesh: a PolygonalMesh struct
// return the result of the reading, true if is successful, false otherwise
bool ImportCell2Ds(PolygonalMesh& mesh);

}

// Display a map where the second element is a std::list
// m : a map structure
void DisplayMap(const map<unsigned int, list<unsigned int>>& m);

// Calculate the area of a polygon
// verticesId: id of the vertices of the polygon
// verticesCoord: coordinates of the vertices of the polygon
// return true if the area is non zero, false otherwise
bool AreaOfPolygon(const unsigned int& numVertices,
						const vector<unsigned int>& verticesId,
						const MatrixXd& verticesCoord);
