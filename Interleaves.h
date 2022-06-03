#pragma once
#include <iostream>
#include <fstream>
#include <map>

#include "Prime.h"

using namespace std;

class Interleaves
{
public:
	struct VertexPlus {
		int id, key = -1;
		float pos[3], attr[3];
	};

	struct TetraPlus {
		int state;
		int vs[4], keys[4];
		int getMaxKey() {
			int ans = -1;
			for (int i = 0; i < 4; i++) {
				ans = max(ans, keys[i]);
			}
			return ans;
		}
	};

	string inputPath = "./sortTemp/", outputPath = "./soup/";
	void convert(string fileName);
};

