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
	cout << endl << "***************************" << endl;
	cout << "Display markers of Cell0D" << endl;
	DisplayMap(mesh.MarkerCell0Ds);
	
    if(!ImportCell1Ds(mesh))
        return false;
	cout << endl << "***************************" << endl;
	cout << "Display markers of Cell1D" << endl;
	DisplayMap(mesh.MarkerCell1Ds);
	
    if(!ImportCell2Ds(mesh))
        return false;
	cout << endl << "***************************" << endl;
	cout << "Display markers of Cell2D" << endl;
	DisplayMap(mesh.MarkerCell2Ds);
	
    return true;
	
}

// *********************************************************

bool ImportCell0Ds(PolygonalMesh& mesh)
{
	ifstream file("./Cell0Ds.csv");
	
	if(file.fail())
	{
		cerr << "unable to open Cell0Ds.csv file" << endl;
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
	mesh.Cell0DsCoordinates = MatrixXd::Zero(3, mesh.NumCell0Ds);
	
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

bool ImportCell1Ds(PolygonalMesh& mesh)
{
	ifstream file("./Cell1Ds.csv");
	
	if(file.fail())
	{
		cerr << "unable to open Cell1Ds.csv file" << endl;
		return false;
	}
	
	// importo in una lista tutte le righe del file
	list<string> listLines;
	string line;
	while(getline(file,line))
		listLines.push_back(line);
	
	file.close();
	
	// remove header
	listLines.pop_front();
	
	mesh.NumCell1Ds = listLines.size();
	
	if (mesh.NumCell1Ds == 0)
	{
		cerr << "There is no cell 1D" << endl;
		return false;
	}
	
	// salvo le informazioni nelle righe in mesh	
	mesh.Cell1DsId.reserve(mesh.NumCell1Ds);
	mesh.Cell1DsExtrema = MatrixXi(2, mesh.NumCell1Ds);
	
	for (const string& str : listLines)
	{	
		string line = str;
		replace(line.begin(), line.end(), ';', ' ');
		istringstream converter(line);
		
		unsigned int id;
		unsigned int marker;
		unsigned int Xcoord;
		unsigned int Ycoord;
		
		converter >> id >> marker >> Xcoord >> Ycoord;
		
		// test per verificare che nessun bordo abbia lunghezza zero
		if(Xcoord == Ycoord)
		{
			cerr << "at least one edge has zero length";
			return false;
		}
		
		mesh.Cell1DsExtrema(0, id) = Xcoord;
		mesh.Cell1DsExtrema(1, id) = Ycoord;
		
		mesh.Cell1DsId.push_back(id);
		
		// Memorizza i marker
		if(marker != 0)
		{
			const auto it = mesh.MarkerCell1Ds.find(marker);
			if(it == mesh.MarkerCell1Ds.end())
				mesh.MarkerCell1Ds.insert({marker, {id}});
			else
				it->second.push_back(id);
		}
	}
	
	return true;
}

// *********************************************************

bool ImportCell2Ds(PolygonalMesh& mesh) 
{
	ifstream file("./Cell2Ds.csv");
	
	if(file.fail())
	{
		cerr << "unable to open Cell2Ds.csv file" << endl;
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
	
	mesh.NumCell2Ds = listLines.size();
	
	if(mesh.NumCell2Ds == 0)
	{
		cerr << "there is no cell 2D" << endl;
		return false;
	}
	
	// salvo le informazioni nelle righe in mesh
	mesh.Cell2DsId.reserve(mesh.NumCell2Ds);
	mesh.Cell2DsVertices.reserve(mesh.NumCell2Ds);
	mesh.Cell2DsEdges.reserve(mesh.NumCell2Ds);
	
	for (const string& str : listLines)
	{
		string line = str;
		replace(line.begin(), line.end(), ';', ' ');
		istringstream converter(line);
		
		unsigned int id;
		unsigned int marker;
		
		converter >> id >> marker;
		
		mesh.Cell2DsId.push_back(id);
		
		// memorizzo i vertici
		unsigned int numVertices;
		converter >> numVertices;
		vector<unsigned int> vertices(numVertices);
		for(unsigned int i = 0; i < numVertices; i++)
			converter >> vertices[i];
		
		// test per verificare che il poligono identificato dai vertici 
		// non abbia area nulla
		if (!AreaOfPolygon(numVertices, vertices, mesh.Cell0DsCoordinates))
		{
			cerr << "at least one polygon has zero area" << endl;
			return false;
		}
		
		mesh.Cell2DsVertices.push_back(vertices);
		
		// memorizzo i bordi
		unsigned int numEdges;
		converter >> numEdges;
		vector<unsigned int> edges(numEdges);
		for(unsigned int i = 0; i < numEdges; i++)
			converter >> edges[i];
		mesh.Cell2DsEdges.push_back(edges);
		
		// memorizzo i marker
		if(marker != 0) 
		{
			const auto it = mesh.MarkerCell2Ds.find(marker);
			if(it == mesh.MarkerCell2Ds.end())
				mesh.MarkerCell2Ds.insert({marker, {id}});
			else
				it->second.push_back(id);
		}
	}
	
	return true;
}

}

void DisplayMap(const map<unsigned int, list<unsigned int>>& m) {
	cout << "Marker" << "\tIds" << endl;
	for (const auto i : m)
	{
		cout << i.first << "\t{ ";
		for (const auto& el : i.second)
			cout << el << " ";
		cout << "}" << endl;
	}
}

bool AreaOfPolygon(const unsigned int& numVertices,
						const vector<unsigned int>& verticesId,
						const MatrixXd& verticesCoord) 
{	
	double area = 0.0;
	for (unsigned int i = 0; i < numVertices-1; i++)
	{
		const double &x1 = verticesCoord(0, verticesId[i]);
		const double &y1 = verticesCoord(1, verticesId[i]);
		const double &x2 = verticesCoord(0, verticesId[i+1]);
		const double &y2 = verticesCoord(1, verticesId[i+1]);
		
		area += x1*y2 - x2*y1;
	}
	
	area += verticesCoord(0, verticesId[numVertices-1])*verticesCoord(1, verticesId[0]) - verticesCoord(0, verticesId[0])*verticesCoord(1, verticesId[numVertices-1]);
	
	area = 0.5*abs(area);
	
	if (area < 1e-16)
		return false;
	
	return true;
}
		
