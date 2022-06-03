#include "AttachToVtk.h"

istream& operator>>(istream& in, AttachToVtk::Vertex& v) {
	in >> v.id >> v.pos[0] >> v.pos[1] >> v.pos[2] >> v.attr[0] >> v.attr[1] >> v.attr[2];
	return in;
}

void AttachToVtk::convert(string fileName)
{
	ll cnt = 0;
	string inputRoot = "./attach/";
	string outputRoot = "./vtk/";
	string attachPath = inputRoot + fileName + ".attach";
	string elePath = inputRoot + fileName + ".ele";
	string vtkPath = outputRoot + fileName + ".vtk";

	ifstream attachFs(attachPath.c_str()), eleFs(elePath.c_str());
	vtkNew<vtkUnstructuredGrid>unGrid;
	vtkNew<vtkPoints>points;
	vtkNew<vtkCellArray>cellArray;
	vtkNew<vtkFloatArray>attrs[3];
	string attrNames[3] = { "U1","U2","U3" };
	for (int i = 0; i < 3; i++) {
		attrs[i]->SetName(attrNames[i].c_str());
		attrs[i]->SetNumberOfComponents(1);
	}
	Vertex v;
	while (attachFs >> v) {
		points->InsertNextPoint(v.pos);
		for (int i = 0; i < 3; i++) {
			attrs[i]->InsertNextTuple1(v.pos[i]);
		}
	}
	unGrid->SetPoints(points);
	for (int i = 0; i < 3; i++) {
		unGrid->GetPointData()->AddArray(attrs[i]);
	}
	ll ids[4];
	cnt = 0;
	while (eleFs >> ids[0]>>ids[1]>>ids[2]>>ids[3])
	{
		cnt++;
		if (cnt % 10000 == 0) {
			cout << "AttachToVtk:Read " << cnt << "tetras.\n";
		}
		vtkNew<vtkTetra>tetra;
		for (int i = 0; i < 4; i++) {
			tetra->GetPointIds()->SetId(i, ids[i]);
		}
		cellArray->InsertNextCell(tetra);
	}
	unGrid->SetCells(10, cellArray);
	vtkNew<vtkUnstructuredGridWriter> writer;
    writer->SetFileName(vtkPath.c_str());
    writer->SetInputData(unGrid);
    writer->Write();
}
