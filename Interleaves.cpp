#include "Interleaves.h"

void Interleaves::convert(string fileName)
{
	ifstream vertexFs(inputPath + fileName + ".vkey",ios::binary);
	ifstream tetraFs(inputPath + fileName + ".tfinal",ios::binary);
	ofstream soupFs(outputPath + fileName + ".soup", ios::binary);
	map<int, int>key2cnt;
	VertexPlus vp; TetraPlus tp;
	while (tetraFs.peek() != EOF) {
		tetraFs.read((char*)&tp,sizeof(tp));
		for (int i = 0; i < 4; i++) {
			key2cnt[tp.keys[i]]++;
		}
	}
	tetraFs.close();
	tetraFs.open(inputPath + fileName + ".tfinal", ios::binary);

	while (tetraFs.peek() != EOF)
	{
		tetraFs.read((char*)&tp, sizeof(tp));
		while (vp.key < tp.getMaxKey())
		{
			vertexFs.read((char*)&vp, sizeof(vp));
			Vertex v;
			int type = 0;
			//标记位置，v为0
			v.id = vp.key;
			for (int i = 0; i < 3; i++) {
				v.pos[i] = vp.pos[i];
				v.attr[i] = vp.attr[i];
			}
			soupFs.write((char*)&type, sizeof(type));
			soupFs.write((char*)&v, sizeof(v));
		}
		int type = 1;
		soupFs.write((char*)&type, sizeof(type));
		Tetra t;
		for (int i = 0; i < 4; i++) {
			t.ids[i] = tp.keys[i];
		}
		soupFs.write((char*)&t, sizeof(t));

		for (int i = 0; i < 4; i++) {
			key2cnt[t.ids[i]]--;
			if (key2cnt[t.ids[i]] == 0) {
				key2cnt.erase(t.ids[i]);
				type = 2;
				soupFs.write((char*)&type, sizeof(type));
				soupFs.write((char*)&t.ids[i], sizeof(t.ids[i]));
			}
		}
	}


}
