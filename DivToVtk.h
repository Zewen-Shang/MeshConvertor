#pragma once
#include <string>
#include <iostream>
#include <fstream>

#include <vtkNew.h>
#include <vtkUnstructuredGrid.h>
#include <vtkUnstructuredGridWriter.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkPointData.h>
#include <vtkFloatArray.h>
#include <vtkTetra.h>

#include "Prime.h"
#include <vector>
#include <assert.h>

using namespace std;

class DivToVtk
{
public:
	string inputRoot = "./div/";
	string outputRoot = "./vtk/";
	void convert(string fileName);

};
