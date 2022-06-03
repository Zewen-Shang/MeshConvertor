#pragma once

#include <vtkNew.h>
#include <vtkUnstructuredGrid.h>
#include <vtkUnstructuredGridReader.h>
#include <vtkUnstructuredGridWriter.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkPointData.h>
#include <vtkFloatArray.h>
#include <vtkTetra.h>

#include <string>

using namespace std;

class VtkAddKey
{
public:
	string inputRoot = "./vtk/";
	string outputRoot = "./addkey/";
	void convert(string fileName,double weight[3]);
};

