#include "AttachAttr.h"

istream& operator>>(istream& in, AttachAttr::Vertex& v) {
	in >> v.id >> v.pos[0] >> v.pos[1] >> v.pos[2];
	return in;
}

ostream& operator<<(ostream& out, AttachAttr::Vertex& V) {
	out << V.id << " " << V.pos[0] << " " << V.pos[1] << " " << V.pos[2] << " ";
	return out;
};

istream& operator>>(istream& in, AttachAttr::Attr& a) {
	in >> a.id >> a.attrs[0] >> a.attrs[1] >> a.attrs[2];
	return in;
}

ostream& operator<<(ostream& out, AttachAttr::Attr& A) {
	out << A.attrs[0] << " " << A.attrs[1] << " " << A.attrs[2] << " ";
	return out;
}

void AttachAttr::attach(string fileName)
{
	string inputRoot = "./depart/";
	string outputRoot = "./attach/";
	string vertPath = inputRoot + fileName + ".vert";
	string attrPath = inputRoot + fileName + ".attr";
	string elePath = inputRoot + fileName + ".ele";
	
	string outPath = outputRoot + fileName + ".attach";
	string eleOutPath = outputRoot + fileName + ".ele";

	ifstream vertFs(vertPath.c_str(),ios::binary), attrFs(attrPath.c_str(),ios::binary),eleFs(elePath.c_str(),ios::binary);
	ofstream outFs(outPath.c_str(),ios::binary),eleOutFs(eleOutPath.c_str(),ios::binary);
	Vertex v;
	Attr a;
	attrFs.read((char*)&a, sizeof(a));
	//¿ÉÄÜ³ö´í
	while (vertFs.peek() != EOF){
		vertFs.read((char*)&v, sizeof(v));
		char buffer[28];
		memset(buffer, 0, sizeof(buffer));
		*(Vertex*)buffer = v;
		if (a.id == -1 || v.id == a.id) {
			for (int i = 0; i < 3; i++) {
				*(float*)(buffer + 4 * (i + 4)) = a.attrs[i];
			}
		}
		else {
		}
		outFs.write(buffer, 28);
		if (attrFs.peek() == EOF) {
			a.id = -1;
			a.attrs[0] = a.attrs[1] = a.attrs[2] = 0;
		}
		else if(a.id == v.id){
			attrFs.read((char*)&a, sizeof(a));
		}
		else {
			assert(-1);
		}
	}
	outFs.close();

	eleOutFs << eleFs.rdbuf();
	eleOutFs.close();
}
