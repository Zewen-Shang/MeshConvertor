#include "VtkToDiv.h"

void VtkToDiv::convert(string fileName)
{
	ofstream outputFs(outputRoot + fileName + ".div",ios::binary);
	vtkNew<vtkUnstructuredGridReader>reader;
	reader->SetFileName((inputRoot + fileName + ".vtk").c_str());
	reader->Update();
	vtkUnstructuredGrid* unGrid;
	unGrid = reader->GetOutput();
	for (int i = 0; i < unGrid->GetNumberOfPoints(); i++) {
		double* pos, *attr;
		pos = unGrid->GetPoint(i);
		attr = unGrid->GetPointData()->GetArray("U")->GetTuple(i);
		Vertex v;
		v.id = i;
		for (int j = 0; j < 3; j++) {
			v.pos[j] = pos[j];
			v.attr[j] = attr[j];
		}
		int type = 0;
		outputFs.write((char*)&type, sizeof(type));
		outputFs.write((char*)&v, sizeof(v));
	}

	for (int i = 0; i < unGrid->GetNumberOfCells(); i++) {
		int type = 1;
		outputFs.write((char*)&type, sizeof(type));
		vtkIdList* ids;
		ids = unGrid->GetCell(i)->GetPointIds();
		Tetra t;
		for (int j = 0; j < 4; j++) {
			t.ids[j] = ids->GetId(j);
		}
		outputFs.write((char*)&t, sizeof(t));
	}
	outputFs.close();
}
