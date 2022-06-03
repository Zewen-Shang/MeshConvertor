#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;


#define PART_N 100

template <class item>
class ExternalSort
{
public:

	struct HeapNode {
		ifstream fs;
		item value;
	};
	struct Heap {
		HeapNode* arr[PART_N];
		int size = 0;
		void up(int pos) {
			int f = pos / 2;
			while (f != 0 && arr[pos]->value < arr[f]->value) {
				swap(arr[f], arr[pos]);
				pos = f;
				f = pos / 2;
			}
		}

		void down(int pos) {
			int son = pos * 2;
			while (son <= size) {
				if (son + 1 <= size && arr[son + 1]->value < arr[son]->value)
					son++;
				if (arr[son]->value < arr[pos]->value) {
					swap(arr[son], arr[pos]);
					pos = son;
					son = pos * 2;
				}
				else {
					break;
				}
			}
		}

		void insert(HeapNode* hn) {
			size++;
			arr[size] = hn;
			hn->fs.read((char*)&hn->value, sizeof(item));
			//hn->fs >> hn->value;
			up(size);
		}

		item getFirst() {
			item ans = arr[1]->value;
			//if(arr[1]->fs >> arr[1]->value){
			if(arr[1]->fs.peek() != EOF){
				arr[1]->fs.read((char*)&(arr[1]->value), sizeof(item));
				down(1);
			}
			else {
				arr[1] = arr[size];
				size--;
				down(1);
			}
			return ans;
		}
	};
	ExternalSort() {};
	ExternalSort(string fileName, string inputRoot, string outputRoot, string inputSuf, string outputSuf,int partSize);
	string fileName;
	string inputRoot,outputRoot;
	string inputSuf, outputSuf;
	int partCnt = 0;
	int partSize;
	void divideInPart();
	void sortParts();
	void merge();
	void clean();
};

template<class item>
ExternalSort<item>::ExternalSort(string fileName, string inputRoot, string outputRoot, string inputSuf, string outputSuf, int partSize)
	:fileName(fileName), inputRoot(inputRoot), outputRoot(outputRoot), inputSuf(inputSuf), outputSuf(outputSuf), partSize(partSize)
{

}


template<class item>
void ExternalSort<item>::divideInPart()
{
	string outputPaths[PART_N];
	for (int i = 0; i < PART_N; i++) {
		outputPaths[i] = outputRoot + fileName + to_string(i) + ".part";
	}
	string inputPath = inputRoot + fileName + inputSuf;
	ofstream outputFs(outputPaths[partCnt].c_str(),ios::binary);
	ifstream inputFs(inputPath.c_str(),ios::binary);
	int cnt = 0;
	item t;
	//while (inputFs >> t)
	while (inputFs.peek() != EOF)
	{
		inputFs.read((char*)&t, sizeof(t));
		cnt++;
		outputFs.write((char*)&t, sizeof(t));
		if (cnt % partSize == 0) {
			outputFs.close();
			//整除时会出bug
			if (inputFs.peek() != EOF) {
				partCnt++;
				outputFs.open(outputPaths[partCnt], ios::binary);
			}
		}
	}
	partCnt++;
}

template<class item>
void ExternalSort<item>::sortParts()
{
	
	for (int i = 0; i < partCnt; i++) {
		ifstream inputFs(outputRoot + fileName + to_string(i) + ".part",ios::binary);
		vector<item>arr;
		arr.reserve(partSize+10);
		item v;
		while (inputFs.peek() != EOF)
		{
			inputFs.read((char*)&v, sizeof(v));
			arr.push_back(v);
		}
		sort(arr.begin(), arr.end());
		string sortedVPath = outputRoot + fileName + to_string(i) + ".sorted";
		ofstream sortedVFs(sortedVPath.c_str(),ios::binary);
		for (auto v : arr) {
			sortedVFs.write((char*)&v, sizeof(v));
		};
		sortedVFs.close();
	}
}

template<class item>
void ExternalSort<item>::merge()
{
	Heap H;
	HeapNode *nodes = new HeapNode[partCnt];
	string mergePath = outputRoot + fileName + outputSuf;
	ofstream mergeFs(mergePath.c_str(),ios::binary);
	for (int i = 0; i < partCnt; i++) {
		nodes[i].fs.open(outputRoot + fileName + to_string(i) + ".sorted",ios::binary);
		H.insert(nodes + i);
	}
	while (H.size != 0) {
		item t = H.getFirst();
		mergeFs.write((char*)&t, sizeof(t));;
	}
	delete[] nodes;
}

template<class item>
void ExternalSort<item>::clean()
{
	for (int i = 0; i < partCnt; i++) {
		string path1 = outputRoot + fileName + to_string(i) + ".part";
		string path2 = outputRoot + fileName + to_string(i) + ".sorted";
		remove(path1.c_str());
		remove(path2.c_str());
	}
}
