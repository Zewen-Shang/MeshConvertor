#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <assert.h>
#include "Prime.h"

#define ll long long

using namespace std;


class SoupToDiv
{
public:
	string inputRoot = "./soup/", outputRoot = "./div/";
	void convert(string fileName,int divSize);
};


