#include <iostream>
#include <Eigen/Eigen>

using namespace std; 
using namespace Eigen;

int main()
{
	const int i = 2;
	double d = 2;
	const int &ri = i;
	auto ai = ri;
	auto pi = &i;	// pi è un puntatore, non posso modificare i attraverso pi perché è un puntatore a una costante
	auto ad = 2.0;
	
	cout << sizeof(ai) << endl;
	cout << sizeof(ad) << endl;
	
	ai++; // posso modificare perché il const non è dedotto dal compilatore, ai è solo una variabile di tipo intero
	
	// i++;
	
	cout << "ri: " << ri << endl;
	cout << "ai: " << ai << endl;	// ai non è incrementato perché ha fatto una copia, ai non è una referenza
	cout << "*pi: " << *pi << endl;
	
	/// LIBRERIA STL 
	std::vector<int> v = {1,2,3};
	std::array<int, 3> a = {1,2,3};
	std::list<int> l = {1,2,3};
	
	for (unsigned int i = 0; i < v.size(); i++) 
	{
		int &j = v[i];
		j++;
		cout << j << " ";
	}
	cout << endl;
	
	for (int &j : v)
		cout << j << " ";
	
	cout << endl;
	
	for (auto it = v.begin(); it != v.end(); it++)
	{
		int j = *it;
		cout << j << " ";
	}
	cout << endl;
	
	/*
	v.insert(v.begin(), 5);
	v.erase(v.begin(), v.end()+1);
	v.push_back(5);
	
	for (int j: v)
		cout << j << " ";
	cout << endl;
	*/
	
	std::vector<int> w;
	for (unsigned int i = 0; i < 8; i++)
	{
		w.push_back(i);
		cout << "&w[0]: " << &w[0] << endl;
		cout << "w.size(): " << w.size() << endl;
		cout << "w.capacity(): " << w.capacity() << endl;
	}
	
	w.resize(10);
	cout << "w.size(): " << w.size() << endl;
	cout << "w.capacity(): " << w.capacity() << endl;
	
	w.resize(5);
	w.reserve(10);
	cout << "w.size(): " << w.size() << endl;
	cout << "w.capacity(): " << w.capacity() << endl;
	
	Eigen::VectorXd e = Eigen::VectorXd::Ones(8);
	e.resize(10);
	
	cout << e.transpose() << endl;
	
    return 0;
}

