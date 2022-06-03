#include "VtkAddKey.h"

void VtkAddKey::convert(string fileName,double weight[3])
{
	string inputPath = inputRoot + fileName + ".vtk";
	string outputPath = outputRoot + fileName + ".vtk";

	vtkNew<vtkUnstructuredGridReader>reader;
	reader->SetFileName(inputPath.c_str());
	reader->Update();
	vtkUnstructuredGrid *unGrid = reader->GetOutput();
	vtkNew<vtkFloatArray>floatArr;
	floatArr->SetName("key");
	floatArr->SetNumberOfComponents(4);
	int vCnt = unGrid->GetNumberOfPoints();
	floatArr->SetNumberOfTuples(unGrid->GetNumberOfPoints());
	for (int i = 0; i < vCnt; i++) {
		double* pos = unGrid->GetPoint(i);
		floatArr->SetTuple4(i, pos[0], pos[1], pos[2], pos[0] * weight[0] + pos[1] * weight[1] + pos[2] * weight[2]);
	}
	unGrid->GetPointData()->AddArray(floatArr);
	vtkNew<vtkUnstructuredGridWriter>writer;
	writer->SetFileName(outputPath.c_str());
	writer->SetInputData(unGrid);
	writer->Write();
	return;
}
