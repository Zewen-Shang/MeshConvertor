#include "AbaqusToDepart.h"

string deleteAllMark(string& s, char x)
{
	string ans;
	for (char c : s) {
		if (c != x)
			ans.append(1, c);
	}
	return ans;
}

void AbaqusToDepart::convertFile(string fileName)
{
	map<int, int>M;
	string inputRoot = "./abaqus/";
	string outputRoot = "./depart/";
	string inpPath = inputRoot + fileName + ".inp";
	string datPath = inputRoot + fileName + ".dat";
	string vertPath = outputRoot + fileName + ".vert";
	string elePath = outputRoot + fileName + ".ele";
	string attrPath = outputRoot + fileName + ".attr";
	ifstream inpInFs,datInFs;
	ofstream vertOutFs, eleOutFs,attrOutFs;
	inpInFs.open(inpPath);
	datInFs.open(datPath);
	vertOutFs.open(vertPath, ios::binary);
	eleOutFs.open(elePath, ios::binary);
	attrOutFs.open(attrPath, ios::binary);
	string line;
	//跳过开头
	while (getline(inpInFs,line))
	{
		if (line == "*NODE") {
			break;
		}
	}
	int cnt = 0;
	while (getline(inpInFs, line))
	{
		if (line[0] == '*')break;
		line = deleteAllMark(line, ' ');
		int id;
		float pos[3];
		sscanf_s(line.c_str(), "%d,%f,%f,%f", &id, pos, pos+1, pos+2);
		M[id] = cnt++;
		char buffer[16];
		*(int*)buffer = cnt - 1;
		*(float*)(buffer+4) = pos[0];
		*(float*)(buffer + 8) = pos[1];
		*(float*)(buffer + 12) = pos[2];
		vertOutFs.write(buffer, 16);
		//vertOutFs << cnt-1 << " " << pos[0] << " " << pos[1] << " " << pos[2] << endl;
	}
	cout << "Read vertex done.\n";
	//跳过中间信息
	do
	{
		if (line.substr(0,18) == "*ELEMENT,TYPE=C3D4")break;
	} while (getline(inpInFs, line));
	cnt = 0;
	while (getline(inpInFs, line))
	{
		if (line[0] == '*')break;
		line = deleteAllMark(line, ' ');
		int id[5];
		sscanf_s(line.c_str(), "%d,%d,%d,%d,%d", id, id + 1, id + 2, id + 3, id + 4);
		char buffer[16];
		for (int i = 1; i <= 4; i++) {
			*(int*)(buffer+(i-1)*4) = M[id[i]];
		}
		eleOutFs.write(buffer, 16);
		//eleOutFs << M[id[1]] << " " << M[id[2]] << " " << M[id[3]] << " " << M[id[4]] << endl;
		cnt++;
		if (cnt % 10000 == 0) {
			cout << "Read " << cnt << " elements\n";
		}
	}
	cout << "Read element done.\n" << cnt;

	while (getline(datInFs,line))
	{
		if (line == "   THE FOLLOWING TABLE IS PRINTED FOR ALL NODES") {
			break;
		}
	}
	for (int i = 0; i < 4; i++) {
		getline(datInFs, line);
	}
	cnt = 0;
	while (getline(datInFs, line))
	{
		if (line == "\n") {
			break;
		}
		int id;
		float attr[3];
		sscanf_s(line.c_str(), "%d %f %f %f", &id, attr, attr + 1, attr + 2);
		char buffer[16];
		*(int*)buffer = M[id];
		for (int i = 0; i < 3; i++) {
			*(float*)(buffer + 4 * (i + 1)) = attr[i];
		}
		//attrOutFs << M[id] << " " << attr[0] << " " << attr[1] << " " << attr[2] << endl;
		attrOutFs.write(buffer, 16);
		cnt++;
		if (cnt % 10000 == 0)
			cout << "Read " << cnt << "attrs.\n";
	}
}
