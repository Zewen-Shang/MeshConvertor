#pragma once
#include <string>
#include <iostream>
#include <fstream>
#define ll long long

using namespace std;

class Vertex {
public:
	int id;
	float pos[3], attr[3];
};

class Tetra {
public:
	int ids[4];
};

ifstream& operator>>(ifstream& in, Vertex& V);
ofstream& operator<<(ofstream& out, Vertex& v);
ifstream& operator>>(ifstream& in, Tetra& t);
ofstream& operator<<(ofstream& out, Tetra& t);
