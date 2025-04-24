#pragma once

#include <iostream>
#include "Eigen/Eigen"

using namespace std;
using namespace Eigen;


namespace TriangularLibrary {

struct TriangularMesh
{
	// number of Cell
	unsigned int NumCell0Ds = 0;
	unsigned int NumCell1Ds = 0;
	unsigned int NumCell2Ds = 0;
	
	vector<unsigned int> Cell0DsId = {};	// Cell0D id, size 1 x NumberCell0D
	vector<unsigned int> Cell1DsId = {};	// Cell1D id, size 1 x NumberCell1D
	vector<unsigned int> Cell2DsId = {};	// Cell2D id, size 1 x NumberCell2D
	
	// proprietà Cell0D
	Eigen::MatrixXd Cell0DsCoordinates = {};		// Cell0D coordinates, size 2 x NumberCell0D (x,y)
	map<unsigned int, list<unsigned int>> MarkerCell0Ds = {};	// Cell0D marker
	
	// proprietà Cell1D
	Eigen::MatrixXi Cell1DsExtrems = {};			// Cell1D vertices indices, size 2 x NumberCell1D (fromId,toId)			
	map<unsigned int, list<unsigned int>> MarkerCell1Ds = {}; 	// Cell1D properties
	
	// proprietà Cell2D
	vector<array<unsigned int, 3>> Cell2DsVertices = {};	// Cell2D Vertices indices, size 1 x NumberCell2DVertices[NumberCell2D]
	vector<array<unsigned int, 3>> Cell2DsEdges = {};		// Cell2D Cell1D indices, size 1 x NumberCell2DEdges[NumberCell2D]
};

}
