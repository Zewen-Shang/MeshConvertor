#pragma once

#include <vtkNew.h>
#include <vtkUnstructuredGrid.h>
#include <vtkUnstructuredGridWriter.h>
#include <vtkUnstructuredGridReader.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkPointData.h>
#include <vtkFloatArray.h>
#include <vtkTetra.h>

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class VtkToAttach
{
public:
	string inputRoot = "./vtk/", outputRoot = "./attach/";
	struct Vertex {
		int id;
		float pos[6];
	};
	struct Tetra {
		int ids[4];
	};
	void convert(string fileName);
};

