// AbaqusReader.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType);

#include <vtkSmartPointer.h>
#include <vtkConeSource.h>
#include <vtkSphereSource.h>
#include <vtkCubeSource.h>
#include <vtkActor.h>
#include <vtkPolyData.h>
#include <vtkImageData.h>
#include <vtkStructuredGrid.h>
#include <vtkUnstructuredGrid.h>
#include <vtkPolyDataMapper.h>
#include <vtkDataSetMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkNamedColors.h>
#include <vtkLine.h>
#include <vtkPolygon.h>
#include <vtkTriangle.h>
#include <vtkTetra.h>
#include <vtkPolyDataWriter.h>
#include <vtkUnsignedCharArray.h>
#include <vtkFloatArray.h>
#include <vtkPointData.h>
#include <vtkCellData.h>
#include <vtkGenericDataObjectReader.h>
#include <vtkUnstructuredGrid.h>
#include <vtkCamera.h>
#include <vtkUnstructuredGridWriter.h>

#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <map>
#include <chrono>

#include "AbaqusToDepart.h"
#include "AttachAttr.h"
#include "AttachToVtk.h"
#include "AttachToSoup.h"
#include "SoupToDiv.h"
#include "DivToVtk.h"
#include "VtkAddKey.h"
#include "Dereference.h"
#include "Interleaves.h"
#include "VtkToDiv.h"
#include "VtkToAttach.h"


#define N 500000
#define ll long long

using namespace std;

using namespace std::chrono;


//VtkAddKey vak;
//double weight[3] = { 1,1,3 };
//vak.convert("small",weight);

struct pa {
    int d; float f;
    bool operator<(const pa& other)const {
        return f < other.f;
    }
};

int main()
{

    //VtkToDiv v2d;
    //v2d.convert("box1m");

    //VtkToAttach v2a;
    //v2a.convert("box1m");

    //AbaqusToDepart a2d;
    //a2d.convertFile("big");
    
    //AttachAttr aa;
    //aa.attach("big");

    //system_clock::duration timeCount;
    //Dereference D;
    //D.convert("cylinder1m");
    //timeCount = D.timeCount;
    //
    //system_clock::time_point start, end;
    //start = system_clock::now();
    //Interleaves il;
    //il.convert("cylinder1m");
    //end = system_clock::now();
    //std::cout << "time:" << duration_cast<seconds>(timeCount).count() << std::endl;
    //timeCount += end - start;
    //std::cout << "time:" << duration_cast<microseconds>(timeCount).count() << std::endl;

    //AttachToSoup ats;
    //ats.convert("box1m");

    //SoupToDiv s2d;
    //s2d.convert("cylinder1m",240000);

    //ifstream ifs("./div/small1.div", ios::binary);
    //int type;
    //while (ifs.peek() != EOF)
    //{
    //    ifs.read((char*)&type, sizeof(type));
    //    switch (type)
    //    {
    //    case 0:
    //        cout << "v ";
    //        Vertex v;
    //        ifs.read((char*)&v, sizeof(v));
    //        cout << v.id << " ";
    //        for (int i = 0; i < 3; i++) {
    //            cout << v.pos[i] << " ";
    //        }
    //        for (int i = 0; i < 3; i++) {
    //            cout << v.attr[i] << " ";
    //        }
    //        cout << endl;
    //        break;
    //    case 1:
    //        cout << "t ";
    //        Tetra t;
    //        ifs.read((char*)&t, sizeof(t));
    //        for (int i = 0; i < 4; i++) {
    //            cout << t.ids[i] << " ";
    //        }
    //        cout << endl;
    //        break;
    //    case 3:
    //        cout << "c ";
    //        int id;
    //        ifs.read((char*)&id, sizeof(id));
    //        cout << id << endl;
    //        break;
    //    default:
    //        break;
    //    }
    //}


    DivToVtk d2v;
    d2v.convert("cylinder1m0");
    d2v.convert("cylinder1m1");
    d2v.convert("cylinder1m2");
    d2v.convert("cylinder1m3");


    return 0;
}


