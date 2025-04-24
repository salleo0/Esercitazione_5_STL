#pragma once

#include <iostream>
#include "Eigen/Eigen"

using namespace std;
using namespace Eigen;

namespace PolygonalLibrary {

struct PolygonalMesh
{
	// Cell0D
	unsigned int NumCell0Ds = 0;
	vector<unsigned int> Cell0DsId = {};
	MatrixXd Cell0DsCoordinates = {};
	map<unsigned int, list<unsigned int>> MarkerCell0Ds = {};
	
	// Cell1D
	unsigned int NumCell1Ds = 0;
	vector<unsigned int> Cell1DsId = {};
	MatrixXi Cell1DsExtrema = {};
	map<unsigned int, list<unsigned int>> MarkerCell1Ds = {};
	
	// Cell2D
	unsigned int NumCell2Ds = 0;
	vector<unsigned int> Cell2DsId = {};
	vector<unsigned int> NumVerticesCell2Ds = {};
	vector<vector<unsigned int>> VerticesCell2Ds = {};
	vector<unsigned int> NumEdgesCell2Ds = {};
	vector<vector<unsigned int>> EdgesCell2Ds = {};
	map<unsigned int, list<unsigned int>> MarkerCell2Ds = {};
};

}
