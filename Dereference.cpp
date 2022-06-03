#include "Dereference.h"

#define ADD_TIME(X) \
start = system_clock::now(); \
X ;\
end = system_clock::now(); \
timeCount += end - start

istream& operator>>(istream& in, Dereference::VertexWithoutKey& V) {
    in >> V.id >> V.pos[0] >> V.pos[1] >> V.pos[2] >> V.attr[0] >> V.attr[1] >> V.attr[2];
    return in;
}

ostream& operator<<(ostream& out, Dereference::VertexWithoutKey& V) {
    out << V.id << " " << V.pos[0] << " " << V.pos[1] << " " << V.pos[2] << " " << V.attr[0] << " " << V.attr[1] << " " << V.attr[2];
    return out;
}

istream& operator>>(istream& in, Dereference::VertexWithKey& v)
{
    in >> v.id >> v.key;
    in >> v.pos[0] >> v.pos[1] >> v.pos[2];
    in >> v.attr[0] >> v.attr[1] >> v.attr[2];
    return in;
}

ostream& operator<<(ostream& out, Dereference::VertexWithKey& v)
{
    out << v.id << " " << v.key << " ";
    out << v.pos[0] << " " << v.pos[1] << " " << v.pos[2] << " ";
    out << v.attr[0] << " " << v.attr[1] << " " << v.attr[2] << " ";
    return out;
}

istream& operator>>(istream& in, Dereference::Tetra& t)
{
    in >> t.s;
    for (int i = 0; i < 4; i++) {
        in >> t.vs[i] >> t.keys[i];
    }
    return in;
}

ostream& operator<<(ostream& out, Dereference::Tetra& t)
{
    out << t.s << " ";
    for (int i = 0; i < 4; i++) {
        out << t.vs[i] << " " << t.keys[i] << " ";
    }
    return out;
}

void Dereference::convert(string fileName)
{
    //system_clock start, end;
    this->timeCount.zero();
    this->fileName = fileName;
    system_clock::time_point start, end;
    
    ADD_TIME(sortVertexByPos());
    cout << "Vertex Sort by Pos done.\n";
    addKeyForVertex();
    cout << "Add key for vertex done.\n";
    ADD_TIME(sortVertexById());
    cout << "Vertex Sort by Id done.\n";
    addKeyforTetra();
    ADD_TIME(sortTetraByvid(".tkey",".tsort0"));
    refKey(0, ".tsort0", ".tref0");
    cout << "0 done\n";
    ADD_TIME(sortTetraByvid(".tref0", ".tsort1"));
    refKey(1, ".tsort1", ".tref1");
    cout << "1 done\n";
    ADD_TIME(sortTetraByvid(".tref1", ".tsort2"));
    refKey(2, ".tsort2", ".tref2");
    cout << "2 done\n";
    ADD_TIME(sortTetraByvid(".tref2", ".tsort3"));
    refKey(3, ".tsort3", ".tref3");
    cout << "3 done\n";
    ADD_TIME(sortTetraByvid(".tref3", ".tfinal"));
    cout << "final sort done\n";
    clean();
}

void Dereference::sortVertexByPos()
{
    ExternalSort<Dereference::VertexWithoutKey> E(fileName, inputRoot, "./sortTemp/", ".attach", ".vposSort",SORT_PART_SIZE);
    E.divideInPart();
    E.sortParts();
    E.merge();
    E.clean();
}

void Dereference::addKeyForVertex() {
    ifstream inputFs((tmpRoot + fileName + ".vposSort").c_str(),ios::binary);
    ofstream outputFs(tmpRoot + fileName + ".vkey",ios::binary);
    VertexWithoutKey vno;
    VertexWithKey vkey;
    int cnt = 0;
    while (inputFs.peek() != EOF) {
        inputFs.read((char*)&vno, sizeof(vno));
        vkey = VertexWithKey(vno);
        vkey.key = cnt++;
        outputFs.write((char*)&vkey, sizeof(vkey));
    }
}

void Dereference::sortVertexById()
{
    ExternalSort<Dereference::VertexWithKey> E(fileName, tmpRoot,tmpRoot, ".vkey", ".vidSort", SORT_PART_SIZE);
    E.divideInPart();
    E.sortParts();
    E.merge();
    E.clean();
}

void Dereference::addKeyforTetra()
{
    ifstream inputFs(inputRoot + fileName + ".ele",ios::binary);
    ofstream outputFs(tmpRoot + fileName + ".tkey",ios::binary);
    int vs[4];
    while (inputFs.peek()!=EOF) {
        inputFs.read((char*)vs, 16);
        Tetra t;
        for (int i = 0; i < 4; i++) {
            t.vs[i] = vs[i];
            t.keys[i] = -1;
        }
        outputFs.write((char*)&t, sizeof(t));
    }
    inputFs.close();
    outputFs.close();
}

void Dereference::sortTetraByvid(string inputSuf,string outputSuf)
{
    ExternalSort<Dereference::Tetra> E(fileName, tmpRoot, tmpRoot, inputSuf, outputSuf, SORT_PART_SIZE);
    E.divideInPart();
    E.sortParts();
    E.merge();
    E.clean();
}

void Dereference::refKey(int vIndex,string inputSuf,string outputSuf)
{
    ifstream tetraFs(tmpRoot + fileName + inputSuf,ios::binary),vertexFs(tmpRoot+fileName + ".vidSort",ios::binary);
    ofstream outputFs(tmpRoot + fileName + outputSuf,ios::binary);
    Tetra t; VertexWithKey v;
    vertexFs.read((char*)&v,sizeof(v));
    while (tetraFs.peek() != EOF)
    {
        tetraFs.read((char*)&t, sizeof(t));
        if (v.id == 1443) {
            int i = 0;
        }
        while (v.id != t.vs[vIndex]) {
            vertexFs.read((char*)&v, sizeof(v));
        }
        t.keys[vIndex] = v.key;
        t.s++;
        outputFs.write((char*)&t,sizeof(t));
    }
    tetraFs.close();
    vertexFs.close();
    outputFs.close();
}

void Dereference::clean()
{
    for (int i = 0; i < 4; i++) {
        string path0 = tmpRoot + fileName + ".tsort" + to_string(i);
        string path1 = tmpRoot + fileName + ".tref" + to_string(i);
        remove(path0.c_str());
        remove(path1.c_str());
    }
}
