#include "Utils.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>

namespace PolygonalLibrary
{
bool ImportMesh(PolygonalMesh& mesh)
{

    if(!ImportCell0Ds(mesh))
        return false;
	/*
    if(!ImportCell1Ds(mesh))
        return false;

    if(!ImportCell2Ds(mesh))
        return false;
	*/
    return true;
	
}

// *********************************************************

bool ImportCell0Ds(PolygonalMesh& mesh)
{
	ifstream file("./Cell0Ds.csv");
	
	if(file.fail())
	{
		cerr << "unable to open file" << endl;
		return false;
	}
	
	// importo in una lista tutte le righe del file
	list<string> listLines;
	string line;
	while (getline(file, line))
		listLines.push_back(line);
	
	file.close();
	
	// remove header
	listLines.pop_front();
	
	mesh.NumCell0Ds = listLines.size();
	
	if(mesh.NumCell0Ds == 0)
	{
		cerr << "There is no cell 0D" << endl;
		return false;
	}
	
	// salvo le informazioni nelle righe in mesh
	mesh.Cell0DsId.reserve(mesh.NumCell0Ds);
	mesh.Cell0DsCoordinates = MatrixXd::Zero(2, mesh.NumCell0Ds);
	
	for (const string& str : listLines)
	{
		string line = str;
		replace(line.begin(), line.end(), ';', ' ');
		istringstream converter(line);
		
		unsigned int id;
		unsigned int marker;
		
		converter >> id >> marker >> mesh.Cell0DsCoordinates(0, id) >> mesh.Cell0DsCoordinates(1, id);
		
		mesh.Cell0DsId.push_back(id);
		
		// Memorizza i marker
		if(marker != 0)
		{
			const auto it = mesh.MarkerCell0Ds.find(marker);
			if(it == mesh.MarkerCell0Ds.end())
				mesh.MarkerCell0Ds.insert({marker, {id}});
			else
				it->second.push_back(id);
		}
	}
	
	return true;
}

// *********************************************************



}