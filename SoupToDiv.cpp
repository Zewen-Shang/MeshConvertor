#include "SoupToDiv.h"

void SoupToDiv::convert(string fileName,int divSize)
{
	ifstream soupFs(inputRoot + fileName + ".soup",ios::binary);
	vector<string> divPaths;
	for (int i = 0; i < 20; i++) {
		string id(1,'0'+i);
		string path = outputRoot + fileName + id + ".div";
		divPaths.push_back(path);
	}
	int currentPath = 0;

	ofstream divFs(divPaths[currentPath].c_str(),ios::binary);

	map<int, Vertex>vMap;
	int type;
	int tCnt = 0;
	while (soupFs.peek() != EOF) {
	    soupFs.read((char*)&type, sizeof(type));
	    switch (type)
	    {
	    case 0:
	        Vertex v;
	        soupFs.read((char*)&v, sizeof(v));
			divFs.write((char*)&type, sizeof(type));
			divFs.write((char*)&v, sizeof(v));
			if (vMap.count(v.id)) {
				assert(-1);
			}
			vMap[v.id] = v;
	        break;
	    case 1:
	        Tetra t;
			tCnt++;
	        soupFs.read((char*)&t, sizeof(t));
			divFs.write((char*)&type, sizeof(type));
			divFs.write((char*)&t, sizeof(t));
			if (tCnt % divSize == 0) {
				if (soupFs.peek() != EOF) {
					//cut
					type = 3;
					for (auto p : vMap) {
						divFs.write((char*)&type, sizeof(type));
						divFs.write((char*)&p.first, sizeof(p.first));
					}
					divFs.close();
					divFs.open(divPaths[++currentPath], ios::binary);
					for (auto p : vMap) {
						//先把顶点写进去
						type = 0;
						divFs.write((char*)&type, sizeof(type));
						divFs.write((char*)&p.second, sizeof(p.second));
						//再cut掉
						type = 3;
						divFs.write((char*)&type, sizeof(type));
						divFs.write((char*)&p.first, sizeof(p.first));
					}
				}
			}
			break;
	    case 2:
	        int id;
	        soupFs.read((char*)&id, sizeof(id));
			vMap.erase(id);
	        break;
	    default:
			assert(-1);
	        break;
	    }
	    
	}

}
