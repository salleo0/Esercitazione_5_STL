#include <iostream>
#include "PolygonalMesh.hpp"
#include "Utils.hpp"
#include "UCDUtilities.hpp"

using namespace std;
using namespace Eigen; 
using namespace PolygonalLibrary;

int main()
{
	PolygonalMesh mesh;
	
	if(!ImportMesh(mesh))
	{
		cerr << "something went wrong while importing data" << endl;
	}
	
	
    return 0;
}
