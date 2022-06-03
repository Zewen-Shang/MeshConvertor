#include "Prime.h"

ifstream& operator>>(ifstream& in, Vertex& V)
{
	in >> V.id >> V.pos[0] >> V.pos[1] >> V.pos[2] >> V.attr[0] >> V.attr[1] >> V.attr[2];
	return in;
}

ofstream& operator<<(ofstream& out, Vertex& v)
{
	out << "v " << v.id << " " << v.pos[0] << " " << v.pos[1] << " " << v.pos[2] << " " << v.attr[0] << " " << v.attr[1] << " " << v.attr[2];
	return out;
}

ifstream& operator>>(ifstream& in, Tetra& t)
{
	in >> t.ids[0] >> t.ids[1] >> t.ids[2] >> t.ids[3];
	return in;
}

ofstream& operator<<(ofstream& out, Tetra& t)
{
	out << "t " << t.ids[0] << " " << t.ids[1] << " " << t.ids[2] << " " << t.ids[3];
	return out;
}
