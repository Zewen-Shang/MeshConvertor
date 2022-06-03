#include "AttachToSoup.h"

istream& operator>>(istream& in, AttachToSoup::Vertex& v) {
	in >> v.id >> v.pos[0] >> v.pos[1] >> v.pos[2] >> v.attr[0] >> v.attr[1] >> v.attr[2];
	return in;
};

ostream& operator<<(ostream& out, AttachToSoup::Vertex& v)
{
	out << "v " << v.rank << " " << v.pos[0] << " " << v.pos[1] << " " << v.pos[2] << " " << v.attr[0] << " " << v.attr[1] << " " << v.attr[2];
	return out;
}

istream& operator>>(istream& in, AttachToSoup::Tetra& t)
{
	in >> t.ids[0] >> t.ids[1] >> t.ids[2] >> t.ids[3];
	return in;
}

ostream& operator<<(ostream& out, AttachToSoup::Tetra& t)
{
	out << "t ";
	for (int i = 0; i < 4; i++) {
		out << t.ranks[i] << " ";
	}
	return out;
}


void AttachToSoup::convert(string fileName)
{
	string inputRoot = "./attach/";
	string outputRoot = "./soup/";

	string attachPath = inputRoot + fileName + ".attach";
	string elePath = inputRoot + fileName + ".ele";
	string soupPath = outputRoot + fileName + ".soup";

	ifstream attachFs(attachPath.c_str()),eleFs(elePath.c_str());
	ofstream soupFs(soupPath.c_str());
	vector<Vertex>vs,vc;
	Vertex v;
	while (attachFs >> v) {
		vs.push_back(v);
		vc.push_back(v);
	}
	sort(vc.begin(), vc.end());
	for (int i = 0; i < vc.size(); i++) {
		vc[i].rank = i;
		vs[vc[i].id].rank = i;
	}
	vector<Tetra>ts;
	Tetra t;
	while (eleFs >> t)
	{
		for (int i = 0; i < 4; i++) {
			t.ranks[i] = vs[t.ids[i]].rank;
			vc[t.ranks[i]].cnt++;
		}
		ts.push_back(t);
	}
	sort(ts.begin(), ts.end());
	map<ll, int>M;
	ll vCnt = 0;
	for (auto t : ts) {
		while (!M[t.getKey()]) {
			M[vc[vCnt].rank] = vc[vCnt].cnt;
			soupFs << vc[vCnt] << endl;
			vCnt++;
		}
		soupFs << t << endl;
		for (int i = 0; i < 4; i++) {
			M[t.ranks[i]]--;
			if (M[t.ranks[i]] == 0) {
				M.erase(t.ranks[i]);
				soupFs << "d " << t.ranks[i] << endl;
			}
		}
	}
	soupFs.close();
}
