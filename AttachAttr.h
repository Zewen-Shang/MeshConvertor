#pragma once
#include <iostream>
#include <istream>
#include <string>
#include <fstream>
#include <assert.h>
#define ll long long

using namespace std;


class AttachAttr
{
public:
	struct Vertex {
		int id;
		float pos[3];
	};
	struct Attr {
		int id;
		float attrs[3];
	};
	void attach(string fileName);
};

istream& operator>>(istream& in,AttachAttr::Vertex&);
ostream& operator<<(ostream& out,AttachAttr::Vertex& V);

istream& operator>>(istream& in,AttachAttr::Attr&);
ostream& operator<<(ostream& out,AttachAttr::Attr&);

