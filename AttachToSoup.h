#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>

#define ll long long

using namespace std;

class AttachToSoup
{
public:
	struct Vertex {
	public:
		ll id;
		double pos[3];
		double attr[3];
		ll rank;
		ll cnt = 0;
		double getKey()const {
			return pos[2];
		}
		bool operator<(const Vertex& other) {
			return getKey() < other.getKey();
		}
	};

	struct Tetra {
		ll ids[4];
		ll ranks[4];
		ll getKey()const{
			ll ans = -1;
			for (int i = 0; i < 4; i++) {
				ans = max(ans,ranks[i]);
			}
			return ans;
		}
		bool operator<(const Tetra& other) {
			return getKey() < other.getKey();
		}
	};

	void convert(string fileName);

};

istream& operator>>(istream& in, AttachToSoup::Vertex &v);
ostream& operator<<(ostream& out, AttachToSoup::Vertex& v);
istream& operator>>(istream& in, AttachToSoup::Tetra& t);
ostream& operator<<(ostream& out, AttachToSoup::Tetra& t);
