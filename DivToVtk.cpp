#include "DivToVtk.h"

void DivToVtk::convert(string fileName)
{
	string vtkPath = outputRoot + fileName + ".vtk";
	ifstream divFs(inputRoot + fileName + ".div",ios::binary);

	vector<Vertex>vertexArr;
	vector<Tetra>tetraArr;
	vector<int>cutArr;
	int type;
	Vertex v; Tetra t;
	int maxId = -1;
	while (divFs.peek() != EOF)
	{
		divFs.read((char*)&type, sizeof(type));
		switch (type)
		{
		case 0:
			divFs.read((char*)&v, sizeof(v));
			vertexArr.push_back(v);
			maxId = max(maxId, v.id);
			break;
		case 1:
			divFs.read((char*)&t, sizeof(t));
			tetraArr.push_back(t);
			break;
		case 3:
			int id;
			divFs.read((char*)&id, sizeof(id));
			cutArr.push_back(id);
		default:
			assert(-1);
			break;
		}
	}

	vtkNew<vtkUnstructuredGrid>unGrid;
	vtkNew<vtkFloatArray>attr,cut;
	attr->SetName("attr");
	attr->SetNumberOfComponents(3);
	attr->SetNumberOfTuples(maxId + 1);
	cut->SetName("cut");
	cut->SetNumberOfComponents(1);
	cut->SetNumberOfTuples(maxId + 1);
	vtkNew<vtkPoints> points;
	vtkNew<vtkCellArray> cellArray;
	points->SetNumberOfPoints(maxId + 1);
	for (auto v : vertexArr) {
		int id = v.id;
		points->SetPoint(id, v.pos);
		attr->SetTuple(id, v.attr);
		cut->SetTuple1(v.id, 0);
	}
	for (auto id : cutArr) {
		cut->SetTuple1(id, 1);
	}
	unGrid->SetPoints(points);
	unGrid->GetPointData()->AddArray(attr);
	unGrid->GetPointData()->AddArray(cut);
	for (auto t : tetraArr) {
		vtkNew<vtkTetra>tetra;
		for (int i = 0; i < 4; i++) {
			tetra->GetPointIds()->SetId(i, t.ids[i]);
		}
		cellArray->InsertNextCell(tetra);
	}
	unGrid->SetCells(10, cellArray);
	vtkNew<vtkUnstructuredGridWriter>writer;
	writer->SetFileTypeToBinary();
	writer->SetFileName(vtkPath.c_str());
	writer->SetInputData(unGrid);
	writer->Write();
}
