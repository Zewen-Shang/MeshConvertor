#include "VtkToAttach.h"

void VtkToAttach::convert(string fileName)
{
	ofstream eleFs(outputRoot + fileName + ".ele", ios::binary),attachFs(outputRoot + fileName + ".attach", ios::binary);
	vtkNew<vtkUnstructuredGridReader>reader;
	reader->SetFileName((inputRoot + fileName + ".vtk").c_str());
	reader->Update();
	vtkUnstructuredGrid* unGrid;
	unGrid = reader->GetOutput();
	for (int i = 0; i < unGrid->GetNumberOfPoints(); i++) {
		double* pos, * attr;
		pos = unGrid->GetPoint(i);
		attr = unGrid->GetPointData()->GetArray("U")->GetTuple(i);
		Vertex v;
		v.id = i;
		for (int j = 0; j < 3; j++) {
			v.pos[j] = pos[j];
			v.pos[j+3] = attr[j];
		}
		int type = 0;
		attachFs.write((char*)&v, sizeof(v));
	}

	for (int i = 0; i < unGrid->GetNumberOfCells(); i++) {
		int type = 1;
		vtkIdList* ids;
		ids = unGrid->GetCell(i)->GetPointIds();
		Tetra t;
		for (int j = 0; j < 4; j++) {
			t.ids[j] = ids->GetId(j);
		}
		eleFs.write((char*)&t, sizeof(t));
	}
	attachFs.close();
	eleFs.close();
}
