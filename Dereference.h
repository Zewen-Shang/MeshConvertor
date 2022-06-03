#pragma once
#include <string>
#include <iostream>
#include <assert.h>
#include <chrono>

#include "ExternalSort.h"

#define SORT_PART_SIZE 20000

using namespace std;
using namespace std::chrono;
class Dereference
{
public:
    system_clock::duration timeCount;
    class VertexWithoutKey {
    public:
        int id;
        float pos[3]; float attr[3];
        float getKey() const {
            return pos[2];
        }
        bool operator<(const VertexWithoutKey& other) {
            return getKey() < other.getKey();
        }
    };

    class VertexWithKey {
    public:
        int id;
        int key;
        float pos[3]; float attr[3];
        VertexWithKey() {}
        VertexWithKey(VertexWithoutKey other) {
            id = other.id;
            for (int i = 0; i < 3; i++) {
                pos[i] = other.pos[i];
                attr[i] = other.attr[i];
            }
        }
        bool operator<(const VertexWithKey& other) {
            return id < other.id;
        }
    };

    class Tetra {
    public:
        int s = 0;
        int vs[4];
        int keys[4];
        int getMaxKey() const {
            int ans = -1;
            for (int i = 0; i < 4; i++) {
                assert(keys[i] != -1);
                ans = max(ans, keys[i]);
            }
            return ans;
        };
        bool operator<(const Tetra& other) {
            switch (s)
            {
            case 0:
                return vs[0] < other.vs[0];
                break;
            case 1:
                return vs[1] < other.vs[1];
                break;
            case 2:
                return vs[2] < other.vs[2];
                break;
            case 3:
                return vs[3] < other.vs[3];
                break;
            default:
                return getMaxKey() < other.getMaxKey();
            }
        }
    };

    string inputRoot = "./attach/", outputRoot = "./soup/", tmpRoot = "./sortTemp/";
    string fileName;
    void convert(string fileName);
    void sortVertexByPos();
    void addKeyForVertex();
    void sortVertexById();
    void addKeyforTetra();
    void sortTetraByvid(string inputSuf, string outputSuf);
    void refKey(int vIndex, string inputSuf, string outputSuf);
    void clean();
};


istream& operator>>(istream& in, Dereference::VertexWithoutKey& V);
ostream& operator<<(ostream& out, Dereference::VertexWithoutKey& V);

istream& operator>>(istream& in, Dereference::VertexWithKey& v);
ostream& operator<<(ostream& out, Dereference::VertexWithKey& v);

istream& operator>>(istream& in, Dereference::Tetra& t);
ostream& operator<<(ostream& out, Dereference::Tetra& t);