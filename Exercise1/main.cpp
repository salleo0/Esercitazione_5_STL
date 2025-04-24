#include <iostream>
#include "TriangularMesh.hpp"
#include "Utils.hpp"
#include "UCDUtilities.hpp"

using namespace std;
using namespace Eigen;
using namespace TriangularLibrary;

int main()
{
    TriangularMesh mesh;

    if(!ImportMesh(mesh))
    {
        cerr << "file not found" << endl;
        return 1;
    }
	
	/*
	Gedim::UCDUtilities
	utilities.ExportPoints("./Cell0Ds.inp", 
							mesh.Cell0D

    return 0;
	*/
}

