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

#include <iostream>
#include <string>
#include "Prime.h"

using namespace std;

class VtkToDiv
{
public:
	string inputRoot = "./vtk/", outputRoot = "./div/";
	void convert(string fileName);
};

