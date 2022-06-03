#pragma once

#include <vtkSmartPointer.h>
#include <vtkUnstructuredGrid.h>
#include <vtkTetra.h>
#include <vtkFloatArray.h>
#include <vtkPointData.h>
#include <vtkCellArray.h>
#include <vtkUnstructuredGrid.h>
#include <vtkUnstructuredGridWriter.h>

#include <string>
#include <iostream>
#include <fstream>

#define ll long long

using namespace std;




class AttachToVtk
{
public:
	struct Vertex {
		ll id;
		double pos[3], attr[3];
	};
	void convert(string fileName);
};

istream& operator>>(istream& in, AttachToVtk::Vertex& v);

